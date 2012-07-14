SET(WTDBOMYSQL_SOVERSION 23)

SET(WTDBOMYSQL_STATIC true)

# Boost is used nearly everywhere, so we can put these here
INCLUDE_DIRECTORIES(
  ${Wt_INCLUDE_DIR}
  ${BOOST_INCLUDE_DIRS}
)

LINK_DIRECTORIES(${BOOST_LIB_DIRS})
SUBDIRS(dbobackendmysql)
