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
#ifndef __reslable_H__
#define __reslable_H__

namespace Resources
{
	struct ResLable
	{
		// 文件头和文件尾
		const static int L_Mesh = 'MESH';
		const static int L_Skeleton = 'SKEL';
		const static int L_Animation = 'ANIM';
		const static int L_End = 'ENDF';

		// Mesh数据段类型
		const static int L_MeshID = 'MSID';
		const static int L_Tolopogy = 'VTIF';
		const static int L_Position = 'VERT';
		const static int L_Index = 'INDX';
		const static int L_Color = 'COLR';
		const static int L_TexCoord = 'TEXC';
		const static int L_Normal = 'NORM';
		const static int L_Tangent = 'TAGE';
		const static int L_BiNormal = 'BNOR';
		const static int L_BoneInfo = 'BONE';
		const static int L_SubMesh = 'SMSH';
		const static int L_AffectedBones = 'BOSM';

		// Mesh数据的存储类型
		const static int S_StdPosition = 'VF3S';
		const static int S_StdIndex16 = 'INSR';
		const static int S_StdIndex32 = 'ININ';
		const static int S_StdColor = 'CNIN';
		const static int S_StdTexCoord = 'TF2S';
		const static int S_StdNormal = 'NF3S';
		const static int S_StdTangent = 'TGF4';
		const static int S_StdBiNormal = 'BNF4';
		const static int S_StdBoneInfo = 'BNST';
		const static int S_StdSubMesh = 'SMST';
		const static int S_StdAffectedBones = 'UNCH';

		// skeleton数据段类型
		const static int L_Bone = 'SBON';
		const static int L_SkelID = 'SKID';

		// skeletion数据的存储类型
		const static int S_StdBone = 'BOUC';

		// skeleton整体数据结构
		const static int L_BoneTree = 'BOST';

		// skeleton整体数据结构类型
		const static int S_StdBoneTree = 'BSDA';

		// animation数据段类型
		const static int L_AnimClip = 'ACLI';

		// animation数据的存储类型
		const static int S_StdAnimNode = 'ANDS';
		const static int S_StdCurveTrans = 'CTSD';
		const static int S_PackedCurveTrans = 'CTPD';
		const static int S_StdCurveScale = 'CSSD';
		const static int S_PackedCurveScale = 'CSPD';
		const static int S_StdCurveRota = 'CRSD';
		const static int S_PackedCurveRota = 'CRPD';

		// float 和 int数据块压缩存储格式
		const static int S_PackedFloatFmt = 'PAFF';
		const static int S_PackedIntFmt = 'PAIF';

	};
}








#endif // __reslable_H__
