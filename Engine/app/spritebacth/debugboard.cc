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
#include "debugboard.h"
#include "basegamefeature/managers/timesource.h"
#include "graphicsystem/GraphicSystem.h"

namespace App
{
	DebugBoard::DebugBoard()
		: m_mainWin(NULL)
		, m_fps(NULL)
	{

	}
	DebugBoard::~DebugBoard()
	{
		_release();
	}

	DebugBoard& DebugBoard::Instance()
	{
		static DebugBoard inst;
		return inst;
	}

	void DebugBoard::Open()
	{		
		GUIServer::Instance()->eventBeforeDrawUI += Delegates::newDelegate(&Instance(), &DebugBoard::_eventUpdate);
		if (NULL == Instance().m_mainWin)
		{
			Instance()._init();
		}
		
		Instance().m_mainWin->setVisible(true);
	}

	void DebugBoard::Close()
	{
		if (GUIServer::Instance()->IsOpen() && Instance().m_mainWin)
		{
			Instance().m_mainWin->setVisible(false);
		}
		GUIServer::Instance()->eventBeforeDrawUI -= Delegates::newDelegate(&Instance(), &DebugBoard::_eventUpdate);
	}
	void DebugBoard::_release()
	{
	}
	void DebugBoard::_init()
	{
		const MyGUI::VectorWidgetPtr& root = MyGUI::LayoutManager::getInstance().loadLayout("debug_info.layout");
		if (root.size())
		{
			using namespace Graphic;
			RenderBase::GraphicCardCapability gcc =  GraphicSystem::Instance()->GetGraphicCardCapability();
			const RenderBase::DisplayMode& dm = Graphic::GraphicSystem::Instance()->GetMainViewPortWindow()->GetDisplayMode();

			m_mainWin = root.at(0)->findWidget("_Main");
			int height = m_mainWin->getHeight();
			m_mainWin->setPosition(0, dm.GetHeight() - height);

			m_mainWin->findWidget("CardName")->castType<MyGUI::TextBox>()->setCaption(gcc.mDriverName.AsCharPtr());
			m_mainWin->findWidget("API")->castType<MyGUI::TextBox>()->setCaption(gcc.mApiVersion.AsCharPtr());

			m_fps = m_mainWin->findWidget("FPS")->castType<MyGUI::TextBox>();
			m_fps->setCaption("");
		}
	}
	void DebugBoard::_eventUpdate(void* sender)
	{
		if (GUIServer::Instance()->IsOpen())
		{
			static float time = 0;
			static int count = 0;
			time += (float)GameTime::Instance()->GetFrameTime();
			++count;
			if (time > 1.5f)
			{
				Util::String temp = Util::String::FromInt((int)(count / time));
				m_fps->setCaption(temp.AsCharPtr());
				time = 0;
				count = 0;
			}
		}
	}
}