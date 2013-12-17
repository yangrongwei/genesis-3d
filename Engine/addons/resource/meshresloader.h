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
#ifndef __meshresLoader_H__
#define __meshresLoader_H__
#include "resource/meshres.h"
#include "io/binaryreader.h"

namespace Resources
{
	class MeshResLoader: public ResourceLoader
	{
		__DeclareSubClass(MeshResLoader, ResourceLoader);
	public:
		MeshResLoader();
		virtual ~MeshResLoader();
		/// @ResourceLoader::LoadResource
		virtual bool LoadResource(Resource* res );

	protected:
		bool Load_1(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh);

		bool Load_2(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh);

		bool Load_3(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh);

		bool LoadMesh(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh );

		bool ReadTopology(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh); 

		bool ReadPosition(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh); 

		bool ReadIndex(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh);

		bool ReadColor(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh);

		bool ReadTexCoord(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh);

		bool ReadNormal(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh);

		bool ReadTangent(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh);

		bool ReadBiNormal(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh);

		bool ReadBoneInfo(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh);

		bool ReadSubMesh(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh);

		bool ReadAffectedBones(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh);
	};
}

#endif // __meshresLoader_H__

