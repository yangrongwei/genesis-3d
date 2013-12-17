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
#include "vegetation/MeshInstanceMap.h"
#include "vegetation/VegetationObejct.h"

namespace Vegetation
{
	using namespace Serialization;


	class MeshInstanceMapSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( MeshInstanceMap* obj,  SVersion ver, SerializeReader* pReader )
		{
			if ( 1 == ver )
			{
				Load_1(obj, pReader);
				return;
			}
			n_error(" %s Load unknown version.\n", obj->GetClassName().AsCharPtr() );
		}
		//------------------------------------------------------------------------
		void Load_1(MeshInstanceMap* obj, SerializeReader* pReader)
		{


		}
		//------------------------------------------------------------------------
		void Save( const MeshInstanceMap* obj, SerializeWriter* pWriter )
		{

		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion MeshInstanceMap::GetVersion() const
	{
		return 1;	//	current version is 1
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void MeshInstanceMap::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		MeshInstanceMapSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void MeshInstanceMap::Save( SerializeWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		MeshInstanceMapSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void MeshInstanceMap::CopyFrom( const GPtr<VegeInstanceMap>& instmap )
	{
		if( !instmap.isvalid()  )
			return;
		if( !instmap->GetRtti()->IsDerivedFrom( *(this->GetRtti()) ) )
			return;

		Super::CopyFrom(instmap);
	}

}