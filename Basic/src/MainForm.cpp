//
// Copyright (c) 2012 Samsung Electronics Co., Ltd.
//
// Licensed under the Flora License, Version 1.1 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://floralicense.org/license/
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an AS IS BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include <FApp.h>
#include <FBase.h>

#include "AppResourceId.h"
#include "ImagePanel.h"
#include "MainForm.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;

MainForm::MainForm(void)
{
	__pPanel = null;
}

MainForm::~MainForm(void)
{
}

result
MainForm::Initialize()
{
	result r = Form::Construct(IDF_MAINFORM);

	return r;
}

result
MainForm::CreateImagePanel(void)
{
	ImagePanel* pImagePanel = new (std::nothrow) ImagePanel();
	result r = pImagePanel->Initialize(Rectangle(0, 0, GetClientAreaBounds().width, GetClientAreaBounds().height));
	r = AddControl(pImagePanel);
	__pPanel = pImagePanel;

	return r;
}

result
MainForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	CreateImagePanel();

	return r;
}

result
MainForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	return r;
}


void
MainForm::OnFormBackRequested(Form& source)
{
	UiApp* pApp = UiApp::GetInstance();
	AppAssert(pApp);
	pApp->Terminate();
}
