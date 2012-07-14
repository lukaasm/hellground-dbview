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

#include "LoginDialog.h"

#include <Wt/WAnchor>
#include <Wt/WBreak>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>

#include "Language.h"

LoginDialog* LoginDialog::Create()
{
    // it will be removed in done method
    return new LoginDialog();
}

LoginDialog::LoginDialog() : Wt::WDialog()
{
    setTitleBarEnabled(false);

    setModal(true);
    setClosable(true);

    contents()->setId("login-box");

    Wt::WContainerWidget* body = addWidget(contents(), new Wt::WContainerWidget());

    addWidget(body, new Wt::WLineEdit())->setEmptyText(LANG_LOGIN);
    addWidget(body, new Wt::WBreak);
    Wt::WLineEdit* l = addWidget(body, new Wt::WLineEdit());
    l->setEmptyText(LANG_PASSWORD);
    l->setEchoMode(Wt::WLineEdit::Password);

    addWidget(contents(), new Wt::WAnchor("http://panel.hellground.pl/panel.wt/password",LANG_FORGOTTEN_PASSWORD));

    Wt::WContainerWidget* footer = addWidget(contents(), new Wt::WContainerWidget());

    addWidget(footer, new Wt::WPushButton(LANG_OK))->clicked().connect(SLOT(this, LoginDialog::done));
    addWidget(footer, new Wt::WPushButton(LANG_CANCEL))->clicked().connect(SLOT(this, LoginDialog::done));
}

void LoginDialog::done()
{
    setHidden(true);
    delete this;
}
