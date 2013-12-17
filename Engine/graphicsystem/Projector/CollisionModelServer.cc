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
#include "CollisionModelServer.h"
#include "CollisionModel.h"

#define DEFAULT_CACHE_LIMIT (8*1024*1024)

namespace Graphic
{

	__ImplementClass(Graphic::CollisionModelServer, 'CMSR', Core::RefCounted);
	__ImplementImageSingleton(Graphic::CollisionModelServer);

	CollisionModelServer::CollisionModelServer()
		: m_nCacheLimit(DEFAULT_CACHE_LIMIT),
		m_nMemoryUsage(0)
	{
		__ConstructImageSingleton;
		m_CacheSentinel.next = m_CacheSentinel.prev = &m_CacheSentinel;
	}

	CollisionModelServer::~CollisionModelServer()
	{
		__DestructImageSingleton;
		CleanCache();
	}

	SizeT CollisionModelServer::CacheItem::GetMemoryUsage() const
	{
		return opModel->GetMemoryUsage();
	}

	void CollisionModelServer::SetCacheLimit(SizeT limit)
	{
		m_nCacheLimit = limit;

		_CheckMemoryUsage();
	}

	SizeT CollisionModelServer::GetCacheLimit() const
	{
		return m_nCacheLimit;
	}

	bool CollisionModelServer::_IsEmpty() const
	{
		return m_CacheSentinel.next == m_CacheSentinel.prev;
	}

	CollisionModelServer::CacheItem* CollisionModelServer::_Front() const
	{
		n_assert(! _IsEmpty() );

		return m_CacheSentinel.next;
	}

	CollisionModelServer::CacheItem* CollisionModelServer::_Back() const
	{
		n_assert(! _IsEmpty() );

		return m_CacheSentinel.prev;
	}

	void CollisionModelServer::_LinkToFront(CacheItem* pItem)
	{
		n_assert(!pItem->next && !pItem->prev);

		CacheItem* next = m_CacheSentinel.next;
		CacheItem* prev = &m_CacheSentinel;

		pItem->next = next;
		next->prev  = pItem;

		pItem->prev = prev;
		prev->next  = pItem;
	}

	void CollisionModelServer::_LinkToBack(CacheItem* pItem)
	{
		n_assert(!pItem->next && !pItem->prev);

		CacheItem* next = &m_CacheSentinel;
		CacheItem* prev = m_CacheSentinel.prev;

		pItem->next = next;
		next->prev  = pItem;

		pItem->prev = prev;
		prev->next  = pItem;
	}

	void CollisionModelServer::_UnLink(CacheItem* pItem)
	{
		CacheItem* next = pItem->next;
		CacheItem* prev = pItem->prev;

		n_assert( next && prev );

		if (next)
		{
			next->prev = prev;
			pItem->next = 0;
		}

		if (prev)
		{
			prev->next  = next;
			pItem->prev = 0;
		}
	}

	void CollisionModelServer::_MoveToFront(CacheItem* pItem)
	{
		_UnLink(pItem);
		_LinkToFront(pItem);
	}

	void CollisionModelServer::_MoveToBack(CacheItem* pItem)
	{
		_UnLink(pItem);
		_LinkToBack(pItem);
	}

	void CollisionModelServer::_CheckMemoryUsage()
	{
		while (!_IsEmpty() && m_nMemoryUsage > m_nCacheLimit)
		{
			CacheItem* item = _Back();
			m_nMemoryUsage -= item->GetMemoryUsage();
			_UnLink(item);

			m_CacheItemMap.erase(item->meshName);
		}
	}

	void CollisionModelServer::_AddOpModel(const Util::String& meshName, const GPtr<CollisionModel>& pModel)
	{
		std::pair<CacheItemMap::iterator, bool> inserted 
			= m_CacheItemMap.insert(CacheItemMap::value_type(meshName, CacheItem(meshName,pModel)));

		n_assert(inserted.second);

		_LinkToFront(&inserted.first->second);

		m_nMemoryUsage += pModel->GetMemoryUsage();
	}

	GPtr<CollisionModel> CollisionModelServer::GetCollisionModel(const Util::String& meshName)
	{
		CacheItemMap::iterator it = m_CacheItemMap.find(meshName);

#ifndef __PROJECTOR_COMMIT__ 
		if( it == m_CacheItemMap.end() )
		{
			_CheckMemoryUsage();
			GPtr<CollisionModel> opModel = CollisionModel::Create();
			opModel->SetPrimitveInfo(meshName);
			opModel->CreateOpModel();

			_AddOpModel(meshName, opModel);

			return opModel;
		} 
		else
		{
			CacheItem* pItem = &it->second;

			_MoveToFront(pItem);

			return pItem->opModel;
		}
#else
		// temp code, for android compile
		CacheItem* pItem = &it->second;

		_MoveToFront(pItem);

		return pItem->opModel;
#endif __PROJECTOR_COMMIT__

	}

	void CollisionModelServer::CleanCache()
	{
		m_nMemoryUsage = 0;
		m_CacheSentinel.next = m_CacheSentinel.prev = &m_CacheSentinel;
		m_CacheItemMap.clear();
	}

}