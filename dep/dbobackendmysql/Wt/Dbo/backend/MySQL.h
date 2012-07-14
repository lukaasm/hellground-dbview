// This may look like C code, but it's really -*- C++ -*-
/*
 * Copyright (C) 2008 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 *
 * Contributed by: Paul Harrison
 */
#ifndef WT_DBO_BACKEND_MYSQL_H_
#define WT_DBO_BACKEND_MYSQL_H_

#include <Wt/Dbo/SqlConnection>
#include <Wt/Dbo/SqlStatement>
#include <Wt/Dbo/backend/WDboMySQLDllDefs.h>

#ifdef WIN32
#include <winsock.h>
#include <mysql.h>
#else
#include <mysql/mysql.h>
#endif


namespace Wt {
  namespace Dbo {
    namespace backend {

/*! \class MySQL
 *  \brief A MySQL connection
 *
 * This class provides the backend implementation for MySQL databases. It has been tested against MySQL 5.1.28.
 *
 * In order to work properly with Wt::Dbo, MySQL must be configured with
 *     - ANSI mode enabled - to ensure the correct quoting of table/column names.
 *     - InnoDB as the default database engine - so that the transaction based functionality works.
 *
 * \ingroup dbo
 */
class /*WTDBOMYSQL_API*/ MySQL : public SqlConnection
{
public:
  /*! \brief Opens a new MySQL backend connection.
   *
 *  \param db The database name.
 *  \param dbuser The username for the database connection - defaults to "root".
 *  \param dbpasswd The password for the database conection - defaults to an empty string.
 *  \param dbhost The hostname of the database - defaults to localhost.
 *
   */
  MySQL(const std::string& db, const std::string& dbuser="root", const std::string& dbpasswd="", const std::string dbhost="localhost");

  /*! \brief Copies a MySQL connection.
   */
  MySQL(const MySQL& other);

  /*! \brief Destructor.
   *
   * Closes the connection.
   */
  ~MySQL();

  virtual MySQL *clone() const;

  bool connect();

  /*! \brief Returns the underlying connection.
   */
  MYSQL *connection() { return handle_; }

  virtual void executeSql(const std::string &sql);

  virtual void startTransaction();
  virtual void commitTransaction();
  virtual void rollbackTransaction();

  virtual SqlStatement *prepareStatement(const std::string& sql);

  /** @name Methods that return dialect information
   */
  //@{
  virtual std::string autoincrementSql() const;
  virtual std::string autoincrementType() const;
  virtual std::string autoincrementInsertSuffix() const;
  virtual std::vector<std::string> autoincrementDropSequenceSql(const std::string &table, const std::string &id) const;
  virtual std::vector<std::string> autoincrementCreateSequenceSql(const std::string &table, const std::string &id) const;

  virtual const char *dateTimeType(SqlDateTimeType type) const;
  virtual const char *blobType() const;
  //@}

private:
  std::string dbname_;
  std::string dbuser_;
  std::string dbpasswd_;
  std::string dbhost_;

  MYSQL* handle_; // MySQL connection handle
};

    }
  }
}

#endif // WT_DBO_BACKEND_MYSQL_H_
