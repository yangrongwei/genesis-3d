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
#ifndef RENDERDEVICETYPES_H_
#define RENDERDEVICETYPES_H_

#include "../config/RenderDeviceConfig.h"
#include "../foundation/util/array.h"
#include "../foundation/math/float4.h"
#include "../foundation/io/mediatype.h"
#include "../foundation/util/string.h"
#include "../foundation/util/stringatom.h"
#include "../foundation/util/guid.h"
#include "core/refcounted.h"
#include "../foundation/util/scriptbind.h"
#include "../rendersystem/base/PixelFormat.h"
#include "../rendersystem/base/RenderCommandType.h"

namespace RenderBase
{
	typedef Util::StringAtom ResourcePath;

	class RenderResourceHandle
	{
	public:
		RenderResourceHandle()
			: mRO(NULL){
		}
		RenderResourceHandle(RenderCommandType* ro)
			: mRO(ro){
		}

		const Core::RefCounted* AsObject(void) const{
			return static_cast<const Core::RefCounted*>(mRO);
		}
		Core::RefCounted* AsObject(void){
			return static_cast<Core::RefCounted*>(mRO);
		}
		RenderCommandType::eRenderCMDType GetType() const{	
			return (NULL == mRO)? RenderCommandType::InvalidRenderCMDType : mRO->GetRenderCommandType();
		}
		bool IsValid() const{
			return mRO != NULL;
		}

		operator bool() const{
			return  mRO != NULL;
		}

		bool operator!=(const RenderResourceHandle& rhs) const{
			return this->mRO != rhs.mRO;
		}

		bool operator==(const RenderResourceHandle& rhs) const{
			return this->mRO == rhs.mRO;
		}

		bool operator<(const RenderResourceHandle& rhs) const{
			return this->mRO < rhs.mRO;
		}
		//------------------------------------------------------------------------
		bool operator<=(const RenderResourceHandle& rhs) const{
			return this->mRO <= rhs.mRO;
		}
		//------------------------------------------------------------------------
		bool operator>(const RenderResourceHandle& rhs) const{
			return this->mRO > rhs.mRO;
		}
		//------------------------------------------------------------------------
		bool operator>=(const RenderResourceHandle& rhs) const{
			return this->mRO >= rhs.mRO;
		}
	protected:
		// 线程安全： 绝对不允许直接在RenderSystem以外访问RenderCommandType的数据
		// 所有的访问都要通过RenderSystem来访问
		RenderCommandType* mRO;
		friend class RenderSystem;
	};

	typedef RenderResourceHandle PrimitiveHandle;
	typedef RenderResourceHandle RenderTargetHandle;
	typedef RenderResourceHandle MultipleRenderTargetHandle;
	typedef RenderResourceHandle GPUProgramHandle;
	typedef RenderResourceHandle TextureHandle;
	typedef RenderResourceHandle RenderStateDescHandle;


	enum FillMode
	{
		eFMPOINT,
		eFMWIREFRAME,
		eFMSOLID
	};

	struct FillModeConverter
	{
		/// convert from string
		static FillMode FromString(Util::String str);
		/// convert to string
		static Util::String ToString(FillMode code);
	};

	enum CullMode
	{
		eCMNONE,
		eCMFRONT,
		eCMBACK
	};

	struct CullModeConverter
	{
		/// convert from string
		static CullMode FromString(Util::String str);
		/// convert to string
		static Util::String ToString(CullMode code);
	};

	enum BlendOperation
	{
		eBOADD		= 1,
		eBOSUBSTRACT		= 2,
		eBOREVSUBTRACT	= 3,
		eBOMIN		= 4,
		eBOMAX		= 5,
	};

	struct BlendOperationConverter
	{
		/// convert from string
		static BlendOperation FromString(Util::String str);
		/// convert to string
		static Util::String ToString(BlendOperation bo);
	};

	enum BlendFactor
	{
		eBFZERO,
		eBFONE,
		eBFSRCCOLOR,
		eBFINVSRCCOLOR,		
		eBFSRCALPHA,		
		eBFINVSRCALPHA,
		eBFDSTALPHA,
		eBFINVDESTALPHA,		
		eBFDESTCOLOR,
		eBFINVDESTCOLOR,
		eBFSRCALPHASAT
	};

	struct AlphaBlendFactorConverter
	{
		/// convert from string
		static BlendFactor FromString(Util::String str);
		/// convert to string
		static Util::String ToString(BlendFactor bo);
	};

	enum CompareFunction
	{
		eCFNEVER,		
		eCFLESS,
		eCFEQUAL,
		eCFLESSEQUAL,
		eCFGREATER,
		eCFNOTEQUAL,
		eCFGREATEREQUAL,	
		eCFALWAYS,
	};

	struct CompareFunctionConverter
	{
		/// convert from string
		static CompareFunction FromString(Util::String str);
		/// convert to string
		static Util::String ToString(CompareFunction cf);
	};


	enum StencilOperation
	{
		eSOKEEP,
		eSOZERO,
		eSOREPLACE,
		eSOINCR,
		eSODECR,
		eSOINCRWRAP,
		eSODECRSAT,
		eSOINVERT

	};

	enum ColorMask
	{
		eCOLORMASKRED   = 1UL << 3,
		eCOLORMASKGREEN = 1UL << 2,
		eCOLORMASKBLUE  = 1UL << 1,
		eCOLORMASKALPHA = 1UL << 0,
		eCOLORMASKRGB   = eCOLORMASKRED | eCOLORMASKGREEN | eCOLORMASKBLUE,
		eCOLORMASKRGBA   = eCOLORMASKRED | eCOLORMASKGREEN | eCOLORMASKBLUE | eCOLORMASKALPHA
	};

	struct ColorMaskConverter
	{
		/// convert from string
		static ColorMask FromString(Util::String str);
		/// convert to string
		static Util::String ToString(ColorMask cm);
	};


	enum TextureAddressMode
	{
		eTAMWRAP,
		eTAMMIRROR,
		eTAMCLAMP,
		eTAMBORDER
	};

	struct TextureAddressModeConverter
	{
		/// convert from string
		static TextureAddressMode FromString(Util::String str);
		/// convert to string
		static Util::String ToString(TextureAddressMode tam);
	};

	enum TextureFilter
	{
		eTFPOINT,
		eTFLINEAR,
		eTFANISOTROPIC,
	};

	struct TextureFilterOperationConverter
	{
		/// convert from string
		static TextureFilter FromString(Util::String str);
		/// convert to string
		static Util::String ToString(TextureFilter tfo);
	};

	struct DeviceRasterizerState
	{
		FillMode			m_fillMode;
		CullMode			m_cullMode;
		float				m_slopScaleDepthBias;
		float				m_depthBias;
		bool				m_scissorTestEnable;
		bool				m_multisampleEnable;

		DeviceRasterizerState();
	};

	struct DeviceDepthAndStencilState
	{
		bool				m_depthEnable;
		bool				m_depthWriteMask;
		CompareFunction		m_zFunc;
		
		int                 m_stencilRef;
		bool				m_stencilEnable;
		CompareFunction		m_stencilFunc;
		unsigned short		m_stencilReadMask;
		unsigned short		m_stencilWriteMask;
		StencilOperation	m_stencilFail;
		StencilOperation	m_stencilZFail;
		StencilOperation	m_stencilPass;

		bool				m_stencilTwoEnable;
		CompareFunction		m_StencilTwoFunc;
		unsigned short		m_stencilTwoReadMask;
		unsigned short		m_stencilTwoWriteMask;
		StencilOperation	m_stencilTwoFail;
		StencilOperation	m_stencilTwoZFail;
		StencilOperation	m_stencilTwoPass;



		DeviceDepthAndStencilState();

	};

	struct DeviceBlendState
	{
		bool				m_alphaTestEnable;
		bool				m_separateAlphaBlendEnable;
		CompareFunction		m_alphaFunc;
		float				m_alphaRef;

		Util::Array<bool>				m_alphaBlendEnable;
		Util::Array<BlendOperation>		m_blendOP;
		Util::Array<BlendFactor>		m_srcBlend;
		Util::Array<BlendFactor>		m_destBlend;
		Util::Array<BlendOperation>		m_blendOPAlpha;
		Util::Array<BlendFactor>		m_srcBlendAlpha;
		Util::Array<BlendFactor>		m_destBlendAlpha;
		Util::Array<unsigned short int>	m_colorWriteMask;


		DeviceBlendState();
	};

	struct DeviceSamplerState
	{
		Util::Array<bool>				m_textureIndexEnable;
		Util::Array<TextureAddressMode> m_addressU;
		Util::Array<TextureAddressMode> m_addressV;
		Util::Array<TextureAddressMode> m_addressW;
		Util::Array<Util::String>		m_textureType;
		Util::Array<TextureFilter>		m_Filter;
		Util::Array<unsigned char>		m_maxAnisotropy;
		DeviceSamplerState();
	};

	class PrimitiveTopology
	{
	public:
		/// enumeration
		enum Code
		{
			InvalidPrimitiveTopology,

			PointList,
			LineList,
			LineStrip,
			TriangleList,
			TriangleStrip,
		};

		/// convert from string
		static Code FromString(const Util::String& str);
		/// convert to string
		static Util::String ToString(Code code);

	};


	class ImageFileFormat
	{
	public:
		/// image file formats
		enum Code
		{
			BMP,
			JPG,
			PNG,
			DDS,

			InvalidImageFileFormat,
		};

		/// convert from string
		static Code FromString(const Util::String& str);
		/// convert to string
		static Util::String ToString(Code c);
		/// convert from media type (MIME)
		static Code FromMediaType(const IO::MediaType& mediaType);
		/// convert to media type (MIME)
		static IO::MediaType ToMediaType(Code c);
	};

	class AntiAliasQuality
	{
	public:
		/// enum
		enum Code
		{
			None,
			Low,
			Medium,
			High,
		};

		/// convert from string
		static Code FromString(const Util::String& str);
		/// convert to string
		static Util::String ToString(Code code);
	};

	struct BoolModeConverter
	{ 
		/// convert from string
		static bool FromString(Util::String str);
		/// convert to string
		static Util::String ToString(bool b);
	};

}

#endif //RENDERDEVICETYPES_H_