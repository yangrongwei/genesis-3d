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

#ifndef __VEGETATION_SERVER_H__
#define __VEGETATION_SERVER_H__
#include "vegetation/InstanceMap.h"
#include "vegetation/vegetation_fwd_decl.h"

namespace Vegetation
{
	/*! \class VegetationServer VegetationServer.h
	*  \brief  This is a class.
	*
	* for Serialization. !!!!
	* Do not create extern!!!!!
	*/
	class VegetationInstanceContainer: public Core::RefCounted, Serialization::ISerialize
	{
		__DeclareClass( VegetationInstanceContainer ); 

	public:

		VegetationInstanceContainer(){ };
		virtual ~VegetationInstanceContainer(){ };

		// @ISerialization::GetVersion. when change storage, must add SerializeSVersion count
		virtual Serialization::SVersion GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Serialization::SVersion ver, Serialization::SerializeReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( Serialization::SerializeWriter* pWriter ) const;

		Util::Dictionary<Util::StringAtom, VegeInstanceMapPtr> mContainer;
	};

	/*! \class VegetationServer VegetationServer.h
	*  \brief  This is a class.
	*
	*  setup a thread for update vegetation render data
	*/
	class VegetationServer: public Core::RefCounted
	{
		__DeclareClass(VegetationServer);
		__DeclareImageSingleton(VegetationServer);

	public:

		VegetationServer();
		virtual ~VegetationServer();

		//-------------------------------manage template-----------------------------------------
		bool OpenTemplateFile( Util::String filePath = Util::String("asset:vegetation.veg") );

		void SaveTemplateFile( Util::String filePath = Util::String("asset:vegetation.veg") );

		VegeInstanceMapPtr CreateFromTemplate(const Util::StringAtom& tplname);
		VegeInstanceMapPtr CreateFromLast();

		SizeT GetTemplateCount(void) const;

		bool HasTemplate(const Util::StringAtom&) const;

		const VegeInstanceMapPtr& GetTemplate(IndexT index ) const;  

		const VegeInstanceMapPtr& FindTemplate(const Util::StringAtom& name) const;

		// add template . if exist, replace; Else add a new template.
		bool AddTemplate(const Util::StringAtom& tplname, const VegeInstanceMapPtr& instmap );

		// Remove template. 
		void RemoveTemplate( const Util::StringAtom& tplName );

		//-------------------------------manage active ParticleSystem -----------------------------------------
		SizeT GetActiveCount(void) const;

		void Update(void);

		void ClearActives();

	protected:
		void _attachVegetationInstMap( const VegeInstanceMapPtr& instmap );
		void _deattachVegetationInstMap( const VegeInstanceMapPtr& instmap );

	protected:

		GPtr<VegetationInstanceContainer> mTemplates;

		Util::Array<VegeInstanceMapPtr> mActives;

		friend class VegeInstanceMap;
	};

	//------------------------------------------------------------------------
	inline SizeT VegetationServer::GetTemplateCount(void) const
	{
		return mTemplates->mContainer.Size();
	}
	//------------------------------------------------------------------------
	inline bool VegetationServer::HasTemplate(const Util::StringAtom& name) const
	{
		return mTemplates->mContainer.FindIndex( name ) != InvalidIndex;
	}
	//------------------------------------------------------------------------
	inline const VegeInstanceMapPtr&  VegetationServer::GetTemplate(IndexT index ) const
	{
		if ( index >= 0 && index < mTemplates->mContainer.Size() )
		{
			return mTemplates->mContainer.ValueAtIndex( index );
		}
		else
		{
			return VegeInstanceMap::NullVegeInstMap;
		}
	}
	//------------------------------------------------------------------------
	inline const VegeInstanceMapPtr& VegetationServer::FindTemplate(const Util::StringAtom& name) const
	{
		IndexT findIndex = mTemplates->mContainer.FindIndex( name );
		return GetTemplate( findIndex );
	}
	//------------------------------------------------------------------------
	inline SizeT VegetationServer::GetActiveCount(void) const
	{
		return mActives.Size();
	}
}
#endif // __VEGETATION_SERVER_H__