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
#include "meshSpliter.h"
#include "RenderSystem.h"

//#define __DEBUG_MESHSPLITER__
//#define __DEBUG_MESHSPLITER_Print__
namespace Resources
{
	//---------------------------------------------------------------------
	__ImplementClass(MeshSpliter,'MHSP',Core::RefCounted);
	__ImplementImageSingleton(MeshSpliter);
	//---------------------------------------------------------------------
	MeshSpliter::MeshSpliter():mMaxBoneBySubmesh( (128-16)/4 ),
		mbInit(false)
	{
		__ConstructImageSingleton;
		
	}
	MeshSpliter::~MeshSpliter()
	{
		__DestructImageSingleton;
	}
	void MeshSpliter::Init()
	{
		if ( mbInit )
		{
			return;
		}
		mbInit = true;
#if RENDERDEVICE_OPENGLES		
		const RenderBase::GraphicCardCapability& caps = RenderBase::RenderSystem::Instance()->GetGraphicCardCapability();
		mMaxBoneBySubmesh = (caps.mMaxUniformVectors-16)/4;
#else
		mMaxBoneBySubmesh = 60;
#endif
#ifdef __DEBUG_MESHSPLITER__
		mMaxBoneBySubmesh = 30;
#endif


	}
	void MeshSpliter::DebugPrint(GPtr<MeshRes>& pMesh)
	{
	#ifdef __DEBUG_MESHSPLITER_Print__
		if ( pMesh->GetAffectedBonesIndex(0).Size() == 0 )
		{
			return;
		}
		mMeshRes=pMesh;

		//debug=============
		n_printf("meshID %s===================================\n",pMesh->GetMeshID().Get());
		n_printf("submesh===================================\n");
		for ( IndexT i = 0; i < mMeshRes->mSubMeshs.Size(); i++ )
		{
			n_printf("sub%d: 		\n",i);
			n_printf("first index %d\n",mMeshRes->mSubMeshs[i].FirstIndex);
			n_printf("number index %d\n",mMeshRes->mSubMeshs[i].numIndex);
			n_printf("first vertex %d\n",mMeshRes->mSubMeshs[i].firstVertex);
			n_printf("number vertex %d:\n",mMeshRes->mSubMeshs[i].numVertex);
		}
		n_printf("affected bone===================================\n");
		for ( IndexT i = 0; i < mMeshRes->mAffectedBonesIndex.Size(); i++  )
		{
			Util::Array<uchar> affectedIdx = mMeshRes->mAffectedBonesIndex[i];
			n_printf("sub%d------------------		\n",i);
			for ( IndexT j = 0; j < affectedIdx.Size(); j++ )
			{
				uchar uVal = affectedIdx[j];
				n_printf("%d\n",uVal);
			}
		}
		n_printf("bone info===================================\n");
		for ( IndexT i = 0; i < mMeshRes->mBoneInfo.Size(); i++ )
		{
			n_printf("mBoneInfo[%d]: ",i);
			for ( IndexT j = 0; j < 4; j++ )
			{
				IndexT val = mMeshRes->mBoneInfo[i].boneIndex[j];
				n_printf("%d	",val);

			}
			n_printf("\n");			
		}

		n_printf("IB ===================================\n");
		for ( IndexT i = 0; i < mMeshRes->mIndex16.Size(); i++ )
		{
			n_printf("Index16: ");

			IndexT val = mMeshRes->mIndex16[i];
			n_printf("%d	",val);


			n_printf("\n");			
		}

		/*	n_printf("VB ===================================\n");
		for ( IndexT i = 0; i < mMeshRes->mPosition.Size(); i++ )
		{
		n_printf("vbData: ");

		Math::float3& v3Val =  mMeshRes->mPosition[i];
		n_printf("%f,%f,%f	\n",v3Val.x(),v3Val.y(),v3Val.z());
		}*/

		//====================
	#endif
	}
	void MeshSpliter::DoWork(GPtr<MeshRes>& pMesh)
	{
#if RENDERDEVICE_OPENGLES



#ifdef __DEBUG_MESHSPLITER__
		static bool bSkip = false;
#ifdef __GENESIS_EDITOR__
		bSkip = true;
#endif
		if ( bSkip )
		{
			return;
		}
		//if ( pMesh->GetMeshID() != "body_di" )
		//{
		//	return;
		//}


		n_printf("meshspliter editor======================\n");
		DebugPrint(pMesh);


		
#endif

		DoWork_1(pMesh);
#ifdef __DEBUG_MESHSPLITER__
		n_printf("meshspliter after======================\n");
		DebugPrint(pMesh);
#endif
#endif

	}
	//------------------------------------------------------------------------
	void MeshSpliter::DoWork_1(GPtr<MeshRes>& pMesh)
	{
		if ( pMesh->GetAffectedBonesIndex(0).Size() == 0 )
		{
			return;
		}
		if ( !_IsNeedSplit(pMesh) )
		{
			return;
		}
		
		mMeshRes=pMesh;

		mSubmeshMapWorkPart.Clear();
		SubMeshArray allSubMeshArray;
		bool bSuc(false);
		bSuc = _SplitMesh(mMeshRes,allSubMeshArray);		
		if ( !bSuc )
		{
			return;
		}

#ifdef __DEBUG_MESHSPLITER_Print__
		n_printf("meshspliter meshid %s======================\n",pMesh->GetMeshID().Get());
		n_printf("meshspliter before======================\n");
		DebugPrint(pMesh);
#endif
		MeshReviseWorkspace workspace;
		workspace.Init(mMeshRes);

		// update AffectedBonesIndex
		//_UpdateAffectedBonesIndex(mMeshRes->mSubMeshs,workspace);	

		_RestoreRawBoneInfo(mMeshRes->mSubMeshs,workspace);

		_SplitVertexs(allSubMeshArray,workspace);
		
		//update 
		//debug start==============================
		//allSubMeshArray.EraseIndex(1);
		//mMeshRes->mSummeshUsedMaterial[0] = 0;
		//debug end==============================
		mMeshRes->mSubMeshs.Swap(allSubMeshArray);
	}

	//-------------------------------------------------------------------------
	bool  MeshSpliter::_IsNeedSplit(GPtr<MeshRes>& pMesh)
	{
		SizeT oldSubmeshCount =pMesh->GetSubMeshCount();
		for ( SizeT i = 0; i < oldSubmeshCount; ++i )
		{
			Util::Array<uchar>& affectdBones = pMesh->GetAffectedBonesIndex(i);
			if ( affectdBones.Size() > mMaxBoneBySubmesh )
			{
				return true;
			}

		}
		return false;
	}

	//--------------------------------------------------------------------------
	bool MeshSpliter::_SplitMesh(GPtr<MeshRes>& pMesh,SubMeshArray& mergeResult)
	{	
		bool bSuc(false);
		SizeT oldSubmeshCount =pMesh->GetSubMeshCount();
		for ( SizeT i = 0; i < oldSubmeshCount; ++i )
		{
			SubMesh* pSubMesh= pMesh->GetSubMesh(i);
			Util::Array<uchar>& affectdBones = pMesh->GetAffectedBonesIndex(i);
			bSuc |= _TrySplitSubmesh(i,pSubMesh,affectdBones);
		}

		// submesh合并		
		_MergeSubmeshes(mergeResult,mSubmeshMapWorkPart);		

		// add materialIdx used by submesh
		mMeshRes->mSummeshUsedMaterial.Resize(oldSubmeshCount,1);
		for ( SizeT i = 0; i < oldSubmeshCount; ++i )
		{
			IndexT keyIdx = mSubmeshMapWorkPart.FindIndex(i);
			if ( keyIdx != InvalidIndex  )
			{// 被拆过
				mMeshRes->mSummeshUsedMaterial[i] = mSubmeshMapWorkPart[i].Size();
			} 			
		}

		return bSuc;		
	}
	bool MeshSpliter::_TrySplitSubmesh(int iSubmesh,SubMesh* pSubmesh,Util::Array<uchar>& affectdBones)
	{
		int nSubmesh_bones = affectdBones.Size();
		if ( nSubmesh_bones <= mMaxBoneBySubmesh )
		{// no need split
			return false;
		}

		// 循环拆分		
		int		numIndex				= pSubmesh->numIndex;
		IndexT	begin					= pSubmesh->FirstIndex;
		IndexT	end						= begin + pSubmesh->numIndex;
		int		curIndexByNewSubmesh	= begin;
		n_assert(numIndex%3 == 0);
		
		Util::FixedArray<uint> aVertex;
		aVertex.Resize(3);		
		SubMeshArray aSubmesh;
		StdSetHelper helperSet;

		//以三角形为单位，判断是否超出subMesh的最大骨骼数
		for (IndexT iIndex = begin; iIndex < end; iIndex += 3)
		{
			aVertex[0] = _GetVertexIndex(iIndex);
			aVertex[1] = _GetVertexIndex(iIndex+1);
			aVertex[2] = _GetVertexIndex(iIndex+2);

			if ( _IsOverMaxBonesByTri(aVertex,helperSet) )
			{
				// add one new submesh
				SubMesh newSubmesh;
				newSubmesh.FirstIndex = curIndexByNewSubmesh;
				//newSubmesh.numIndex   = (iIndex - 1) - curIndexByNewSubmesh + 1;
				newSubmesh.numIndex   = (iIndex-1) - curIndexByNewSubmesh + 1;

				curIndexByNewSubmesh  = newSubmesh.FirstIndex + newSubmesh.numIndex;

				aSubmesh.Append(newSubmesh);
				helperSet.clear();
				iIndex -= 3;
			}
		}

		// 处理old submesh 拆分为几个new submesh 后剩余的碎片submesh
		IndexT endIdxByOldSubmesh = pSubmesh->FirstIndex + pSubmesh->numIndex -1;
		if ( curIndexByNewSubmesh-1 < endIdxByOldSubmesh)
		{//有碎片
			// add  one new submesh by left
			SubMesh newSubmesh;
			newSubmesh.FirstIndex = curIndexByNewSubmesh ;
			newSubmesh.numIndex   = endIdxByOldSubmesh - newSubmesh.FirstIndex + 1;
			aSubmesh.Append(newSubmesh);
		}

		n_assert(aSubmesh.Size() >= 2); //既然拆，一定会拆出2个以上来
		if ( aSubmesh.Size() > 0 )
		{
			mSubmeshMapWorkPart.Add(iSubmesh,aSubmesh);
		}
		return true;
	}
	int MeshSpliter::_GetSubmeshFirstIndex(int iSubmesh)
	{
		int firstIndex = 0;
		for ( int i = 0; i < iSubmesh; ++i)
		{
			firstIndex += mMeshRes->GetSubMesh(i)->numIndex;
		}
		return firstIndex;
	}
	bool MeshSpliter::_IsOverMaxBonesByTri(Util::FixedArray<uint>& aVertex,StdSetHelper& helperSet)
	{
		n_assert(aVertex.Size() == 3);
		BoneInfoData::Elem* boneInfo = (BoneInfoData::Elem*)mMeshRes->GetDataImpl(VertexIndex::egBoneInfo,0);
		for ( IndexT iVet = 0; iVet < aVertex.Size(); ++iVet )
		{
			uint iVetex = aVertex[iVet];			

			// 一个顶点受4根骨头影响
			for ( int i = 0; i < 4; ++i )
			{
				ushort usIdxValue = boneInfo[iVetex].boneIndex[i]; // 对BoneInfoData的索引
				helperSet.insert(usIdxValue);
				if ( (IndexT)helperSet.size() >= mMaxBoneBySubmesh )
				{
					return true;
				}
			}
		}
		return false;
	}
#ifdef __DEBUG_MESHSPLITER__
	typedef std::set<IndexT> StdSetIdx;
	typedef std::map<IndexT,StdSetIdx> StdMapIdx;
	static StdMapIdx g_stdMapIdx;
	bool PreSubMeshHaveIVetIdx(IndexT iSubmesh,IndexT iVet)
	{
		for ( IndexT i = 0; i< iSubmesh; i++ )
		{
			StdSetIdx& oSet = g_stdMapIdx[i];
			return (oSet.count(iVet) == 1);
		}
		return false;

	}
#endif
	void MeshSpliter::_RestoreRawBoneInfo(SubMeshArray& arrayRawSubmeshs, MeshReviseWorkspace& workspace)
	{
#ifdef __DEBUG_MESHSPLITER__
		g_stdMapIdx.clear();
#endif

		// 恢复原始索引值
		workspace.mRestoreBoneInfo = mMeshRes->mBoneInfo;
		IndexT boneIdxOffset(0);
		for ( IndexT  iSubmesh = 0;  iSubmesh < (IndexT)arrayRawSubmeshs.Size(); ++iSubmesh )
		{

			std::set<IndexT> stdSetModifedIdx;
			if ( iSubmesh >= 1 )
			{
				boneIdxOffset +=  mMeshRes->GetAffectedBonesIndex(iSubmesh-1).Size();
			}	
			IndexT begin = arrayRawSubmeshs[iSubmesh].FirstIndex;
			IndexT end   = begin + arrayRawSubmeshs[iSubmesh].numIndex;	
			for ( IndexT i = begin; i < end; i++ )
			{
				IndexT iVet = _GetVertexIndex(i);
#ifdef __DEBUG_MESHSPLITER__
				if ( iSubmesh >= 1 && PreSubMeshHaveIVetIdx(iSubmesh,iVet) )
				{
					n_error("pre submesh have ivet!!");
				}
				g_stdMapIdx[iSubmesh].insert(iVet);
#endif
				if ( stdSetModifedIdx.count(iVet) == 1 )
				{
					continue;

				} 
				stdSetModifedIdx.insert(iVet);
				for ( int j = 0; j < 4; j++ )
				{
					workspace.mRestoreBoneInfo[iVet].boneIndex[j] = workspace.mRestoreBoneInfo[iVet].boneIndex[j] + boneIdxOffset;
				}
			}

		}
		
	}
	

	void MeshSpliter::_MergeSubmeshes(SubMeshArray& outResult, Util::Dictionary<IndexT,SubMeshArray>& aNewSubmesh)
	{
		SubMeshArray& oldSubmesh = mMeshRes->mSubMeshs;
		for ( IndexT i = 0; i < oldSubmesh.Size(); i++ )
		{
			IndexT keyIdx = aNewSubmesh.FindIndex(i);
			if ( keyIdx != InvalidIndex )
			{// 该submesh 被拆过了
				outResult.AppendArray( aNewSubmesh.ValueAtIndex(keyIdx) );
			} 
			else
			{// 延用old submesh
				outResult.Append( oldSubmesh[i]);
			}
		}
	}
	//顶点分裂======================================================================
	void MeshSpliter::_SplitVertexs(SubMeshArray& allSubMeshArray,MeshReviseWorkspace& workspace)
	{// vertex分裂
		/*
		 * 以allSubMeshArray的数据为基准，做顶点clone需要做如下工作：
		 *	1.扩充vertexBuffer（包括vertexcolor,norma等顶点属性），IndexBuffer。
		 *  2.排序vertexBuffer，Indexbuffer
		 *  3.修正submesh数据（firstVertex，numVertex,firstIndex,numIndex）
		 *  remark:同编辑器拆分一致，clone的顶点放后面
		*/
		n_assert(allSubMeshArray.Size() >= 1);
		n_printf("=====================submeshID: %s \n",mMeshRes->meshId.Get());		
		
		//Util::Array<StdMapVertexArrayIdx> ssvaVertexIdx;
		std::vector<StdMapVertexArrayIdx> ssvaVertexIdx;
		Util::Array<IndexT>				  helperAfftectedBone;
		std::vector<uint>					  subIndexVB;
		StdMapVertexArrayIdx emptyMap;
		emptyMap.clear();
		//ssvaVertexIdx.Resize(allSubMeshArray.Size(),emptyMap);
		ssvaVertexIdx.resize(allSubMeshArray.Size(),emptyMap);

		//workspace
		Util::Array<uchar> emptArrayUChar;
		workspace.mAffectedBoneIndex.Resize(allSubMeshArray.Size(),emptArrayUChar);	
		
		// 处理第0个submesh的顶点索引（第0个不会和其他的submesh有公用的顶点）
		IndexT begin = allSubMeshArray[0].FirstIndex;
		IndexT end   = begin + allSubMeshArray[0].numIndex;	
		IndexT vertexCountDebug = 0;
		IndexT iSub(0);
		for ( IndexT i = begin; i < end; i++ )
		{
			IndexT rawVertexIdx = _GetVertexIndex(i);
			_MakeAffectedBoneAndBoneInfo(iSub,rawVertexIdx,rawVertexIdx,workspace,helperAfftectedBone);	

			//std::vector< uint >itFindRaw = std::find(subIndexVB.begin(),subIndexVB.end(),rawVertexIdx);
			//if ( itFindRaw == subIndexVB.end() )
			//{
				subIndexVB.push_back(rawVertexIdx);
			//}
			ssvaVertexIdx[iSub].insert(std::make_pair(rawVertexIdx,-1));
			
		
		}
		helperAfftectedBone.Clear();


		// update submesh vertexIdx vertexNum
		std::sort(subIndexVB.begin(), subIndexVB.end());
		allSubMeshArray[0].firstVertex = subIndexVB.front();
		allSubMeshArray[0].numVertex   = subIndexVB.back() - subIndexVB.front() + 1;
		subIndexVB.clear();

		// 遍历被submesh共用的顶点
		for ( IndexT iSub = 1; iSub < allSubMeshArray.Size(); ++iSub )
		{
			subIndexVB.clear();
			helperAfftectedBone.Clear();
			IndexT begin = allSubMeshArray[iSub].FirstIndex;
			IndexT end   = begin + allSubMeshArray[iSub].numIndex;
			for ( IndexT indexIdx = begin; indexIdx < end; indexIdx++ )
			{
				IndexT rawVertexIdx  = _GetVertexIndex(indexIdx);
				bool bNeedClone = _HaveVertexIdx(ssvaVertexIdx,iSub,rawVertexIdx);
				StdMapVertexArrayIdx::iterator itFind = ssvaVertexIdx[iSub].find(rawVertexIdx);
				bool bHadCloned = ( ( itFind != ssvaVertexIdx[iSub].end() ) && ( itFind->second != (uint)-1) ) ;
				
				// clone vertex
				if ( bNeedClone )
				{
					if ( !bHadCloned )
					{// 当前submesh中第一次索引到这个顶点,需要clone
						IndexT lastVertexIdx = workspace.AddVertex(rawVertexIdx);
						workspace.SetIBValue(indexIdx,lastVertexIdx);
						
						ssvaVertexIdx[iSub].insert(std::make_pair(rawVertexIdx,lastVertexIdx));
						subIndexVB.push_back(lastVertexIdx);
						_MakeAffectedBoneAndBoneInfo(iSub,rawVertexIdx,lastVertexIdx,workspace,helperAfftectedBone);
					} 
					else
					{// had cloned 直接指向那个索引
						workspace.SetIBValue(indexIdx,itFind->second);
						//subIndexVB.push_back(itFind->second);
						
					}
					
				}
				else
				{
					// 
					ssvaVertexIdx[iSub].insert(std::make_pair(rawVertexIdx,-1));
					subIndexVB.push_back(rawVertexIdx);
					_MakeAffectedBoneAndBoneInfo(iSub,rawVertexIdx,rawVertexIdx,workspace,helperAfftectedBone);
				}
					
				
				
			}

			// update submesh vertexIdx vertexNum
			std::sort(subIndexVB.begin(), subIndexVB.end());
			allSubMeshArray[iSub].firstVertex = subIndexVB.front();
			allSubMeshArray[iSub].numVertex   = subIndexVB.back() - subIndexVB.front() + 1;
		}
		workspace.Swap();


	}
	
	//------------------------------------------------------------------------
	void MeshSpliter::_MakeAffectedBoneAndBoneInfo(IndexT iSub,IndexT rawVertexIdx,IndexT newVertexIdx,MeshReviseWorkspace& workspace,Util::Array<IndexT>& helperAfftectedBone)
	{
		// 根据原始affectedBone，重新生成workspace中的affectedbone，
		// 根据workspace中的affectedbone 更新boneInfo中的boneidx为渲染单位的索引

		for ( int j = 0; j < 4; j++ )
		{
			// 恢复后的boneIndex
			IndexT idxAffetedBone		= workspace.mRestoreBoneInfo[rawVertexIdx].boneIndex[j];
			//
			IndexT affectedBoneValue	= _GetRawAffectedBonesValue(mMeshRes->mAffectedBonesIndex,idxAffetedBone);
			


			if ( helperAfftectedBone.FindIndex(affectedBoneValue) == InvalidIndex )
			{// 没有，追加
				helperAfftectedBone.Append(affectedBoneValue);
				
				// make affecteBone
				workspace.mAffectedBoneIndex[iSub].Append( (uchar)affectedBoneValue );
				IndexT lastIdxAffectedBoneIndex = workspace.mAffectedBoneIndex[iSub].Size() - 1;

				// make boneInfo中的boneIndex
				workspace.mBoneInfo[newVertexIdx].boneIndex[j] = lastIdxAffectedBoneIndex;

			}
			else
			{// 有，需要修改boneInfo中的boneIndex
				IndexT idxFind = workspace.mAffectedBoneIndex[iSub].FindIndex(affectedBoneValue);
				n_assert(idxFind != InvalidIndex);	//idxFind 跟 helperAfftectedBone.FindIndex(affectedBoneValue)是相等的

				// make boneInfo中的boneIndex
				workspace.mBoneInfo[newVertexIdx].boneIndex[j] = idxFind;
			}					

		}
	}

	//基础函数======================================================================
	
	IndexT MeshSpliter::_GetVertexIndex(IndexT idxAtIndexArray)
	{
		Index16Container::value_type* index16;
		Index32Container::value_type* index32;
		if ( mMeshRes->IsUseIndex16() )
		{
			index16 = mMeshRes->GetIndex16();
		}
		else
		{
			index32 = mMeshRes->GetIndex32();
		}

		IndexT iVet = mMeshRes->IsUseIndex16() ? index16[idxAtIndexArray] : index32[idxAtIndexArray];
		return iVet;
	}
	//-------------------------------------------------------------------------
	void MeshSpliter::_GetAffectedBonesIndex(FixedArrayBonesIndex& outAffectedBonesIndex, IndexT idxAtVertexArray,MeshReviseWorkspace& workspace)
	{
		outAffectedBonesIndex.Resize(4);
		for ( int i = 0; i < 4; i++ )
		{
			outAffectedBonesIndex[i] = workspace.mRestoreBoneInfo[idxAtVertexArray].boneIndex[i];
		}
		
	}
	
	
	//------------------------------------------------------------------------
	bool MeshSpliter::_HaveVertexIdx(std::vector<StdMapVertexArrayIdx> ssvaVertexIdx, IndexT end, IndexT testVal)
	{
		for ( IndexT iSub = 0; iSub < end; iSub++ )
		{
			if ( ssvaVertexIdx[iSub].find(testVal) != ssvaVertexIdx[iSub].end() )
			{
				return true;
			}

		}
		return false;
	}
	//------------------------------------------------------------------------
	IndexT MeshSpliter::_GetRawAffectedBonesValue(AffectedBonesIndex& rawAffectedBones, IndexT restoreBoneIdx)
	{
		IndexT totalIdx(0),preTotalNum(0);
		for ( IndexT i = 0; i < rawAffectedBones.Size(); i++ )
		{
			if ( i >= 1 )
			{
				preTotalNum += rawAffectedBones[i-1].Size();
			}
			
			totalIdx += rawAffectedBones[i].Size();
			if ( restoreBoneIdx <totalIdx )
			{
				return rawAffectedBones[i][restoreBoneIdx - preTotalNum];
			}

		}
		n_assert(0);
		return InvalidIndex;
	}
	//-------------------------------------------------------------------------
	MeshReviseWorkspace::MeshReviseWorkspace()
	{

	}
	MeshReviseWorkspace::~MeshReviseWorkspace()
	{

	}
	//-------------------------------------------------------------------------
	void MeshReviseWorkspace::Init(GPtr<MeshRes>& pMesh)
	{
		mMeshRes = pMesh;
		mbUseIndex16 = mMeshRes->IsUseIndex16();

		// clone IB
		if ( mbUseIndex16 )
		{
			mIndex16 = mMeshRes->mIndex16;
		} 
		else
		{
			mIndex32 = mMeshRes->mIndex32;
		}
		// clone VB
		// position		
		mPosition = mMeshRes->mPosition;

		// color
		mColor = mMeshRes->mColor;

		// other...
		mTexCoords = mMeshRes->mTexCoords;
		mNormal = mMeshRes->mNormal;
		mTangent = mMeshRes->mTangent;
		mBiNormal = mMeshRes->mBiNormal;
		mBoneInfo = mMeshRes->mBoneInfo;		
	}
	//-------------------------------------------------------------------------
	void MeshReviseWorkspace::Reserve(int num)
	{

	}
	//-------------------------------------------------------------------------
	IndexT MeshReviseWorkspace::AddVertex(int rawVetexArrayIdx)
	{// 把原始vb中的数据，拷贝到工作区中
		// position
		if(rawVetexArrayIdx < mMeshRes->mPosition.Size())
			mPosition.Append( mMeshRes->mPosition[rawVetexArrayIdx] );
		// color
		if(rawVetexArrayIdx < mMeshRes->mColor.Size())
			mColor.Append( mMeshRes->mColor[rawVetexArrayIdx] );
		
		// other...
		for ( IndexT i = 0 ; i < mMeshRes->mTexCoords.Size(); ++i )
		{
			TexCoordData& texcoordRht = mMeshRes->mTexCoords[i];
			TexCoordData& texcoord	  = mTexCoords[i];
			texcoord.Append(texcoordRht[rawVetexArrayIdx]);	
		}

		if(rawVetexArrayIdx < mMeshRes->mNormal.Size())
			mNormal.Append( mMeshRes->mNormal[rawVetexArrayIdx] );
		if(rawVetexArrayIdx < mMeshRes->mTangent.Size())
			mTangent.Append( mMeshRes->mTangent[rawVetexArrayIdx] );
		if(rawVetexArrayIdx < mMeshRes->mBiNormal.Size())
			mBiNormal.Append( mMeshRes->mBiNormal[rawVetexArrayIdx] );
		if(rawVetexArrayIdx < mMeshRes->mBoneInfo.Size())
			mBoneInfo.Append( mMeshRes->mBoneInfo[rawVetexArrayIdx] );


		return mPosition.Size() - 1;
	}
	//------------------------------------------------------------------------
	void MeshReviseWorkspace::Swap()
	{
		if ( mbUseIndex16 )
		{			
			mIndex16.Swap( mMeshRes->mIndex16);
		} 
		else
		{
			mIndex32.Swap( mMeshRes->mIndex32);
		}
		mPosition.Swap(mMeshRes->mPosition);
		mColor.Swap(mMeshRes->mColor);
		mTexCoords.Swap(mMeshRes->mTexCoords);
		mNormal.Swap(mMeshRes->mNormal);
		mTangent.Swap(mMeshRes->mTangent);

		mBiNormal.Swap(mMeshRes->mBiNormal);
		mBoneInfo.Swap(mMeshRes->mBoneInfo);
		mAffectedBoneIndex.Swap(mMeshRes->mAffectedBonesIndex);

		n_assert(mMeshRes->Validate());
	}
	//-------------------------------------------------------------------------
	void MeshReviseWorkspace::AddIndex(IndexT newIndexArrayIdxValue)
	{
		if ( mbUseIndex16 )
		{			
			mIndex16.Append( (ushort)newIndexArrayIdxValue );
		} 
		else
		{
			mIndex32.Append( newIndexArrayIdxValue );
		}
	}
	//------------------------------------------------------------------------
	void MeshReviseWorkspace::SetIBValue(IndexT indexIB,IndexT val)
	{
		if ( mbUseIndex16 )
		{				
			mIndex16[indexIB] = (ushort)val;
		} 
		else
		{
			mIndex32[indexIB] = val;
		}

	}
	//-------------------------------------------------------------------------
	IndexT MeshReviseWorkspace::GetVertexArraySize()
	{
		return mPosition.Size();
	}
	


}