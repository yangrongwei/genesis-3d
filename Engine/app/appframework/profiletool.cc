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
#include "profiletool.h"
#include "inputfeature/inputfeature.h"
#include "input/inputkeyboard.h"
#include "profilesystem/ProfileSystem.h"
#include "basegamefeature/managers/timesource.h"
#include "spritebacth/DrawTextManager.h"
namespace App
{
#ifdef __PROFILER__
	static Profile::DeviceStats gDeviceStas;
	static Profile::TickStats gTickStats;
	void Profiler::_Present()
	{
		PROFILER_COPYDEVICESTATS(gDeviceStas);
		PROFILER_COPYTICKSTATS(gTickStats);
	}
#	define PROFILER_GETVALUE(Stats, Value) Stats.Value
#	define PROFILER_TIMEVALUE(Stats, Value) (float)( ( (double)PROFILER_GETVALUE(Stats, Value) ) / 1000.0 ) // 1000.0f
#else
#	define PROFILER_GETVALUE(Stats, Value) 0
#	define PROFILER_TIMEVALUE(Stats, Value) 0.0f
#endif


	int Profiler::GetDrawCalls()
	{
		return PROFILER_GETVALUE(gDeviceStas, calls);
	}

	int Profiler::GetTris()
	{
		return PROFILER_GETVALUE(gDeviceStas, tris);
	}

	int Profiler::GetVerts()
	{
		return PROFILER_GETVALUE(gDeviceStas, verts);
	}

	int Profiler::GetTrisSent()
	{
		return PROFILER_GETVALUE(gDeviceStas, trisSent);
	}

	int Profiler::GetRenderTargets()
	{
		return PROFILER_GETVALUE(gDeviceStas, renderTargetNum);
	}

	int Profiler::GetTextures()
	{
		return PROFILER_GETVALUE(gDeviceStas, textureNum);
	}

	int Profiler::GetVideoRam()
	{
		return PROFILER_GETVALUE(gDeviceStas, videoRam);
	}

	int Profiler::GetTexRam()
	{
		return PROFILER_GETVALUE(gDeviceStas, texRam);
	}

	int Profiler::GetVBORam()
	{
		return PROFILER_GETVALUE(gDeviceStas, vboRam);
	}

	int Profiler::GetFBORam()
	{
		return PROFILER_GETVALUE(gDeviceStas, fboRam);
	}

	float Profiler::GetParticlesTime()
	{
		return PROFILER_TIMEVALUE(gTickStats, particlesTime);
	}

	float Profiler::GetAnimationsTime()
	{
		return PROFILER_TIMEVALUE(gTickStats, animationsTime);
	}

	float Profiler::GetScriptsTime()
	{
		return PROFILER_TIMEVALUE(gTickStats, scriptsTime);
	}

	float Profiler::GetPhysicsTime()
	{
		return PROFILER_TIMEVALUE(gTickStats, physicsTime);
	}

	float Profiler::GetSoundsTime()
	{
		return PROFILER_TIMEVALUE(gTickStats, soundsTime);
	}

	float Profiler::GetDrawTime()
	{
		return PROFILER_TIMEVALUE(gTickStats, drawTime);
	}

	float Profiler::GetPostTime()
	{
		return PROFILER_TIMEVALUE(gTickStats, postTime);
	}


	static int gXBegin = 30;
	static int gYBegin = 30;
	static int gLineHeight = 15;

	__ImplementClass(App::ProfileManager, 'PFMG', App::Manager);
	__ImplementThreadSingleton(App::ProfileManager);

	//------------------------------------------------------------------------
	ProfileManager::ProfileManager()
		:mTotalTime(0.0f)
		,mTotalFrams(0)
		,mFps(60)
		,mShortcutKey(true)
	{
		__ConstructThreadSingleton;
#ifdef __WIN32__
		mStatVisArray[SV_Base] = true;
		mStatVisArray[SV_Advanced] = false;
		mStatVisArray[SV_TickTime] = false;
#else
		mStatVisArray[SV_Base] = true;
		mStatVisArray[SV_Advanced] = true;
		mStatVisArray[SV_TickTime] = true;
#endif



		Memory::Clear(mVisibleFunc, sizeof(mVisibleFunc));

		mVisibleFunc[SV_Base] = &ProfileManager::SetBaseStatsVisible;
		mVisibleFunc[SV_Advanced] = &ProfileManager::SetAdvancedVisible;
		mVisibleFunc[SV_TickTime] = &ProfileManager::SetTickTimeVisible;
	}

	//------------------------------------------------------------------------
	ProfileManager::~ProfileManager()
	{
		__DestructThreadSingleton;

	}

	//------------------------------------------------------------------------
	void ProfileManager::resetView()
	{
		DrawTextManager* mgr = DrawTextManager::Instance();
		int beginX = gXBegin;
		int beginY = gYBegin;
		for (int st = Stat_Begin; st < Stat_Count; ++st)
		{
			if (mStatTexts[st].textID >= 0)
			{
				if (mgr->TextVisible(mStatTexts[st].textID))
				{
					mgr->UpdateDrawTextPostion(mStatTexts[st].textID, beginX, beginY);
					beginY += gLineHeight;
				}
			}
			else
			{
				beginY += gLineHeight;
			}
		}
	}


	void ProfileManager::SetBaseStatsVisible(bool visible)
	{
		mStatVisArray[SV_Base] = visible;
		DrawTextManager* mgr = DrawTextManager::Instance();
		for (int st = Stat_BaseBegin; st < Stat_BaseEnd; ++st)
		{
			mgr->SetTextVisible(mStatTexts[st].textID, visible);
		}
		resetView();
	}

	void ProfileManager::SetAdvancedVisible(bool visible)
	{
		mStatVisArray[SV_Advanced] = visible;
		DrawTextManager* mgr = DrawTextManager::Instance();
		for (int st = Stat_AdvancedBegin; st < Stat_AdvancedEnd; ++st)
		{
			mgr->SetTextVisible(mStatTexts[st].textID, visible);
		}
		resetView();
	}

	void ProfileManager::SetTickTimeVisible(bool visible)
	{
		mStatVisArray[SV_TickTime] = visible;
		DrawTextManager* mgr = DrawTextManager::Instance();
		for (int st = Stat_TickTimeBegin; st < Stat_TickTimeEnd; ++st)
		{
			mgr->SetTextVisible(mStatTexts[st].textID, visible);
		}
		resetView();
	}



	//------------------------------------------------------------------------
	void ProfileManager::OnActivate()
	{
		DrawTextManager* mgr = DrawTextManager::Instance();

		mStatTexts.Resize(Stat_Count, StatText());
		for (int st = Stat_Begin; st < Stat_Count; ++st)
		{
			mStatTexts[st].type = (StatType)st;
		}
#ifndef __GENESIS_EDITOR__
		mStatTexts[Stat_Explain].textID = mgr->AppendDrawText(0, 0,"Control: F9", mStatVisArray[SV_Base]);
#endif		

		mStatTexts[Stat_Fps].textID = mgr->AppendDrawText(0, 0,"Fps:", mStatVisArray[SV_Base]);
		mStatTexts[Stat_Triangles].textID = mgr->AppendDrawText(0, 0,"Triangles:", mStatVisArray[SV_Base]);
		mStatTexts[Stat_Vertices].textID = mgr->AppendDrawText(0, 0,"Vertices:", mStatVisArray[SV_Base]);

		mStatTexts[Stat_Textures].textID = mgr->AppendDrawText(0, 0,"Textures:", mStatVisArray[SV_Advanced]);
		mStatTexts[Stat_RenderTargets].textID = mgr->AppendDrawText(0, 0,"RenderTargets:", mStatVisArray[SV_Advanced]);
		mStatTexts[Stat_VideoRam].textID = mgr->AppendDrawText(0, 0,"Video Ram:", mStatVisArray[SV_Advanced]);
		mStatTexts[Stat_TextureRam].textID = mgr->AppendDrawText(0, 0,"Texture Ram:", mStatVisArray[SV_Advanced]);
		mStatTexts[Stat_VBORam].textID = mgr->AppendDrawText(0, 0,"VBO Ram:", mStatVisArray[SV_Advanced]);
		mStatTexts[Stat_FBORam].textID = mgr->AppendDrawText(0, 0,"FBO Ram:", mStatVisArray[SV_Advanced]);

		mStatTexts[Stat_RenderTick].textID = mgr->AppendDrawText(0, 0,"Render Time:", mStatVisArray[SV_TickTime]);
		mStatTexts[Stat_PostTick].textID = mgr->AppendDrawText(0, 0,"Post Time:", mStatVisArray[SV_TickTime]);

		mStatTexts[Stat_ScriptTick].textID = mgr->AppendDrawText(0, 0,"Script Time:", mStatVisArray[SV_TickTime]);
		mStatTexts[Stat_PhysicsTick].textID = mgr->AppendDrawText(0, 0,"Physics Time:", mStatVisArray[SV_TickTime]);
		mStatTexts[Stat_ParticleTick].textID = mgr->AppendDrawText(0, 0,"Particle Time:", mStatVisArray[SV_TickTime]);
		mStatTexts[Stat_AnimationTick].textID = mgr->AppendDrawText(0, 0,"Animation Time:", mStatVisArray[SV_TickTime]);


		resetView();
	}
	//------------------------------------------------------------------------
	void ProfileManager::OnDeactivate()
	{
		DrawTextManager* mgr = DrawTextManager::Instance();
		for (int st = Stat_Begin; st < Stat_Count; ++st)
		{
			if(mStatTexts[st].textID >= 0 )
			{
				mgr->RemoveDrawText(mStatTexts[st].textID);
				mStatTexts[st] = StatText();
			}
		}
	}


	//------------------------------------------------------------------------
	void ProfileManager::OnBeginFrame()
	{

	}
	//------------------------------------------------------------------------
	void ProfileManager::OnFrame()
	{

		if (mShortcutKey)
		{
#ifdef __WIN32__
			const GPtr<Input::InputKeyboard>& keyboard = App::InputFeature::Instance()->GetInputServer()->GetDefaultKeyboard();
			if (keyboard->KeyUp(Input::InputKey::F9))
			{
				int i = 0;
				while(i < SV_Count)
				{
					if (!mStatVisArray[i])
					{
						break;
					}
					++i;
				}
				if (i < SV_Count)
				{
					(this->*mVisibleFunc[i])(true);
				}
				else
				{
					for (int j = 0; j < SV_Count; ++j)
					{
						(this->*mVisibleFunc[j])(false);
					}
				}
			}
#endif
		}


		mTotalTime += (Math::scalar)App::GameTime::Instance()->GetFrameTime();
		++mTotalFrams;

		//update 
		if ( mTotalTime > 1.f )
		{
			DrawTextManager* mgr = DrawTextManager::Instance();
			mFps = (mTotalFrams / mTotalTime) * 0.9f + mFps * 0.1f;

			mTotalTime = 0.0f;
			mTotalFrams = 0;
			if (mStatVisArray[SV_Base])
			{
				Util::String strFps, strTri, strVert, strTex, strTar;
				strFps.Format("FPS: %d", (int)mFps);
				strTri.Format("Triangles: %d", Profiler::GetTris());
				strVert.Format("Vertices: %d", Profiler::GetVerts());


				mgr->UpdateDrawText(mStatTexts[Stat_Fps].textID, strFps);
				mgr->UpdateDrawText(mStatTexts[Stat_Triangles].textID, strTri);
				mgr->UpdateDrawText(mStatTexts[Stat_Vertices].textID, strVert);

			}

			if (mStatVisArray[SV_Advanced])
			{
				Util::String strTexs, strTar;
				strTexs.Format("Textures:%d", Profiler::GetTextures());
				strTar.Format("RenderTargets:%d", Profiler::GetRenderTargets());
				mgr->UpdateDrawText(mStatTexts[Stat_Textures].textID, strTexs);
				mgr->UpdateDrawText(mStatTexts[Stat_RenderTargets].textID, strTar);

				Util::String strVid, strTex, strVbo, strFbo;
				strVid.Format("Video Ram: %.3f", ((float)Profiler::GetVideoRam()) / (1024.0f * 1024.0f));
				strTex.Format("Texture Ram: %.3f", ((float)Profiler::GetTexRam()) / (1024.0f * 1024.0f));
				strVbo.Format("VBO Ram: %.3f", ((float)Profiler::GetVBORam()) / (1024.0f * 1024.0f));
				strFbo.Format("FBO Ram: %.3f", ((float) Profiler::GetFBORam()) / (1024.0f * 1024.0f));

				mgr->UpdateDrawText(mStatTexts[Stat_VideoRam].textID, strVid);
				mgr->UpdateDrawText(mStatTexts[Stat_TextureRam].textID, strTex);
				mgr->UpdateDrawText(mStatTexts[Stat_VBORam].textID, strVbo);
				mgr->UpdateDrawText(mStatTexts[Stat_FBORam].textID, strFbo);
			}

			if (mStatVisArray[SV_TickTime])
			{
				Util::String strPar, strAni, strScr, strPhy, strRen, strPos;
				strScr.Format("Script Time: %.3f", Profiler::GetScriptsTime());
				strPhy.Format("Physics Time: %.3f", Profiler::GetPhysicsTime());
				strPar.Format("Particle Time: %.3f", Profiler::GetParticlesTime());
				strAni.Format("Animation Time: %.3f", Profiler::GetAnimationsTime());
				strRen.Format("Render Time: %.3f", Profiler::GetDrawTime());
				strPos.Format("Post Time: %.3f", Profiler::GetPostTime());

				mgr->UpdateDrawText(mStatTexts[Stat_RenderTick].textID, strRen);
				mgr->UpdateDrawText(mStatTexts[Stat_PostTick].textID, strPos);
				mgr->UpdateDrawText(mStatTexts[Stat_ScriptTick].textID, strScr);
				mgr->UpdateDrawText(mStatTexts[Stat_PhysicsTick].textID, strPhy);
				mgr->UpdateDrawText(mStatTexts[Stat_ParticleTick].textID, strPar);
				mgr->UpdateDrawText(mStatTexts[Stat_AnimationTick].textID, strAni);

			}
		}
	}

	//------------------------------------------------------------------------
	void ProfileManager::OnEndFrame()
	{

	}
}