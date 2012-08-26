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

void ResultDiv::CreateResultsView(SearchResults & results, Searchers searcher)
{
    // dummy
    for (SearchResults::const_iterator itr = results.begin(); itr != results.end(); ++itr);

}

void ResultDiv::CreateDetailedView(Wt::WString & entry, Searchers searcher)
{
    //printf("\nCreate detailed view for entry %s\n", entry.toUTF8().c_str());
}

void ResultDiv::CreateDetailedView(uint32 entry, Searchers searcher)
{
    Wt::WString entryStr("?");
    entryStr.arg(int64_t(entry));

    CreateDetailedView(entryStr, searcher);
}
