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
#include "skinnedrenderable.h"
#include "graphicsystem/Material/materialinstance.h"

namespace App
{
	SkinnedRenderable::SkinnedRenderable()
		: m_bUseHWSkinning(true)
		, m_bHasBuildRemap(false)
		, m_IsUseDrawMats(false)
		, m_DrawMats(NULL)
	{

	}

	SkinnedRenderable::~SkinnedRenderable()
	{
	}

	void SkinnedRenderable::UpdateRegIndexOfAffected()
	{
		SizeT nPass = GetMaterial()->GetTech()->GetPassList().Size();

		for (IndexT i = 0; i < nPass; ++i)
		{
			IndexT RegIndexOfAffected = GetMaterial()->GetRegisterIndex("gFinalXForms0", Graphic::SCT_VS, i);
			m_RegIndexOfAffected.Add(i, RegIndexOfAffected);
		}
	}

	void SkinnedRenderable::ResetFinalMatrix(SizeT size)
	{
		Reserve(size);
		m_AffectedTrans.Fill(Math::matrix44::identity());
	}
}