#
#    Copyright (C) 2012 lukaasm <lukaasm.pl>
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Affero General Public License version 3 as
#    published by the Free Software Foundation.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Affero General Public License for more details.
#
#    You should have received a copy of the GNU Affero General Public License
#    along with this program. If not, see <http://www.gnu.org/licenses/>.
#


file(GLOB_RECURSE DBVIEW_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.h)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/dep/dbobackendmysql
    ${MYSQL_INCLUDE_DIR}
    ${Wt_INCLUDE_DIR}
    if (NOT USE_FCGI_CONNECTOR)
        ${Boost_INCLUDE_DIR}
    endif (NOT USE_FCGI_CONNECTOR)
)
link_directories(${Boost_LIBRARY_DIRS})

add_executable(dbview.wt ${DBVIEW_SRCS})

if(WIN32 AND MSVC)
    set_target_properties(dbview.wt PROPERTIES COMPILE_FLAGS "${BUILD_PARALLEL} /wd4251 /wd4275 /wd4355 /wd4800 /wd4996 /wd4101 /wd4267")
endif(WIN32 AND MSVC)

if (UNIX)
    set(Wt_LIBRARIES ${Wt_LIBRARIES} ${Boost_SIGNALS_LIBRARY})
else (UNIX)
    set(Wt_LIBRARIES ${Wt_LIBRARIES} ${OPENSSL_LIBRARIES})
endif(UNIX)

add_dependencies(dbview.wt wtdbomysql)

target_link_libraries(dbview.wt
    ${Wt_LIBRARIES}
    wtdbomysql
    ${MYSQL_LIBRARIES}
)

install(TARGETS dbview.wt
    RUNTIME DESTINATION ${INSTALL_DIR}
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
                GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ
)
