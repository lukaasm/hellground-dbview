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

#ifndef H_SearchDiv
#define H_SearchDiv

#include <Wt/WContainerWidget>

#include "DboClasses.h"

class SearchDiv : public Wt::WContainerWidget
{
    public:
        SearchDiv(Wt::WContainerWidget* = NULL);

        template<class T>
        T* addWidget(Wt::WContainerWidget* c, T* w)
        {
            w->setStyleClass("search");
            c->addWidget(w);
            return w;
        }

    private:
        Wt::WLineEdit *_searchBar;

        void bindSearch(Wt::EventSignal<Wt::WMouseEvent>& signal, Searchers searcher);
        void search(Searchers searcher);
};

#endif
