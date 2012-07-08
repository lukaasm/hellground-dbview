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

#include "LoginWidget.h"

#include <Wt/WBreak>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>

#include "Language.h"

LoginWidget* LoginWidget::Create()
{
    // it will be removed in done method
    return new LoginWidget();
}

LoginWidget::LoginWidget() : Wt::WDialog()
{
    setTitleBarEnabled(false);

    setModal(true);
    setClosable(true);

    contents()->setId("login-box");

    Wt::WContainerWidget* body = addWidget(contents(), new Wt::WContainerWidget());

    addWidget(body, new Wt::WLineEdit(LANG_LOGIN_TEXT));
    addWidget(body, new Wt::WBreak);
    addWidget(body, new Wt::WLineEdit(LANG_PASSWORD_TEXT));

    //addWidget(contents(), new Wt::WAnchor( ... /*forgotten password*/));

    Wt::WContainerWidget* footer = addWidget(contents(), new Wt::WContainerWidget());

    Wt::WPushButton* b = addWidget(footer, new Wt::WPushButton(LANG_LOGIN_BUT_OK));
    b->clicked().connect(SLOT(this, LoginWidget::done));

    b = addWidget(footer, new Wt::WPushButton(LANG_LOGIN_BUT_CANCEL));
    b->clicked().connect(SLOT(this, LoginWidget::done));
}

void LoginWidget::done()
{
    setHidden(true);
    delete this;
}
