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

#include <Wt/WPushButton>
#include <Wt/WText>

#include "Language.h"

LoginWidget* LoginWidget::Create()
{
    // it will be removed in done method
    return new LoginWidget(LANG_LOGINWIDGET_TITLE);
}

LoginWidget::LoginWidget(const Wt::WString& title) : Wt::WDialog(title)
{
    setModal(false);
    setClosable(true);

    new Wt::WText("Test", contents());

    Wt::WPushButton* b = new Wt::WPushButton("Ok", contents());
    b->clicked().connect(SLOT(this, LoginWidget::done));
}

void LoginWidget::done()
{
    setHidden(true);
    delete this;
}
