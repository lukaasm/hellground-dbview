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

#include "SearchDiv.h"

#include <Wt/Dbo/backend/MySQL.h>
#include <Wt/WBreak>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>

#include "Language.h"

SearchDiv::SearchDiv(Wt::WContainerWidget* parent) : Wt::WContainerWidget(parent)
{
    setContentAlignment(Wt::AlignCenter);

    addWidget(this, new Wt::WBreak());

    Wt::WContainerWidget* c = addWidget(this, new Wt::WContainerWidget());
    c->setContentAlignment(Wt::AlignMiddle);

    _searchBar = addWidget(c, new Wt::WLineEdit());
    _searchBar->setEmptyText(LANG_SEARCHEMPTYTEXT);
    // bind on-enter event

    addWidget(this, new Wt::WBreak());

    bindSearch(addWidget(this, new Wt::WPushButton(LANG_CREATURE))->clicked(), SEARCH_CREATURE);
    bindSearch(addWidget(this, new Wt::WPushButton(LANG_OBJECT))->clicked(), SEARCH_GAMEOBJECT);
    bindSearch(addWidget(this, new Wt::WPushButton(LANG_QUEST))->clicked(), SEARCH_QUEST);
    bindSearch(addWidget(this, new Wt::WPushButton(LANG_SPELL))->clicked(), SEARCH_SPELL);
    bindSearch(addWidget(this, new Wt::WPushButton(LANG_ITEM))->clicked(), SEARCH_ITEM);
}

void SearchDiv::bindSearch(Wt::EventSignal<Wt::WMouseEvent>& signal, Searchers searcher)
{
    signal.connect(boost::bind(&SearchDiv::search, this, searcher));
}

void SearchDiv::search(Searchers searcher)
{
    Wt::WString searchFor = _searchBar->text();

    if (searchFor.empty())
        return;

    searchFor = "%" + searchFor + "%";

    Wt::Dbo::backend::MySQL db("dbname", "login", "pass", "host");

    Wt::Dbo::Session session;
    session.setConnection(db);

    session.mapClass<SearchResult>(SearcherTableNames[searcher]);

    Wt::Dbo::Transaction transaction(session);
    SearchResults results = session.find<SearchResult>().where("name LIKE ?").bind(searchFor.toUTF8().c_str());
    transaction.commit();

    // dummy for now - just omit whole result
    for (SearchResults::const_iterator itr = results.begin(); itr != results.end(); ++itr);
}
