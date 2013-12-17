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
#include "physxmaterialsaver.h"
#include "reslable.h"

namespace Resources
{
	__ImplementClass(Resources::PhysXMaterialSaver,'PXSA',Resources::ResourceSaver);
	static const char* s_cPhysicsMatVersion  = "PhysicsMatVersion";
	static const char* s_cStaticFriction  = "StaticFriction";
	static const char* s_cDynamicFriction = "DynamicFriction";
	static const char* s_cRestitution	  = "Restitution";
	static const char* s_cFrictionCombineMode  = "FrictionCombineMode";
	static const char* s_cRestitutionCombineMode = "RestitutionCombineMode";

	PhysXMaterialSaver::PhysXMaterialSaver()
	{

	}

	PhysXMaterialSaver::~PhysXMaterialSaver()
	{

	}

	bool PhysXMaterialSaver::SaveResource( Resource* res )
	{

		GPtr<Serialization::SerializeWriter> pWriter = Serialization::SerializeXmlWriter::Create();
		n_assert(pWriter.isvalid());

		pWriter->SetStream( mStream );

		return SavePhysXMaterialRes(res, pWriter);
	}

	bool PhysXMaterialSaver::SavePhysXMaterialRes(const GPtr<Resource> pRes ,GPtr<Serialization::SerializeWriter>& pWriter)
	{
		pWriter->BeginFileSerialize();
		GPtr<PhysXMaterialRes> phyMatRes = pRes.downcast<PhysXMaterialRes>();
		pWriter->SerializeInt(s_cPhysicsMatVersion,GetVersion());
		pWriter->SerializeFloat(s_cStaticFriction,phyMatRes->GetStaticFriction());
		pWriter->SerializeFloat(s_cDynamicFriction,phyMatRes->GetDynamicFriction());
		pWriter->SerializeFloat(s_cRestitution,phyMatRes->GetRestitution());
		pWriter->SerializeUInt(s_cFrictionCombineMode,phyMatRes->GetFrictionCombine());
		pWriter->SerializeUInt(s_cRestitutionCombineMode,phyMatRes->GetRestitutionCombine());
		pWriter->EndFileSerialize();
		return true;
	}
}