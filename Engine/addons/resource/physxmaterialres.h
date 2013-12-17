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
#ifndef __physxmaterial_H__
#define __physxmaterial_H__
#include "resource/resource.h"
#include "util/dictionary.h"

namespace App
{
	class	PhysicsMaterial;
}

namespace Resources
{
	class PhysXMaterialRes: public Resources::Resource
	{
		__DeclareSubClass(PhysXMaterialRes, Resource );
	public:
		PhysXMaterialRes();
		virtual ~PhysXMaterialRes();

		// @Resource::CalculateRuntimeSize
		virtual SizeT CalculateRuntimeSize(void) const;
	public:
		void SetStaticFriction (float sfriction );
		void SetDynamicFriction(float dfriction );
		void SetRestitution    (float restitute );
		void SetFrictionCombine (uint mode);
		void SetRestitutionCombine(uint mode);
		void SetMat       ( Core::RefCounted* pMat);

		float GetStaticFriction () const;
		float GetDynamicFriction() const;
		float GetRestitution    () const;
		uint   GetFrictionCombine () const;
		uint   GetRestitutionCombine() const;
		App::PhysicsMaterial* GetMat();

	protected:
		// @Resource::SwapLoadImpl
		virtual bool SwapLoadImpl( const GPtr<Resource>& tempRes);
		// @Resource::UnLoadImpl
		virtual void UnLoadImpl(void);

	protected:
		float		               m_StaticFriction ;
		float		               m_DynamicFriction ;
		float					   m_Restitution ;
		uint			           m_FrictionCombine ;
		uint			           m_RestitutionCombine ;
		GPtr<Core::RefCounted>      m_pPxMat;
	};

	inline void PhysXMaterialRes::SetStaticFriction( float sfriction )
	{
		m_StaticFriction = sfriction;
	}

	inline void PhysXMaterialRes::SetDynamicFriction( float dfriction )
	{
		m_DynamicFriction = dfriction;
	}

	inline void PhysXMaterialRes::SetRestitution( float restitute )
	{
		m_Restitution     = restitute;
	}

	inline void PhysXMaterialRes::SetFrictionCombine( uint mode )
	{
		m_FrictionCombine = mode;
	}

	inline void PhysXMaterialRes::SetRestitutionCombine( uint mode )
	{
		m_RestitutionCombine = mode;
	}

	inline void PhysXMaterialRes::SetMat( Core::RefCounted* pMat )
	{
		m_pPxMat = pMat;
	}

	inline float PhysXMaterialRes::GetStaticFriction() const
	{
		return m_StaticFriction;
	}

	inline float PhysXMaterialRes::GetDynamicFriction() const
	{
		return m_DynamicFriction;
	}

	inline float PhysXMaterialRes::GetRestitution() const
	{
		return m_Restitution;
	}

	inline uint PhysXMaterialRes::GetFrictionCombine() const
	{
		return m_FrictionCombine;
	}

	inline uint PhysXMaterialRes::GetRestitutionCombine() const
	{
		return m_RestitutionCombine;
	}

	inline App::PhysicsMaterial* PhysXMaterialRes::GetMat()
	{
		return (App::PhysicsMaterial*)m_pPxMat.get_unsafe();
	}
}
#endif