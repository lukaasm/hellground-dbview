/*
 * Copyright (C) 2008 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 *
 * Contributed by: Paul Harrison
 */
#include <Wt/Dbo/backend/MySQL.h>
#include <Wt/Dbo/Exception>

#include <boost/lexical_cast.hpp>
#include <iostream>
#include <vector>
#include <sstream>

#include <boost/date_time/posix_time/posix_time.hpp>


#ifdef WIN32
#define snprintf _snprintf
#endif

#define BYTEAOID 17

//#define DEBUG(x) x
#define DEBUG(x)

namespace Wt {
namespace Dbo {
namespace backend {

class MySQLException : public Exception
{
  public:
  MySQLException(const std::string& msg)
  : Exception(msg)
  { }
};
/*!
 * \brief MySQL prepared statement.
 * @todo the bind statements leak a little memory each time they are reused for the same statment
 * @todo should the getResult requests all be type checked...
 */
class MySQLStatement : public SqlStatement
{
  public:
    MySQLStatement(MySQL& conn, const std::string& sql)
    : conn_(conn),
      sql_(sql)
    {
      lastId_ = -1;
      row_ = affectedRows_ = 0;
      result_ = 0;

      sql_ = boost::algorithm::replace_all_copy(sql_, "\"", "");

      stmt_ =  mysql_stmt_init(conn_.connection());
      mysql_stmt_attr_set(stmt_, STMT_ATTR_UPDATE_MAX_LENGTH, &mysqltrue_);
      if(mysql_stmt_prepare(stmt_, sql_.c_str(), sql_.length()) != 0) {
        throw  MySQLException(std::string("error creating prepared statement ")+ mysql_stmt_error(stmt_) + std::string(" | sql: ") + sql_);
      }
      if(mysql_stmt_param_count(stmt_)> 0)
      {
          in_pars_ = new MYSQL_BIND[mysql_stmt_param_count(stmt_)];
          memset(in_pars_, 0, sizeof(struct st_mysql_bind)*mysql_stmt_param_count(stmt_));
      }
      else{
        in_pars_ = 0;
      }
      out_pars_ = 0;
//      snprintf(name_, 64, "SQL%p%08X", this, rand());


      DEBUG(std::cerr <<  " new SQLStatement for: " << sql_ << std::endl);

      state_ = Done;
    }

    virtual ~MySQLStatement()
    {
      std::cerr << "closing prepared stmt " << sql_ << std::endl;
      for(int i = 0;   i < mysql_stmt_param_count(stmt_) ; ++i) {
        switch (in_pars_[i].buffer_type) {
           case MYSQL_TYPE_STRING:
           case MYSQL_TYPE_BLOB:
           case MYSQL_TYPE_VAR_STRING:
           if(in_pars_[i].buffer != 0 ) free(in_pars_[i].buffer);

           if(in_pars_[i].length != 0 ) delete in_pars_[i].length;
           break;
           default:
             if(in_pars_[i].buffer != 0 ) free(in_pars_[i].buffer);
           break;
         }
      }
      if(in_pars_) delete [] in_pars_;

      if(result_) {
        if(out_pars_) free_outpars();
        mysql_free_result(result_);
      }
      mysql_stmt_close(stmt_);
    }

    virtual void reset()
    {
      state_ = Done;
    }

    virtual void bind(int column, const std::string& value)
    {
      DEBUG(std::cerr << this << " bind " << column << " " << value << std::endl);
      unsigned long * len = new unsigned long();
      char * data;
      in_pars_[column].buffer_type = MYSQL_TYPE_STRING;

      if(!value.empty()){
      *len = value.length();
      data = (char *)malloc(*len + 1);
      strcpy(data, value.c_str());
      in_pars_[column].buffer = data;
      in_pars_[column].buffer_length = *len+1;
      in_pars_[column].length = len;
      in_pars_[column].is_null = 0;
      }
      else {
        in_pars_[column].buffer_type = MYSQL_TYPE_NULL;
        in_pars_[column].is_null = const_cast<my_bool *>(&mysqltrue_);
      }
    }

    virtual void bind(int column, short value)
    {
      DEBUG(std::cerr << this << " bind " << column << " " << value << std::endl);
      short * data = new short();
      *data = value;
      in_pars_[column].buffer_type = MYSQL_TYPE_SHORT;
      in_pars_[column].buffer = data;
      in_pars_[column].length = 0;
      in_pars_[column].is_null = 0;

    }

    virtual void bind(int column, int value)
    {
      DEBUG(std::cerr << this << " bind " << column << " " << value << std::endl);
      int * data = new int();
      *data = value;
      in_pars_[column].buffer_type = MYSQL_TYPE_LONG;
      in_pars_[column].buffer = data;
      in_pars_[column].length = 0;
      in_pars_[column].is_null = 0;
    }

    virtual void bind(int column, long long value)
    {
      DEBUG(std::cerr << this << " bind " << column << " " << value << std::endl);
      long long * data = new long long();
      *data = value;
      in_pars_[column].buffer_type = MYSQL_TYPE_LONGLONG;
      in_pars_[column].buffer = data;
      in_pars_[column].length = 0;
      in_pars_[column].is_null = 0;
    }

    virtual void bind(int column, float value)
    {
      DEBUG(std::cerr << this << " bind " << column << " " << value << std::endl);
      float * data = new float();
      *data = value;
      in_pars_[column].buffer_type = MYSQL_TYPE_FLOAT;
      in_pars_[column].buffer = data;
      in_pars_[column].length = 0;
      in_pars_[column].is_null = 0;
   }

    virtual void bind(int column, double value)
    {
      DEBUG(std::cerr << this << " bind " << column << " " << value << std::endl);
      double * data = new double();
      *data = value;
      in_pars_[column].buffer_type = MYSQL_TYPE_DOUBLE;
      in_pars_[column].buffer = data;
      in_pars_[column].length = 0;
      in_pars_[column].is_null = 0;
    }

    virtual void bind(int column, const boost::posix_time::ptime& value,
                      SqlDateTimeType type)
    {
      DEBUG(std::cerr << this << " bind " << column << " "
            << boost::posix_time::to_simple_string(value) << std::endl);

      MYSQL_TIME*  ts = new MYSQL_TIME();

      boost::posix_time::ptime::time_duration_type  tim = value.time_of_day();
      boost::posix_time::ptime::date_type dd = value.date();
      ts->year = dd.year();
      ts->month = dd.month();
      ts->day = dd.day();

      if (type == SqlDate){
        in_pars_[column].buffer_type = MYSQL_TYPE_DATE;
           ts->hour = 0;
           ts->minute = 0;
           ts->second = 0;
           ts->second_part = 0;

      }
      else {
        in_pars_[column].buffer_type = MYSQL_TYPE_DATETIME;
        ts->hour = tim.hours();
        ts->minute = tim.minutes();
        ts->second = tim.seconds();
        ts->second_part = tim.fractional_seconds(); //IMPL not actually stored according to MySQL documentation.
      }
      in_pars_[column].buffer = ts;
      in_pars_[column].length = 0;
      in_pars_[column].is_null = 0;

     }

    virtual void bind(int column, const boost::posix_time::time_duration& value)
    {
      DEBUG(std::cerr << this << " bind " << column << " "
            << boost::posix_time::to_simple_string(value) << std::endl);

      MYSQL_TIME*  ts = new MYSQL_TIME();

      //IMPL note that there is not really a "duration" type in mysql...mapping to a datetime
      in_pars_[column].buffer_type = MYSQL_TYPE_DATETIME;
      ts->hour = value.hours();
      ts->minute = value.minutes();
      ts->second = value.seconds();
      ts->second_part = value.fractional_seconds(); //IMPL not actually used according to MySQL documentation.
      in_pars_[column].buffer = ts;
      in_pars_[column].length = 0;
      in_pars_[column].is_null = 0;


    }



    virtual void bind(int column, const std::vector<unsigned char>& value)
    {
      DEBUG(std::cerr << this << " bind " << column << " (blob, size=" <<
            value.size() << ")" << std::endl);

      unsigned long * len = new unsigned long();
      char * data;
      in_pars_[column].buffer_type = MYSQL_TYPE_BLOB;

      if(!value.empty()){
        *len = value.size();
        data = (char *)malloc(*len);
        memcpy(data, &(*value.begin()), *len);

        in_pars_[column].buffer = data;
        in_pars_[column].buffer_length = *len;
        in_pars_[column].length = len;
        in_pars_[column].is_null = 0;
      }
      else {
        in_pars_[column].buffer_type = MYSQL_TYPE_NULL;
        in_pars_[column].is_null = const_cast<my_bool*>(&mysqltrue_);
      }

      // FIXME if first null was bound, check here and invalidate the prepared
      // statement if necessary because the type changes
    }

    virtual void bindNull(int column)
    {
      DEBUG(std::cerr << this << " bind " << column << " null" << std::endl);

      in_pars_[column].buffer_type = MYSQL_TYPE_NULL;
      in_pars_[column].is_null = const_cast<my_bool*>(&mysqltrue_);
      unsigned long * len = new unsigned long();
      in_pars_[column].buffer = 0;
      in_pars_[column].buffer_length = 0;
      in_pars_[column].length = len;

    }


    virtual void execute()
    {
      if (conn_.showQueries())
        std::cerr << sql_ << std::endl;


      if(mysql_stmt_bind_param(stmt_, &in_pars_[0]) == 0){
        if (mysql_stmt_execute(stmt_) == 0) {
          if(mysql_stmt_field_count(stmt_) == 0) { // assume not select
            affectedRows_ = mysql_stmt_affected_rows(stmt_);
           state_ = NoFirstRow;
            if (affectedRows_ == 1 ) {
              lastId_ = mysql_stmt_insert_id(stmt_);
            }
          }
          else {
            row_ = 0;
            result_ = mysql_stmt_result_metadata(stmt_);
            mysql_stmt_store_result(stmt_); //possibly not efficient, but suffer from "commands out of sync" errors with the usage patterns that Wt::Dbo uses if not called.
            if( result_ ) {
              if(mysql_num_fields(result_) > 0){
                state_ = NextRow;
              }
              else {
                state_ = NoFirstRow; // not sure how/if this can happen
              }
            }
            else {
              throw MySQLException(std::string("error getting result metadata ") + mysql_stmt_error(stmt_));
            }
          }
        }
        else {
          throw MySQLException(std::string("error executing prepared statement ")+ mysql_stmt_error(stmt_));
        }
      }
      else {
        throw MySQLException(std::string("error binding parameters")+ mysql_stmt_error(stmt_));
      }
    }

    virtual long long insertedId()
    {
      return lastId_;
    }

    virtual int affectedRowCount()
    {
      return affectedRows_;
    }

    virtual bool nextRow()
    {
      int status;
      switch (state_) {
        case NoFirstRow:
          state_ = Done;
          return false;
        case FirstRow:
          state_ = NextRow;
 //         return true; do binding on every row for now - not sure if memory reuse is possible.
        case NextRow:
          //bind the output..
          bind_output();
          if ((status = mysql_stmt_fetch(stmt_)) == 0 || status ==  MYSQL_DATA_TRUNCATED) { //perhaps should set state to indicate truncated
            row_++;
            return true;
          } else {
            if(status == MYSQL_NO_DATA  ){
            mysql_free_result(result_);
            mysql_stmt_free_result(stmt_);
            mysql_stmt_reset(stmt_);//too drastic?...
            result_ = 0;
            state_ = Done;
            return false;
            }
            else{
              throw MySQLException(std::string("MySQL: row fetch failure: ") + mysql_stmt_error(stmt_));
            }
          }
          break;
        case Done:
          throw MySQLException("MySQL: nextRow(): statement already "
              "finished");
      }

      return false;
    }

    virtual bool getResult(int column, std::string *value, int size)
    {
      if (*(out_pars_[column].is_null) == 1)
        return false;

      if(*(out_pars_[column].length) > 0){
        char * str;
        out_pars_[column].buffer = malloc(*(out_pars_[column].length)+1);
        out_pars_[column].buffer_length = *(out_pars_[column].length)+1;
        mysql_stmt_fetch_column(stmt_,  &out_pars_[column], column, 0);
        str = static_cast<char*>( out_pars_[column].buffer);
        str[*out_pars_[column].length] = '\0';
        *value = str;

        DEBUG(std::cerr << this
              << " result string " << column << " " << *value << std::endl);

        return true;
      }
      else
        return false;
    }

    virtual bool getResult(int column, short *value)
    {
      if (*(out_pars_[column].is_null) == 1)
         return false;

       *value = *static_cast<short*>(out_pars_[column].buffer);
    }

    virtual bool getResult(int column, int *value)
    {
      if (*(out_pars_[column].is_null) == 1)
        return false;
      switch (out_pars_[column].buffer_type ){
        case MYSQL_TYPE_LONG:

          *value = *static_cast<int*>(out_pars_[column].buffer);
          break;

        case MYSQL_TYPE_LONGLONG:

          *value = *static_cast<long long*>(out_pars_[column].buffer);
          break;

      }

      DEBUG(std::cerr << this
            << " result  int " << column << " " << *value << std::endl);

      return true;
    }

    virtual bool getResult(int column, long long *value)
    {
      if (*(out_pars_[column].is_null) == 1)
        return false;
      switch (out_pars_[column].buffer_type ){
        case MYSQL_TYPE_LONG:

          *value = *static_cast<int*>(out_pars_[column].buffer);
          break;

        case MYSQL_TYPE_LONGLONG:

          *value = *static_cast<long long*>(out_pars_[column].buffer);
          break;

      }

      DEBUG(std::cerr << this
            << " result long long " << column << " " << *value << std::endl);

      return true;
    }

    virtual bool getResult(int column, float *value)
    {
      if (*(out_pars_[column].is_null) == 1)
         return false;

       *value = *static_cast<float*>(out_pars_[column].buffer);

      DEBUG(std::cerr << this
            << " result float " << column << " " << *value << std::endl);

      return true;
    }

    virtual bool getResult(int column, double *value)
    {
      if (*(out_pars_[column].is_null) == 1)
         return false;

       *value = *static_cast<double*>(out_pars_[column].buffer);

      DEBUG(std::cerr << this
            << " result double " << column << " " << *value << std::endl);

      return true;
    }

    virtual bool getResult(int column, boost::posix_time::ptime *value,
                           SqlDateTimeType type)
    {
      if (*(out_pars_[column].is_null) == 1)
         return false;

      MYSQL_TIME* ts = static_cast<MYSQL_TIME*>(out_pars_[column].buffer);

      if (type == SqlDate){
        *value = boost::posix_time::ptime(boost::gregorian::date(ts->year, ts->month, ts->day),
                                          boost::posix_time::hours(0));
      }
      else
        *value = boost::posix_time::ptime(boost::gregorian::date(ts->year, ts->month, ts->day),
                                          boost::posix_time::time_duration(ts->hour, ts->minute, ts->second)+boost::posix_time::microseconds(ts->second_part));

      return true;
    }

    virtual bool getResult(int column, boost::posix_time::time_duration* value)
    {
      if (*(out_pars_[column].is_null) == 1)
         return false;

       MYSQL_TIME* ts = static_cast<MYSQL_TIME*>(out_pars_[column].buffer);
       *value = boost::posix_time::time_duration(ts->hour, ts->minute, ts->second);
    }

    virtual bool getResult(int column, std::vector<unsigned char> *value,
                           int size)
    {
      if (*(out_pars_[column].is_null) == 1)
        return false;

      if(*(out_pars_[column].length) > 0){
        out_pars_[column].buffer = malloc(*(out_pars_[column].length));
        out_pars_[column].buffer_length = *(out_pars_[column].length);
        mysql_stmt_fetch_column(stmt_,  &out_pars_[column], column, 0);

        std::size_t vlength = *(out_pars_[column].length);
        unsigned char *v = static_cast<unsigned char*>(out_pars_[column].buffer);

        value->resize(vlength);
        std::copy(v, v + vlength, value->begin());

        DEBUG(std::cerr << this
              << " result blob " << column << " (blob, size = " << vlength << ")"
              << std::endl);

        return true;
      }
      else
        return false;
    }

    virtual std::string sql() const {
      return sql_;
    }

  private:

    MySQL& conn_;
    std::string sql_;
    char name_[64];
    MYSQL_RES *result_;
    MYSQL_STMT* stmt_;
    MYSQL_BIND* in_pars_;
    MYSQL_BIND* out_pars_;
    static const my_bool mysqltrue_; //  true value to use because mysql specifies that pointer to the boolean is passed in many cases....
    enum { NoFirstRow, FirstRow, NextRow, Done } state_;
    int lastId_, row_, affectedRows_;

    void bind_output() {
       if(out_pars_) free_outpars();
       out_pars_ = new MYSQL_BIND[mysql_num_fields(result_)];
       for(int i = 0; i < mysql_num_fields(result_); ++i){
         MYSQL_FIELD* field = mysql_fetch_field_direct(result_, i);
             out_pars_[i].buffer_type = field->type;
             switch(field->type){
               case MYSQL_TYPE_TINY:
                  out_pars_[i].buffer = malloc(1);
                  out_pars_[i].buffer_length = 1;
                  break;

               case MYSQL_TYPE_SHORT:
                 out_pars_[i].buffer = malloc(2);
                 out_pars_[i].buffer_length = 2;
                 break;

               case MYSQL_TYPE_LONG:
               case MYSQL_TYPE_FLOAT:
                 out_pars_[i].buffer = malloc(4);
                 out_pars_[i].buffer_length = 4;
                 break;

               case MYSQL_TYPE_LONGLONG:
               case MYSQL_TYPE_DOUBLE:
                 out_pars_[i].buffer = malloc(8);
                 out_pars_[i].buffer_length = 8;
                 break;

               case MYSQL_TYPE_TIME:
               case MYSQL_TYPE_DATE:
               case MYSQL_TYPE_DATETIME:
               case MYSQL_TYPE_TIMESTAMP:
                 out_pars_[i].buffer = malloc(sizeof(MYSQL_TIME));
                 out_pars_[i].buffer_length = sizeof(MYSQL_TIME);
                 break;

               case MYSQL_TYPE_STRING:
               case MYSQL_TYPE_VAR_STRING:
               case MYSQL_TYPE_BLOB:
                 out_pars_[i].buffer = 0;
                 out_pars_[i].buffer_length = 0; // actually get data later- see http://dev.mysql.com/doc/refman/5.0/en/mysql-stmt-fetch.html
                 break;
               default:
                 std::cerr << "Programming Error: unknown type " << field->type << std::endl;
             }
             out_pars_[i].buffer_type = field->type;
             out_pars_[i].is_null = new my_bool();
             out_pars_[i].length = new unsigned long();
             out_pars_[i].error = new my_bool();
       }
       mysql_stmt_bind_result(stmt_, out_pars_);
    }
    void free_outpars() {

      for (int i = 0; i < mysql_num_fields(result_); ++i){
       if(out_pars_[i].buffer != 0)free(out_pars_[i].buffer);
       if(out_pars_[i].is_null != 0)delete out_pars_[i].is_null ;
       if(out_pars_[i].length != 0)delete out_pars_[i].length;
       if(out_pars_[i].error != 0)delete out_pars_[i].error;

      }
      delete [] out_pars_;
    }

};

const my_bool MySQLStatement::mysqltrue_ = 1;

MySQL::MySQL(const std::string& db,  const std::string& dbuser, const std::string& dbpasswd, const std::string dbhost)
: handle_(NULL), dbname_(db), dbuser_(dbuser), dbpasswd_(dbpasswd), dbhost_(dbhost)
{
  connect();
}

MySQL::MySQL(const MySQL& other)
: SqlConnection(other), dbname_(other.dbname_), dbuser_(other.dbuser_), dbpasswd_(other.dbpasswd_), dbhost_(other.dbhost_)
{
  if (!other.dbname_.empty())
    connect();
}

MySQL::~MySQL()
{
  clearStatementCache();
  if (handle_)
    mysql_close(handle_);
}

MySQL *MySQL::clone() const
{
  return new MySQL(*this);
}

bool MySQL::connect()
{
  if(!dbname_.empty()){
    if((handle_ = mysql_init(NULL))){
      my_bool reconnect = true;
      if(!mysql_options(handle_, MYSQL_OPT_RECONNECT, &reconnect))
      {
        if(mysql_real_connect(handle_, dbhost_.c_str(), dbuser_.c_str(), dbpasswd_.empty() ? 0 : dbpasswd_.c_str(), dbname_.c_str(),
            0, 0, CLIENT_FOUND_ROWS) != handle_){
          std::string errtext = mysql_error(handle_);
          mysql_close(handle_);
          throw MySQLException(std::string("MySQL : Failed to connect to database server: ") + errtext);
        }
      }
      else
      {
        throw MySQLException("MySQL : Failed to set the reconnect option");
      }
    }
    else
    {
      throw MySQLException(std::string("MySQL : Failed to initialize database: ") + dbname_);
    }
  }

  return true;
}

SqlStatement *MySQL::prepareStatement(const std::string& sql)
{
  return new MySQLStatement(*this, sql);
}

void MySQL::executeSql(const std::string &sql)
{
  MYSQL_RES *result;

  if (showQueries())
    std::cerr << sql << std::endl;

  if( mysql_query(handle_, sql.c_str()) != 0 ){
    std::cerr << "MySQL error performing query: " << mysql_error(handle_) << std::endl;
    throw MySQLException(std::string("MySQL error performing query: ") + mysql_error(handle_));
  }
  //use any results up
  MYSQL_RES* res = mysql_store_result(handle_);
  if(res) mysql_free_result(res);

}

std::string MySQL::autoincrementType() const
{
  return "BIGINT";
}

std::string MySQL::autoincrementSql() const
{
  return "AUTO_INCREMENT";
}

std::string MySQL::autoincrementInsertSuffix() const
{
  return std::string();
}

std::vector<std::string> MySQL::autoincrementDropSequenceSql(const std::string &table, const std::string &id) const
{
    return std::vector<std::string>();
}

std::vector<std::string> MySQL::autoincrementCreateSequenceSql(const std::string &table, const std::string &id) const
{
    return std::vector<std::string>();
}

const char *MySQL::dateTimeType(SqlDateTimeType type) const
{
  switch (type) {
    case SqlDate:
      return "date";
    case SqlDateTime:
      return "datetime";
    case SqlTime:
      return "time"; //IMPL note that there is not really a "duration" type in mysql...
  }
  std::stringstream ss;
  ss << __FILE__ << ":" << __LINE__ << ": implementation error";
  throw MySQLException(ss.str());
}

const char *MySQL::blobType() const
{
  return "blob";
}

void MySQL::startTransaction()
{
  if (showQueries())
     std::cerr << "start transaction" << std::endl;
  if( mysql_query(handle_, "start transaction") != 0 ){
    throw MySQLException(std::string("MySQL error starting transaction: ") + mysql_error(handle_));
  }
  //use any results up
  MYSQL_RES* res = mysql_store_result(handle_);
  if(res) mysql_free_result(res);
}

void MySQL::commitTransaction()
{
  my_bool status;
  if (showQueries())
     std::cerr << "commit transaction" << std::endl;
  if( (status = mysql_commit(handle_)) != 0 ){
    std::cerr << "error committing transaction: "<< mysql_error(handle_) << std::endl;
    throw MySQLException(std::string("MySQL error committing transaction: ") + mysql_error(handle_));
  }
  //use any results up
  MYSQL_RES* res = mysql_store_result(handle_);
  if(res) mysql_free_result(res);
}

void MySQL::rollbackTransaction()
{
  my_bool status;
  if (showQueries())
     std::cerr << "rollback" << std::endl;
  if((status =  mysql_rollback(handle_)) != 0 ){
    throw MySQLException(std::string("MySQL error rolling back transaction: ") + mysql_error(handle_));
  }
  //use any results up
  MYSQL_RES* res = mysql_store_result(handle_);
  if(res) mysql_free_result(res);
}

}
}
}
