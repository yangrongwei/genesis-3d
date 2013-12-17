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
#include "physxmaterialres.h"

namespace Resources
{
	__ImplementClass(Resources::PhysXMaterialRes, 'PXMT', Resources::Resource);

	PhysXMaterialRes::PhysXMaterialRes()
		:m_pPxMat(0)
		,m_StaticFriction(0.f)
		,m_DynamicFriction(0.f)
		,m_Restitution(0.f)
		,m_FrictionCombine(0)
		,m_RestitutionCombine(0)
	{

	}

	PhysXMaterialRes::~PhysXMaterialRes()
	{

	}

	SizeT PhysXMaterialRes::CalculateRuntimeSize( void ) const
	{
		return Super::CalculateRuntimeSize()+40;
	}

	bool PhysXMaterialRes::SwapLoadImpl( const GPtr<Resource>& tempRes )
	{

		n_assert( tempRes.isvalid() );
		if ( tempRes->GetRtti() == this->GetRtti() )
		{
			GPtr<PhysXMaterialRes> physXMat = tempRes.downcast<PhysXMaterialRes>();
			n_assert( physXMat.isvalid() );
			this->m_StaticFriction = physXMat->GetStaticFriction();
			this->m_DynamicFriction = physXMat->GetDynamicFriction();
			this->m_Restitution = physXMat->GetRestitution();
			this->m_FrictionCombine = physXMat->GetFrictionCombine();
			this->m_RestitutionCombine = physXMat->GetRestitutionCombine();
			return true;
		}
		return false;
	}

	void PhysXMaterialRes::UnLoadImpl( void )
	{
		m_StaticFriction    = 0.f;
		m_DynamicFriction   = 0.f;
		m_Restitution		= 0.f;
		m_FrictionCombine	= 0;
		m_RestitutionCombine = 0;
	}

}
