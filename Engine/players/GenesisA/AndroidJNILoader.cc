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

#include <jni.h>

#include <unistd.h>
#include <android/log.h>

#include "simplegameapplication.h"
#include "input/inputwindowsource.h"
#include "input/android/androidinputsource.h"
#include "input/android/androidtouchevent.h"

#include "rendersystem/gles/OpenGLES.h"

using namespace Genesis;

static DemoPublishGameApplication* g_pApp = NULL;
static bool g_bPause = false;
static Util::String g_gamedir = "";
static Util::String g_scenename = "";
static Util::String g_pakagename = "";
static Util::String g_apklocation = "";

#define KEYCODE_BACK 4
#define KEYCODE_MENU 52


enum StorageType
{
	Compressed = 0,
	PackageName,
	SDCard,
};

static int g_StorageType = SDCard;

void Init(jint width, jint height,jfloat dpiw,jfloat dpih)
{
	g_pApp->SetCompanyName( "CYOU" );
	g_pApp->SetAppTitle( "Genesis Android" );

	//设置资源路径
	g_pApp->SetResourceBaseDir(g_gamedir);
	g_pApp->SetDebugScript(false);
	g_pApp->SetGui(true);
	g_pApp->SetGameResolution(width, height);
	if(g_StorageType==Compressed)
	{
		g_pApp->SetNeedReadAPK(true);
	}
	else
	{
		g_pApp->SetNeedReadAPK(false);
	}
	g_pApp->SetAPKPath(g_apklocation);
	g_pApp->SetPackageName(g_pakagename);
	GPtr<Input::InputSource> input = Input::InputWindowSource::Create();
	g_pApp->SetInput(input);

	LOGI("Before Open Scene");
	g_pApp->Open();

	LOGI("After Core App Open");

	g_pApp->Start();

	//设置scene文件
	g_pApp->OpenScene(g_scenename);
	LOGI("After Open Scene");

	GLES::GLESImpl::Instance()->CheckError();
}

void RenderFrame()
{
	GLES::GLESImpl::Instance()->CheckError();

	if (g_pApp->IsOpen())
	{
		g_pApp->Run();
	}

	GLES::GLESImpl::Instance()->CheckError();
}

void CleanUp()
{
	if (g_pApp != NULL)
	{
		g_pApp->Exit();
		n_delete(g_pApp);
		g_pApp = NULL;
	}
}

void ProcessInputMulTouch(JNIEnv * pEnv, Input::MobileTouchEvent& event, const jintArray& pIDs, const jfloatArray& pXs, const jfloatArray& pYs)
{
	jsize nPointers = pEnv->GetArrayLength(pIDs);
	jint* pPointers = pEnv->GetIntArrayElements(pIDs, NULL);

	jfloat* pPosX = pEnv->GetFloatArrayElements(pXs, NULL);
	jfloat* pPosY = pEnv->GetFloatArrayElements(pYs, NULL);


	if (pEnv->ExceptionCheck())
	{
		n_delete_array(pPointers);

		n_error("--------------------JNI ERROR: Touches Move--------------------");

		return;
	}

	for (IndexT i = 0; i < nPointers; ++i)
	{
		Math::float2 pos( pPosX[i], pPosY[i] );

		event.SetPointerPos(pPointers[i], pos);
	}

	const GPtr<Input::InputSource>& pInputSource = g_pApp->GetInputSource();

	if (pInputSource.isvalid())
	{
		pInputSource.downcast<AndroidInput::AndroidInputSource>()->OnAndroidProc(&event);
	}

	pEnv->ReleaseIntArrayElements(pIDs, pPointers, 0);
	pEnv->ReleaseFloatArrayElements(pXs, pPosX, 0);
	pEnv->ReleaseFloatArrayElements(pYs, pPosY, 0);
}

void ProcessInputTouch(JNIEnv * pEnv, Input::MobileTouchEvent& event, const jint& pID, const jfloat& pX, const jfloat& pY)
{
	if (pEnv->ExceptionCheck())
	{
		n_error("--------------------JNI ERROR: Touches Move--------------------");
		return;
	}

	Math::float2 pos( pX, pY );

	event.SetPointerPos(pID, pos);

	const GPtr<Input::InputSource>& pInputSource = g_pApp->GetInputSource();

	if (pInputSource.isvalid())
	{
		pInputSource.downcast<AndroidInput::AndroidInputSource>()->OnAndroidProc(&event);
	}

}

extern "C" {

	JNIEXPORT void JNICALL Java_org_genesis_lib_GenesisRenderer_nativeConfig(JNIEnv*  env, jobject thiz, jstring gamedir, jstring scenename);
	JNIEXPORT void JNICALL Java_org_genesis_lib_GenesisRenderer_nativeStorage(JNIEnv*  env, jobject thiz, jint type, jstring pakagename, jstring apklocation);
	JNIEXPORT void JNICALL Java_org_genesis_lib_GenesisRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h,jfloat dpiw,jfloat dpih);
	JNIEXPORT void JNICALL Java_org_genesis_lib_GenesisRenderer_nativeRender(JNIEnv * env, jobject obj);
	JNIEXPORT void JNICALL Java_org_genesis_lib_GenesisRenderer_nativeOnPause(JNIEnv * env, jobject obj);
	JNIEXPORT void JNICALL Java_org_genesis_lib_GenesisRenderer_nativeOnResume(JNIEnv * env, jobject obj);
	JNIEXPORT void JNICALL Java_org_genesis_lib_GenesisRenderer_nativeOnStop(JNIEnv * env, jobject obj);
	JNIEXPORT void JNICALL Java_org_genesis_lib_GenesisRenderer_nativeTouchesBegin(JNIEnv * env, jobject obj, jint pIDs, jfloat pXs, jfloat pYs);
	JNIEXPORT void JNICALL Java_org_genesis_lib_GenesisRenderer_nativeTouchesMove(JNIEnv * env, jobject obj, jintArray pIDs, jfloatArray pXs, jfloatArray pYs);
	JNIEXPORT void JNICALL Java_org_genesis_lib_GenesisRenderer_nativeTouchesEnd(JNIEnv * env, jobject obj, jint pIDs, jfloat pXs, jfloat pYs);
	JNIEXPORT void JNICALL Java_org_genesis_lib_GenesisRenderer_nativeTouchesCancel(JNIEnv * env, jobject obj, jintArray pIDs, jfloatArray pXs, jfloatArray pYs);
	JNIEXPORT void JNICALL Java_org_genesis_lib_GenesisRenderer_nativeKeyDown(JNIEnv * env, jobject obj, jint pKeyCode);
};	

JNIEXPORT void Java_org_genesis_lib_GenesisRenderer_nativeConfig(JNIEnv*  env, jobject thiz, jstring gamedir, jstring scenename)
{
	const char* dirP = env->GetStringUTFChars(gamedir, NULL);
	g_gamedir = dirP;
	const char* sceneP = env->GetStringUTFChars(scenename, NULL);
	g_scenename = sceneP;
	env->ReleaseStringUTFChars(gamedir, dirP);
	env->ReleaseStringUTFChars(scenename, sceneP);
}

JNIEXPORT void Java_org_genesis_lib_GenesisRenderer_nativeStorage(JNIEnv*  env, jobject thiz, jint type, jstring pakagename , jstring apklocation)
{
	const char* pakage = env->GetStringUTFChars(pakagename, NULL);
	g_pakagename = pakage;
	env->ReleaseStringUTFChars(pakagename, pakage);

	const char* loc = env->GetStringUTFChars(apklocation, NULL);
	g_apklocation = loc;
	env->ReleaseStringUTFChars(apklocation, loc);

	g_StorageType = type;
}

JNIEXPORT void Java_org_genesis_lib_GenesisRenderer_nativeInit(JNIEnv* env, jobject thiz, jint w, jint h, jfloat dpiw,jfloat dpih)
{
	if (g_pApp != NULL)
	{
		g_pApp->SetDeviceLost();
	} 
	else
	{
		Threading::ThreadRunTimeInfo::SetupMyThreadRunTime("GL Thread");

		g_pApp = n_new(DemoPublishGameApplication);

		Init(w, h,dpiw,dpih);
	}

}

JNIEXPORT void Java_org_genesis_lib_GenesisRenderer_nativeRender(JNIEnv * env, jobject obj)
{
	if (g_pApp != NULL && !g_bPause)
	{
		RenderFrame();
	}

}

JNIEXPORT void Java_org_genesis_lib_GenesisRenderer_nativeTouchesBegin(JNIEnv * env, jobject obj, jint pIDs, jfloat pXs, jfloat pYs)
{
	AndroidInput::AndroidTouchEvent event;
	event.SetType(Input::MoibleInputEvent::INPUT_EVENT_TYPE_MOTION);
	event.SetMotionType(Input::MobileTouchEvent::MOTION_EVENT_ACTION_DOWN);
	event.SetSourceType(AndroidInput::AndroidTouchEvent::INPUT_SOURCE_TOUCHSCREEN);

	ProcessInputTouch(env, event, pIDs, pXs, pYs);
}

JNIEXPORT void Java_org_genesis_lib_GenesisRenderer_nativeTouchesMove(JNIEnv * pEnv, jobject obj, jintArray pIDs, jfloatArray pXs, jfloatArray pYs)
{
	AndroidInput::AndroidTouchEvent event;
	event.SetType(Input::MoibleInputEvent::INPUT_EVENT_TYPE_MOTION);
	event.SetMotionType(Input::MobileTouchEvent::MOTION_EVENT_ACTION_MOVE);
	event.SetSourceType(AndroidInput::AndroidTouchEvent::INPUT_SOURCE_TOUCHSCREEN);

	ProcessInputMulTouch(pEnv, event, pIDs, pXs, pYs);
}

JNIEXPORT void Java_org_genesis_lib_GenesisRenderer_nativeTouchesEnd(JNIEnv * env, jobject obj, jint pIDs, jfloat pXs, jfloat pYs)
{
	AndroidInput::AndroidTouchEvent event;
	event.SetType(Input::MoibleInputEvent::INPUT_EVENT_TYPE_MOTION);
	event.SetMotionType(Input::MobileTouchEvent::MOTION_EVENT_ACTION_UP);
	event.SetSourceType(AndroidInput::AndroidTouchEvent::INPUT_SOURCE_TOUCHSCREEN);

	ProcessInputTouch(env, event, pIDs, pXs, pYs);
}

JNIEXPORT void Java_org_genesis_lib_GenesisRenderer_nativeTouchesCancel(JNIEnv * env, jobject obj, jintArray pIDs, jfloatArray pXs, jfloatArray pYs)
{
	AndroidInput::AndroidTouchEvent event;
	event.SetType(Input::MoibleInputEvent::INPUT_EVENT_TYPE_MOTION);
	event.SetMotionType(Input::MobileTouchEvent::MOTION_EVENT_ACTION_CANCEL);
	event.SetSourceType(AndroidInput::AndroidTouchEvent::INPUT_SOURCE_TOUCHSCREEN);

	ProcessInputMulTouch(env, event, pIDs, pXs, pYs);
}

JNIEXPORT void Java_org_genesis_lib_GenesisRenderer_nativeOnPause(JNIEnv * env, jobject obj)
{
	LOGI("-----------------------------nativeOnPause-----------------------------");

	g_bPause = true;
}

JNIEXPORT void Java_org_genesis_lib_GenesisRenderer_nativeOnResume(JNIEnv * env, jobject obj)
{
	LOGI("-----------------------------nativeOnResume-----------------------------");

	g_bPause = false;

}

JNIEXPORT void Java_org_genesis_lib_GenesisRenderer_nativeKeyDown(JNIEnv * env, jobject obj, jint pKeyCode)
{
	LOGI("-----------------------------nativeKeyDown-----------------------------");

	switch (pKeyCode)
	{
	case KEYCODE_BACK:
		CleanUp();
		break;
	default:
		break;
	}

}

JNIEXPORT void Java_org_genesis_lib_GenesisRenderer_nativeOnStop(JNIEnv * env, jobject obj)
{
	LOGI("-----------------------------nativeOnStop-----------------------------");
}