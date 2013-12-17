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
#ifndef VERTEXCOMPONENT_H_
#define VERTEXCOMPONENT_H_
#include "core/types.h"
#include "util/string.h"
#include "util/array.h"
#include "core/refcounted.h"
//------------------------------------------------------------------------------
namespace RenderBase
{
class VertexComponent
{
public:
    /// component semantic
    enum SemanticName
    {
        Position = 0,
        Normal,
        Tangent,
        Binormal,
        TexCoord,        
        Color,
        SkinWeights,
        SkinJIndices,

        Invalid,
    };

    /// component format
    enum Format
    {
        Float,      //> one-component float, expanded to (float, 0, 0, 1)
        Float2,     //> two-component float, expanded to (float, float, 0, 1)
        Float3,     //> three-component float, expanded to (float, float, float, 1)
        Float4,     //> four-component float
        UByte4,     //> four-component unsigned byte
        Short2,     //> two-component signed short, expanded to (value, value, 0, 1)
        Short4,     //> four-component signed short
        UByte4N,    //> four-component normalized unsigned byte (value / 255.0f)
        Short2N,    //> two-component normalized signed short (value / 32767.0f)
        Short4N,    //> four-component normalized signed short (value / 32767.0f)
		ColorBGRA,	//> color type. for D3D9 fix function support
		ColorRGBA,	//> color type. for opengl fix function support

        // PS3-specific
        Float16,
        Float16_2,
        Float16_3,
        Float16_4,
    };
    
    /// access type hint, this is only relevant on the Wii
    enum AccessType
    {
        None,
        Direct,     //> component has direct value (non-indexed)
        Index8,     //> component is indexed with 8-bit indices           
        Index16,    //> component is indexed with 16-bit indices
        Index32,    //> component is indexed with 32-bit indices
    };

    /// default constructor
    VertexComponent();
    /// constructor
    VertexComponent(SemanticName semName, IndexT semIndex, Format format, IndexT streamIndex=0);
    /// get semantic name
    SemanticName GetSemanticName() const;
    /// get semantic index
    IndexT GetSemanticIndex() const;
    /// get vertex component format
    Format GetFormat() const;
    /// get stream index
    IndexT GetStreamIndex() const;
    /// get the byte size of the vertex component
    SizeT GetByteSize() const;
    /// get a unique signature of the vertex component
    Util::String GetSignature() const;
    /// get access type
    AccessType GetAccessType() const;
    /// convert string to semantic name
    static SemanticName StringToSemanticName(const Util::String& str);
    /// convert semantic name to string
    static Util::String SemanticNameToString(SemanticName n);
    /// convert string to format
    static Format StringToFormat(const Util::String& str);
    /// convert format to string
    static Util::String FormatToString(Format f);
    /// get the byte offset of this component (only valid when part of a VertexLayout)
    IndexT GetByteOffset() const;
	/// Utility method which returns the count of values in a given type
	static uint GetTypeCount(Format format);
	static SizeT GetByteSize(Format format);
	static int BuildComponentsOffsetAndSize(Util::Array<VertexComponent>& in_out);

protected:
    friend class VertexLayout;

    /// set the vertex byte offset (called from VertexLayoutBase::Setup())
    void SetByteOffset(IndexT offset);

    SemanticName semName;
    IndexT semIndex;
    Format format;
    AccessType accessType;
    IndexT streamIndex;
    IndexT byteOffset;
};

//------------------------------------------------------------------------------
/**
*/
inline
VertexComponent::VertexComponent() :
    semName(Invalid),
    semIndex(0),
    format(Float),
    accessType(Index16),
    streamIndex(0),
    byteOffset(0)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline
VertexComponent::VertexComponent(SemanticName semName_, IndexT semIndex_, Format format_, IndexT streamIndex_) :
    semName(semName_),
    semIndex(semIndex_),
    format(format_),
    accessType(Index16),
    streamIndex(streamIndex_),
    byteOffset(-1)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline VertexComponent::SemanticName
VertexComponent::GetSemanticName() const
{
    return this->semName;
}

//------------------------------------------------------------------------------
/**
*/
inline VertexComponent::AccessType
VertexComponent::GetAccessType() const
{
    return this->accessType;     
}

//------------------------------------------------------------------------------
/**
*/
inline IndexT
VertexComponent::GetSemanticIndex() const
{
    return this->semIndex;
}

//------------------------------------------------------------------------------
/**
*/
inline VertexComponent::Format
VertexComponent::GetFormat() const
{
    return this->format;
}

//------------------------------------------------------------------------------
/**
*/
inline IndexT
VertexComponent::GetStreamIndex() const
{
    return this->streamIndex;
}
//------------------------------------------------------------------------------
/**
*/
inline SizeT
	VertexComponent::GetByteSize(Format format)
{
	switch (format)
	{
	case Float:     return 4;
	case Float2:    return 8;
	case Float3:    return 12;
	case Float4:    return 16;
	case UByte4:    return 4;
	case Short2:    return 4;
	case Short4:    return 8;
	case UByte4N:   return 4;
	case Short2N:   return 4;
	case Short4N:   return 8;
	case ColorBGRA: return 4;
	case ColorRGBA: return 4;

		// PS3-specific
	case Float16:   return 2;
	case Float16_2: return 4;
	case Float16_3: return 6;
	case Float16_4: return 8;
	}
	n_error("Can't happen");
	return 0;
}

//------------------------------------------------------------------------------
/**
*/
inline SizeT
VertexComponent::GetByteSize() const
{
   return GetByteSize(this->format);
}

//------------------------------------------------------------------------------
/**
*/
inline Util::String
VertexComponent::SemanticNameToString(SemanticName n)
{
    switch (n)
    {
        case Position:      return "Position";
        case Normal:        return "Normal";
        case Tangent:       return "Tangent";
        case Binormal:      return "Binormal";
        case TexCoord:      return "TexCoord";
        case Color:         return "Color";
        case SkinWeights:   return "SkinWeights";
        case SkinJIndices:  return "SkinJIndices";
        default:
            n_error("VertexComponent::SemanticNameToString(): invalid SemanticName code!");
            return "";
    }
}

//------------------------------------------------------------------------------
/**
*/
inline VertexComponent::SemanticName
VertexComponent::StringToSemanticName(const Util::String& str)
{
    if (str == "Position") return Position;
    else if (str == "Normal") return Normal;
    else if (str == "Tangent") return Tangent;
    else if (str == "Binormal") return Binormal;
    else if (str == "TexCoord") return TexCoord;
    else if (str == "Color") return Color;
    else if (str == "SkinWeights") return SkinWeights;
    else if (str == "SkinJIndices") return SkinJIndices;
    else
    {
        n_error("VertexComponent::StringToSemanticName(): invalid string '%s'!", str.AsCharPtr());
        return Invalid;
    }
}

//------------------------------------------------------------------------------
/**
*/
inline Util::String
VertexComponent::FormatToString(Format f)
{
    switch (f)
    {
        case Float:     return "Float";
        case Float2:    return "Float2";
        case Float3:    return "Float3";
        case Float4:    return "Float4";
        case UByte4:    return "UByte4";
        case Short2:    return "Short2";
        case Short4:    return "Short4";
        case UByte4N:   return "UByte4N";
        case Short2N:   return "Short2N";
        case Short4N:   return "Short4N";
		case ColorBGRA: return "ColorBGRA";
		case ColorRGBA: return "ColorRGBA";

        // PS3-specific
        case Float16:   return "Float16";
        case Float16_2: return "Float16_2";
        case Float16_3: return "Float16_3";
        case Float16_4: return "Float16_4";

        default:
            n_error("VertexComponent::FormatToString(): invalid Format code!");
            return "";
    }
}

//------------------------------------------------------------------------------
/**
*/
inline VertexComponent::Format
VertexComponent::StringToFormat(const Util::String& str)
{
    if (str == "Float") return Float;
    else if (str == "Float2") return Float2;
    else if (str == "Float3") return Float3;
    else if (str == "Float4") return Float4;
    else if (str == "UByte4") return UByte4;
    else if (str == "Short2") return Short2;
    else if (str == "Short4") return Short4;
    else if (str == "UByte4N") return UByte4N;
    else if (str == "Short2N") return Short2N;
    else if (str == "Short4N") return Short4N;
	else if (str == "ColorBGRA") return ColorBGRA;
	else if (str == "ColorRGBA") return ColorRGBA;
    else if (str == "Float16") return Float16;
    else if (str == "Float16_2") return Float16_2;
    else if (str == "Float16_3") return Float16_3;
    else if (str == "Float16_4") return Float16_4;
    else
    {
        n_error("VertexComponent::StringToFormat(): invalid string '%s'!\n", str.AsCharPtr());
        return Float;
    }
}

//------------------------------------------------------------------------------
/**
*/
inline Util::String
VertexComponent::GetSignature() const
{
    Util::String str;
    switch (this->semName)
    {
        case Position:      str = "pos"; break;
        case Normal:        str = "nrm"; break;
        case Tangent:       str = "tan"; break;
        case Binormal:      str = "bin"; break;
        case TexCoord:      str = "tex"; break;
        case Color:         str = "clr"; break;
        case SkinWeights:   str = "skw"; break;
        case SkinJIndices:  str = "sji"; break;
        default:
            n_error("can't happen!");
            break;
    }
    str.AppendInt(this->semIndex);    
    str.Append(FormatToString(this->format));
    return str;
}

//------------------------------------------------------------------------------
/**
*/
inline void
VertexComponent::SetByteOffset(IndexT offset)
{
    this->byteOffset = offset;
}

//------------------------------------------------------------------------------
/**
*/
inline IndexT
VertexComponent::GetByteOffset() const
{
    return this->byteOffset;
}

//------------------------------------------------------------------------------
/**
*/
inline uint
	VertexComponent::GetTypeCount(Format format)
{
	switch (format)
	{
	case Float:	
		return 1;
	case Float2:
		return 2;
	case Float3:
		return 3;
	case Float4:
		return 4;
	case UByte4:
		return 4;
	case Short2:
		return 2;
	case Short4:
		return 4;
	case UByte4N:
		return 4;
	case Short2N:
		return 2;
	case Short4N:
		return 4;
	case ColorBGRA:
	case ColorRGBA:
		return 4;
	}

	n_error("Invalid type!");

	return 0;
}

} // namespace RenderBase
//------------------------------------------------------------------------------

#endif