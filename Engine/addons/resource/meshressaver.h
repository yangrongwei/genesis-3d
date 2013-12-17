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
#ifndef __meshressaver_H__
#define __meshressaver_H__

#include "resource/meshres.h"
#include "io/binarywriter.h"

namespace Resources
{
	class MeshResSaver: public Resources::ResourceSaver
	{
		__DeclareSubClass(MeshResSaver, ResourceSaver);
	public:
		MeshResSaver();
		virtual ~MeshResSaver();
		/// @ResourceSaver::LoadResource
		virtual bool SaveResource(Resource* res );

	protected:
		bool SaveMesh(GPtr<IO::BinaryWriter>& pWriter, GPtr<MeshRes>& pMesh );

		bool WriteTopology(GPtr<IO::BinaryWriter>& pWriter, GPtr<MeshRes>& pMesh); 

		bool WritePosition(GPtr<IO::BinaryWriter>& pWriter, GPtr<MeshRes>& pMesh); 

		bool WriteIndex(GPtr<IO::BinaryWriter>& pWriter, GPtr<MeshRes>& pMesh);

		bool WriteColor(GPtr<IO::BinaryWriter>& pWriter, GPtr<MeshRes>& pMesh);

		bool WriteTexCoord(GPtr<IO::BinaryWriter>& pWriter, GPtr<MeshRes>& pMesh);

		bool WriteNormal(GPtr<IO::BinaryWriter>& pWriter, GPtr<MeshRes>& pMesh);

		bool WriteTangent(GPtr<IO::BinaryWriter>& pWriter, GPtr<MeshRes>& pMesh);

		bool WriteBiNormal(GPtr<IO::BinaryWriter>& pWriter, GPtr<MeshRes>& pMesh);

		bool WriteBoneInfo(GPtr<IO::BinaryWriter>& pWriter, GPtr<MeshRes>& pMesh);

		bool WriteSubMesh(GPtr<IO::BinaryWriter>& pWriter, GPtr<MeshRes>& pMesh);
	};
}


#endif // __meshressaver_H__







