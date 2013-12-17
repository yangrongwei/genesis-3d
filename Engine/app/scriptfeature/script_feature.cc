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
#include "profilesystem/ProfileSystem.h"
#include "scriptfeature/inc/script_feature.h"
#include "scriptfeature/mono_script.h"
#include "scriptfeature/inc/script_instance.h"
#include "scriptfeature/inc/script_component.h"

namespace App
{
	__ImplementClass( App::ScriptFeature, 'SCSR', App::Feature );
	__ImplementImageSingleton( App::ScriptFeature );

	//------------------------------------------------------------------------
	ScriptFeature::ScriptFeature()
	{
		__ConstructImageSingleton;

		mFeatureName = "Script";
	}
	//------------------------------------------------------------------------
	ScriptFeature::~ScriptFeature()
	{
		for ( int i = 0; i<m_ScriptInstances.Size(); i++ )
		{
			for ( int j = 0; i<m_ScriptInstances[i].Size(); j++)
			{
				m_ScriptInstances[i][j] = NULL;
			}
			m_ScriptInstances[i].Clear();
		}
		m_ScriptInstances.Clear();
		__DestructImageSingleton;
	}
	//------------------------------------------------------------------------
	void ScriptFeature::OnActivate()
	{
		Feature::OnActivate();

		m_ScriptInstances.Reserve( 20 );
	}
	//------------------------------------------------------------------------
	void ScriptFeature::OnDeactivate()
	{
		m_ScriptInstances.Clear();
		m_pScriptComs.Clear();

		Feature::OnDeactivate();
	}
	//------------------------------------------------------------------------
	void ScriptFeature::OnBeginFrame()
	{
		PROFILER_ADDDTICKBEGIN(scriptsTime);
		Utility_ScriptRootTick();
#ifdef __GENESIS_EDITOR__ 
		//- because we can't call the onload fun in onactive() on editor side,so we've to do the onload here
		for( IndexT i=0; i < m_pScriptComs.Size(); ++i )
		{
			m_pScriptComs[i]->OnLoad_Editor();
		}
#endif 
		for( IndexT i=0; i < m_ScriptInstances.Size(); ++i )
		{

			for( IndexT j=0; j < m_ScriptInstances[i].Size(); ++j )
			{
				if ( m_ScriptInstances[i][j].isvalid() )
				{
					
					m_ScriptInstances[i][j]->OnBeginFrame();
				}
			}
		}
		PROFILER_ADDDTICKEND(scriptsTime);
	}
	//------------------------------------------------------------------------
	void ScriptFeature::OnFrame()
	{
		PROFILER_ADDDTICKBEGIN(scriptsTime);
		for( IndexT i=0; i < m_ScriptInstances.Size(); ++i )
		{
			for( IndexT j=0; j < m_ScriptInstances[i].Size(); ++j)
			{
				if (m_ScriptInstances[i][j].isvalid())
				{
					m_ScriptInstances[i][j]->OnFrame();
				}
			}
		}
		PROFILER_ADDDTICKEND(scriptsTime);
	}
	//------------------------------------------------------------------------
	void ScriptFeature::OnEndFrame()
	{
		PROFILER_ADDDTICKBEGIN(scriptsTime);
		for ( IndexT i=0; i<m_ScriptInstances.Size(); ++i )
		{

			for ( IndexT j=0; j<m_ScriptInstances[i].Size(); ++j )
			{
				if ( m_ScriptInstances[i][j].isvalid() )
				{
					m_ScriptInstances[i][j]->OnEndFrame();
				}
			}
		}
		PROFILER_ADDDTICKEND(scriptsTime);
	}
	//------------------------------------------------------------------------
	void ScriptFeature::OnStopped()
	{
		for ( IndexT i=0; i<m_ScriptInstances.Size(); ++i )
		{

			for ( IndexT j=0; j<m_ScriptInstances[i].Size(); ++j )
			{
				if ( m_ScriptInstances[i][j].isvalid() )
				{
					m_ScriptInstances[i][j]->OnStopped();
				}
			}
		}
		Utility_ScriptRootStop();
	}
	//------------------------------------------------------------------------
	void ScriptFeature::OnResumed()
	{
		for ( IndexT i=0; i<m_ScriptInstances.Size(); ++i )
		{

			for ( IndexT j=0; j<m_ScriptInstances[i].Size(); ++j )
			{
				if ( m_ScriptInstances[i][j].isvalid() )
				{
					m_ScriptInstances[i][j]->OnResumed();
				}
			}
		}
		Utility_ScriptRootResume();
	}
	//------------------------------------------------------------------------
	void ScriptFeature::AttachScriptInstances(const Util::Array< GPtr<ScriptInstance> > &scriptInstances)
	{
		IndexT found = m_ScriptInstances.FindIndex( scriptInstances );

		if ( found == InvalidIndex )
		{
			m_ScriptInstances.Append( scriptInstances );
		}
	}
	//------------------------------------------------------------------------
	void ScriptFeature::AttachScriptCom(App::ScriptComponent* pCom)
	{
		IndexT found = m_pScriptComs.FindIndex( pCom );

		if ( found==InvalidIndex )
		{
			m_pScriptComs.Append( pCom );
		}
	}

	void ScriptFeature::RemoveScriptInstances( const ScriptInstances& scriptInstances )
	{	
		IndexT found = m_ScriptInstances.FindIndex( scriptInstances );
		if( found!=InvalidIndex )
		{
			m_ScriptInstances.EraseIndex( found );
		}
	}

	void ScriptFeature::RemoveScriptCom( ScriptComponent* const pCom )
	{
		IndexT found = m_pScriptComs.FindIndex( pCom );
		if( found!=InvalidIndex )
		{
			m_pScriptComs.EraseIndex( found );
		}
	}

	void ScriptFeature::RemoveScript( ScriptComponent* const pCom, const ScriptInstances& scriptInstances )
	{
		RemoveScriptCom(pCom);
		RemoveScriptInstances(scriptInstances);
	}

	void ScriptFeature::AttachScript( ScriptComponent* const pCom, const ScriptInstances& scriptInstances )
	{
		AttachScriptCom(pCom);
		AttachScriptInstances(scriptInstances);
	}
}