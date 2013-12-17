/****************************************************************************
Copyright (c) 2011-2013,WebJet Business Division,CYOU
 
http://www.genesis-3d.com.cn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef __scriptgui_H__
#define __scriptgui_H__
#include "MyGUI.h"
namespace App
{
	class ScriptGui
	{
	public:
		static MyGUI::Widget* loadLayout(MyGUI::Widget* parent, const std::string& file_name);
		static void destroyWidget(MyGUI::Widget* widget);
		static MyGUI::Widget* findWidget(MyGUI::Widget* parent, const std::string& widget_name);
		static MyGUI::IntSize getScreenSize();

		static void setResolution(int width, int height);//0 means auto.
		static void setResolution(const MyGUI::IntSize& size);//0 means auto.
		static const MyGUI::IntSize& getResolution();
		static bool autoResolutionWidth();
		static bool autoResolutionHeight();
	};
}



#endif //__scriptgui_H__