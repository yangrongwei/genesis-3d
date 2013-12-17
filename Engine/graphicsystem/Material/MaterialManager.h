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
#ifndef __MaterialManager_H__
#define __MaterialManager_H__
#include "graphicsystem/GraphicSystem.h"
#include "addons/serialization/serialize.h"



namespace Graphic
{

	class MaterialInstanceManager: public Core::RefCounted
	{
		__DeclareClass( MaterialInstanceManager )


	public:
		typedef Resources::ResourceId MaterialId;

		MaterialInstanceManager();
		virtual ~MaterialInstanceManager();

	public:	


		// will be deprecated
		GPtr<Graphic::MaterialInstance>			CreateMaterialInstance( const Resources::ResourceId& shaderID );
		GPtr<Graphic::MaterialInstance>			NewMaterialInstanceCopyByMatID(const MaterialId& matID);
		bool									HaveMaterialInstance(const MaterialId& matID);
		const GPtr<Graphic::MaterialInstance>&	GetMaterialInstance(const MaterialId& matID);

		// for serialization.
		GPtr<Graphic::MaterialInstance>			LoadMaterialInstance(const MaterialId& matID,const Resources::ResourceId& shaderID );

		void									RemoveMaterialInstance(const MaterialId& matID);

		GPtr<Graphic::MaterialInstance>			ModifyMaterialInstance(const MaterialId& matID,const Resources::ResourceId& newShaderID);

		/*
		* change material id.
		Note： temp code.
		此为临时代码，为临时解决材质名字冲突问题，在材质修改自动反射机制建立前，除fbx导入模块，其他地方不要调用它
		*/
		void									ModifyMaterialInstanceID(const MaterialId& matID,const MaterialId& newMatID);
		void									SaveMaterial();
		void									SaveOneMaterialInstance(const Resources::ResourceId& matID);
		const IndexT							GetMaterialNameIdx()const;
		const SizeT								GetMaterialCnt()const ;
		GPtr<Graphic::MaterialInstance>			UpdateShader(const Resources::ResourceId& shaderID);
		Util::String							GetInitParamValue(const Resources::ResourceId& matID,int paramIndex);
	protected:

		//
		GPtr<Graphic::MaterialInstance>			_CreateMaterialInstance( const Resources::ResourceId& shaderID );
		GPtr<Graphic::MaterialInstance>			_CreateNewMaterialInstance( const Resources::ResourceId& shaderID );
		void									_SetMaterialID(GPtr<Graphic::MaterialInstance>& matIns);	
		void									_InitMaterialInstance(GPtr<Graphic::MaterialInstance>& matIns, const Resources::ResourceId& shaderID,const GPtr<Graphic::Material>& mat);

	private:

		typedef Util::Dictionary< Resources::ResourceId, GPtr<Graphic::Material> >			GraphicMaterialMap;
		typedef Util::Dictionary< MaterialId, GPtr<Graphic::MaterialInstance> > GraphicMaterialInstanceMap;
		GraphicMaterialMap						m_graphicMaterialMap;
		GraphicMaterialInstanceMap				m_graphicMaterialInstanceMap;	
		IndexT									m_usedMaterialNameIdx;

		friend class MaterialInstanceManagerSerialization;
		friend class MaterialInstanceSerialization;
	};
	inline const IndexT MaterialInstanceManager::GetMaterialNameIdx()const
	{
		return m_usedMaterialNameIdx;
	}
	inline const SizeT MaterialInstanceManager::GetMaterialCnt()const 
	{
		return m_graphicMaterialInstanceMap.Size();
	}
}
#endif //MATERIALINSTANCE_H_
