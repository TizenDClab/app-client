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
#include <FMedia.h>

#include "ImagePanel.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Io;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Media;
using namespace Tizen::Graphics;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Base::Collection;


ImagePanel::ImagePanel(void)
   : __pTizenBitmap(null)
{
}

ImagePanel::~ImagePanel(void)
{
}

result
ImagePanel::Initialize(Tizen::Graphics::Rectangle rect)
{
   timer.Construct(*this);
   filelist.Construct();

   return Panel::Construct(rect);
}

result
ImagePanel::OnInitializing(void)
{
   result r = image.Construct();
   Directory dir;

   dir.Construct(App::GetInstance()->GetAppDataPath());
   File outfile;
   outfile.Construct(L"/tmp/my_filename.txt", L"w");

   pDirEnum = dir.ReadN();
   while(pDirEnum->MoveNext() == E_SUCCESS) {
      DirEntry cur = pDirEnum->GetCurrentDirEntry();
      if(cur.IsDirectory() == true || cur.GetName().Contains(".jpg") == false)
         continue;
      filelist.Add(new String(cur.GetName()));
   }
   fidx = filelist.GetCount();
   cidx = 0;
   filelist.Sort(StringComparer());

   String* cur = static_cast<String*>(filelist.GetAt(cidx++));
   String path(App::GetInstance()->GetAppDataPath() + *cur);
   __pTizenBitmap = image.DecodeN(path, BITMAP_PIXEL_FORMAT_ARGB8888);
   outfile.Write(path + L"\n");
   Draw();
   timer.Start(5000);
   return r;
}

result
ImagePanel::OnTerminating(void)
{
   result r = E_SUCCESS;

   delete __pTizenBitmap;
   return r;
}

result
ImagePanel::OnDraw(void)
{
   result r = E_SUCCESS;

   Canvas* pCanvas = GetCanvasN();

   if (pCanvas != null && __pTizenBitmap != null)
      r = pCanvas->DrawBitmap(Rectangle(0, 0, __pTizenBitmap->GetWidth(), __pTizenBitmap->GetHeight()), *__pTizenBitmap);

   delete pCanvas;

   return r;
}

void
ImagePanel::OnTimerExpired(Timer& timer)
{
   File outfile;
   outfile.Construct(L"/tmp/my_filename.txt", L"w");
   if(cidx >= fidx) {
      cidx = 0;
   }
   String* cur = static_cast<String*>(filelist.GetAt(cidx++));
   String path(App::GetInstance()->GetAppDataPath() + *cur);
   __pTizenBitmap = image.DecodeN(path, BITMAP_PIXEL_FORMAT_ARGB8888);
   outfile.Write(path + L"\n");
   Draw();
   timer.Start(5000);
}
