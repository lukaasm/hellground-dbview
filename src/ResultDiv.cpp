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

#include "ResultDiv.h"

#include <boost/lexical_cast.hpp>
#include <Wt/Dbo/backend/MySQL.h>
#include <Wt/WAnchor>
#include <Wt/WDialog>
#include <Wt/WPushButton>
#include <Wt/WTable>
#include <Wt/WText>

#include "config.h"
#include "Language.h"

ResultDiv::ResultDiv(Wt::WContainerWidget * parent)
 : Wt::WContainerWidget(parent), _searcherUsed(SEARCH_NONE)
{
    setStyleClass("results");
}

Wt::WAnchor * ResultDiv::createAnchor(const std::string & text, const std::string & entry)
{
    Wt::WAnchor * tmpAnchor = new Wt::WAnchor();

    std::string tmpStr = ADDRESS;
    tmpStr += SearcherInternalPaths[_searcherUsed];
    tmpStr += "/" + entry;

    tmpAnchor->setText(text);
    tmpAnchor->setLink(Wt::WLink(tmpStr));
    tmpAnchor->setTarget(Wt::TargetNewWindow);

    return tmpAnchor;
}

void ResultDiv::CreateResultsView(std::list<TemplateInfo> & results, Searchers searcher)
{
    _searcherUsed = searcher;

    clear();
    Wt::WTable * tmpTable = new Wt::WTable(this);
    tmpTable->setStyleClass("results");

    tmpTable->setHeaderCount(1);
    tmpTable->elementAt(0, 0)->addWidget(new Wt::WText(LANG_ENTRY));
    tmpTable->elementAt(0, 1)->addWidget(new Wt::WText(LANG_NAME));

    int i = 1;
    std::string tmpStr;

    for (std::list<TemplateInfo>::const_iterator itr = results.begin(); itr != results.end(); ++itr, ++i)
    {
        const TemplateInfo & tmpResult = *itr;

        tmpStr = boost::lexical_cast<std::string>(tmpResult.GetEntry());

        tmpTable->elementAt(i, 0)->addWidget(createAnchor(tmpStr, tmpStr));
        tmpTable->elementAt(i, 0)->setStyleClass("entry");
        tmpTable->elementAt(i, 1)->addWidget(createAnchor(tmpResult.GetName(), tmpStr));
        tmpTable->elementAt(i, 1)->setStyleClass("name");

        bindShowDetailedInfo(tmpTable->elementAt(i, 0)->clicked(), tmpResult.GetEntry());
        bindShowDetailedInfo(tmpTable->elementAt(i, 1)->clicked(), tmpResult.GetEntry());
    }
}

void ResultDiv::CreateDetailedView(Wt::WString & entry, Searchers searcher)
{
    //printf("\nCreate detailed view for entry %s\n", entry.toUTF8().c_str());
    addWidget(this, new Wt::WText(entry));
    addWidget(this, new Wt::WText(entry));
    addWidget(this, new Wt::WText(entry));
    addWidget(this, new Wt::WText(entry));
    addWidget(this, new Wt::WText(entry));
    addWidget(this, new Wt::WText(entry));
    addWidget(this, new Wt::WText(entry));
}

void ResultDiv::CreateDetailedView(long entry, Searchers searcher)
{
    Wt::WString entryStr = boost::lexical_cast<std::string>(entry);

    CreateDetailedView(entryStr, searcher);
}

void ResultDiv::bindShowDetailedInfo(Wt::EventSignal<Wt::WMouseEvent>& signal, long entry)
{
    signal.connect(boost::bind(&ResultDiv::showDetailedInfo, this, entry));
}

void ResultDiv::showDetailedInfo(long entry)
{
    ResultDiv * newResDiv = new ResultDiv();

    newResDiv->CreateDetailedView(entry, _searcherUsed);

    Wt::WDialog * detailedInfo = new Wt::WDialog();

    detailedInfo->setWindowTitle(Wt::WString::LANG_RESULT_TITLE.arg(SearcherInternalPaths[_searcherUsed]).arg(_detailedName).arg(int64_t(entry)));
    detailedInfo->setTitleBarEnabled(true);
    detailedInfo->setModal(true);
    detailedInfo->setClosable(true);
    detailedInfo->rejectWhenEscapePressed();

    detailedInfo->contents()->setId("result-detailbox");
    detailedInfo->contents()->addWidget(newResDiv);

    detailedInfo->exec(Wt::WAnimation(Wt::WAnimation::Fade, Wt::WAnimation::Linear, 1000));

    delete detailedInfo;
}
