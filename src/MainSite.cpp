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
#include <Wt/WPushButton>
#include <Wt/WStackedWidget>

#include "Language.h"
#include "SearchWidget.h"

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
    setTitle(LANG_SITE_TITLE);
    useStyleSheet("res/style.css");

    Wt::WContainerWidget* header = new Wt::WContainerWidget(root());
    header->setId("header");
    header->setContentAlignment(Wt::AlignRight);

    Wt::WPushButton* b = new Wt::WPushButton("Sign In", header);
    b->setStyleClass("header");

    b = new Wt::WPushButton("Register", header);
    b->setStyleClass("header");

    Wt::WStackedWidget* body = new Wt::WStackedWidget(root());
    body->setId("content");

    body->setContentAlignment(Wt::AlignCenter);
    body->addWidget(new SearchWidget());
}
