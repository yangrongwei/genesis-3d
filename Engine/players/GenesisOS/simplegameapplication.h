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

#ifndef _iOSSimpleGameApplication_H_
#define  _iOSSimpleGameApplication_H_

#include "appframework/gameapplication.h"
#include "simplegamestatehandler.h"
#include "tools/WebJetLoader/WebJetLoaderData.h"

namespace iOSGame
{

	class iOSGameApplication : public App::GameApplication
	{
		typedef App::GameApplication Super;
		__DeclareThreadSingleton(iOSGameApplication);   
	public:
		/// constructor
		iOSGameApplication();
		/// destructor
		~iOSGameApplication();
		/// open the application
		virtual bool Open();
		/// close application
		virtual void Close( void );

		virtual void SetAppDic(const Util::String& dic);

		virtual Util::String GetAppDicOnMobile();
	protected:
		/// setup game features
		virtual void SetupGameFeatures();
		/// cleanup game features
		virtual void CleanupGameFeatures(); 

	private:
		Util::String mAppDic;

	};
	inline void iOSGameApplication::SetAppDic(const Util::String& dic)
	{
		mAppDic = dic; 
	}
} 




#endif