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
#ifndef __gameapplication_H__
#define __gameapplication_H__

#include "feature_fwd_decl.h"
#include "core/singleton.h"
#include "util/dictionary.h"
#include "util/stringatom.h"
#include "app/application.h"
#include "jobs/jobsystem.h"   
#include "io/ioserver.h"
#include "io/iointerface.h"
#include "core/coreserver.h"
#include "foundation/delegates/delegatetype.h"

#if __NEBULA3_HTTP__
#include "debug/debuginterface.h"
#include "http/httpinterface.h"
#include "http/httpserverproxy.h"
#endif

//------------------------------------------------------------------------------
namespace Input
{
	class InputSource;
	class GuiInputHandler;
}

namespace Graphic
{
	class CollisionModelServer;
}

namespace IO
{
	class PackageSystem;
}

namespace ShaderProgramCompiler
{
	class ShaderFactory;
}

namespace App
{
class GameServer;
class Scene;

class GameApplication : public Application
{
	typedef Application Super;
    __DeclareThreadSingleton(GameApplication);   
	 
public:
	typedef Delegates::delegates::CDelegate1<const Application&> EventHandle_Exit;//CDelegate1

    /// constructor
    GameApplication();
    /// destructor
    virtual ~GameApplication();
    /// open the application
    virtual bool Open();
	/// start the application
	virtual bool Start();
    /// close the application
    virtual void Close();
    /// run the application
    virtual void Run();
	/// exit the application
	virtual void Exit();

	virtual void Quit();

	virtual bool IsQuit();
	/// open a scence
	virtual bool OpenScene(const Util::String& sSceneName, bool create = false);
	/// close a scence
	virtual bool CloseScene(const Util::String& sSceneName);
	/// called when the game stopped
	virtual void OnStopped();
	/// called when the game resumed
	virtual void OnResumed();


	virtual const GPtr<Scene>& GetCurrentScene() const;
	/// close all scene
	virtual void CloseAllScenes();

	/// set version
	void SetWebVersion( bool bWebVersion, void* hWebWindow );
	///// set asset directory
	//void SetAssetName( const Util::String& sAssetName );
	/// set resource download URL
	void SetResDownloadUrl( const Util::String& sPath );

	void SetFileServicePath( const Util::String& sPath );

	void SetUseFileService( bool use );
	/// set method
	void SetEngineDir(const Util::String& sEngineDir);
	void SetResourceBaseDir( const Util::String& sPath );
	void SetPipeName( const Util::String& sPipeName );
	void SetGameResolution( unsigned int uGameWidth, unsigned int uGameHeight );
	void SetUseLocalRes( bool bUseLocalRes );
	void SetDebugScript( bool bDebugScript );
	void SetGui( bool bGui );
	void SetInput(const GPtr<Input::InputSource>& input);

	const Util::String& GetResourceBaseDir() const;
	//- get methods
	bool IsWebVersion();
	const Util::String& GetPipeName();
	unsigned int GetGameWidth();
	unsigned int GetGameHeight();
	const GPtr<Input::InputSource>& GetInputSource() const;

	EventHandle_Exit eventExit;

	void SetDeviceLost();
	
#if __ANDROID__	
	void SetNeedReadAPK(bool need);
	void SetAPKPath(const Util::String& apk);
	void SetPackageName(const Util::String& package);

	void SetDPI(float width,float height);

	float GetDPIHeight();
	float GetDPIWidth();
#endif

#if __ANDROID__||__OSX__
	virtual Util::String GetAppDicOnMobile();
#endif

protected:
    /// cleanup application state handlers
    //virtual void CleanupStateHandlers(); 
    /// setup game features
    virtual void setupGameFeatures();
    /// cleanup game features
    virtual void cleanupGameFeatures(); 
    /// setup app from cmd lines
    virtual void setupAppFromCmdLineArgs();

	virtual void setupProjectAssigns();

	void setupSciptSystem();
	/// loading scene logo
	virtual void displayLOGO();

#ifdef __GENESIS_EDITOR__
	void BuildEditorVersion(void);
#endif

protected:
	static void _renderDeviceLost();
	void _RegisterDynamicClass() const;

	enum DeviceState
	{
		DS_Normal,
		DS_Lost,
		DS_Losted,
		DS_Reset,
	};


    GPtr<Core::CoreServer> mCoreServer;
    GPtr<Jobs::JobSystem> mJobSystem;
    GPtr<IO::IoServer> mIoServer;//主线程io
    GPtr<IO::IoInterface> mIoInterface;
	typedef GPtr<GraphicObjectManager> TGraphicObjectManagerPtr;
	TGraphicObjectManagerPtr mGraphicObjectManager;

#if __NEBULA3_HTTP__
	GPtr<Debug::DebugInterface> mDebugInterface;
	GPtr<Http::HttpInterface> mHttpInterface;
	GPtr<Http::HttpServerProxy> mHttpServerProxy;
#endif

	TGraphicsFeaturePtr mGraphicsFeature;

	TBaseGameFeaturePtr mBaseGameFeature;
	TInputFeaturePtr mInputFeature;
	TParticleFeaturePtr mParticleFeature;
	TVegetationFeaturePtr mVegeFeature;
    TScriptFeaturePtr mScriptFeature;
    TFontFeaturePtr mFontFeature;
	GPtr<GUIServer> mGuiServer;
#ifndef __SOUND_COMMIT__
	TSoundFeaturePtr mSoundFeature;
#endif // __SOUND_COMMIT__
#ifndef __OSX__
	//TNetworkFeaturePtr mNetworkFeature;
	TPhysicsFeaturePtr mPhysicsFeature;
#endif
    TAnimationFeaturePtr mAnimationFeature;
	TResourceFeaturePtr mResourceFeature;
    TALSystemFeaturePtr mALSystemFeature;
	GPtr<GameServer> mGameServer;
    GPtr<Input::GuiInputHandler> mGuiInputHandler;
	GPtr<Input::InputSource> mInputSource;
	GPtr<Graphic::CollisionModelServer> mCollisonServer;
	//GPtr<IO::PackageServer> mPackageServer;

	unsigned int mGameWidth;
	unsigned int mGameHeight;
	//引擎所在目录
	Util::String mEngineDir;
	//资源放置的基础目录
	Util::String mResourceBaseDir;
	//资源下载的基础url
	Util::String mResDownloadUrl;
	//file service exe 所在目录
	Util::String mFileServicePath;
	//Packet Pipe
	Util::String mPipeName;
	////是否使用本地资源 
	bool mUseLocalRes;
	//是否调试脚本
	bool mDebugScript;
	//是否启动gui
	bool mInitGui;
	//if use FileService to download resource
	bool mbUseFileService;
	bool mQuit;
	bool mUseWeb;
	void* mWinHandle;

	IO::AssignRegistry* mAssignRegistry;

	DeviceState mDeviceState;

	ShaderProgramCompiler::ShaderFactory* m_pShaderFactory;

#if __ANDROID__
	bool mbNeedReadApk;
	Util::String mApkPath;
	Util::String mPackageName;
	float mDpiWidth;
	float mDpiHeight;
#endif
};

inline const GPtr<Input::InputSource>& GameApplication::GetInputSource() const
{
	return mInputSource;
}

inline void GameApplication::SetEngineDir(const Util::String& sEngineDir)
{
	mEngineDir = sEngineDir;
}

inline void GameApplication::SetResourceBaseDir(const Util::String& sPath)
{
	mResourceBaseDir = sPath;
}
//------------------------------------------------------------------------
//inline void GameApplication::SetAssetName(const Util::String& sAssetName)
//{
//	mAssetName = sAssetName;
//}
//------------------------------------------------------------------------
inline void GameApplication::SetResDownloadUrl(const Util::String& sPath)
{
	mResDownloadUrl = sPath;
}

inline void GameApplication::SetFileServicePath( const Util::String& sPath )
{
	mFileServicePath = sPath;
}
inline void GameApplication::SetUseFileService( bool use )
{
	mbUseFileService = use;
}
////------------------------------------------------------------------------
//inline void GameApplication::SetSceneName(const Util::String& sSceneName)
//{
//	mSceneName = sSceneName;
//}
//------------------------------------------------------------------------
inline void GameApplication::SetPipeName(const Util::String& sPipeName)
{
	mPipeName = sPipeName;
}
//------------------------------------------------------------------------
inline const Util::String& GameApplication::GetPipeName()
{
	return mPipeName;
}
//------------------------------------------------------------------------
inline void GameApplication::SetGameResolution(unsigned int uGameWidth,unsigned int uGameHeight)
{
	mGameWidth = uGameWidth;
	mGameHeight = uGameHeight;
}
//------------------------------------------------------------------------
inline void GameApplication::SetWebVersion( bool bWebVersion,void* hWebWindow )
{
	mUseWeb = bWebVersion;
	mWinHandle = hWebWindow;
}
//------------------------------------------------------------------------
inline unsigned int GameApplication::GetGameWidth()
{
	return mGameWidth;
}
//------------------------------------------------------------------------
inline unsigned int GameApplication::GetGameHeight()
{
	return mGameHeight;

}
////------------------------------------------------------------------------
inline void GameApplication::SetUseLocalRes( bool bUseLocalRes )
{
	mUseLocalRes = bUseLocalRes;
}
//------------------------------------------------------------------------
inline void GameApplication::SetDebugScript( bool bDebugScript )
{
	mDebugScript = bDebugScript;
}
//------------------------------------------------------------------------
inline void GameApplication::SetGui(bool bGui)
{
	mInitGui = bGui;
}
//------------------------------------------------------------------------
inline bool GameApplication::IsWebVersion()
{
	return mUseWeb;
}
//------------------------------------------------------------------------
inline const Util::String& GameApplication::GetResourceBaseDir() const
{
	return mResourceBaseDir;
}
#if __ANDROID__
inline void GameApplication::SetNeedReadAPK(bool need)
{
	mbNeedReadApk = need;
}
inline void GameApplication::SetAPKPath(const Util::String& apk)
{
	mApkPath = apk;
}
inline void GameApplication::SetPackageName(const Util::String& package)
{
	mPackageName = package;
}

inline void GameApplication::SetDPI( float width,float height )
{
	mDpiWidth = width;
	mDpiHeight = height;
}
inline float GameApplication::GetDPIHeight()
{
	return mDpiHeight;
}
inline float GameApplication::GetDPIWidth()
{
	return mDpiWidth;
}
#endif
}
#endif // __gameapplication_H__






