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
    addWidget(new Wt::WBreak());

    Wt::WContainerWidget* c = new Wt::WContainerWidget();
    c->setContentAlignment(Wt::AlignMiddle);

    addWidget(c);

    Wt::WLineEdit* l = new Wt::WLineEdit(LANG_SEARCHBAR_TEXT, c);
    l->setStyleClass("search");
    // bind on-enter event

    addWidget(new Wt::WBreak());

    addWidget(new Wt::WPushButton(LANG_CREATURE));
    addWidget(new Wt::WPushButton(LANG_OBJECT));
    addWidget(new Wt::WPushButton(LANG_QUEST));
    addWidget(new Wt::WPushButton(LANG_SPELL));
    addWidget(new Wt::WPushButton(LANG_ITEM));
}

void SearchWidget::addWidget(Wt::WWidget* w)
{
    w->setStyleClass("search");
    Wt::WContainerWidget::addWidget(w);
}
