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

#ifndef __VEGETATION_OBJECT_H__
#define __VEGETATION_OBJECT_H__
#include "resource/resource.h"
#include "resource/meshres.h"
#include "vegetation/vegetation_fwd_decl.h"
#include "graphicsystem/Material/materialinstance.h"
#include "vegetation/InstanceMap.h"
#include "vegetation/VegetationRenderObject.h"
#include "graphicsystem/RenderUnit.h"
#include "foundation/util/fixedarray.h"

namespace Vegetation
{
	typedef Graphic::ShaderParamString ShaderParamString;

	enum RenderType
	{
		eRT_Grass = 0,
		eRT_DetailMesh,
		eRT_Tree,		
	};

	/*! \class VegetationObejct VegetationObejct.h
	*  \brief  This is a class.
	*
	* organize a brush and render data
	*/
	class VegetationObject : public Core::RefCounted, Serialization::ISerialize
	{
		__DeclareClass(VegetationObject);
	public:
		typedef VegetationRenderObject RenderObjectType;
		typedef GPtr<VegetationRenderObject> RenderObjectPtr;
		VegetationObject();
		virtual ~VegetationObject(void);

		//----------------------------------------------------
		const static GPtr<VegetationObject> NullVegeObj;

		RenderBase::PrimitiveHandle& GetPrimHandle();
		void  SetPrimHandle(const RenderBase::PrimitiveHandle&);

		VegeInstanceMapPtr& CreateInstanceMap();
		const VegeInstanceMapPtr& GetInstanceMap() const;
		VegeInstanceMapPtr& GetInstanceMap();
		struct INSTANCEDATA_POS* CreateInstance();
		void RemoveInstance(IndexT);
		void SetInstanceMap(const VegeInstanceMapPtr&);

		void SetHWInstancing(bool);
		bool IsHWInstancing() const;


		void  SetRenderType(RenderType etype);
		RenderType GetRenderType(void) const;

		void  ClearRenderables(void);
		Graphic::RenderableResUnitArray& GetResUnits();

		RenderBase::TextureHandle _CreateErrorTexture(const Resources::ResourceId& errorTexID );
		void  Active();
		void  DeActive(void);
		bool  IsActive(void) const;

		void  Update();

		//--------------------------------property----------------------------------------
		void SetName( const Util::String& name);
		const Util::String& GetName(void) const; 

		void SetInstanceFilePath( const Util::String& path);
		const Util::String& GetInstanceFilePath(void) const;

		/// set meshid 
		void SetMeshID(const Resources::ResourceId& meshID, const Resources::Priority priority = Resources::ResourcePriority::MeshDefault);
		/// 
		const Resources::ResourceId& GetMeshID( ) const;
		///
		const Resources::PrimitiveResInfo* GetMeshInfo( void ) const;

		/// 
		void SetShaderID(IndexT iSubMesh , const Resources::ResourceId& shaderID);
		void RemoveShader(IndexT iSubMesh);
		/// 
		const Resources::ResourceId& GetShaderID(IndexT iSubMesh ) const;
		SizeT GetShaderCount() const;

		/// get  struct ptr of material
		GPtr<Graphic::MaterialInstance> GetMaterial( int  );
		/// 
		const GPtr<Graphic::MaterialInstance>& GetMaterial( int  ) const;

		/// 
		SizeT GetTextureParamCount(IndexT) const;
		void SetTexture( IndexT , const ShaderParamString& , const Resources::ResourceId&  );
		const Resources::ResourceId& GetTexture(IndexT , const ShaderParamString&  ) const;
		const ShaderParamString& GetTextureName(IndexT , IndexT  ) const;
		void RemoveTexture( IndexT , const ShaderParamString& );

		/// if has texture param referenced by submesh's shader
		bool HasTextureParam(IndexT , const ShaderParamString&  ) const;
		const ShaderParamString& GetShaderConstantParam(IndexT , IndexT ) const;

		SizeT GetMaterialCount() const;
		const Resources::ResourceId& GetMaterialID(IndexT iSubMesh ) const;
		/**
		* SetMaterialID  
		* @param: IndexT iSubMesh
		* @param: const Resources::ResourceId& matID,
		* @param: const bool bCopy = false				if bcopy is true, create material's copy, if is false, use exist material(create if not exist)
		* @return: void  
		* @see: 
		* @remark:  
		*/
		void SetMaterialID( IndexT iSubMesh, const Resources::ResourceId& matID,const bool bCopy = false );

		void SetShaderConstantParam( IndexT , const ShaderParamString& , const Util::String& );	
		void SetShaderConstantParam( IndexT , const ShaderParamString& , const Math::float4& );
		void SetShaderConstantParam( IndexT , const ShaderParamString& , const Math::matrix44& );
		void SetShaderConstantParam( IndexT , const ShaderParamString& , const Math::scalar&  );

		void RemoveShaderConstParam( IndexT , const ShaderParamString& );
		void ClearShaderConstantParams( IndexT  );

		SizeT GetShaderConstantParamCount(IndexT iSubMesh) const;

		const Util::String& GetShaderConstantParamValue(IndexT index, const ShaderParamString& paramname ) const;
		const Util::String& GetShaderConstantParamValue(IndexT iSubmesh, IndexT nIdx ) const;


		const Math::matrix44& GetWorldMatrix(void) const;
		void SetWorldMatrix( const Math::matrix44& m );

		void DirtyMaterial(IndexT iSubMesh );

		// cull distance visual
		void SetCullDistance(Math::scalar);
		Math::scalar GetCullDistance() const;

		/// set Local rot and scale . was convenience for edit template
		void SetRotation(Math::quaternion rot);
		void SetScale (Math::vector scale);		
		Math::quaternion GetRotation(void) const;
		Math::vector GetScale(void) const;

		void ReBuildRenderables();


		//	Serialization
		// @ISerialization::GetVersion. when change storage, must add SerializeSVersion count
		virtual Serialization::SVersion GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Serialization::SVersion ver, Serialization::SerializeReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( Serialization::SerializeWriter* pWriter ) const;

		// copy 
		virtual void CopyFrom( const GPtr<VegetationObject>& obj );

		RenderObjectPtr& GetRenderObject();


		Util::FixedArray<VEGE_VERTEX_INSTANCE>& GetVertices();
		Util::FixedArray<uchar>& GetIndices();
		void GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const;

	protected:
		void _onActive(void);
		void _onDeactive(void);

		void _ModifyMaterialDir(const Resources::ResourceId& oldMatID, Resources::ResourceId& outMatID);
	public:
		bool mIsBuildMaterials;
		bool mIsBuildRenderable;
		bool mIsAttached;
		bool mIsTrans;
		bool mRenderQueueDirty;

		bool mMeshDirty;
		bool mMatDirty;
		bool mCanCreateMaterial;
		bool mIsAllTexLoaded;

	protected:

		//GPtr<VegetationBrush> mVegeBrush;
		Graphic::RenderableResUnitArray mRenderableResUnitList;
		GPtr<Resources::PrimitiveResInfo> mMeshInfo;

		GPtr<VegeInstanceMap> mInstMap;
		//VegeRenderableArray mVegeRenderables;
		RenderObjectPtr mRenderObject;

		Math::quaternion mLocalRotation;
		Math::vector mLocalScale;		

		Util::FixedArray<VEGE_VERTEX_INSTANCE> m_vertices;
		Util::FixedArray<uchar> m_indices;
		RenderBase::PrimitiveHandle m_primHandle;
		//GPtr<RenderBase::PrimitiveGroup> m_primitiveGroup;

		RenderType m_renderType;

		bool mIsActive;
		Util::String mName;
		Util::String mInstanceFilePath;

		Math::matrix44 mWorldMatrix;

		Math::scalar mCullDistance;


		friend class VegetationServer;

	};

	//--------------------------------------------------------------------------------
	inline void VegetationObject::SetCullDistance(Math::scalar fDist)
	{
		mCullDistance = fDist;
	}
	//--------------------------------------------------------------------------------
	inline Math::scalar VegetationObject::GetCullDistance() const
	{
		return mCullDistance;
	}
	//-----------------------------------------------------------------------------
	inline RenderBase::PrimitiveHandle& VegetationObject::GetPrimHandle()
	{
		return m_primHandle;
	}
	//-----------------------------------------------------------------------------
	inline void VegetationObject::SetPrimHandle(const RenderBase::PrimitiveHandle& handle)
	{
		m_primHandle = handle;
	}

	////-----------------------------------------------------------------------------
	//inline GPtr<RenderBase::PrimitiveGroup>& VegetationObject::GetPrimGroup()
	//{
	//	return m_primitiveGroup;
	//}
	//-----------------------------------------------------------------------------
	inline VegetationObject::RenderObjectPtr& VegetationObject::GetRenderObject()
	{
		return mRenderObject;
	}
	//-----------------------------------------------------------------------------
	inline const VegeInstanceMapPtr& VegetationObject::GetInstanceMap() const
	{
		return mInstMap;
	}
	//-------------------------------------------------------------------------------
	inline VegeInstanceMapPtr& VegetationObject::GetInstanceMap()
	{
		return mInstMap;
	}
	//-----------------------------------------------------------------------------
	inline void VegetationObject::SetRenderType(RenderType etype)
	{
		m_renderType = etype;
	}
	//-----------------------------------------------------------------------------
	inline RenderType VegetationObject::GetRenderType(void) const
	{
		return m_renderType;
	}
	//------------------------------------------------------------------------
	inline bool VegetationObject::IsActive(void) const
	{
		return mIsActive;
	}
	//------------------------------------------------------------------------
	inline void VegetationObject::SetName( const Util::String& name)
	{
		if ( name.IsEmpty() )
		{
			return;
		}
		mName = name;
	}
	//------------------------------------------------------------------------
	inline const Util::String& VegetationObject::GetName(void) const
	{
		return mName;
	}
	//------------------------------------------------------------------------
	inline
		const Math::matrix44& 
		VegetationObject::GetWorldMatrix(void) const
	{
		return mWorldMatrix;
	}

	//--------------------------------------------------------------------------------
	inline void VegetationObject::SetInstanceFilePath( const Util::String& path)
	{
		mInstanceFilePath = path;
	}
	//--------------------------------------------------------------------------------
	inline const Util::String& VegetationObject::GetInstanceFilePath(void) const
	{
		return mInstanceFilePath;
	}
	//--------------------------------------------------------------------------------
	inline Math::quaternion VegetationObject::GetRotation() const
	{
		return this->mLocalRotation;
	}

	//--------------------------------------------------------------------------------	
	inline Math::vector VegetationObject::GetScale() const
	{
		return this->mLocalScale;
	}
	//--------------------------------------------------------------------------------	
	inline SizeT VegetationObject::GetMaterialCount() const
	{
		return mRenderableResUnitList.Size();
	}

	inline Util::FixedArray<VEGE_VERTEX_INSTANCE>& VegetationObject::GetVertices()
	{
		return m_vertices;
	}
	inline Util::FixedArray<uchar>& VegetationObject::GetIndices()
	{
		return m_indices;
	}
}

#endif //__VEGETATION_OBJECT_H__
