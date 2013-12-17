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
#ifndef __meshSpliter_h__
#define __meshSpliter_h__
#include "foundation/core/refcounted.h"
#include "foundation/core/singleton.h"
#include "core/ptr.h"
#include "resource/meshres.h"
#include <set>
#include <map>
#include <vector>
namespace Resources
{
	class MeshRes;
	struct SubMesh;
	class MeshReviseWorkspace;
	typedef std::set<ushort> StdSetHelper;
	typedef Util::Array<ushort>  HelperBonesIdx;
	typedef std::map<uint,uint>		 StdMapVertexArrayIdx;
	typedef Util::FixedArray<ushort> FixedArrayBonesIndex;
	typedef Util::Array<uchar>		 ArrayBonesIndex;
	class MeshSpliter : public Core::RefCounted
	{
		__DeclareClass(MeshSpliter);
		__DeclareImageSingleton(MeshSpliter);
	public:
		MeshSpliter();
		virtual ~MeshSpliter();
		void Init();
		void DoWork(GPtr<MeshRes>& pMesh);
		void DoWork_1(GPtr<MeshRes>& pMesh);
		void DebugPrint(GPtr<MeshRes>& pMesh);
	private:
		// split mesh===============================================
		// split mesh base on max bone count
		bool _SplitMesh(GPtr<MeshRes>& pMesh,SubMeshArray& mergeResult);
		// try split submesh
		bool _TrySplitSubmesh(int iSubmesh,SubMesh* pSubmesh,Util::Array<uchar>& affectdBones);

		int _GetSubmeshFirstIndex(int iSubmesh);
			// Check is over max bone use triangle as unit
		bool _IsOverMaxBonesByTri(Util::FixedArray<uint>& aVertex,StdSetHelper& helperSet);
		void _MergeSubmeshes(SubMeshArray& outResult, Util::Dictionary<IndexT,SubMeshArray>& aNewSubmesh);
		void _RestoreRawBoneInfo(SubMeshArray& arrayRawSubmeshs, MeshReviseWorkspace& workspace);

		// split vertexs===============================================
		void _SplitVertexs(SubMeshArray& allSubMeshArray,MeshReviseWorkspace& workspace);
		void _MakeAffectedBoneAndBoneInfo(IndexT iSub,IndexT rawVertexIdx,IndexT newVertexIdx,MeshReviseWorkspace& workspace,Util::Array<IndexT>& helperAfftectedBone);

		// common func===============================================
		IndexT _GetVertexIndex(IndexT idxAtIndexArray);
		void   _GetAffectedBonesIndex(FixedArrayBonesIndex& outAffectedBonesIndex, IndexT idxAtVertexArray,MeshReviseWorkspace& workspace);
		IndexT _GetRawAffectedBonesValue(AffectedBonesIndex& rawAffectedBones, IndexT restoreBoneIdx);		
		bool   _HaveVertexIdx(std::vector<StdMapVertexArrayIdx> ssvaVertexIdx, IndexT end, IndexT testVal);
		bool   _IsNeedSplit(GPtr<MeshRes>& pMesh);

	private:
		bool			mbInit;
		int				mMaxBoneBySubmesh;
		GPtr<MeshRes>   mMeshRes;
		Util::Dictionary<IndexT,SubMeshArray>	mSubmeshMapWorkPart;	
	};

	class MeshReviseWorkspace
	{
		friend class MeshSpliter;
	public:
		MeshReviseWorkspace();
		~MeshReviseWorkspace();
		void	Init(GPtr<MeshRes>& pMesh);
		void	Reserve(int num);
		IndexT	AddVertex(int rawVetexArrayIdx);
		void	AddIndex(IndexT newIndexArrayIdxValue);
		void	SetIBValue(IndexT indexIB,IndexT val);
		IndexT	GetVertexArraySize();
		void	Swap();
	private:
		GPtr<MeshRes>   mMeshRes;
		PositionData				mPosition;
		ColorData					mColor;
		Util::Array<TexCoordData>	mTexCoords;
		NormalData					mNormal;
		TangentData					mTangent;
		BiNormalData				mBiNormal;
		BoneInfoData				mBoneInfo;
		BoneInfoData				mRestoreBoneInfo;			
		Index16Container			mIndex16;
		Index32Container			mIndex32;
		AffectedBonesIndex			mAffectedBoneIndex;

		bool						mbUseIndex16;

	};
}
#endif