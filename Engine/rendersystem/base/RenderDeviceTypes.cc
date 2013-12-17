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

#include "stdneb.h"
#include "RenderDeviceTypes.h"
#ifdef __OSX__
#include "../rendersystem/config/RenderDeviceConfig.h"
#else
#include "config/RenderDeviceConfig.h"
#endif
namespace RenderBase
{

	using namespace Util;

	FillMode FillModeConverter::FromString(Util::String str)
	{
		str.ToUpper();
		if (str == "POINT") return eFMPOINT;
		else if (str == "LINE") return eFMWIREFRAME;
		else if (str == "FILL") return eFMSOLID;
		else
		{
			n_error("FillModeConverter::FromString():Invalid FillMode: %s",str.AsCharPtr());
			return eFMSOLID;
		}
	}

	Util::String FillModeConverter::ToString(FillMode mode)
	{
		switch (mode)
		{
		case eFMPOINT:     return "POINT";
		case eFMWIREFRAME:    return "LINE";
		case eFMSOLID:     return "FILL";

		default:
			n_error("FillModeConverter::ToString(): Invalid FillMode!");
			return "";
		}
	}

	CullMode CullModeConverter::FromString(Util::String str)
	{
		str.ToUpper();
		if (str == "NONE") return eCMNONE;
		else if (str == "FRONT") return eCMFRONT;
		else if (str == "BACK") return eCMBACK;
		else
		{
			n_error("CullModeConverter::FromString():Invalid CullMode: %s",str.AsCharPtr());
			return eCMNONE;
		}
	}

	Util::String CullModeConverter::ToString(CullMode mode)
	{
		switch (mode)
		{
		case eCMNONE:     return "NONE";
		case eCMFRONT:    return "FRONT";
		case eCMBACK:     return "BACK";

		default:
			n_error("CullModeConverter::ToString(): Invalid CullMode!");
			return "";
		}
	}

	BlendOperation BlendOperationConverter::FromString(Util::String str)
	{
		str.ToUpper();
		if (str == "ADD") return eBOADD;
		else if (str == "SUBTRACT") return eBOSUBSTRACT;
		else if (str == "REVSUBTRACT") return eBOREVSUBTRACT;
		else if (str == "MIN") return eBOMIN;
		else if (str == "MAX")	return eBOMAX;
		else
		{
			n_error("BlendOperationConverter::FromString():Invalid BlendOperation: %s",str.AsCharPtr());
			return eBOADD;
		}
	}

	Util::String BlendOperationConverter::ToString(BlendOperation bo)
	{
		switch (bo)
		{
		case eBOADD:				return "ADD";
		case eBOSUBSTRACT:				return "SUBTRACT";
		case eBOREVSUBTRACT:			return "REVSUBTRACT";
		case eBOMIN:				return "MIN";
		case eBOMAX:				return "MAX";

		default:
			n_error("BlendOperationConverter::ToString(): Invalid BlendOperation!");
			return "";
		}

	}

	BlendFactor AlphaBlendFactorConverter::FromString(Util::String str)
	{
		str.ToUpper();
		if (str == "ZERO") return eBFZERO;
		else if (str == "ONE") return eBFONE;
		else if (str == "SRCALPHA") return eBFSRCALPHA;
		else if (str == "DESTALPHA") return eBFDSTALPHA;
		else if (str == "INVSRCALPHA") return eBFINVSRCALPHA;
		else if (str == "INVDESTALPHA") return eBFINVDESTALPHA;
		else if (str == "SRCCOLOR") return eBFSRCCOLOR;
		else if (str == "DESTCOLOR") return eBFDESTCOLOR;
		else if (str == "INVSRCCOLOR") return eBFINVSRCCOLOR;
		else if (str == "INVDESTCOLOR") return eBFINVDESTCOLOR;
		else if (str == "SRCALPHASAT") return eBFSRCALPHASAT;
		else
		{
			n_error("AlphaBlendFactorConverter::FromString():Invalid AlphaBlendFactor: %s",str.AsCharPtr());
			return eBFZERO;
		}
	}

	Util::String AlphaBlendFactorConverter::ToString(BlendFactor abf)
	{
		switch (abf)
		{
		case eBFZERO:     return "ZERO";
		case eBFONE:		return "ONE";
		case eBFSRCALPHA:			return "SRCALPHA";
		case eBFDSTALPHA:		return "DESTALPHA";
		case eBFINVSRCALPHA:			return "INVSRCALPHA";
		case eBFINVDESTALPHA:		return "INVDESTALPHA";
		case eBFSRCCOLOR:	return "SRCCOLOR";
		case eBFDESTCOLOR:		return "DESTCOLOR";
		case eBFINVSRCCOLOR:		return "INVSRCCOLOR";
		case eBFINVDESTCOLOR:		return "INVDESTCOLOR";
		case eBFSRCALPHASAT:		return "DESTCOLOR";

		default:
			n_error("AlphaBlendFactorConverter::ToString(): Invalid AlphaBlendFactor!");
			return "";
		}

	}

	ColorMask ColorMaskConverter::FromString(Util::String str)
	{
		str.ToUpper();
		if (str == "RGBA") return eCOLORMASKRGBA;
		else if (str == "R") return eCOLORMASKRED;
		else if (str == "G") return eCOLORMASKGREEN;
		else if (str == "B") return eCOLORMASKBLUE;
		else if (str == "A") return eCOLORMASKALPHA;
		else if (str == "RGB") return eCOLORMASKRGB;
		else
		{
			n_error("ColorMaskConverter::FromString():Invalid ColorMask: %s",str.AsCharPtr());
			return eCOLORMASKRGBA;
		}
	}

	Util::String ColorMaskConverter::ToString(ColorMask cm)
	{
		switch (cm)
		{
		case eCOLORMASKRGBA:		return "RGBA";
		case eCOLORMASKRED:     return "R";
		case eCOLORMASKGREEN:		return "G";
		case eCOLORMASKBLUE:			return "B";
		case eCOLORMASKALPHA:		return "A";
		case eCOLORMASKRGB:			return "RGB";
		default:
			n_error("ColorMaskConverter::ToString(): invalid ColorMask!");
			return "";
		}
	}

	CompareFunction CompareFunctionConverter::FromString(Util::String str)
	{
		str.ToUpper();
		if (str == "NEVER") return eCFNEVER;
		else if (str == "ALWAYS") return eCFALWAYS;
		else if (str == "LESS") return eCFLESS;
		else if (str == "LESSEQUAL") return eCFLESSEQUAL;
		else if (str == "EQUAL") return eCFEQUAL;
		else if (str == "NOTEQUAL") return eCFNOTEQUAL;
		else if (str == "GREATEREQUAL") return eCFGREATEREQUAL;
		else if (str == "GREATER") return eCFGREATER;
		else
		{
			n_error("CompareFunctionConverter::FromString():Invalid CompareFunction: %s",str.AsCharPtr());
			return eCFNEVER;
		}
	}

	Util::String CompareFunctionConverter::ToString(CompareFunction cf)
	{
		switch (cf)
		{
		case eCFNEVER:     return "NEVER";
		case eCFALWAYS:		return "ALWAYS";
		case eCFLESS:			return "LESS";
		case eCFLESSEQUAL:		return "LESSEQUAL";
		case eCFEQUAL:			return "EQUAL";
		case eCFNOTEQUAL:		return "NOTEQUAL";
		case eCFGREATEREQUAL:	return "GREATEREQUAL";
		case eCFGREATER:		return "GREATER";

		default:
			n_error("CompareFunctionConverter::ToString(): Invalid CompareFunction!");
			return "";
		}

	}

	TextureAddressMode TextureAddressModeConverter::FromString(Util::String str)
	{
		str.ToUpper();
		if (str == "WRAP") return eTAMWRAP;
		else if (str == "CLAMP") return eTAMCLAMP;
		else if (str == "MIRROR") return eTAMMIRROR;
		else if (str == "BORDER") return eTAMBORDER;
		else
		{
			n_error("TextureAddressModeConverter::FromString():Invalid TextureAddressMode: %s",str.AsCharPtr());
			return eTAMWRAP;
		}
	}

	Util::String TextureAddressModeConverter::ToString(TextureAddressMode tam)
	{
		switch (tam)
		{
		case eTAMWRAP:      return "WRAP";
		case eTAMCLAMP:		return "CLAMP";
		case eTAMMIRROR:	return "MIRROR";
		case eTAMBORDER:		return "BORDER";

		default:
			n_error("TextureAddressModeConverter::ToString(): invalid TextureAddressMode!");
			return "";
		}

	}

	TextureFilter TextureFilterOperationConverter::FromString(Util::String str)
	{
		str.ToUpper();
		if (str == "POINT") return eTFPOINT;
		else if (str == "LINEAR") return eTFLINEAR;
		else if (str == "ANISOTROPIC") return eTFANISOTROPIC;
		else
		{
			n_error("TextureFilterOperationConverter::FromString():Invalid TextureFilterOperation: %s",str.AsCharPtr());
			return eTFPOINT;
		}
	}

	Util::String TextureFilterOperationConverter::ToString(TextureFilter tfo)
	{
		n_error("TexFilterOpConverter::ToString():not implemented!");
		return "";
	}

	DeviceRasterizerState::DeviceRasterizerState()
		: m_fillMode(eFMSOLID),
		m_cullMode(eCMBACK),
		m_slopScaleDepthBias(0),
		m_depthBias(0),
		m_scissorTestEnable(false),
		m_multisampleEnable(true)
	{
	}

	DeviceDepthAndStencilState::DeviceDepthAndStencilState()
		: m_depthEnable(true),
		m_depthWriteMask(true),
		m_zFunc(eCFLESSEQUAL),
		m_stencilRef(0),
		m_stencilEnable(false),
		m_stencilFunc(eCFALWAYS),
		m_stencilReadMask(0xFFFF),
		m_stencilWriteMask(0xFFFF),
		m_stencilFail(eSOKEEP),
		m_stencilZFail(eSOKEEP),
		m_stencilPass(eSOKEEP),
		m_stencilTwoEnable(false),
		m_StencilTwoFunc(eCFALWAYS),
		m_stencilTwoReadMask(0xFFFF),
		m_stencilTwoWriteMask(0xFFFF),
		m_stencilTwoFail(eSOKEEP),
		m_stencilTwoZFail(eSOKEEP),
		m_stencilTwoPass(eSOKEEP)
		
	{
	}

	DeviceBlendState::DeviceBlendState()
		: m_alphaTestEnable(false),
		m_alphaFunc(eCFALWAYS),
		m_alphaRef(0),
		m_separateAlphaBlendEnable(false)
	{
		m_alphaBlendEnable.Fill(0,9,false);
		m_blendOP.Fill(0,9,eBOADD);
		m_srcBlend.Fill(0,9,eBFZERO);
		m_destBlend.Fill(0,9,eBFONE);
		m_blendOPAlpha.Fill(0,9,eBOADD);
		m_srcBlendAlpha.Fill(0,9,eBFZERO);
		m_destBlendAlpha.Fill(0,9,eBFONE);
		m_colorWriteMask.Fill(0,9,eCOLORMASKRGBA);

	}

	DeviceSamplerState::DeviceSamplerState()
	{
		m_textureIndexEnable.Fill(0,12,false);
		m_addressU.Fill(0,12,eTAMWRAP);
		m_addressV.Fill(0,12,eTAMWRAP);
		m_addressW.Fill(0,12,eTAMWRAP);
		m_Filter.Fill(0,12,eTFPOINT);
		m_maxAnisotropy.Fill(0,12,16);
		m_textureType.Fill(0, 12, "Texture2D");
	}

	//------------------------------------------------------------------------------
	/**
	*/
	PrimitiveTopology::Code
		PrimitiveTopology::FromString(const String& str)
	{
		if (str == "PointList")             return PointList;
		else if (str == "LineList")         return LineList;
		else if (str == "LineStrip")        return LineStrip;
		else if (str == "TriangleList")     return TriangleList;
		else if (str == "TriangleStrip")    return TriangleStrip;
		else
		{
			n_error("PrimitiveTopology::FromString(): invalid string '%s'!", str.AsCharPtr());
			return InvalidPrimitiveTopology;
		}
	}

	//------------------------------------------------------------------------------
	/**
	*/
	String
		PrimitiveTopology::ToString(Code code)
	{
		switch (code)
		{
		case PointList:     return "PointList";
		case LineList:      return "LineList";
		case LineStrip:     return "LineStrip";
		case TriangleList:  return "TriangleList";
		case TriangleStrip: return "TriangleStrip";

		default:
			n_error("PrimitiveTopology::ToString(): invalid topology code!");
			return "";
		}
	}

	//------------------------------------------------------------------------------
	/**
	*/
	ImageFileFormat::Code
		ImageFileFormat::FromString(const Util::String& str)
	{
		if (str == "bmp") return BMP;
		else if (str == "jpg") return JPG;
		else if (str == "png") return PNG;
		else if (str == "dds") return DDS;
		else
		{
			return InvalidImageFileFormat;
		}
	}

	//------------------------------------------------------------------------------
	/**
	*/
	Util::String
		ImageFileFormat::ToString(ImageFileFormat::Code c)
	{
		switch (c)
		{
		case BMP:   return "bmp";
		case JPG:   return "jpg";
		case PNG:   return "png";
		case DDS:   return "dds";
		default:
			n_error("ImageFileFormat::ToString(): invalid image file format code!");
			return "";
		}
	}

	//------------------------------------------------------------------------------
	/**
	*/
	ImageFileFormat::Code
		ImageFileFormat::FromMediaType(const IO::MediaType& mediaType)
	{
		n_assert(mediaType.IsValid());
		if (mediaType.GetType() != "image")
		{
			return InvalidImageFileFormat;
		}
		else
		{
			const String& subType = mediaType.GetSubType();
			if (subType == "bmp")       return BMP;
			else if (subType == "jpeg") return JPG;
			else if (subType == "png")  return PNG;
			else if (subType == "dds")  return DDS; // hmm... non-standard
			else
			{
				return InvalidImageFileFormat;
			}
		}
	}

	//------------------------------------------------------------------------------
	/**
	*/
	IO::MediaType
		ImageFileFormat::ToMediaType(Code c)
	{
		switch (c)
		{
		case BMP:   return IO::MediaType("image", "bmp");
		case JPG:   return IO::MediaType("image", "jpeg");
		case PNG:   return IO::MediaType("image", "png");
		case DDS:   return IO::MediaType("image", "dds");   // hmm... non-standard
		default:
			n_error("ImageFileFormat::ToMediaType(): invalid image file format code!");
			return IO::MediaType();
		}
	}

	//------------------------------------------------------------------------------
	/**
	*/
	AntiAliasQuality::Code
		AntiAliasQuality::FromString(const Util::String& str)
	{
		if ("None" == str) return None;
		else if ("Low" == str) return Low;
		else if ("Medium" == str) return Medium;
		else if ("High" == str) return High;
		else
		{
			n_error("Invalid antialias quality string '%s'!", str.AsCharPtr());
			return None;
		}
	}

	//------------------------------------------------------------------------------
	/**
	*/
	Util::String
		AntiAliasQuality::ToString(Code code)
	{
		switch (code)
		{
		case None:      return "None";
		case Low:       return "Low";
		case Medium:    return "Medium";
		case High:      return "High";
		default:
			n_error("Invalid antialias quality code!");
			return "";
		}
	}

	//------------------------------------------------------------------------------
	/**
	*/
	bool 
		BoolModeConverter::FromString(Util::String str)
	{
		str.ToUpper();
		if ("FALSE" == str) return false;
		else if ("TRUE" == str) return true;
		else
		{
			n_error("Invalid bool string '%s'!", str.AsCharPtr());
			return false;
		}

	}

	//------------------------------------------------------------------------------
	/**
	*/
	Util::String 
		BoolModeConverter::ToString(bool b)
	{
		if (b)
		{
			return "TRUE";
		} 
		else
		{
			return "FALSE";
		}
	}


}