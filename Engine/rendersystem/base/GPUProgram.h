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
#pragma once

#ifndef GPUPROGRAM_H_
#define GPUPROGRAM_H_
#include "RenderDeviceTypes.h"
#include "RenderCommandType.h"
namespace RenderBase
{
	class GPUProgram : public RenderCommandType
	{
		__DeclareSubClass(GPUProgram,RenderCommandType)
	public:
		/// constructor
		GPUProgram();
		/// destructor
		virtual ~GPUProgram();
		/// set GPU code file path
		void SetCodePath(const ResourcePath& path);
		/// get GPU code file path
		const ResourcePath& GetCodePath() const;
		/// set vertex shader code
		void SetVertexCode(const Util::String& vcode);
		/// set pixel shader code
		void SetPixelCode(const Util::String& pcode);
		/// get vertex shader code
		const Util::String& GetVertexCode() const;
		/// get pixel shader code
		const Util::String& GetPixelCode() const;

		const Util::StringAtom& GetID(void) const;

		void SetID(const Util::StringAtom& id);

	protected:
		ResourcePath m_codePath;
		Util::String m_vertexCode;
		Util::String m_pixelCode;
		Util::StringAtom m_id;
	};

	inline void GPUProgram::SetCodePath(const ResourcePath& path)
	{
		m_codePath = path;
	}

	inline const ResourcePath& GPUProgram::GetCodePath() const
	{
		return m_codePath;
	}


	inline void GPUProgram::SetVertexCode(const Util::String& vcode)
	{
		m_vertexCode = vcode;
	}

	inline const Util::String& GPUProgram::GetVertexCode() const
	{
		return m_vertexCode;
	}

	inline void GPUProgram::SetPixelCode(const Util::String& pcode)
	{
		m_pixelCode = pcode;
	}

	inline const Util::String& GPUProgram::GetPixelCode() const
	{
		return m_pixelCode;
	}
	
	inline const Util::StringAtom& GPUProgram::GetID(void) const
	{
		return m_id;
	}

	inline void GPUProgram::SetID(const Util::StringAtom& id)
	{
		m_id = id;
	}
}

#endif