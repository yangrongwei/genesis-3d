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
#ifndef GPUProgramD3D9_H_
#define GPUProgramD3D9_H_
#include "base/GPUProgram.h"

namespace D3D9
{
	using namespace RenderBase;
	class GPUProgramD3D9 : public GPUProgram
	{
		__DeclareSubClass(GPUProgramD3D9,GPUProgram)
	public:	
		/// constructor
		GPUProgramD3D9();
		/// destructor
		virtual ~GPUProgramD3D9();
		/// get d3d9 vs buffer
		IDirect3DVertexShader9* GetVertexShaderD3D9() const;
		/// get d3d9 ps buffer
		IDirect3DPixelShader9* GetPixelShaderD3D9() const;
		/// compile shader code,being deprecated
		void LoadBuffers();
		/// load shader code
		void LoadCodes();
		/// if using HLSL
		bool UseHLSL();
	private:
		bool m_useHLSL;
		IDirect3DVertexShader9* m_iVertexShaderD9;
		IDirect3DPixelShader9* m_iPixelShaderD9;
		
	};

	inline IDirect3DVertexShader9* GPUProgramD3D9::GetVertexShaderD3D9() const
	{
		return m_iVertexShaderD9;
	}

	inline IDirect3DPixelShader9* GPUProgramD3D9::GetPixelShaderD3D9() const
	{
		return m_iPixelShaderD9;
	}

	inline bool GPUProgramD3D9::UseHLSL()
	{
		return m_useHLSL;
	}

}

#endif //GPUProgramD3D9_H_