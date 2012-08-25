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

    Wt::WPushButton * tmpBtn;

    tmpBtn = addWidget(this, new Wt::WPushButton(LANG_CREATURE));
    BindSearch(tmpBtn->clicked(), SEARCH_CREATURE);

    tmpBtn = addWidget(this, new Wt::WPushButton(LANG_OBJECT));
    BindSearch(tmpBtn->clicked(), SEARCH_GAMEOBJECT);

    tmpBtn = addWidget(this, new Wt::WPushButton(LANG_QUEST));
    BindSearch(tmpBtn->clicked(), SEARCH_QUEST);

    tmpBtn = addWidget(this, new Wt::WPushButton(LANG_SPELL));
    BindSearch(tmpBtn->clicked(), SEARCH_SPELL);

    tmpBtn = addWidget(this, new Wt::WPushButton(LANG_ITEM));
    BindSearch(tmpBtn->clicked(), SEARCH_ITEM);
}

void SearchDiv::BindSearch(Wt::EventSignal<Wt::WMouseEvent>& signal, Searchers searcher)
{
    signal.connect(boost::bind(&SearchDiv::Search, this, searcher));
}

void SearchDiv::Search(Searchers searcher)
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

    // dummy for now - just ommit whole result
    for (SearchResults::const_iterator itr = results.begin(); itr != results.end(); ++itr);
}
