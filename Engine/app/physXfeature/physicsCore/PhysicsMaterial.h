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
#ifndef __PHYSICSMATERIAL_H__
#define __PHYSICSMATERIAL_H__

#include "core/refcounted.h"
#include "util/string.h"
#include "PhysicsDeclaration.h"

using namespace physx;

namespace App
{
	class PhysicsMaterial : public Core::RefCounted
	{
		__DeclareSubClass( PhysicsMaterial, Core::RefCounted );

	public://nested struct
		enum CombineMode
		{
			AVERAGE	= 0,		//!< Average: (a + b)/2
			MIN		= 1,		//!< Minimum: minimum(a,b)
			MULTIPLY= 2,		//!< Multiply: a*b
			MAX		= 3,		//!< Maximum: maximum(a,b)
		};
		enum MaterialFlag
		{
			eDISABLE_FRICTION = 1 << 0,
			eDISABLE_STRONG_FRICTION = 1 << 1,
		};

		// The fast way to create an PhysicsMaterial;
		static PhysicsMaterial* Create(Util::String& materialFile);

		static PhysicsMaterial* Create(Math::scalar staticFriction, Math::scalar dynamicFriction, Math::scalar restitution,
			CombineMode frictionCombine /*= AVERAGE*/, CombineMode restitutionCombine /*= AVERAGE*/);

		PhysicsMaterial();
		virtual ~PhysicsMaterial();
		virtual bool OnCreate();
		virtual bool OnDestory();

		void SetStaticFriction(Math::scalar friction);

		void SetDynamicFriction(Math::scalar friction);

		void SetRestitution(Math::scalar bounce);

		void SetFrictionCombineMode(CombineMode combineMode);

		void SetRestitutionCombineMode(CombineMode bounceMode);

		Math::scalar GetStaticFriction() const { return m_fStaticFriction; }

		Math::scalar GetDynamicFriction() const { return m_fDynamicFriction; }

		Math::scalar GetRestitution() const { return m_fRestitution; }

		CombineMode GetFrictionCombineMode() const { return m_eFrictionComine; }

		CombineMode GetRestitutionCombineMode() const { return m_eRestitutionCombine; }

		void SetFlag(MaterialFlag flag, bool v);

		bool GetFlag(MaterialFlag flag) const;

		void SetMatFile(Util::String& file) { m_sPhyXMatID = file; }

		Util::String GetMatFile() const { return m_sPhyXMatID; }

		void SetMaterial(PxMaterial* pMaterial);

		PxMaterial* GetMaterial() const {  return m_pPhysXMaterial; }

		void SetLoadFromFile(bool fromFile) { m_bCreateFromFile = fromFile; }

		bool IsLoadFromFile() { return m_bCreateFromFile; }
	private:

		Util::String   m_sPhyXMatID;
		Math::scalar   m_fStaticFriction;
		Math::scalar   m_fDynamicFriction;
		Math::scalar   m_fRestitution;
		CombineMode    m_eFrictionComine;
		CombineMode    m_eRestitutionCombine;
		PxMaterial*    m_pPhysXMaterial;
		bool		   m_bCreateFromFile;
	};

}







#endif
