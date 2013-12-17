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
#ifndef __profile_tool_H__
#define __profile_tool_H__
#include "profilesystem/ProfileDef.h"
#include "appframework/manager.h"
#include "core/singleton.h"

namespace App
{
	class Profiler
	{
	public:
		static int GetDrawCalls();
		static int GetTris();
		static int GetVerts();
		static int GetTrisSent();

		static int GetRenderTargets();
		static int GetTextures();

		//unit : byte.
		static int GetVideoRam();
		static int GetTexRam();
		static int GetVBORam();
		static int GetFBORam();

		//unit : millisecond.
		static float GetParticlesTime();
		static float GetAnimationsTime();
		static float GetScriptsTime();
		static float GetPhysicsTime();
		static float GetSoundsTime();
		static float GetDrawTime();
		static float GetPostTime();


#ifdef __PROFILER__
		static void _Present();
#endif
	};

#ifdef __PROFILER__
#	define PROFILE_PRESENT() App::Profiler::_Present()
#else
#	define PROFILE_PRESENT()
#endif

	class ProfileManager: public Manager
	{
		__DeclareSubClass(ProfileManager, App::Manager);
		__DeclareThreadSingleton(ProfileManager);

	public:	
		ProfileManager();
		~ProfileManager();	

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

		void SetShortcutKeyEnable(bool enable);
		bool GetShortcutKeyEnable() const;

		void SetBaseStatsVisible(bool visible);
		bool GetBaseStatsVisible() const;

		void SetAdvancedVisible(bool visible);
		bool GetAdvancedVisible() const;

		void SetTickTimeVisible(bool visible);
		bool GetTickTimeVisible() const;
	private:
		typedef void (ProfileManager::*VisibleFunc)(bool);
		void resetView();
		enum StatType//Statistic
		{
			Stat_Unknown = -1,
			Stat_Begin = 0,
			Stat_BaseBegin = Stat_Begin,

			Stat_Explain  = Stat_Begin,
			Stat_Fps,
			Stat_Triangles,
			Stat_Vertices,			
			Stat_BaseEnd,

			Stat_AdvancedBegin,
			Stat_Textures = Stat_AdvancedBegin,
			Stat_RenderTargets,
			Stat_VideoRam,
			Stat_TextureRam,
			Stat_VBORam,
			Stat_FBORam,
			Stat_AdvancedEnd,

			Stat_TickTimeBegin,
			Stat_RenderTick = Stat_TickTimeBegin,
			Stat_PostTick,
			Stat_ScriptTick,
			Stat_PhysicsTick,
			Stat_ParticleTick,
			Stat_AnimationTick,
			Stat_TickTimeEnd,

			Stat_Count,
		};

		enum StatVis
		{
			SV_Base,
			SV_Advanced,
			SV_TickTime,
			SV_Count,
		};

		struct StatText 
		{
			StatType type;
			int textID;
			inline StatText()
				:type(Stat_Unknown)
				,textID(-1)
			{

			}
		};

		typedef Util::Array<StatText> StatTexts;

		StatTexts mStatTexts;
		Math::scalar                    mTotalTime;
		int								mTotalFrams;
		float							mFps;
		VisibleFunc						mVisibleFunc[SV_Count];	
		bool							mStatVisArray[SV_Count];
		bool							mShortcutKey;

	};

	inline void ProfileManager::SetShortcutKeyEnable(bool enable) 
	{
		mShortcutKey = enable;
	}

	inline bool ProfileManager::GetShortcutKeyEnable() const
	{
		return mShortcutKey;
	}

	inline bool ProfileManager::GetBaseStatsVisible() const
	{
		return mStatVisArray[SV_Base];
	}

	inline bool ProfileManager::GetAdvancedVisible() const
	{
		return mStatVisArray[SV_Advanced];
	}

	inline bool ProfileManager::GetTickTimeVisible() const
	{
		return mStatVisArray[SV_TickTime];
	}
}


#endif //__profile_tool_H__
