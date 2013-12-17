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
#include "vegetation/InstanceMap.h"
#include "vegetation/VegetationObejct.h"

namespace Vegetation
{
	const char* s_InstanceName = "TplName";
	const char* s_InstanceHardWare = "HardWareInst";
	const char* s_InstanceDataCount = "InstCount";
	const char* s_InstanceDataPos = "InstPos";
	const char* s_InstanceDataScale = "InstScale";
	const char* s_InstanceDataRotate = "InstRotate";
	const char* s_InstanceDataColor = "InstColor";
	const char* s_InstanceDataWave = "InstWave";

	using namespace Serialization;


	class InstanceMapSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( VegeInstanceMap* obj,  SVersion ver, SerializeReader* pReader)
		{
			if ( 1 == ver )
			{
				Load_1(obj, pReader);
				return;
			}
			else if ( 2 == ver )
			{
				Load_2(obj, pReader);
				return;
			}
			n_error(" %s Load unknown version.\n", obj->GetClassName().AsCharPtr() );
		}
		//------------------------------------------------------------------------
		void Load_1(VegeInstanceMap* obj, SerializeReader* pReader)
		{
			//Util::String name;			
			//pReader->SerializeString( s_InstanceName, name );

			bool hwInst;
			pReader->SerializeBool( s_InstanceHardWare, hwInst );
			obj->SetHWInstacing(hwInst);			

			int	instCount;
			pReader->SerializeInt( s_InstanceDataCount, instCount );

			for (int i = 0; i < instCount; ++i)
			{
				INSTANCEDATA_POS inst_pos;
				pReader->SerializeFloat3( s_InstanceDataPos, inst_pos.pos );
				float scale = 1;
				pReader->SerializeFloat( s_InstanceDataScale, scale  );
				inst_pos.scale.set(scale, scale, scale);
				Math::float2 rotate(0, 0);
				pReader->SerializeFloat2( s_InstanceDataRotate, rotate  );
				if (rotate.x() == 0) // rotate by x axis
				{
					inst_pos.rotate.set(rotate.y(), 0, 0);
				}
				else if (rotate.x() == 1) // rotate by y axis
				{
					inst_pos.rotate.set(0, rotate.y(), 0);
				}
				else if (rotate.x() == 2) // rotate by z axis
				{
					inst_pos.rotate.set(0, 0, rotate.y());
				}
				pReader->SerializeFloat( s_InstanceDataColor, inst_pos.color );
				pReader->SerializeFloat( s_InstanceDataWave, inst_pos.wave );
				obj->AddInstance(inst_pos);

			}
		}

		//------------------------------------------------------------------------
		void Load_2(VegeInstanceMap* obj, SerializeReader* pReader)
		{
			//Util::String name;			
			//pReader->SerializeString( s_InstanceName, name );

			bool hwInst;
			pReader->SerializeBool( s_InstanceHardWare, hwInst );
			obj->SetHWInstacing(hwInst);			

			int	instCount;
			pReader->SerializeInt( s_InstanceDataCount, instCount );

			for (int i = 0; i < instCount; ++i)
			{
				INSTANCEDATA_POS inst_pos;
				pReader->SerializeFloat3( s_InstanceDataPos, inst_pos.pos );
				pReader->SerializeFloat3( s_InstanceDataScale, inst_pos.scale);
				pReader->SerializeFloat3( s_InstanceDataRotate, inst_pos.rotate);
				pReader->SerializeFloat( s_InstanceDataColor, inst_pos.color );
				pReader->SerializeFloat( s_InstanceDataWave, inst_pos.wave );
				obj->AddInstance(inst_pos);

			}
		}
		//------------------------------------------------------------------------
		void Save( const VegeInstanceMap* obj, SerializeWriter* pWriter )
		{

			//pWriter->SerializeString( s_InstanceName, obj->GetName() );			
			pWriter->SerializeBool(s_InstanceHardWare, obj->IsHWInstancing() );

			SizeT count = obj->GetInstanceCount();
			pWriter->SerializeInt(s_InstanceDataCount, count );

			//const Math::matrix44& _parMat = obj->GetParentVegeObject()->GetWorldMatrix();
			//const Math::matrix44& invMatrix = Math::matrix44::inverse(_parMat);

			for (IndexT curInst = 0; curInst < count; ++curInst)
			{
				const INSTANCEDATA_POS& tPos = obj->GetInstance(curInst);
				pWriter->SerializeFloat3(s_InstanceDataPos, tPos.pos/*.transformPoint(invMatrix)*/ );
				pWriter->SerializeFloat3(s_InstanceDataScale, tPos.scale );
				pWriter->SerializeFloat3(s_InstanceDataRotate, tPos.rotate);
				pWriter->SerializeFloat(s_InstanceDataColor, tPos.color );
				pWriter->SerializeFloat(s_InstanceDataWave, tPos.wave );
			}

		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion VegeInstanceMap::GetVersion() const
	{
		return 2;	//	current version is 2
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void VegeInstanceMap::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		InstanceMapSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void VegeInstanceMap::Save( SerializeWriter* pWriter ) const
	{
		InstanceMapSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void VegeInstanceMap::CopyFrom(const GPtr<VegeInstanceMap>& instmap )
	{
		SizeT count = instmap->GetInstanceCount();
		for (IndexT curInst = 0; curInst < count; ++curInst)
		{
			INSTANCEDATA_POS* tPos = instmap->GetInstance(curInst);
			this->AddInstance( *tPos);
		}
	}

}