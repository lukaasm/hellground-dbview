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
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef H_MainSite
#define H_MainSite

#include <Wt/WApplication>

class LoginDialog;
class SearchDiv;
class ResultDiv;

class MainSite : public Wt::WApplication
{
    public:
        MainSite(const Wt::WEnvironment&);

        static Wt::WApplication* Create(const Wt::WEnvironment&);

    private:
        SearchDiv * _searchDiv;
        ResultDiv * _resultDiv;

        void handleInternalPath();
};

#endif
