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
#ifndef SHADERPPARAM_H_
#define SHADERPPARAM_H_

#include "util/string.h"
#include "rendersystem/base/RenderDeviceTypes.h"
namespace Graphic
{
	enum ShaderParamType
	{
		eShaderParamInvailid = -1,
		eShaderParamMatrix,
		eShaderParamVector,
		eShaderParamFloat,
		eShaderParamTexture1D,
		eShaderParamTexture2D,
		eShaderParamTexture3D,
		eShaderParamTextureCUBE
	};
	class ShaderParam
	{
	public:
		ShaderParam();
		virtual ~ShaderParam();

		void SetParamType(const ShaderParamType& type);
		const ShaderParamType& GetParamType() const;
		void SetRegister(int r);
		const int& GetRegister() const;
		void SetName(const Util::String& name);
		const Util::String& GetName() const;
	private:
		ShaderParamType m_paramType;
		int m_register;
		Util::String m_name;
	};

	typedef Util::Array<Graphic::ShaderParam> ShaderParamList;

	inline void ShaderParam::SetParamType(const ShaderParamType& type)
	{
		m_paramType = type;
	}

	inline const ShaderParamType& ShaderParam::GetParamType() const
	{
		return m_paramType;
	}

	inline void ShaderParam::SetRegister(int r)
	{
		m_register = r;
	}

	inline const int& ShaderParam::GetRegister() const
	{
		return m_register;
	}

	inline void ShaderParam::SetName(const Util::String& name)
	{
		m_name = name;
	}

	inline const Util::String& ShaderParam::GetName() const
	{
		return m_name;
	}

}
#endif //SHADERPPARAM_H_