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

#include <new>

#include "BasicAppFrame.h"
#include "MainForm.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;

BasicAppFrame::BasicAppFrame(void)
{
}

BasicAppFrame::~BasicAppFrame(void)
{
}

result
BasicAppFrame::Initialize()
{
	result r = Frame::Construct();
	return r;
}

result
BasicAppFrame::OnInitializing(void)
{
	// Create a form
	MainForm* pMainForm = new (std::nothrow) MainForm();
	result r = pMainForm->Initialize();

	// Add the form to the frame
	AddControl(pMainForm);

	// Set the current form
	SetCurrentForm(pMainForm);

	// Draw the form
	pMainForm->Invalidate(true);

	return r;
}

result
BasicAppFrame::OnTerminating(void)
{
	result r = E_SUCCESS;

	return r;
}
