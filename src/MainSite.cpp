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

#include <Wt/WContainerWidget>
#include <Wt/WMessageBox>
#include <Wt/WOverlayLoadingIndicator>
#include <Wt/WStackedWidget>
#include <Wt/WString>

#include "Language.h"
#include "HeaderDiv.h"
#include "SearchDiv.h"
#include "ResultDiv.h"

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
    messageResourceBundle().use("res/lang/general");
    useStyleSheet("res/style.css");

    setTitle(Wt::WWidget::LANG_SITE_TITLE);
    setLoadingIndicator(new Wt::WOverlayLoadingIndicator(Wt::WString::LANG_LOADING));

    root()->addWidget(new HeaderDiv());

    _searchDiv = new SearchDiv(root());
    _resultDiv = new ResultDiv(root());

    _searchDiv->SetResultDiv(_resultDiv);

    handleInternalPath();
}

void MainSite::handleInternalPath()
{
    if (internalPath().empty() || internalPath() == "/")
        return;

    // what should we display/search for
    std::string internal1Part = internalPathNextPart("/");

    bool searching = false;

    if (internal1Part == "search")
    {
        searching = true;
        internal1Part = internalPathNextPart("/" + internal1Part + "/");
    }

    // entry/text
    Wt::WString internal2Part = internalPathNextPart((searching ? "/search/" : "/") + internal1Part + "/");

    // detect searcher
    Searchers searcher = SEARCH_NONE;

    for (int i = 0; i < SEARCH_MAX; ++i)
    {
        if (internal1Part == SearcherInternalPaths[i])
        {
            searcher = Searchers(i);
            break;
        }
    }

    if (searcher == SEARCH_NONE)
    {
        Wt::WMessageBox::show("Error !", Wt::WString::LANG_ERROR_WRONG_SEARCHER, Wt::Ok);
        return;
    }

    if (searching)
        _searchDiv->Search(internal2Part, searcher);
    else
        _resultDiv->CreateDetailedView(internal2Part, searcher);
}
