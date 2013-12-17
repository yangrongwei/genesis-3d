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
#ifndef __CollisionModelServer_H__
#define __CollisionModelServer_H__

#include "core/refcounted.h"
#include "core/singleton.h"
#include "util/dictionary.h"
#include "util/string.h"
#include "graphicsystem/Projector/CollisionModel.h"
#include "foundation/util/stl.h"

namespace Graphic
{

	class CollisionModel;

	class CollisionModelServer : public Core::RefCounted
	{
		__DeclareClass(CollisionModelServer);
		__DeclareImageSingleton(CollisionModelServer);

	public:

		CollisionModelServer();

		virtual ~CollisionModelServer();

	public:

		void  CleanCache();

		void  SetCacheLimit(SizeT limit);

		SizeT GetCacheLimit() const;

		SizeT GetMemoryUsage() const;

		GPtr<CollisionModel> GetCollisionModel( const Util::String& meshName);

	protected:

		struct CacheItem
		{
			CacheItem* next;
			CacheItem* prev;

			GPtr<CollisionModel> opModel;
			Util::String		meshName;

			CacheItem()
				: next(NULL),
				prev(NULL),
				opModel(NULL)
			{

			}

			CacheItem(const Util::String& name, const GPtr<CollisionModel>& opModel)
				: next(NULL),
				prev(NULL),
				meshName(name),
				opModel(opModel)
			{

			}

			~CacheItem()
			{

			}

			SizeT GetMemoryUsage(void) const;
		};

		bool  _IsEmpty() const;

		CacheItem* _Front() const;

		CacheItem* _Back() const;

		void       _LinkToFront(CacheItem* pItem);

		void       _LinkToBack(CacheItem* pItem);

		void       _UnLink(CacheItem* pItem);

		void       _MoveToFront(CacheItem* pItem);

		void       _MoveToBack(CacheItem* pItem);

		void       _CheckMemoryUsage();

		void       _AddOpModel(const Util::String& meshName, const GPtr<CollisionModel>& pModel);

		typedef Util::STL_map<Util::String, CacheItem>::type CacheItemMap;

		CacheItemMap	m_CacheItemMap;
		CacheItem		m_CacheSentinel;

		SizeT			m_nCacheLimit;
		SizeT			m_nMemoryUsage;
	};

}


#endif