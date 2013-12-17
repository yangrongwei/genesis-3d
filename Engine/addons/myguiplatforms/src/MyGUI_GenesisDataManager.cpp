/*!
	@file
	@author		Albert Semenov
	@date		04/2009
*/
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
#include "MyGUI_GenesisDataManager.h"
#include "MyGUI_GenesisDiagnostic.h"
#include "MyGUI_GenesisDataStream.h"
#include "foundation/io/memorystream.h"
#include "foundation/io/iointerface.h"
#include "foundation/io/iointerfaceprotocol.h"
//#include <Ogre.h>

//#include "MyGUI_LastHeader.h"


#include "foundation/io/ioserver.h"

namespace MyGUI
{
	GenesisDataManager::GenesisDataManager() :
mAllGroups(false),
	mIsInitialise(false)
{
}
void GenesisDataManager::SetResourcePath(const Util::String& path)
{
	m_srcPath = path;
}
void GenesisDataManager::initialise(const std::string& _group)
{
	MYGUI_PLATFORM_ASSERT(!mIsInitialise, getClassTypeName() << " initialised twice");
	MYGUI_PLATFORM_LOG(Info, "* Initialise: " << getClassTypeName());

	mGroup = _group;
	//if (mGroup == Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME)
	//	mAllGroups = true;
	//else
	mAllGroups = false;

	MYGUI_PLATFORM_LOG(Info, getClassTypeName() << " successfully initialized");
	mIsInitialise = true;
}

void GenesisDataManager::shutdown()
{
	MYGUI_PLATFORM_ASSERT(mIsInitialise, getClassTypeName() << " is not initialised");
	MYGUI_PLATFORM_LOG(Info, "* Shutdown: " << getClassTypeName());

	MYGUI_PLATFORM_LOG(Info, getClassTypeName() << " successfully shutdown");
	mIsInitialise = false;
}

IDataStream* GenesisDataManager::getData(const std::string& _name)
{
	Util::String filename = _name.c_str();
	Util::String url = m_srcPath + filename;
	try
	{
		//Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource(_name, mGroup, true);
		//OgreDataStream* data = new OgreDataStream(stream);
		//return data;
		GPtr<IO::Stream> pStream = IO::MemoryStream::Create();
		n_assert( pStream );
		GPtr<IO::ReadStream> readStreamMsg = IO::ReadStream::Create();
		n_assert( readStreamMsg );
		readStreamMsg->SetFileName( url);
		readStreamMsg->SetStream( pStream );
		IO::IoInterface::Instance()->SendWait( readStreamMsg.upcast<Messaging::Message>() );

		if ( !readStreamMsg->GetResult() )
		{
			n_warning( "GenesisDataManager::getData: can not open %s", _name.c_str() );
			return nullptr;
		}
		pStream->SetAccessMode(IO::Stream::ReadAccess);
		if (pStream->Open())
		{
			GPtr<IO::TextReader> tr = IO::TextReader::Create();

			tr->SetStream(pStream);
			GenesisDataStream* data = new GenesisDataStream(tr);
			return (IDataStream*)data;
		}

		//GPtr<IO::Stream> stream = IO::IoServer::Instance()->CreateStream(IO::URI(url));
		//if (stream && stream->Open())
		//{
		//	GPtr<IO::TextReader> tr = IO::TextReader::Create();
		//	tr->SetStream(stream);
		//	GenesisDataStream* data = new GenesisDataStream(tr);
		//	return (IDataStream*)data;
		//}

	}
	catch(...) //(const Ogre::FileNotFoundException& _e)
	{
		//MYGUI_PLATFORM_LOG(Warning, _e.getDescription());
		MYGUI_PLATFORM_LOG(Warning, std::string(std::string("file error:") + _name));
		return nullptr;
	}
	MYGUI_PLATFORM_LOG(Warning, std::string(std::string("file error:") + _name));
	return nullptr;
}

bool GenesisDataManager::isDataExist(const std::string& _name)
{
	const VectorString& files = getDataListNames(_name);
	return (files.size() == 1);
}

const VectorString& GenesisDataManager::getDataListNames(const std::string& _pattern)
{
	return getDataListNames(_pattern, false);
}

const VectorString& GenesisDataManager::getDataListNames(const std::string& _pattern, bool _fullpath)
{
	static VectorString result;		//[2012/4/13 zhongdaohuan]临时处理。这个接口的具体功能未知。
	result.clear();
	result.push_back(_pattern);
	return result;
}

const std::string& GenesisDataManager::getDataPath(const std::string& _name)
{
	static std::string result;

	const VectorString& files = getDataListNames(_name, true);
	result = files.size() == 1 ? files[0] : "";

	return result;
}

} // namespace MyGUI
