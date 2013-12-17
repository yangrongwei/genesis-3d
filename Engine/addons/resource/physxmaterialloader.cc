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
#include "resource/resource_stdneb.h"
#include "physxmaterialloader.h"

namespace Resources
{
	__ImplementClass(Resources::PhysXMaterialLoader,'PXLD',Resources::ResourceLoader);

	static const char* s_cPhysicsMatVersion  = "PhysicsMatVersion";
	static const char* s_cStaticFriction  = "StaticFriction";
	static const char* s_cDynamicFriction = "DynamicFriction";
	static const char* s_cRestitution	  = "Restitution";
	static const char* s_cStaticFrictionV  = "StaticFrictionV";
	static const char* s_cDynamicFrictionV = "DynamicFrictionV";
	static const char* s_cFrictionDirection  = "FrictionDirection";
	static const char* s_cFrictionCombineMode  = "FrictionCombineMode";
	static const char* s_cRestitutionCombineMode = "RestitutionCombineMode";

	PhysXMaterialLoader::PhysXMaterialLoader()
	{

	}

	PhysXMaterialLoader::~PhysXMaterialLoader()
	{

	}

	bool PhysXMaterialLoader::LoadResource( Resource* res )
	{
		if ( !res )
			return false;

		if ( res->GetRtti() != &PhysXMaterialRes::RTTI )
		{
			return false;
		}

		GPtr<Resource> pRes = res;
		GPtr<PhysXMaterialRes> pPhysXMaterialRes = pRes.downcast<PhysXMaterialRes>();
		n_assert(pPhysXMaterialRes);

		GPtr<Serialization::SerializeXmlReader> pReader =Serialization::SerializeXmlReader::Create();

		pReader->SetStream(mStream);

		n_assert(pReader.isvalid());

		if (!LoadPhysXMaterialRes(pPhysXMaterialRes,pReader))
		{
			return false;
		}

		return true;
	}

	bool PhysXMaterialLoader::LoadPhysXMaterialRes( GPtr<PhysXMaterialRes>& pRes,GPtr<Serialization::SerializeXmlReader>& pReader )
	{
		int version =1;

		pReader->BeginFileSerialize();

		if(pReader->HasAttr(s_cPhysicsMatVersion))
		{
			pReader->SerializeInt(s_cPhysicsMatVersion,version);
		}

		bool ret = LoadPhysXMaterialResByVersion(pRes,pReader,version);


		pReader->EndFileSerialize();
		return ret;
	}

	bool PhysXMaterialLoader::LoadPhysXMaterialResByVersion( GPtr<PhysXMaterialRes>& pRes,GPtr<Serialization::SerializeXmlReader>& pReader,int version )
	{
		float staticFriction = 0.f;
		float dynamicFriction = 0.f;
		float Restitution = 0.f;
		float staticFrictionV = 0.f;
		float dynamicFrictionV = 0.f;
		Math::float3 FrictionDir;
		uint frictionCombineMode = 0;
		uint restitutionCombineMode = 0;

		if(version==1)
		{
			pReader->SerializeFloat(s_cStaticFriction,   staticFriction);
			pReader->SerializeFloat(s_cDynamicFriction,  dynamicFriction);
			pReader->SerializeFloat(s_cRestitution,		 Restitution);
			pReader->SerializeFloat(s_cStaticFrictionV,   staticFrictionV);
			pReader->SerializeFloat(s_cDynamicFrictionV,  dynamicFrictionV);
			pReader->SerializeFloat3(s_cFrictionDirection,	 FrictionDir);
			pReader->SerializeUInt(s_cFrictionCombineMode,   frictionCombineMode);
			pReader->SerializeUInt(s_cRestitutionCombineMode,  restitutionCombineMode);

			pRes->SetStaticFriction(staticFriction);
			pRes->SetDynamicFriction(dynamicFriction);
			pRes->SetRestitution(Restitution);
			//pRes->SetStaticFrictionV(staticFrictionV);
			//pRes->SetDynamicFrictionV(dynamicFrictionV);
			//pRes->SetFrictionDir(FrictionDir);
			pRes->SetFrictionCombine(frictionCombineMode);
			pRes->SetRestitutionCombine(restitutionCombineMode);
			return true;
		}
		else if(version == 2)
		{
			pReader->SerializeFloat(s_cStaticFriction,   staticFriction);
			pReader->SerializeFloat(s_cDynamicFriction,  dynamicFriction);
			pReader->SerializeFloat(s_cRestitution,		 Restitution);
			pReader->SerializeUInt(s_cFrictionCombineMode,   frictionCombineMode);
			pReader->SerializeUInt(s_cRestitutionCombineMode,  restitutionCombineMode);

			pRes->SetStaticFriction(staticFriction);
			pRes->SetDynamicFriction(dynamicFriction);
			pRes->SetRestitution(Restitution);
			pRes->SetFrictionCombine(frictionCombineMode);
			pRes->SetRestitutionCombine(restitutionCombineMode);
		}
		else
		{
			return false;
		}
		return true;
	}

}