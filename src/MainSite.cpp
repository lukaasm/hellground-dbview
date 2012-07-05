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

#include "MainSite.h"

int main(int argc, char* argv[])
{
    return Wt::WRun(argc, argv, &MainSite::Create);
}

Wt::WApplication* MainSite::Create(const Wt::WEnvironment& e)
{
    return new MainSite(e);
}

MainSite::MainSite(const Wt::WEnvironment& e) : Wt::WApplication(e)
{

}
