/*
*    Copyright (C) 2012 lukaasm <lukaasm.pl>
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU Affero General Public License version 3 as
*    published by the Free Software Foundation.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU Affero General Public License for more details.
*
*    You should have received a copy of the GNU Affero General Public License
*    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef H_User
#define H_User

#include <Wt/Dbo/Dbo>
#include <string>

namespace dbo = Wt::Dbo;

class User
{
    std::string username;
    std::string sha1pass;

    template<class Action>
    void persist(Action& a)
    {
        dbo::field(a, username, "username");
        dbo::field(a, sha1pass, "sha_pass_hash");
    }
};

#endif
