message("** Wt::Dbo: building MySQL backend.")

SET(WTDBOMYSQL_STATIC true)

add_library(wtdbomysql STATIC MySQL.C)

target_link_libraries(wtdbomysql ${Wt_DBO_LIBRARY} ${Boost_LIBRARIES})
