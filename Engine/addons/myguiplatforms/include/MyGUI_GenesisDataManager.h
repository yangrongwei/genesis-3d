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
#ifndef __MYGUI_GENESIS_DATA_MANAGER_H__
#define __MYGUI_GENESIS_DATA_MANAGER_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_DataManager.h"
#include "foundation/util/string.h"
namespace MyGUI
{

	class GenesisDataManager :
		public DataManager
	{
	public:
		GenesisDataManager();

		void initialise(const std::string& _group);
		void shutdown();

		static GenesisDataManager& getInstance()
		{
			return *getInstancePtr();
		}
		static GenesisDataManager* getInstancePtr()
		{
			return static_cast<GenesisDataManager*>(DataManager::getInstancePtr());
		}
		void SetResourcePath(const Util::String& path);
		const std::string& getGroup() const
		{
			return mGroup;
		}

		/** @see DataManager::getData */
		virtual IDataStream* getData(const std::string& _name);

		/** @see DataManager::isDataExist */
		virtual bool isDataExist(const std::string& _name);

		/** @see DataManager::getDataListNames */
		virtual const VectorString& getDataListNames(const std::string& _pattern);

		/** @see DataManager::getDataPath */
		virtual const std::string& getDataPath(const std::string& _name);

	private:
		const VectorString& getDataListNames(const std::string& _pattern, bool _fullpath);

	private:
		std::string mGroup;
		bool mAllGroups;
		bool mIsInitialise;
		Util::String m_srcPath;
	};

} // namespace MyGUI

#endif // __MYGUI_GENESIS_DATA_MANAGER_H__
