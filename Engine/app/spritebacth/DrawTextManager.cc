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
#ifdef __OSX__
#include "../../profilesystem/ProfileSystem.h"
#else
#include "profilesystem/ProfileSystem.h"
#endif
#include "spritebacth/statictext.h"
#include "spritebacth/spritebacth.h"
#include "MyGUI_UString.h"
#include "math/float2.h"
#include "../basegamefeature/managers/timesource.h"

#include "DrawTextManager.h"

#ifndef __ANDROID__
// TODO:make this code work in android
//#include "rendersystem\d3d9\RenderDeviceD3D9.h"
#endif


namespace App
{
	
	__ImplementClass(App::DrawTextManager, 'DTMG', App::Manager);
	__ImplementThreadSingleton(App::DrawTextManager);

	//------------------------------------------------------------------------
	DrawTextManager::DrawTextManager()
		:mbStatisticsShow(true)		
		,mTotalTime(0.0f)
		,mTotalFrams(0)
		,mOldFps(60)
		,mStaticTextIndex(0)
	{
		__ConstructThreadSingleton;
	}

	//------------------------------------------------------------------------
	DrawTextManager::~DrawTextManager()
	{
		__DestructThreadSingleton;

	}

	//------------------------------------------------------------------------
	void DrawTextManager::OnActivate()
	{
		Graphic::GraphicSystem::Instance()->SetFontCallBack(_Render);

		mSpriteBatch = SpriteBatch::Create();
		mSpriteBatch->SetShaderName(mShaderName);
		mStaticTextIndex = 0;		
		_Init();
	}
	//------------------------------------------------------------------------
	void DrawTextManager::OnDeactivate()
	{
		mStaticText.Clear();
		mStaticTextIndex = 0;
		mSpriteBatch = NULL;	

		Graphic::GraphicSystem::Instance()->SetFontCallBack(NULL);			
	}


	//------------------------------------------------------------------------
	void DrawTextManager::OnBeginFrame()
	{
		
	}
	//------------------------------------------------------------------------
	void DrawTextManager::OnFrame()
	{
		//Math::scalar frameTime = (Math::scalar)App::GameTime::Instance()->GetFrameTime();
		//mTotalTime += frameTime;
		//mTotalFrams ++;

		////update 
		//if ( mTotalTime >= 1.f )
		//{
		//	Util::String strFps,strTriVertex,strRTDrawCall;
		//	strFps.Format("FPS: %d",
		//		(int)((mTotalFrams*0.1 + mOldFps*0.9)/1));

		//	strTriVertex.Format("Triangles:%d  Vertexes:%d",
		//		PROFILER_GETDEVICESTATEVAL(tris),
		//		PROFILER_GETDEVICESTATEVAL(verts)
		//		);

		//	strRTDrawCall.Format("RenderTargets:%d  DrawCalls:%d",
		//		PROFILER_GETDEVICESTATEVAL(RenderTargetNum),
		//		PROFILER_GETDEVICESTATEVAL(calls));

		//	mOldFps = (int)((mTotalFrams*0.1 + mOldFps*0.9)/1);
		//	mTotalTime = 0.0f;
		//	mTotalFrams = 0;
		//	if(mbStatisticsShow)
		//	{
		//		UpdateDrawText(mFpsIndex,strFps);
		//		UpdateDrawText(mSecondIndex,strTriVertex);
		//		UpdateDrawText(mThirdIndex,strRTDrawCall);
		//	}
		//	
		//}

		//
	}
	//------------------------------------------------------------------------
	void DrawTextManager::UpdateTextColor(const IndexT& idx,const Math::float4& color)
	{
		if (mStaticText.Contains(idx))
		{
			mStaticText[idx]->SetTextColor(color);
		}
	}
	//------------------------------------------------------------------------
	void DrawTextManager::UpdateFontPos(const IndexT& idx,const int& x,const int& y)
	{
		if (mStaticText.Contains(idx))
		{
			mStaticText[idx]->SetPosition(Math::float2((float)x,(float)y));
		}
	}
	//------------------------------------------------------------------------
	void DrawTextManager::OnEndFrame()
	{

	}
	//------------------------------------------------------------------------
	IndexT DrawTextManager::AppendDrawText(const int& x, const int& y, const Util::String& utStr)
	{
		UTF16String ut16Str = _UtilStr_to_Utf16Str(utStr);
		return AppendDrawText(x,y,ut16Str);
	}
	//------------------------------------------------------------------------
	IndexT DrawTextManager::AppendDrawText(const int& x, const int& y, const GuiBase::UTF16String& text)
	{
		GPtr<StaticText> pStaticText = StaticText::Create();
		pStaticText->SetCharSize(mFontSize);
		pStaticText->SetFont(mFontName);
		pStaticText->SetTextColor(mFontColor);
		pStaticText->SetText(text);
		pStaticText->SetPosition(Math::float2((Math::scalar)x, (Math::scalar) y) );

		mStaticText.Add(mStaticTextIndex, pStaticText);
		++mStaticTextIndex;
		return mStaticTextIndex - 1;
	}
	
	IndexT DrawTextManager::AppendDrawText(const int& x, const int& y, const Util::String& utStr, bool visible)
	{
		IndexT index = AppendDrawText(x, y, utStr);
		mStaticText[index]->SetVisible(visible);
		return index;
	}
	
	//------------------------------------------------------------------------
	void DrawTextManager::RemoveDrawText(const Util::String& utStr)
	{
		UTF16String ut16Str = _UtilStr_to_Utf16Str(utStr);
		IndexT idx =  _FindText(ut16Str);
		if (idx != -1)
		{
			mStaticText.Erase(idx);
		}
	}
	void DrawTextManager::RemoveDrawText(int idx)
	{
		if (mStaticText.Contains(idx))
		{
			mStaticText.Erase(idx);
		}
	}
	//------------------------------------------------------------------------
	void DrawTextManager::DisplayDrawText( const int& idx)
	{
		if (mStaticText.Contains(idx))
		{
			mStaticText[idx]->SetVisible(true);
		}
	}

	//-------------------------------------------------------------------------
	void DrawTextManager::HiddenDrawText( const int& idx)
	{
		if (mStaticText.Contains(idx))
		{
			mStaticText[idx]->SetVisible(false);
		}
	}

	//------------------------------------------------------------------------
	void DrawTextManager::SetTextVisible(int idx, bool visible)
	{
		if (mStaticText.Contains(idx))
		{
			mStaticText[idx]->SetVisible(visible);
		}
	}

	//------------------------------------------------------------------------
	bool DrawTextManager::TextVisible(int idx) const
	{
		if (mStaticText.Contains(idx))
		{
			return mStaticText[idx]->GetVisible();
		}
		return false;
	}

	//------------------------------------------------------------------------
	bool DrawTextManager::UpdateDrawText(const IndexT& idx,const Util::String& utStr)
	{
		if (mStaticText.Contains(idx))
		{
			UTF16String ut16Str = _UtilStr_to_Utf16Str(utStr);
			GPtr<StaticText> pStaticText = mStaticText[idx];
			pStaticText->SetText(ut16Str);
			return true;
		}

		return false;
	}

	//------------------------------------------------------------------------
	bool DrawTextManager::UpdateDrawTextPostion(const IndexT& idx, int x, int y)
	{
		if (mStaticText.Contains(idx))
		{
			mStaticText[idx]->SetPosition(Math::float2((Math::scalar)x, (Math::scalar) y));
			return true;
		}
		return false;
	}

	//------------------------------------------------------------------------
	void DrawTextManager::_Init()
	{
		// set font info
		SetFontSize(12);
		SetFontColor(Math::float4(1.f,1.f,1.f,1.f));
		//mFpsIndex	 = AppendDrawText(FPSPOSX,FPSPOSY,"Fps:");
		//mSecondIndex = AppendDrawText(TriVertPOSX,TriVertPOSY,"Triangles:");
		//mThirdIndex  = AppendDrawText(RTDrawPOSX,RTDrawPOSY,"RenderTargets:");

		SetFontSize(12);
	}
	//------------------------------------------------------------------------
	IndexT DrawTextManager::_FindText( const GuiBase::UTF16String& text)
	{
		Util::Dictionary< int, GPtr<StaticText> >::Iterator itBegin = mStaticText.Begin();
		Util::Dictionary< int, GPtr<StaticText> >::Iterator itEnd = mStaticText.End();
		for (; itBegin != itEnd; ++itBegin)
		{
			if (text == itBegin->Value()->GetText())
			{
				return itBegin->Key();
			}
		}
		return -1;
	}
	//------------------------------------------------------------------------
	bool DrawTextManager::_FindText(const int& x, const int& y, const GuiBase::UTF16String& text)
	{
		Util::Dictionary< int, GPtr<StaticText> >::Iterator itBegin = mStaticText.Begin();
		Util::Dictionary< int, GPtr<StaticText> >::Iterator itEnd = mStaticText.End();
		for (; itBegin != itEnd; ++itBegin)
		{
			GPtr<StaticText> pStaticText = itBegin->Value();
			Math::float2 f2 = pStaticText->GetPosition();
			int nX = (int)f2.x();
			int nY = (int)f2.y();
			if ( nX == x && nY == y && text == pStaticText->GetText() )
			{
				return true;
			}	
		}

		return false;
	}
	//------------------------------------------------------------------------
	void DrawTextManager::_RenderAll()
	{			
		if(! mbStatisticsShow)
		{
			return;
		}

		Util::Dictionary< int, GPtr<StaticText> >::Iterator itBegin = mStaticText.Begin();
		Util::Dictionary< int, GPtr<StaticText> >::Iterator itEnd = mStaticText.End();
		for (; itBegin != itEnd; ++itBegin)
		{
			GPtr<StaticText> pStaticText = itBegin->Value();
			int i = itBegin->Key();
			if( pStaticText->GetVisible())
			{
				pStaticText->Flush();

				mSpriteBatch->Begin();
				pStaticText->Render(*mSpriteBatch);
				mSpriteBatch->End();
			}
		}
	}

	//------------------------------------------------------------------------
	//static fun
	void DrawTextManager::_Render()
	{
		DrawTextManager::Instance()->_RenderAll();
	}
	//------------------------------------------------------------------------
	GuiBase::UTF16String DrawTextManager::_UtilStr_to_Utf16Str(const Util::String& utStr)
	{
		MyGUI::UString str(utStr.Get());
		GuiBase::UTF16String ut16Str((GuiBase::UTF16*)str.asWStr_c_str()); 
		return ut16Str;
	}


}
