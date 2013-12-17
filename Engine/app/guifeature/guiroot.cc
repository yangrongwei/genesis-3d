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
#include "guifeature/guiroot.h"

#include "scriptfeature/script_general_manager.h"
#include "scriptfeature/inc/script_utility.h"
#include "scriptfeature/mono_script.h"
#include "scriptfeature/inc/script_fwd_decl.h"
#include "basegamefeature/managers/timesource.h"
namespace App
{

	const Util::String& GuiRoot::UIClassName = "GUIRoot";					//ui全局的类名
	const Util::String& GuiRoot::UINamespace = "ScriptGUI";					//所在的名字空间
	//const Util::String& GuiRoot::UIAssemblyName = s_cpScriptGUILibraryName;	//所在的Dll名字

	enum CSharpMethodIndex
	{
		CSharpMethodIndex_Begin = 0,
		CSharpMethodIndex_OnInit = CSharpMethodIndex_Begin,
		CSharpMethodIndex_OnWinSizeChange,
		CSharpMethodIndex_OnTick,
		CSharpMethodIndex_Count
	};
	struct CSharpMethod
	{
		char* Name;
		uint8 ParamCount;
	};
	static const CSharpMethod gCSharpMethod[] = 
	{
		{"onInit", 0},
		{"onWinSizeChange", 0},
		{"onTick", 1}
	};

	GuiRoot::GuiRoot()
		:m_rootObj(NULL)
	{

	}
	GuiRoot::~GuiRoot()
	{
		//mono_gchandle_free( m_rootRefID );
	}

	void GuiRoot::resetScriptMethods()
	{
		m_methods.Clear();
		for (int i = 0; i < CSharpMethodIndex_Count; ++i)
		{
			m_methods.Append(NULL);
		}
	}

	void GuiRoot::Init()
	{
		resetScriptMethods();
		ScriptGeneralManager* manager = ScriptGeneralManager::Instance();
		if (manager)
		{
			MonoClass* mono_class = manager->GetMonoClassByName("UserDefGUIRoot", "UserDefGUI", s_csUserDefCSharpLibName);//[2012/5/15 zhongdaohuan]前面两个参数没想好。
			MonoClass* parent_class = manager->GetMonoClassByName(UIClassName, UINamespace, s_csScriptGUILibraryName);//[2012/6/12 zhongdaohuan]
			n_assert(NULL != parent_class);
			if (NULL == mono_class)
			{
				mono_class = parent_class;
			}
			else
			{			

				mono_bool bParent = mono_class_is_subclass_of(mono_class, parent_class, true);
				if (c_iMonoBool_False == bParent)
				{
					mono_class = parent_class;
				}
			}

			MonoDomain* mono_domain = mono_domain_get();
			m_rootObj  = mono_object_new(mono_domain, mono_class);
			n_assert(NULL != m_rootObj);
			mono_runtime_object_init(m_rootObj);
			m_rootRefID = mono_gchandle_new ( m_rootObj, 1 );
			n_assert(NULL != m_rootObj);


			for (int i = CSharpMethodIndex_Begin; i < CSharpMethodIndex_Count; ++i)
			{
				MonoMethod* pMethod = mono_class_get_method_from_name( parent_class, 
					gCSharpMethod[i].Name, 
					gCSharpMethod[i].ParamCount );
				m_methods[i] = pMethod;
			}
		}
	}

	void GuiRoot::InitGuiScript()
	{
		if (m_methods[CSharpMethodIndex_OnInit])
		{
			Utility_MonoRuntimeInvoke( m_methods[CSharpMethodIndex_OnInit], m_rootObj, NULL );
		}
	}

	void GuiRoot::WinSizeChange()
	{
		if (m_methods[CSharpMethodIndex_OnWinSizeChange])
		{
			Utility_MonoRuntimeInvoke( m_methods[CSharpMethodIndex_OnWinSizeChange], m_rootObj, NULL );
		}
	}


	void GuiRoot::Tick(void* sender)
	{
        Math::float2 f2;
        
        
		f2.x() = (float)App::GameTime::Instance()->GetFrameTime();
		f2.y() = (float)App::GameTime::Instance()->GetTime();
		        
        static void* parame[1] = {0};
		parame[0] = (void*)(&f2);

		MonoObject* exc = NULL;
		if (m_methods[CSharpMethodIndex_OnTick])
		{
			Utility_MonoRuntimeInvoke( m_methods[CSharpMethodIndex_OnTick], NULL, parame );
		}
	}
}