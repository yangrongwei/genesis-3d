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
#ifndef MATEIRALPARAM_H_
#define MATEIRALPARAM_H_
#include "util/array.h"
#include "util/string.h"
#include "util/stringatom.h"
#include "graphicsystem/base/RenderBase.h"
#include "rendersystem/base/RenderDeviceTypes.h"
#include "foundation/io/ioserver.h"
#include "foundation/io/textreader.h"
#include "foundation/util/scriptbind.h"
#include "math/matrix44.h"
namespace Graphic
{

	class MaterialParam
	{

	public:	

		virtual ~MaterialParam();
		void SetStringValue(const Util::String& valStr);
		const Util::String& GetStringValue() const;
		void SetName(const Util::String& name);
		const Util::String& GetName() const;
		void SetDesc(const Util::String& desc);
		const Util::String& GetDesc() const;
		const MaterialParameterType& GetType() const;
		const bool IsConstType() const;
		const bool IsTexType() const;

	protected:		
		MaterialParam();
		Util::String	m_name;
		Util::String    m_desc;
		Util::String	m_valueStr;
		MaterialParameterType m_type;
	};

	typedef Util::Array<MaterialParam*> MaterialParamList;

	inline MaterialParam::MaterialParam()
	{
		//empty
	};

	inline MaterialParam::~MaterialParam()
	{
		//empty
	};

	inline void MaterialParam::SetName(const Util::String& name)
	{
		m_name = name;
	};

	inline const Util::String& MaterialParam::GetName() const
	{
		return m_name;
	}

	inline void MaterialParam::SetDesc(const Util::String& desc)
	{
		m_desc = desc;
	}

	inline const  Util::String& MaterialParam::GetDesc() const
	{
		return m_desc;
	}

	inline const MaterialParameterType& MaterialParam::GetType() const
	{
		return m_type;
	}
	inline const bool MaterialParam::IsConstType() const
	{
		return m_type >= eMaterialParamMatrix && m_type <= eMaterialParamFloat;
	}
	inline const bool MaterialParam::IsTexType() const
	{
		return m_type >= eMaterialParamTexture1D && m_type <= eMaterialParamTextureCUBE;

	}

	inline void MaterialParam::SetStringValue(const Util::String& valStr)
	{
		m_valueStr = valStr;
	}

	inline const Util::String& MaterialParam::GetStringValue() const
	{
		return m_valueStr;
	}

	class MaterialParamMatrix : public MaterialParam
	{
	public:
		MaterialParamMatrix();
		virtual ~MaterialParamMatrix();
		void SetValue(const Math::matrix44& val);
		const Math::matrix44& GetValue() const;
	private:
		Math::matrix44 m_value;
	};

	inline void MaterialParamMatrix::SetValue(const Math::matrix44& val)
	{
		m_value = val;
	}

	inline const Math::matrix44& MaterialParamMatrix::GetValue() const
	{
		return m_value;
	}

	class MaterialParamVector : public MaterialParam
	{
	public:
		MaterialParamVector();
		virtual ~MaterialParamVector();
		void SetValue(const Math::float4& val);
		const Math::float4& GetValue() const;
	private:
		Math::float4 m_value;
	};

	inline void MaterialParamVector::SetValue(const Math::float4& val)
	{
		m_value = val;
	}

	inline const Math::float4& MaterialParamVector::GetValue() const
	{
		return m_value;
	}

	class MaterialParamFloat : public MaterialParam
	{
	public:
		MaterialParamFloat();
		virtual ~MaterialParamFloat();
		void SetValue(const float& val);
		const float& GetValue() const;
	private:
		float m_value;
	};

	inline void MaterialParamFloat::SetValue(const float& val)
	{
		m_value = val;
	}

	inline const float& MaterialParamFloat::GetValue() const
	{
		return m_value;
	}
	class MaterialParamTexture : public MaterialParam
	{
	public:

		virtual ~MaterialParamTexture();
		void SetHandle(const RenderBase::TextureHandle& handle);
		const RenderBase::TextureHandle& GetHandle() const;
	protected:
		MaterialParamTexture();
	private:
		RenderBase::TextureHandle m_value;
	};

	inline void MaterialParamTexture::SetHandle(const RenderBase::TextureHandle& handle)
	{
		m_value = handle;
	}

	inline const RenderBase::TextureHandle& MaterialParamTexture::GetHandle() const
	{
		return m_value;
	}

	class MaterialParamTex1D : public MaterialParamTexture
	{
	public:
		MaterialParamTex1D();
		virtual ~MaterialParamTex1D();

	};

	class MaterialParamTex2D : public MaterialParamTexture
	{
	public:
		MaterialParamTex2D();
		virtual ~MaterialParamTex2D();
	};
	class MaterialParamTex3D : public MaterialParamTexture
	{
	public:
		MaterialParamTex3D();
		virtual ~MaterialParamTex3D();
	};


	class MaterialParamTexCube : public MaterialParamTexture
	{
	public:
		MaterialParamTexCube();
		virtual ~MaterialParamTexCube();
	};
}

#endif//MATEIRALPARAM_H_
