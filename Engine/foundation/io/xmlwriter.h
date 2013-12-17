/****************************************************************************
Copyright (c) 2006, Radon Labs GmbH
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
//------------------------------------------------------------------------------
/**
    @class IO::XmlWriter
  
    Write XML-formatted data to a stream.
*/    
#include "io/streamwriter.h"
#include "../extlibs/tinyxml/tinyxml.h"
#include "util/scriptbind.h"
#include "util/assetpath.h"

//------------------------------------------------------------------------------
namespace IO
{
class XmlWriter : public IO::StreamWriter
{
    __DeclareClass(XmlWriter);
	__ScriptBind
public:
    /// constructor
    XmlWriter();
    /// destructor
    virtual ~XmlWriter();
    /// begin writing the stream
    virtual bool Open();
    /// end writing the stream
    virtual void Close();

    /// begin a new node under the current node
    bool BeginNode(const Util::String& nodeName);
    /// end current node, set current node to parent
    void EndNode();
    /// write content text
    void WriteContent(const Util::String& text);
    /// write a comment
    void WriteComment(const Util::String& comment);

    /// set string attribute on current node
    void SetString(const Util::String& name, const Util::String& value);
    /// set bool attribute on current node
    void SetBool(const Util::String& name, bool value);
    /// set int attribute on current node
    void SetInt(const Util::String& name, int value);
    /// set float attribute on current node
    void SetFloat(const Util::String& name, float value);  

    /// set float2 attribute on current node
    void SetFloat2(const Util::String& name, const Math::float2& value);
	/// set float3 attribute on current node
	void SetFloat3(const Util::String& name, const Math::float3& value);
    /// set float4 attribute on current node
    void SetFloat4(const Util::String& name, const Math::float4& value);
    /// set matrix44 attribute on current node
    void SetMatrix44(const Util::String& name, const Math::matrix44& value);
	/// set assetPath attribute on current node
	void SetAssetPath(const Util::String& name, const Util::AssetPath& value);

    /// generic setter, template specializations implemented in nebula3/code/addons/nebula2
    template<typename T> void Set(const Util::String& name, const T &value);

private:
    TiXmlDocument* xmlDocument;
    TiXmlElement* curNode;
};

} // namespace IO
//------------------------------------------------------------------------------

