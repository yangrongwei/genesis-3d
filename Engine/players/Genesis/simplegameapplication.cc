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
#include "simplegameapplication.h"

namespace Genesis
{
	__ImplementThreadSingleton(DemoPublishGameApplication);
	//------------------------------------------------------------------------------
	DemoPublishGameApplication::DemoPublishGameApplication()
		: mWnd( 0 )
		, mExternWnd( 0 )
		, m_loaderData()
	{
		__ConstructThreadSingleton;
	}
	//------------------------------------------------------------------------------
	DemoPublishGameApplication::~DemoPublishGameApplication()
	{
		__DestructThreadSingleton;
		if (this->IsOpen())
		{
			this->Close();
		}
	}
	//------------------------------------------------------------------------------
	/**
	*/
	void DemoPublishGameApplication::setupGameFeatures()
	{
		GameApplication::setupGameFeatures();
	}

	//------------------------------------------------------------------------------
	/**
	Cleanup all added game features
	*/
	void DemoPublishGameApplication::cleanupGameFeatures()
	{   
		GameApplication::cleanupGameFeatures();
	}
	//------------------------------------------------------------------------------
	/**
	*/
	bool DemoPublishGameApplication::Open()
	{
		return App::GameApplication::Open();
	}
	//------------------------------------------------------------------------
	void DemoPublishGameApplication::Close()
	{
		App::GameApplication::Close();
	}
	//------------------------------------------------------------------------
	void DemoPublishGameApplication::setupProjectAssigns()
	{
		Super::setupProjectAssigns();

		IO::AssignRegistry* pAssignRegistry = IO::AssignRegistry::Instance();
		Util::String sysDir = m_loaderData.sSystemDir;
		if (sysDir.IsValid())
		{
			pAssignRegistry->SetAssign(IO::Assign("sys",sysDir));
		}
		Util::String shdDir = m_loaderData.sShaderDir;
		if (shdDir.IsValid())
		{
			pAssignRegistry->SetAssign(IO::Assign("shd",shdDir));
		}
	}
} // namespace Tools
