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

#include "HeaderDiv.h"

#include <Wt/WBreak>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>

#include "Language.h"
#include "LoginDialog.h"

HeaderDiv::HeaderDiv(Wt::WContainerWidget* parent) : Wt::WStackedWidget(parent)
{
    setId("header");
    setContentAlignment(Wt::AlignRight);

    addWidget(this, new Wt::WPushButton(LANG_SIGNIN))->clicked().connect(SLOT(this, HeaderDiv::CreateLoginDialog));
    addWidget(this, new Wt::WPushButton(Wt::WWidget::LANG_REGISTER));
}

void HeaderDiv::CreateLoginDialog()
{
    LoginDialog::Create()->show();
}
