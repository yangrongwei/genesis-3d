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
#ifndef _RENDEROBJECT_H_
#define _RENDEROBJECT_H_
#include "graphicsystem/base/GraphicObject.h"
#include "base/RenderBase.h"
#include "foundation/util/array.h"
namespace Graphic
{	
	class Material;
	class Camera;
	class RenderDataCollection;
	class Renderable;
	class IRenderScene;

	typedef uint LayerID;

	class RenderObject : public GraphicObject
	{
		__DeclareSubClass(RenderObject, GraphicObject)
	public:	
		virtual ~RenderObject();
		virtual void Render(const Renderable* renderable, RenderPassType passType, const Material* customizedMaterial);
		virtual void AddToCollection(RenderDataCollection* collection);
		virtual void OnWillRenderObject(Camera* sender);

		virtual void SetTransform(const Math::matrix44& trans);
		virtual void SetBoundingBox(const Math::bbox& box);

		virtual bool IsUseLM() const;
		virtual bool IsLMHandleValid() const;

		virtual void Attach(IRenderScene* rnsc);
		virtual void AttachNoCull(IRenderScene* rnsc);
		virtual void Detach();
		bool Attached() const;

		bool GetProjected() const;
		void SetProjected(bool projected);

		bool GetNeedCullCallBack() const;
		void SetNeedCullCallBack(bool need);


		void SetLayerID(LayerID rl);
		LayerID GetLayerID() const;
		uint GetRenderCullMark() const;

		virtual void SetReceiveShadow( bool bReceiveShadow );
		virtual bool GetReceiveShadow();

		void SetCastShadow( bool bCastShadow );
		bool GetCastShadow();

		// !!!!!!internal call!!!!!  for vis manage. 
		void _SetVisEnt(const GPtr<Vis::VisEntity>& visEnt, IRenderScene* root);
		// !!!!!!internal call!!!!!  for vis manage. 
		const GPtr<Vis::VisEntity>& _GetVisEnt(void) const;

	protected:
		RenderObject();
	private:
		GPtr<Vis::VisEntity> m_VisEnt;
		IRenderScene* m_Root;
		uint m_LayerID;
		bool m_NeedCullCallBack;
		bool m_Projected;
		bool mbReceiveShadow;
		bool mbCastShadow;
	};

	inline void RenderObject::SetLayerID(LayerID rl)
	{
		m_LayerID = rl;
	}

	inline LayerID RenderObject::GetLayerID() const
	{
		return m_LayerID;
	}

	//------------------------------------------------------------------------
	inline void RenderObject::SetReceiveShadow( bool bReceiveShadow )
	{
		mbReceiveShadow = bReceiveShadow;
	}
	//------------------------------------------------------------------------
	inline bool RenderObject::GetReceiveShadow()
	{
		return mbReceiveShadow;
	}
	//------------------------------------------------------------------------

	inline void RenderObject::SetCastShadow( bool bCastShadow )
	{
		mbCastShadow = bCastShadow;
	}
	//------------------------------------------------------------------------
	inline bool RenderObject::GetCastShadow()
	{
		return mbCastShadow;
	}

	inline uint RenderObject::GetRenderCullMark() const
	{
		return 1 << m_LayerID;
	}
	inline void RenderObject::SetProjected(bool projected)
	{
		m_Projected = projected;
	}

	inline bool RenderObject::GetProjected() const
	{
		return m_Projected;
	}

	inline void RenderObject::SetNeedCullCallBack(bool need)
	{
		m_NeedCullCallBack = need;
	}

	inline bool RenderObject::GetNeedCullCallBack() const
	{
		return m_NeedCullCallBack;
	}

	inline bool RenderObject::Attached() const
	{
		return (m_Root != NULL);
	}

	inline bool RenderObject::IsUseLM() const
	{
		return false;
	}

	inline bool RenderObject::IsLMHandleValid() const
	{
		return false;
	}


	//------------------------------------------------------------------------
	inline const GPtr<Vis::VisEntity>& RenderObject::_GetVisEnt(void) const
	{
		return m_VisEnt;
	}
}

#endif //_RENDEROBJECT_H_