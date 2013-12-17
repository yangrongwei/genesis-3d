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

#if WIN32



#include "stdneb.h"
#include "GPUProgramD3D9.h"
#include "RenderDeviceD3D9.h"
namespace D3D9
{
	using namespace RenderBase;
	__ImplementClass(GPUProgramD3D9,'GPD9',RenderBase::GPUProgram)

	GPUProgramD3D9::GPUProgramD3D9() : m_iPixelShaderD9(NULL),
		m_iVertexShaderD9(NULL),
		m_useHLSL(false)
	{

	}

	GPUProgramD3D9::~GPUProgramD3D9()
	{
		if ( m_iVertexShaderD9 )
		{
			m_iVertexShaderD9->Release();
			m_iVertexShaderD9 = NULL;
		}

		if ( m_iPixelShaderD9 )
		{
			m_iPixelShaderD9->Release();
			m_iPixelShaderD9 = NULL;
		}
	}

	void GPUProgramD3D9::LoadBuffers()
	{
		m_useHLSL = true;

		RenderDeviceD3D9* device = RenderDeviceD3D9::Instance();
		ID3DXBuffer*	pCompiledCode;
		ID3DXBuffer*	pCompileErrors;
		//create ps
 		HRESULT hr = D3DXCompileShaderFromFile(m_codePath.Value(),NULL,NULL,"vsMain","vs_3_0", D3DXSHADER_DEBUG|D3DXSHADER_SKIPOPTIMIZATION|D3DXSHADER_SKIPVALIDATION|D3DXSHADER_AVOID_FLOW_CONTROL,&pCompiledCode,&pCompileErrors,NULL);
		if (FAILED(hr))
		{
			n_error("%s",pCompileErrors->GetBufferPointer());
			//DXTRACE_ERR( TEXT("CompileShader"), hr );
		}
 		hr = device->CreateVertexShader((DWORD*)pCompiledCode->GetBufferPointer(),&m_iVertexShaderD9);
 		pCompiledCode->Release();
 		if (FAILED(hr))
 		{
 			DXTRACE_ERR( TEXT("CreateVertexShader"), hr );
 		}
		//create ps
		hr = D3DXCompileShaderFromFile(m_codePath.Value(),NULL,NULL,"psMain","ps_3_0", D3DXSHADER_DEBUG|D3DXSHADER_SKIPOPTIMIZATION|D3DXSHADER_SKIPVALIDATION|D3DXSHADER_AVOID_FLOW_CONTROL,&pCompiledCode,&pCompileErrors,NULL);
		if (FAILED(hr))
		{
			n_error("%s",pCompileErrors->GetBufferPointer());
			DXTRACE_ERR( TEXT("CreatePixelShader"), hr );
		}
		hr = device->CreatePixelShader((DWORD*)pCompiledCode->GetBufferPointer(),&m_iPixelShaderD9);
		pCompiledCode->Release();
		if (FAILED(hr))
		{
			DXTRACE_ERR( TEXT("CreatePixelShader"), hr );
		}

	}

	void GPUProgramD3D9::LoadCodes()
	{
		RenderDeviceD3D9* device = RenderDeviceD3D9::Instance();
		ID3DXBuffer *compiled, *errors;
		DWORD flags = 0;

		HRESULT hr = D3DXAssembleShader(m_vertexCode.AsCharPtr(),m_vertexCode.Length(),NULL,NULL,flags,&compiled,&errors);
		if (FAILED(hr))
		{
			n_error("Compile Vertex Shader:%s \n Error: %s",(const char*)errors->GetBufferPointer(),m_vertexCode.AsCharPtr());
			DXTRACE_ERR( TEXT("CreateVertexShader"), hr );

			if (compiled)
			{
				compiled->Release();
			}
		}

		hr = device->CreateVertexShader((DWORD*)compiled->GetBufferPointer(),&m_iVertexShaderD9);
		compiled->Release();
		if (FAILED(hr))
		{
			DXTRACE_ERR( TEXT("CreateVertexShader"), hr );
		}


		hr = D3DXAssembleShader(m_pixelCode.AsCharPtr(),m_pixelCode.Length(),NULL,NULL,flags,&compiled,&errors);
		if (FAILED(hr))
		{
			n_error("Compile Vertex Shader:%s \n Error: %s",(const char*)errors->GetBufferPointer(),m_pixelCode.AsCharPtr());
			DXTRACE_ERR( TEXT("CreateVertexShader"), hr );

			if (compiled)
			{
				compiled->Release();
			}
		}
		
		hr = device->CreatePixelShader((DWORD*)compiled->GetBufferPointer(),&m_iPixelShaderD9);
		compiled->Release();
		if (FAILED(hr))
		{
			DXTRACE_ERR( TEXT("CreatePixelShader"), hr );
		}

	}
}

#endif