/****************************************************************************
Copyright (c) 2007, Radon Labs GmbH
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
#ifndef VERTEXLAYOUTD3D9_H_
#define VERTEXLAYOUTD3D9_H_
#include "base/VertexLayout.h"

class RenderBase::VertexComponent;
namespace D3D9
{
	class VertexLayoutD3D9 : public RenderBase::VertexLayout
	{
		__DeclareSubClass(VertexLayoutD3D9,RenderBase::VertexLayout)
	public:
		/// constructor
		VertexLayoutD3D9();
		/// destructor
		virtual ~VertexLayoutD3D9();
		/// set d3d9 vertex declaration pointer
		void SetD3D9VertexDeclaration(IDirect3DVertexDeclaration9* ptr);
		/// get pointer to d3d9 vertex declaration
		IDirect3DVertexDeclaration9* GetD3D9VertexDeclaration() const;
		/// set the vertex stride in number of bytes
		void SetVertexByteSize(SizeT vbs);

		void GenerateDeclarationD3D9();
	private:
		IDirect3DVertexDeclaration9* d3d9VertexDeclaration;
	};

	//------------------------------------------------------------------------------
	/**
	*/
	inline void
		VertexLayoutD3D9::SetD3D9VertexDeclaration(IDirect3DVertexDeclaration9* ptr)
	{
		n_assert(0 != ptr);
		n_assert(0 == this->d3d9VertexDeclaration);
		this->d3d9VertexDeclaration = ptr;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline IDirect3DVertexDeclaration9*
		VertexLayoutD3D9::GetD3D9VertexDeclaration() const
	{
		n_assert(0 != this->d3d9VertexDeclaration);
		return this->d3d9VertexDeclaration;
	}

	inline void
		VertexLayoutD3D9::SetVertexByteSize(SizeT vbs)
	{
		n_assert(0 != vbs)
		this->vertexByteSize = vbs;
	}

}
#endif //VERTEXLAYOUTD3D9_H_