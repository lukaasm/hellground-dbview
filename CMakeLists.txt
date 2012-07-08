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

project("HellGround DBView")

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${CMAKE_SOURCE_DIR}/cmake
)

find_package(Wt REQUIRED)

add_subdirectory(src)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${Wt_INCLUDE_DIR}
)
