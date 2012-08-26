/*
*    Copyright (C) 2012 Siof, lukaasm <lukaasm.pl>
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

#ifndef H_ResultDiv
#define H_ResultDiv

#include <Wt/WContainerWidget>

#include "DboClasses.h"

class ResultDiv : public Wt::WContainerWidget
{
    public:
        ResultDiv(Wt::WContainerWidget* parent = NULL) : Wt::WContainerWidget(parent), _searcherUsed(SEARCH_NONE) {}

        template<class T>
        T* addWidget(Wt::WContainerWidget* c, T* w, const char * style = "results")
        {
            w->setStyleClass(style);
            c->addWidget(w);
            return w;
        }

        void CreateResultsView(std::vector<SearchResult> & results, Searchers searcher);
        void CreateDetailedView(long entry, Searchers searcher);
        void CreateDetailedView(Wt::WString & entry, Searchers searcher);

    private:
        Searchers _searcherUsed;    // searcher used for showing results view
        Wt::WString _detailedName;  // name of detailed view entry object

        Wt::WAnchor* createAnchor(const std::string & text, const long & entry);

        void bindShowDetailedInfo(Wt::EventSignal<Wt::WMouseEvent>& signal, long entry);
        void showDetailedInfo(long entry);
};

#endif // H_ResultDiv
