/*!
	@file
	@author		Albert Semenov
	@date		04/2009
*/
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
#ifndef __MYGUI_GENESIS_PLATFORM_H__
#define __MYGUI_GENESIS_PLATFORM_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_GenesisInput.h"
#include "MyGUI_GenesisTexture.h"
#include "MyGUI_GenesisVertexBuffer.h"
#include "MyGUI_GenesisRenderManager.h"
#include "MyGUI_GenesisDataManager.h"
#include "MyGUI_GenesisDiagnostic.h"
#include "MyGUI_GenesisTexture.h"
#include "MyGUI_LogManager.h"

#include "MyGUI_LastHeader.h"

namespace MyGUI
{

	class GenesisPlatform
	{
	public:
		GenesisPlatform() :
		  mIsInitialise(false)
		  {
			  mLogManager = new LogManager();
			  mRenderManager = new GenesisRenderManager();
			  mDataManager = new GenesisDataManager();
			  mInputManager = new GenesisInputManager();

		  }

		  ~GenesisPlatform()
		  {
			  assert(!mIsInitialise);
			  delete mRenderManager;
			  delete mDataManager;
			  delete mLogManager;
			  delete mInputManager;
		  }

		  void initialise( const std::string& _group, const std::string& _logName = MYGUI_PLATFORM_LOG_FILENAME)
		  {			

			  assert(!mIsInitialise);
			  mIsInitialise = true;
			  mRenderManager->setResolution(0, 0);
			  if (!_logName.empty())
				  LogManager::getInstance().createDefaultSource(_logName);

			  mRenderManager->initialise();
			  mDataManager->initialise(_group);
		  }

		  void shutdown()
		  {
			  assert(mIsInitialise);
			  mIsInitialise = false;

			  mRenderManager->shutdown();
			  mDataManager->shutdown();
		  }

		  GenesisRenderManager* getRenderManagerPtr()
		  {
			  assert(mIsInitialise);
			  return mRenderManager;
		  }

		  GenesisDataManager* getDataManagerPtr()
		  {
			  assert(mIsInitialise);
			  return mDataManager;
		  }

	private:
		bool mIsInitialise;
		GenesisRenderManager* mRenderManager;
		GenesisDataManager* mDataManager;
		GenesisInputManager* mInputManager;
		LogManager* mLogManager;
	};

} // namespace MyGUI

#endif // __MYGUI_GENESIS_PLATFORM_H__
