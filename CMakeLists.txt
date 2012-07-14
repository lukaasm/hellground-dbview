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

cmake_minimum_required(VERSION 2.8)

project("DBView")

message(
"\nThis scripts builds DBView site
You can use following options for customization:
    INSTALL_DIR: Path where the server should be installed to (default - current dir)

For example: cmake -DINSTALL_DIR=/var/www ..\n\n"
)

if (NOT INSTALL_DIR)
    set(INSTALL_DIR ${CMAKE_SOURCE_DIR}/bin)
endif (NOT INSTALL_DIR)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${CMAKE_SOURCE_DIR}/cmake
)

option(USE_FCGI_CONNECTOR FALSE)

find_package(Wt REQUIRED)
message(STATUS "Wt include dir: ${Wt_INCLUDE_DIR}")

if(WIN32 AND MSVC)
    set(BUILD_PARALLEL "/MP" CACHE STRING "MSVC option for parallel builds (/MP or /MPx)")
    find_package(OpenSSL)
endif(WIN32 AND MSVC)

set(MYSQL_DIR $ENV{MYSQL_DIR} CACHE PATH "The MySQL Directory Path")
find_package(MySQL)

set(BOOST_PREFIX $ENV{BOOST_ROOT} CACHE PATH "The Boost Directory Path")
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost COMPONENTS signals date_time unit_test_framework test_exec_monitor REQUIRED)
message(STATUS "BOOST include dir: ${Boost_INCLUDE_DIR}")
message(STATUS "BOOST libraries dir: ${Boost_LIBRARY_DIRS}")

install(DIRECTORY res DESTINATION ${INSTALL_DIR}
    FILE_PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
    DIRECTORY_PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
)

message("\nInstall directory: ${INSTALL_DIR}\n\n")

add_subdirectory(dep)
add_subdirectory(src)