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
#ifndef __DrawTextManager_H__
#define __DrawTextManager_H__

#include "guibase/utf16string.h"
#include "util/string.h"
#include "appframework/manager.h"
#include "core/singleton.h"

namespace App
{
	class StaticText;
	class SpriteBatch;
	class DrawTextManager: public Manager
	{
		__DeclareSubClass(DrawTextManager, App::Manager);
		__DeclareThreadSingleton(DrawTextManager);

	public:	

		DrawTextManager();
		~DrawTextManager();	

		/// called when attached to game server
		virtual void OnActivate();

		/// called when removed from game server
		virtual void OnDeactivate();

		/// called before frame by the game server
		virtual void OnBeginFrame();
		/// called per-frame by the game server
		virtual void OnFrame();
		/// called after frame by the game server
		virtual void OnEndFrame();

		IndexT		 AppendDrawText(const int& x, const int& y, const GuiBase::UTF16String& text);
		IndexT		 AppendDrawText(const int& x, const int& y, const Util::String& utStr);
		IndexT		 AppendDrawText(const int& x, const int& y, const Util::String& utStr, bool visible);

		void		 DisplayDrawText( const int& idx);
		void   		 HiddenDrawText( const int& idx);
		void		 SetTextVisible(int idx, bool visible);
		bool		 TextVisible(int idx) const;

		bool		 UpdateDrawText(const IndexT& idx,const Util::String& utStr);
		bool		 UpdateDrawTextPostion(const IndexT& idx, int x, int y);

		void		 RemoveDrawText(const Util::String& utStr);
		void		 RemoveDrawText(int idx);

		SizeT	     DrawTextSize();
		void		 SetFontSize(const SizeT& size);
		void		 SetFontName(const Util::String& name);
		void		 SetShaderName(const Util::String& path);
		void		 SetFontColor(const Math::float4& color);
		void		 UpdateFontPos(const IndexT& idx,const int& x,const int& y);
		void		 UpdateTextColor(const IndexT& idx,const Math::float4& color);
		void		 ShowStatistics(bool show);
		bool         IsShowStatistics();
	protected:
		static	void _Render();
		void		 _Init();
		bool		 _FindText(const int& x, const int& y, const GuiBase::UTF16String& text);
		IndexT		 _FindText(const GuiBase::UTF16String& text);
		void		 _RenderAll();
		GuiBase::UTF16String	_UtilStr_to_Utf16Str(const Util::String& utStr);

		

	private:
		Util::Dictionary< int, GPtr<StaticText> > mStaticText;
		//Util::Array< GPtr<StaticText> >	mStaticText;	
		GPtr<SpriteBatch>				mSpriteBatch;
		SizeT							mFontSize;
		Util::String					mFontName;
		Util::String					mShaderName;
		Math::float4					mFontColor;
		bool							mbStatisticsShow;
		Math::scalar                    mTotalTime;
		int								mTotalFrams;
		int								mOldFps;
		int								mFpsIndex;
		int								mSecondIndex;
		int								mThirdIndex;
		uint							mStaticTextIndex;
	};

	inline	void DrawTextManager::SetFontSize(const SizeT& size)
	{
		mFontSize = size;
	}
	inline 	void DrawTextManager::SetFontName(const Util::String& name)
	{
		mFontName = name;
	}
	inline void DrawTextManager::SetShaderName(const Util::String& path)
	{
		mShaderName = path;
	}
	inline void	DrawTextManager::SetFontColor(const Math::float4& color)
	{
		mFontColor = color;
	}
	inline void DrawTextManager::ShowStatistics(bool show)
	{
		mbStatisticsShow = show;
	}
	inline bool DrawTextManager::IsShowStatistics()
	{
		return mbStatisticsShow;
	}
	inline SizeT DrawTextManager::DrawTextSize()
	{
		return mStaticText.Size();
	}
}

#endif	