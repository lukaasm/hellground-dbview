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

SearchWidget::SearchWidget(Wt::WContainerWidget* parent) : Wt::WContainerWidget(parent)
{
    Wt::WLineEdit* w = new Wt::WLineEdit("What u wanna search?", this);
    w->setStyleClass("search-bar");

    new Wt::WBreak(this);

    Wt::WPushButton* b = new Wt::WPushButton("Creature", this);
    b->setStyleClass("search-button");
    // bind click event

    b = new Wt::WPushButton("Object", this);
    b->setStyleClass("search-button");
    // bind click event

    b = new Wt::WPushButton("Quest", this);
    b->setStyleClass("search-button");
    // bind click event

    b = new Wt::WPushButton("Spell", this);
    b->setStyleClass("search-button");
    // bind click event
}
