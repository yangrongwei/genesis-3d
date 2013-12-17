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

#ifndef __skeletonresloader_H__
#define __skeletonresloader_H__
#include "resource/skeletonres.h"
#include "io/binaryreader.h"

namespace Resources
{
	class SkeletonResLoader: public ResourceLoader
	{
		__DeclareSubClass(SkeletonResLoader, ResourceLoader);

	public:
		SkeletonResLoader();
		virtual ~SkeletonResLoader();

		/// @ResourceLoader::LoadResource
		virtual bool LoadResource(Resource* res );

	protected:

		bool Load_1(GPtr<IO::BinaryReader>& pReader, GPtr<SkeletonRes>& pSkelRes);

		bool Load_2(GPtr<IO::BinaryReader>& pReader, GPtr<SkeletonRes>& pSkelRes);

		bool LoadSkeleton(GPtr<IO::BinaryReader>& pReader, GPtr<SkeletonRes>& pSkelRes );

		bool ReadSkelBone(GPtr<IO::BinaryReader>& pReader, GPtr<SkeletonRes>& pSkelRes);

		bool ReadSkelTree(GPtr<IO::BinaryReader>& pReader, GPtr<SkeletonRes>& pSkelRes);
	};
}

#endif // __skeletonresloader_H__
