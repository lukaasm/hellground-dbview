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

#ifndef H_SearchWidget
#define H_SearchWidget

#include <Wt/WContainerWidget>

class SearchWidget : public Wt::WContainerWidget
{
    public:
        SearchWidget(Wt::WContainerWidget* = NULL);

        void addWidget(Wt::WWidget*);
};

#endif
