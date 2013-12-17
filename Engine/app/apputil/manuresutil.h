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
#ifndef __manuresutil_H__
#define __manuresutil_H__
#include "resource/meshres.h"
#include "util/string.h"
#include "math/float3.h"

namespace AppUtil
{
	class ManuResUtil
	{
	public:
		
		/**
		* CreateManuResource  manual create a resource
		* @param: const Util::String& expectResID  expect ResID     if res id is exist, will auto test "%expectResID%_N", and create "%expectResID%_N" as resource id  
		* @param: const Core::Rtti * ResType   the resource type for create
		* @return: GPtr<Resources::Resource>  if failed, return NULL
		* @see: 
		* @remark:  
		*/
		static GPtr<Resources::Resource> CreateManuResource( const Util::String& expectResID, const Core::Rtti* ResType);

		/**
		* CreateManuMesh   manual create a mesh
		* @param: const Resources::ResourceId & expectResID   if res id is exist, will auto test "%expectResID%_N", and create "%expectResID%_N" as resource id  
		* @return: GPtr<MeshRes>  
		* @see: 
		* @remark:  
		*/
		static GPtr<Resources::MeshRes> CreateManuMesh( const Util::String& expectResID );

		/**
		* CreateManuMesh_LineList  create a meshres with line list
		* @param: const Util::String & expectResID  if res id is exist, will auto test "%expectResID%_N", and create "%expectResID%_N" as resource id   
		* @param: SizeT numVertex                 vertex count, must >= 2 & <=65535
		* @param: const Math::float3 * position         position
		* @param: Math::Color32 color             color
		* @param: SizeT numIndex                  index count
		* @param: const Index16Container::value_type * indicies   index data ptr
		* @return: GPtr<Resources::MeshRes>  
		* @see:     
		* @remark:  if numIndex = 0 and indicies = NULL, we will create primitive like:  position[0]----position[1]   position[1]-----position[2]   position[2]-----position[3]
		*/
		static GPtr<Resources::MeshRes> CreateManuMesh_LineList( const Util::String& expectResID,
																SizeT numVertex,
																const Math::float3* position,
																Math::Color32 color,
																SizeT numIndex = 0,
																const Resources::Index16Container::value_type* indicies = NULL );


		///create box with trianglelist index
		static void Build_Box(const Math::bbox& bb, Resources::PositionData& pos, Resources::Index16Container& indicies);

		
		/***
		* Build_Cone   create vertext of an arrow
		* @param: Math::float3 inAxis  :  Axis of the cone .  eg: vector(1,0,0) means that was X-Axis
		* @param: Resources::PositionData& position  : the vertext Array
		* @param: Resources::Index16Container& indicies : index Array
		* @param: Math::scalar sThickness  : the angle of the cone
		* @param: Math::scalar sHRatio : the height of hemline
		* @param: Math::scalar sThickness : the thickness of the Column
		**/
		static void Build_Cone(Math::float3 inAxis, Resources::PositionData& position, Resources::Index16Container& indicies, Math::scalar sThickness = 0.05f, Math::scalar sHRatio = 0.7f);
		
		static void Build_Column(Math::float3 inAxis, Resources::PositionData& position, Resources::Index16Container& indicies, Math::scalar sThickness = 0.05f);

		/// set a cone mesh
		static GPtr<Resources::MeshRes> CreateManuMesh_WithTopology( const Util::String& expectResID,
			SizeT numVertex,
			const Math::float3* position,
			Math::Color32 color,
			SizeT numIndex = 0,
			const Resources::Index16Container::value_type* indicies = NULL ,
			RenderBase::PrimitiveTopology::Code ptCode = RenderBase::PrimitiveTopology::TriangleList);

		// set mesh data
		static bool SetMesh_LineList( GPtr<Resources::MeshRes>& mesh,
			SizeT numVertex,
			const Math::float3* position,
			Math::Color32 color,
			SizeT numIndex = 0,
			const Resources::Index16Container::value_type* indicies = NULL );
	};

}






#endif // __manuresutil_H__
