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
#include "foundation/memory/memory.h"
#include "foundation/io/assignregistry.h"
#include "scriptfeature/mono_icall_registration.h"
#include "scriptfeature/script_general_manager.h"
#include "scriptfeature/mono_script_manager.h"
#include "scriptfeature/inc/script_utility.h"
#include "scriptfeature/mono_script.h"
#include "foundation/io/stream.h"
#include "foundation/io/ioserver.h"
#include "foundation/io/memorystream.h"
#include "foundation/io/iointerface.h"
#include "foundation/io/iointerfaceprotocol.h"

namespace App
{
	// - ScriptGeneralManager implement --------------------------------------------------------------------
	__ImplementClass( App::ScriptGeneralManager, 'SPGM', Core::RefCounted );
	__ImplementImageSingleton( App::ScriptGeneralManager );
	//------------------------------------------------------------------------
	static Util::Dictionary<MonoClassIndex,MonoClass*> s_dicMonoClassMap;
	//------------------------------------------------------------------------
	ScriptGeneralManager::~ScriptGeneralManager()
	{
		__DestructImageSingleton;
	}
	//------------------------------------------------------------------------
	TMonoScriptPtr ScriptGeneralManager::GetMonoScript( const Util::String& sClassName, 
														const Util::String& sNamespace, 
														const Util::String& sAssemblyName,
														const bool mem /*=false*/)
	{
		TMonoScriptPtr pMonoScript = m_pMonoScriptManager->Find( sClassName, sNamespace, sAssemblyName );
		if ( NULL!=pMonoScript )
		{
			return pMonoScript;
		}

		MonoClass* pMonoClass = GetMonoClassByName( sClassName, sNamespace, sAssemblyName );
		pMonoScript = MonoScript::Create();
		pMonoScript->Init( pMonoClass, sClassName, sNamespace, sAssemblyName, mem );
		
		if ( NULL==pMonoScript ||
			!pMonoScript->IsValid() )
		{
			return pMonoScript;
		}

		MonoScriptIndex key( sClassName, sNamespace, sAssemblyName );
		m_pMonoScriptManager->Add( key, pMonoScript );

		return pMonoScript;
	}
	//------------------------------------------------------------------------
	MonoClass* ScriptGeneralManager::GetMonoClassByName( const Util::String& sClassName, 
														const Util::String& sNamespace,
														const Util::String& sAssemblyName )
	{
		
		MonoClassIndex monoIdx( sClassName, sNamespace, sAssemblyName );
		IndexT idx = s_dicMonoClassMap.FindIndex( monoIdx );
		if ( InvalidIndex!=idx )
		{
			return s_dicMonoClassMap.ValueAtIndex( idx );
		}
		
		// - look up class in the image
		idx = m_dicImages.FindIndex( sAssemblyName );
		if ( InvalidIndex==idx )
		{
			return NULL;
		}

		MonoImage* pImage = m_dicImages.ValueAtIndex( idx );
		n_assert( NULL!=pImage );

		MonoClass* pMonoClass = mono_class_from_name( pImage, sNamespace.AsCharPtr(), sClassName.AsCharPtr() );
		if ( NULL!=pMonoClass )
		{
			s_dicMonoClassMap.Add( monoIdx, pMonoClass );
		}

		return pMonoClass;
	}
	//------------------------------------------------------------------------
	void ScriptGeneralManager::CreateSingleton( void )
	{
		ScriptGeneralManager::Create();
		ScriptGeneralManager::Instance()->AddRef();
	}
	//------------------------------------------------------------------------
	void ScriptGeneralManager::DestorySingleton( void )
	{
		ScriptGeneralManager::Instance()->Release();
	}
	//------------------------------------------------------------------------
	ScriptGeneralManager::ScriptGeneralManager()
		: m_dicImages()
		, m_pMonoScriptManager()
	{
		__ConstructImageSingleton
		MonoScriptManager* pMgr = MonoScriptManager::Create();
		n_assert( NULL!=pMgr );

		m_pMonoScriptManager.reset( pMgr );
	}

	//------------------------------------------------------------------------
	bool ScriptGeneralManager::IsDllLoaded( const Util::String& sDllName )
	{
		int idx = m_dicImages.FindIndex( sDllName );
		if ( InvalidIndex == idx )
		{
			return false;
		}

		return true;
	}
	//------------------------------------------------------------------------
	void ScriptGeneralManager::LoadAssemblies( bool needDebug )
	{
		// clear key(MonoCommonIndex)/value(MonoScript) collections from Mono 
		m_pMonoScriptManager->ClearScriptDic();		
		// clear the MomoImage records that have already loaded into Mono
		m_dicImages.Clear();
		// clear the Script(C#)definitions from Mono 
		s_dicMonoClassMap.Clear();

#ifndef __OSX__
		MonoDomain* pDomain = mono_domain_get();
		script_fatal_error( NULL != pDomain );
		MonoDomain* pRootDomain = mono_get_root_domain();
		script_fatal_error( NULL != pRootDomain );

		//-a child domain must hane been ceated before loading the assemblies;
		script_fatal_error( pDomain!=pRootDomain );
#endif
        
		int iAssemblyCount = sizeof(s_cAssemblies)/sizeof(AssemblyNameAndPath);
		for ( int ii=0; ii<iAssemblyCount; ii++ )
		{
			Util::String sPath = s_cAssemblies[ii].__pAssign;
			sPath += s_cAssemblies[ii].__pName;
			
			// - load the assemblies to memory first,so that mono won't lock it.


			GPtr<IO::Stream> srcStream = IO::IoServer::Instance()->ReadFile( sPath ); 
			if (!srcStream.isvalid())
				continue;

			srcStream->SetAccessMode( IO::Stream::ReadAccess ); 

			void* dllData = NULL;
			int	  dataSize = 0;
 			MonoImage* pImage = NULL;
			int status = 0;
			
			bool streamOpen = srcStream->Open();
			if ( streamOpen ) 
			{
				// read Dll : hard disk -> Memory --> Mono(MonoImage)
				dllData = srcStream->Map(); n_assert( dllData!=NULL );
				dataSize = srcStream->GetSize();

				pImage = mono_image_open_from_data_full ( dllData, dataSize, /*Copy data*/true, &status, false /* ref only*/ );
                script_fatal_error( pImage != NULL );

				// - now we need to load the mdb file by our self ,
				// because mono won't load it automatically if we let it load the image from memory
				if( needDebug )
				{
					Util::String sMdbPath = sPath;
					sMdbPath.Append( ".mdb" );

					GPtr<IO::Stream> srcMdbStream = IO::IoServer::Instance()->ReadFileFromDisk( sMdbPath.AsCharPtr() ); 
					if(srcMdbStream.isvalid())
					{
						srcMdbStream->SetAccessMode( IO::Stream::ReadAccess ); 

						if ( srcMdbStream->Open() )
						{
							int	  mdbSize = 0;
							const char* mdbData = NULL;

							mdbData =static_cast<const char*>( srcMdbStream->Map() ); n_assert( mdbData!=NULL );
							mdbSize = srcMdbStream->GetSize();

							mono_debug_open_image_from_memory( pImage, mdbData, mdbSize );
							srcMdbStream->Close();
						}
						else
						{
							n_warning( "mdb file not found or open failed" );
						}	
					}
					
		
				}

				// Load MonoImage here
				// Maybe you see the code upon the load of the mdb file is to read Dll from hard disk to Memory,
				// and then you want to put these flowing codes before loading the mdb file to make these codes
				// more clear.But, don't do this.
				// Because if function mono_assembly_load_from_full is executed before the load of mdb file ,mono
				// debugger will not work. So keep the code like this, keep it unclear. 
				MonoAssembly* pAssembly = mono_assembly_load_from_full ( pImage, sPath.AsCharPtr (), &status, false/* ref only*/ );
				script_fatal_error( pAssembly != NULL );

				if ( mono_assembly_get_image( pAssembly )!=pImage )
				{
					n_error( "this assemble has already been loaded" );
                    //n_printf( "this assemble has already been loaded" );
				}

				m_dicImages.Add( s_cAssemblies[ii].__pName, pImage );
				srcStream->Close();
			}
			else
			{
				Util::String warning = "ScriptGeneralManager::LoadAssemblies, dll not loaded,path:"+ sPath;
				n_printf( warning.AsCharPtr() );

				continue;
			}
		}

	}

}

