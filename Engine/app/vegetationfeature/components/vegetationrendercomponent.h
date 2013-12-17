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

#ifndef __VEGETATION_RENDER_COMPONENT_H__
#define __VEGETATION_RENDER_COMPONENT_H__

#include "appframework/component.h"
#include "rendersystem/base/PrimitiveGroup.h"
#include "vegetation/vegetation_fwd_decl.h"
#include "vegetation/VegetationObejct.h"
#include "vegetation/InstanceMap.h"

namespace App
{
	//typedef Util::Dictionary<SizeT, MaterialArray> MatrerialListMap;

	/*! \class VegetationRenderComponent
	*  \brief  This is a VegetationRenderComponent class.
	*
	* Be attach with a Actor, used for organizing vegetation data
	*/
	class VegetationRenderComponent: public Component
	{
		__DeclareSubClass(VegetationRenderComponent, Component );


	public:
		struct STR_TERRAINBLOCK
		{
			int xmin;
			int ymin;
			int width;
			int height;
			float heimapX;
			float heimapY;
			float terrainWidth;
			float terrainHeight;
		};

	public:

		VegetationRenderComponent();

		virtual ~VegetationRenderComponent();

		/// setup callbacks for this Component, call by Actor in OnActivate()
		virtual void SetupCallbacks(void);

		/// @Component::SetupAcceptedMessages override to register accepted messages
		virtual void SetupAcceptedMessages();

		/// @Component::SetupAcceptedMessages handle a single message
		virtual void HandleMessage(const GPtr<Messaging::Message>& msg);

		virtual void UpdateRenderLayer();

		/// create a vegeobjet
		GPtr<Vegetation::VegetationObject>& CreateVegetationObject( Vegetation::RenderType etype,  const Resources::ResourceId& meshID = "");

		/// add a valid object
		void AddVegetationObject(const GPtr<Vegetation::VegetationObject>&);

		/// inset a obj
		void InsetVegetationObject(IndexT, const GPtr<Vegetation::VegetationObject>&);

		/// remove a vegeobj
		void RemoveVegetationObject(IndexT);

		void SetShaderId(GPtr<Vegetation::VegetationObject>&, IndexT iSubMesh , const Resources::ResourceId& shaderID);
		/// set meshid 
		void SetMeshID(GPtr<Vegetation::VegetationObject>&, const Resources::ResourceId& );

		void SetMeshID(IndexT, const Resources::ResourceId& );

		/// get vegeobject
		const GPtr<Vegetation::VegetationObject>& GetVegetObject(IndexT index) const;

		/// 
		GPtr<Vegetation::VegetationObject>& GetVegetObject(IndexT index);

		/// get size of vegeobject array
		SizeT GetCountOfObjectArray() const;

		IndexT IntersectInstance( const Actor* camerActor, const Math::float2& mousepos, IndexT nIdx, Math::scalar& fout);

		void NotifiedTerrainChanged(const STR_TERRAINBLOCK&,const Math::scalar& scaleX,const Math::scalar& scaleZ);
		/// called after hole created
		void NotifiedTerrainHole(const STR_TERRAINBLOCK& terrblock);

		void ReCalcBBox(const GPtr<Vegetation::VegetationObject>& vegetObj);

		//	Serialization
		// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
		virtual Version GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( AppWriter* pWriter ) const;

		// copy from other component
		virtual void CopyFrom( const GPtr<Component>& pComponent );
		virtual void GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const;

		virtual void SetVisible(bool bVisible);

		bool CreateInstanceMap(const GPtr<Vegetation::VegetationObject>& obj);

	protected:
		/// @Component::OnActivate  called from Actor::ActivateComponents()
		virtual void OnActivate();

		/// @Component::OnDeactivate called from Actor::DeactivateComponents()
		virtual void OnDeactivate();

		// @Component::_OnDestroy called only form Actor::Destroy
		virtual void OnDestroy();

		virtual void OnRenderSceneChanged();

		virtual void _OnBeginFrame();

		virtual void _OnFrame();

		virtual void _OnMoveBefore();

		virtual void _OnMoveAfter();

		void BuildRenderData( void );
		void _BuildRenderData(  GPtr<Vegetation::VegetationObject>&  );

		void UpdateRenderData(void);
		void _UpdateRenderData(  GPtr<Vegetation::VegetationObject>&  );

		void DiscardRenderData(void);
		void _DiscardRenderData(  GPtr<Vegetation::VegetationObject>&  );
		void _CleanRenderData();

		void AttachRenderObjects(void);
		void _AttachRenderObject(  GPtr<Vegetation::VegetationObject>&  );

		void DeattachRenderObjects(void);
		void _DeattachRenderObject(  GPtr<Vegetation::VegetationObject>&  );

		bool  _LoadBrushRes(GPtr<Vegetation::VegetationObject>&);
		bool  _LoadBrushMaterials(GPtr<Vegetation::VegetationObject>&);

		void _CalculateBBox(Math::bbox& box, const GPtr<Vegetation::VegeInstanceMap>& instmap) ; 



	protected:
		Util::Array<Vegetation::VegetationObjectPtr> mRenderDates;
		bool mIsTrans;
		bool mVisible;
	};


	//--------------------------------------------------------------------------------
	inline const GPtr<Vegetation::VegetationObject>& VegetationRenderComponent::GetVegetObject(IndexT index) const
	{
		static GPtr<Vegetation::VegetationObject> nullVegetationObject;
		if ( !(index >= 0 && index < mRenderDates.Size()) )
		{
			return nullVegetationObject;
		}

		return mRenderDates[index];
	}
	//--------------------------------------------------------------------------------
	inline GPtr<Vegetation::VegetationObject>& VegetationRenderComponent::GetVegetObject(IndexT index)
	{
		static GPtr<Vegetation::VegetationObject> nullVegetationObject;
		if ( !(index >= 0 && index < mRenderDates.Size()) )
		{
			return nullVegetationObject;
		}
		return mRenderDates[index];
	}
	//--------------------------------------------------------------------------------
	inline SizeT VegetationRenderComponent::GetCountOfObjectArray() const
	{
		return mRenderDates.Size();
	}
}
#endif //__VEGETATION_RENDER_COMPONENT_H__