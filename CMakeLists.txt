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

cmake_minimum_required(VERSION 2.6)

project("DBView")

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${CMAKE_SOURCE_DIR}/cmake
)

option(USE_FCGI_CONNECTOR FALSE)

find_package(Wt REQUIRED)
message(STATUS "Wt include dir: ${Wt_INCLUDE_DIR}")

if(WIN32)
    if(MSVC)
        SET(BUILD_PARALLEL "/MP" CACHE STRING "MSVC option for parallel builds (/MP or /MPx)")
    endif(MSVC)
endif(WIN32)

if (NOT USE_FCGI_CONNECTOR)
    set(BOOST_PREFIX $ENV{BOOST_ROOT} CACHE PATH "The Boost Directory Path")
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREADED ON)

    find_package(Boost REQUIRED)
    message(STATUS "BOOST include dir: ${Boost_INCLUDE_DIR}")
    message(STATUS "BOOST libraries dir: ${Boost_LIBRARY_DIRS}")
endif(NOT USE_FCGI_CONNECTOR)

add_subdirectory(src)
