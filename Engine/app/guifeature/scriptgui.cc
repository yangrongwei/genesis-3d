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
#include "stdneb.h"
#include "scriptgui.h"
#include "graphicsystem/GraphicSystem.h"
#include "myguiplatforms/include/MyGUI_GenesisRenderManager.h"
namespace App
{
	MyGUI::Widget* ScriptGui::loadLayout(MyGUI::Widget* parent, const std::string& file_name)
	{
		MyGUI::VectorWidgetPtr insts = MyGUI::LayoutManager::getInstancePtr()->loadLayout(
			file_name,
			"",
			static_cast<MyGUI::Widget*>(parent));

		if (1 == insts.size())
		{
			return insts.at(0);
		}
		else if (1 < insts.size())
		{
			MyGUI::Widget* parent_new = MyGUI::Gui::getInstancePtr()->createWidgetT("Widget","Widget", 0, 0, 0, 0, MyGUI::Align::Default, "Static", (*insts.begin())->getName());
			MyGUI::VectorWidgetPtr::iterator begin = insts.begin();
			MyGUI::VectorWidgetPtr::iterator end = insts.begin();
			while (begin < end)
			{
				(*begin)->attachToWidget(parent_new, MyGUI::WidgetStyle::Popup);
			}
			return parent_new;
		}
		MyGUI::Widget* messing = MyGUI::Gui::getInstancePtr()->createWidgetT("Widget","Widget", 0, 0, 0, 0, MyGUI::Align::Default, "Static", "MissingLayout");
		return messing;
	}
	void ScriptGui::destroyWidget(MyGUI::Widget* widget)
	{
		MyGUI::Gui::getInstancePtr()->destroyWidget(widget);
	}
	MyGUI::Widget* ScriptGui::findWidget(MyGUI::Widget* parent, const std::string& widget_name)
	{
		return parent->findWidget(widget_name);
	}
	MyGUI::IntSize ScriptGui::getScreenSize()
	{
		const RenderBase::DisplayMode& dm = Graphic::GraphicSystem::Instance()->GetMainViewPortWindow()->GetDisplayMode();
		MyGUI::IntSize size;
		size.set(dm.GetWidth(), dm.GetHeight());//
		return size;
	}

	void ScriptGui::setResolution(const MyGUI::IntSize& size)
	{
		MyGUI::GenesisRenderManager::getInstancePtr()->setResolution(size);
	}
	const MyGUI::IntSize& ScriptGui::getResolution()
	{
		return MyGUI::GenesisRenderManager::getInstancePtr()->getResolution();
	}
	bool ScriptGui::autoResolutionWidth()
	{
		return MyGUI::GenesisRenderManager::getInstancePtr()->autoResolutionWidth();
	}
	bool ScriptGui::autoResolutionHeight()
	{
		return MyGUI::GenesisRenderManager::getInstancePtr()->autoResolutionHeight();
	}
}