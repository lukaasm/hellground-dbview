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

#include "SearchWidget.h"

#include <Wt/WBreak>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>

#include "Language.h"

SearchWidget::SearchWidget(Wt::WContainerWidget* parent) : Wt::WContainerWidget(parent)
{
    addWidget(this, new Wt::WBreak());

    Wt::WContainerWidget* c = addWidget(this, new Wt::WContainerWidget());
    c->setContentAlignment(Wt::AlignMiddle);

    _searchBar = addWidget(c, new Wt::WLineEdit());
    _searchBar->setEmptyText(LANG_SEARCHEMPTYTEXT);
    // bind on-enter event

    addWidget(this, new Wt::WBreak());

    addWidget(this, new Wt::WPushButton(LANG_CREATURE));
    addWidget(this, new Wt::WPushButton(LANG_OBJECT));
    addWidget(this, new Wt::WPushButton(LANG_QUEST));
    addWidget(this, new Wt::WPushButton(LANG_SPELL));
    addWidget(this, new Wt::WPushButton(LANG_ITEM));
}
