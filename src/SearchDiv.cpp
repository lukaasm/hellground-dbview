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
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WLineEdit>
#include <Wt/WMessageBox>
#include <Wt/WPushButton>
#include <Wt/WRegExpValidator>
#include <Wt/WText>

#include "config.h"
#include "Language.h"
#include "ResultDiv.h"

SearchDiv::SearchDiv(Wt::WContainerWidget* parent) : Wt::WContainerWidget(parent)
{
    setContentAlignment(Wt::AlignCenter);

    addWidget(this, new Wt::WBreak());

    Wt::WContainerWidget* c = addWidget(this, new Wt::WContainerWidget());
    c->setContentAlignment(Wt::AlignMiddle);

    _searchBar = addWidget(c, new Wt::WLineEdit());
    _searchBar->setEmptyText(LANG_SEARCHEMPTYTEXT);

    Wt::WRegExpValidator * tmpValid = new Wt::WRegExpValidator("[a-zA-Z']{3,}"); // minimum 3 characters
    tmpValid->setMandatory(true);
    _searchBar->setValidator(tmpValid);

    addWidget(this, new Wt::WBreak());

    bindSearch(addWidget(this, new Wt::WPushButton(LANG_CREATURE))->clicked(), SEARCH_CREATURE);
    bindSearch(addWidget(this, new Wt::WPushButton(LANG_OBJECT))->clicked(), SEARCH_GAMEOBJECT);
    bindSearch(addWidget(this, new Wt::WPushButton(LANG_QUEST))->clicked(), SEARCH_QUEST);
    bindSearch(addWidget(this, new Wt::WPushButton(LANG_SPELL))->clicked(), SEARCH_SPELL);
    bindSearch(addWidget(this, new Wt::WPushButton(LANG_ITEM))->clicked(), SEARCH_ITEM);
}

void SearchDiv::SetResultDiv(ResultDiv * resultDiv)
{
    _resultDiv = resultDiv;
}

void SearchDiv::bindSearch(Wt::EventSignal<Wt::WMouseEvent>& signal, Searchers searcher)
{
    signal.connect(boost::bind(&SearchDiv::search, this, searcher));
}

void SearchDiv::Search(Wt::WString & searchFor, Searchers searcher)
{
    //printf("\nSearch for %s\n", searchFor.toUTF8().c_str());

    if (!_searchBar->text().empty() && _searchBar->validate() != Wt::WValidator::Valid)
    {
        Wt::WMessageBox::show(Wt::WString::LANG_ERROR, Wt::WString::LANG_ERROR_SEARCH_VALIDATION, Wt::Ok);
        return;
    }

    Wt::WRegExpValidator tmpValid("[a-zA-Z']{3,}"); // minimum 3 characters
    tmpValid.setMandatory(true);
    if (tmpValid.validate(searchFor).state() != Wt::WValidator::Valid)
    {
        Wt::WMessageBox::show(Wt::WString::LANG_ERROR, Wt::WString::LANG_ERROR_SEARCH_VALIDATION, Wt::Ok);
        return;
    }

    _searchBar->setText(searchFor);     // in case of internal path searching

    searchFor = "%" + searchFor + "%";

    Wt::Dbo::backend::MySQL db(DB_NAME, DB_LOGIN, DB_PASS, DB_HOST);

    Wt::Dbo::Session session;
    session.setConnection(db);

    std::list<SearchInfo> results;

    session.mapClass<SearchInfo>(SearcherTableNames[searcher]);

    Wt::Dbo::Transaction transaction(session);
    SearchResults tmpResults = session.find<SearchInfo>().where("name LIKE ?").bind(searchFor.toUTF8().c_str()).limit(30);

    for (SearchResults::const_iterator itr = tmpResults.begin(); itr != tmpResults.end(); ++itr)
        results.push_back(SearchInfo((*itr)->GetEntry(), (*itr)->GetName()));

    transaction.commit();

    _resultDiv->CreateResultsView(results, searcher);
}

void SearchDiv::search(Searchers searcher)
{
    Wt::WString searchFor = _searchBar->text();

    if (searchFor.empty() || searcher == SEARCH_NONE)
        return;

    std::string intPath = "/search/";
    intPath += SearcherInternalPaths[searcher];
    intPath += "/" + searchFor.toUTF8();

    wApp->setInternalPath(intPath, false);

    Search(searchFor, searcher);
}
