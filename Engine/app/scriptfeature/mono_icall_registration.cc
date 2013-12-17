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
#include "app/scriptfeature/mono_icall_registration.h"

namespace App
{
	// - declare register function here!
	void ICallReg_ScriptRuntime_Actor( void );
	void ICallReg_ScriptRuntime_Application( void );
	void ICallReg_ScriptRuntime_ScriptableClass( void );
	void ICallReg_ScriptRuntime_AnimationComponent( void );
	void ICallReg_ScriptRuntime_Input( void );
    void ICallReg_ScriptRuntime_InAppPurchase(void);
	void ICallReg_ScriptRuntime_RenderComponent(void);
	void ICallReg_ScriptRuntime_MeshRenderComponent( void );
	void ICallReg_ScriptRuntime_ProjectorRenderComponent( void );
	void ICallReg_ScriptRuntime_MeshComponent( void );
	void ICallReg_ScriptRuntime_SkeletonComponent( void );

	void ICallReg_ScriptRuntime_ParticleSystem( void );
	void ICallReg_ScriptRuntime_ParticleRenderComponent( void );
	void ICallReg_ScriptRuntime_IntersectWorld( void );
	void ICallReg_ScriptRuntime_ActorManager( void );
		
	void ICallReg_ScriptRuntime_Camera(void);
	void ICallReg_ScriptRuntime_CameraComponent( void );
	void ICallReg_ScriptRuntime_LightComponent( void );
	void ICallReg_ScriptRuntime_Util( void );
    void ICallReg_ScriptRuntime_ScriptComponent( void );
	void ICallReg_ScriptRuntime_Debug( void );
	void ICallReg_ScriptRuntime_XmlReader( void );
	void ICallReg_ScriptRuntime_IO( void);
	void ICallReg_ScriptRuntime_XmlWriter( void );

	void ICallReg_ScriptRuntime_PhysicsScene( void );
	void ICallReg_ScriptRuntime_PhysicsShape( void );
	void ICallReg_ScriptRuntime_PhysicsBoxShape( void );
	void ICallReg_ScriptRuntime_PhysicsSphere( void );
	void ICallReg_ScriptRuntime_PhysicsCapsuleShape( void );
	void ICallReg_ScriptRuntime_PhysicsMeshShape( void );
	void ICallReg_ScriptRuntime_PhysicsBodyComponent( void );
	
	void ICallReg_ScriptRuntime_Component( void );

	void ICallReg_ScriptRuntime_SoundSource( void );
	void ICallReg_ScriptRuntime_SoundFilter( void );
	void ICallReg_ScriptRuntime_SoundListener(void);
	void ICallReg_ScriptRuntime_SoundLowPassFilterComponent( void );
	void ICallReg_ScriptRuntime_SoundEchoFilterComponent( void );
	void ICallReg_ScriptRuntime_SoundReverbFilterComponent( void );
	void ICallReg_ScriptRuntime_Scene( void );
	void ICallReg_ScriptRuntime_SpriteRenderComponent( void );
	//gui
	void ICallReg_ScriptGUI_GUI();
	void ICallReg_ScriptGUI_Widget();
	void ICallReg_ScriptGUI_TextBox();
	void ICallReg_ScriptGUI_ScrollBar();
	void ICallReg_ScriptGUI_EditBox();
	void ICallReg_ScriptGUI_Button();
	void ICallReg_ScriptGUI_Canvas();
	void ICallReg_ScriptGUI_RenderTarget();
	void ICallReg_ScriptGUI_DDContainer();
	void ICallReg_ScriptGUI_ItemBox();
	void ICallReg_ScriptGUI_ImageBox();
	void ICallReg_ScriptGUI_ListBox();
	void ICallReg_ScriptGUI_Window();


    //postagent
#ifdef __HAVE_NETWORK__
    void ICallReg_ScriptRuntime_PostAgent( void );
    void ICallReg_ScriptRuntime_NetworkStreamWriter( void );
    void ICallReg_ScriptRuntime_NetworkStreamReader( void );
#endif

#if __ANDROID__
	void ICallReg_ScriptRuntime_AndroidJNIHelper(void) ;
	void ICallReg_ScriptRuntime_AndroidJNI(void);
#endif
    
	void ICallReg_ScriptRuntime_Material( void );
	void ICallReg_ScriptRuntime_GraphicSystem( void );
	void ICallReg_ScriptRuntime_RenderToTexture( void );

	// - call all register functions
	void RegisterInternalCalls( void )
	{
		ICallReg_ScriptRuntime_Actor();
		ICallReg_ScriptRuntime_Application();
		ICallReg_ScriptRuntime_ScriptableClass();
		ICallReg_ScriptRuntime_AnimationComponent();
		ICallReg_ScriptRuntime_Input();
        ICallReg_ScriptRuntime_InAppPurchase();
		ICallReg_ScriptRuntime_RenderComponent();
		ICallReg_ScriptRuntime_MeshRenderComponent();
		ICallReg_ScriptRuntime_ProjectorRenderComponent();
		ICallReg_ScriptRuntime_SkeletonComponent();
		
		ICallReg_ScriptRuntime_ParticleSystem();
		ICallReg_ScriptRuntime_ParticleRenderComponent();

		ICallReg_ScriptRuntime_IntersectWorld();
		ICallReg_ScriptRuntime_ActorManager();

		ICallReg_ScriptRuntime_Camera();
		ICallReg_ScriptRuntime_CameraComponent();
		ICallReg_ScriptRuntime_LightComponent();

		ICallReg_ScriptRuntime_Util();
		ICallReg_ScriptRuntime_ScriptComponent();

		ICallReg_ScriptRuntime_Debug();
		ICallReg_ScriptRuntime_XmlReader();
		ICallReg_ScriptRuntime_IO();
		ICallReg_ScriptRuntime_XmlWriter();

#ifndef __PHYSX_COMMIT__
		ICallReg_ScriptRuntime_PhysicsScene();
		ICallReg_ScriptRuntime_PhysicsShape();
		ICallReg_ScriptRuntime_PhysicsBoxShape();
		ICallReg_ScriptRuntime_PhysicsSphere();
		ICallReg_ScriptRuntime_PhysicsCapsuleShape();
		ICallReg_ScriptRuntime_PhysicsMeshShape();
		ICallReg_ScriptRuntime_PhysicsBodyComponent();
#endif
		ICallReg_ScriptRuntime_Component();
#ifndef __SOUND_COMMIT__
		ICallReg_ScriptRuntime_SoundSource();
		ICallReg_ScriptRuntime_SoundListener();
		ICallReg_ScriptRuntime_SoundFilter();
		ICallReg_ScriptRuntime_SoundLowPassFilterComponent();
		ICallReg_ScriptRuntime_SoundEchoFilterComponent();
		ICallReg_ScriptRuntime_SoundReverbFilterComponent();

#endif		
		ICallReg_ScriptRuntime_SpriteRenderComponent();
		ICallReg_ScriptRuntime_Scene();

		//gui
		ICallReg_ScriptGUI_GUI();
		ICallReg_ScriptGUI_Widget();
		ICallReg_ScriptGUI_TextBox();
		ICallReg_ScriptGUI_ScrollBar();
		ICallReg_ScriptGUI_EditBox();
		ICallReg_ScriptGUI_Button();
		ICallReg_ScriptGUI_Canvas();
		ICallReg_ScriptGUI_RenderTarget();
		ICallReg_ScriptGUI_DDContainer();
		ICallReg_ScriptGUI_ItemBox();
		ICallReg_ScriptGUI_ImageBox();
		ICallReg_ScriptGUI_ListBox();
		ICallReg_ScriptGUI_Window();
        
#ifdef __HAVE_NETWORK__
        //postagent
        ICallReg_ScriptRuntime_PostAgent();
        ICallReg_ScriptRuntime_NetworkStreamWriter();
        ICallReg_ScriptRuntime_NetworkStreamReader();
#endif

#if __ANDROID__
		ICallReg_ScriptRuntime_AndroidJNI ();
		ICallReg_ScriptRuntime_AndroidJNIHelper () ;
#endif
		ICallReg_ScriptRuntime_Material();
		ICallReg_ScriptRuntime_GraphicSystem();
		ICallReg_ScriptRuntime_RenderToTexture();
	}
}

