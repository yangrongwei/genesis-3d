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

#ifndef _SKINNEDRENDERABLE_H_
#define _SKINNEDRENDERABLE_H_
#include "app/graphicfeature/components/apprenderable.h"
namespace App
{		
	typedef Util::Array<Math::matrix44> DrawMatrices;
	typedef DrawMatrices* DrawMatricesPtr;
	typedef Util::Array<uchar> AffectedBones;
	typedef Util::FixedArray<Math::matrix44> AffectedTransform;
	class SkinnedRenderable : public AppRenderable
	{
	public:
		enum RegIndex
		{
			UnkownIndex = -1
		};
		SkinnedRenderable();
		~SkinnedRenderable();

		void SetAffectedBones(const AffectedBones& bonesArray);

		const Util::Array<uchar>& GetAffectedBonesIndex() const;

		void UpdateRegIndexOfAffected();

		SizeT GetAffectedBonesCount() const;

		void SetFinalMatrix(int index, const Math::matrix44& finalTrans);

		void ResetFinalMatrix(SizeT size);

		void SetHWSkinning(bool enable);

		const bool HasUseHWSkinning() const;

		void Reserve(SizeT size);

		const IndexT& GetBoneIndexRemap(IndexT index) const;

		void SetBuildBoneRemap(bool enable);

		const bool HasBuildBoneRemap() const;

		void BuildBoneRemap();

		//Used when multiple render in one frame, e.g particle's skin animation
		void SetDrawMats(DrawMatricesPtr ptrMatrixArray);

		DrawMatricesPtr GetDrawMats(void) const;

		void SetUseDrawMats(bool bset);

		bool UseDrawMats() const;

		int GetRegIndexOfAffected(IndexT iPass) const;

		const AffectedTransform& GetAffectedTransform() const;

		//friend class SkinnedRenderObject;
	protected:
		typedef Util::Dictionary<IndexT, IndexT> BoneIndexRemap;

		AffectedBones  m_AffectedBones;
		AffectedTransform m_AffectedTrans;
		BoneIndexRemap m_BoneIndexRemap;

		// matrix data used when multiple render in one frame 
		DrawMatricesPtr m_DrawMats;

		//True when use hardware, false when use software
		bool m_bUseHWSkinning;

		bool m_bHasBuildRemap;

		// is or not use the matrix which used when multiple render in one frame 
		bool m_IsUseDrawMats;

		//the number i Pass's Register index 
		Util::Dictionary<IndexT, IndexT> m_RegIndexOfAffected;

	};

	inline void SkinnedRenderable::SetAffectedBones(const AffectedBones& bonesArray)
	{
		m_AffectedBones = bonesArray;
	}

	inline const Util::Array<uchar>& SkinnedRenderable::GetAffectedBonesIndex() const
	{
		return m_AffectedBones;
	}

	inline SizeT SkinnedRenderable::GetAffectedBonesCount() const
	{
		return m_AffectedBones.Size();
	}

	inline void SkinnedRenderable::SetFinalMatrix(int index, const Math::matrix44& finalTrans)
	{
		m_AffectedTrans[index] = finalTrans;
	}

	inline void SkinnedRenderable::SetHWSkinning(bool enable)
	{
		m_bUseHWSkinning = enable;
	}

	inline const bool SkinnedRenderable::HasUseHWSkinning() const
	{
		return m_bUseHWSkinning;
	}

	inline void SkinnedRenderable::Reserve(SizeT size)
	{
		if (size != m_AffectedTrans.Size())
		{
			m_AffectedTrans.Resize(size);
		}
	}

	inline const IndexT& SkinnedRenderable::GetBoneIndexRemap(IndexT index) const
	{
		return m_BoneIndexRemap[index];
	}

	inline void SkinnedRenderable::SetBuildBoneRemap(bool enable)
	{
		m_bHasBuildRemap = enable;
	}

	inline const bool SkinnedRenderable::HasBuildBoneRemap() const
	{
		return m_bHasBuildRemap;
	}

	inline void SkinnedRenderable::BuildBoneRemap()
	{
		for (IndexT i = 0; i<m_AffectedBones.Size(); ++i)
		{
			m_BoneIndexRemap.Add(i, (IndexT)m_AffectedBones[i]);
		}
	}

	inline void SkinnedRenderable::SetDrawMats(DrawMatricesPtr ptrMatrixArray)
	{
		m_DrawMats = ptrMatrixArray;
		m_IsUseDrawMats = true;
	}

	inline DrawMatricesPtr SkinnedRenderable::GetDrawMats(void) const
	{
		return m_DrawMats;
	}

	inline void SkinnedRenderable::SetUseDrawMats(bool bset)
	{
		m_IsUseDrawMats = bset;
	}

	inline int SkinnedRenderable::GetRegIndexOfAffected(IndexT iPass) const
	{
		if(iPass>=0 && iPass < m_RegIndexOfAffected.Size())
		{
			return m_RegIndexOfAffected[iPass];
		}
		else
		{
			return InvalidIndex;
		}
	}

	inline const AffectedTransform& SkinnedRenderable::GetAffectedTransform() const
	{
		return m_AffectedTrans;
	}

	inline bool SkinnedRenderable::UseDrawMats() const
	{
		return m_IsUseDrawMats;
	}
}


#endif //_SKINNEDRENDERABLE_H_