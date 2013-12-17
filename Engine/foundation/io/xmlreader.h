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
    @class IO::XmlReader
  
    Reads XML formatted data with random access from a stream using 
    TinyXML as backend. The XML document is represented as a tree of
    nodes, which can be navigated and queried.
    
*/
#include "io/streamreader.h"

#include "math/float4.h"
#include "math/float2.h"
#include "math/matrix44.h"
#include "util/assetpath.h"

#include "../extlibs/tinyxml/tinyxml.h"
#include "util/scriptbind.h"

//------------------------------------------------------------------------------
namespace IO
{
class XmlReader : public StreamReader
{
    __DeclareClass(XmlReader);
	__ScriptBind
public:
    /// constructor
    XmlReader();
    /// destructor
    virtual ~XmlReader();

    /// begin reading from the stream
    virtual bool Open();
    /// end reading from the stream
    virtual void Close();

    /// return true if node exists 
    bool HasNode(const Util::String& path) const;
    /// get short name of current node
    Util::String GetCurrentNodeName() const;
    /// get path to current node
    Util::String GetCurrentNodePath() const;
    /// returns the line number of the current node
    int GetCurrentNodeLineNumber() const;
    
    /// set current node as path
    void SetToNode(const Util::String& path);
    /// set current node to first child node, return false if no child exists
    bool SetToFirstChild(const Util::String& name = "");
    /// set current node to next sibling node, return false if no more sibling exists
    bool SetToNextChild(const Util::String& name = "");
    /// set current node to parent, return false if no parent exists
    bool SetToParent();

    /// return true if matching attribute exists on current node
    bool HasAttr(const char* attr) const;
    /// return names of all attrs on current node
    Util::Array<Util::String> GetAttrs() const;

    /// return true if current node has embedded content
    bool HasContent() const;
    /// return embedded content of current node
    Util::String GetContent() const;

    /// get string attribute value from current node
    Util::String GetString(const char* attr) const;
	/// get char* attribute value from current node and step fword
	const char* GetString_forward(const char* name );
    /// get bool attribute value from current node
    bool GetBool(const char* attr) const;
    /// get int attribute value from current node
    int GetInt(const char* attr) const;
    /// get float attribute value from current node
    float GetFloat(const char* attr) const;

    /// get float2 attribute value from current node
	Math::float2 GetFloat2(const char* attr) const;
    /// get float4 attribute value from current node
    Math::float4 GetFloat4(const char* attr) const;
	/// get float4 attribute value from current node
	Math::float3 GetFloat3(const char* attr) const;
    /// get matrix44 attribute value from current node
    Math::matrix44 GetMatrix44(const char* attr) const;
	/// get assetpath attribute value from current node
	Util::AssetPath GetAssetPath(const char* attr) const;

    /// generic getter for extension types
    template<typename T> T Get(const char* attr) const;

    /// get optional string attribute value from current node
    Util::String GetOptString(const char* attr, const Util::String& defaultValue) const;
    /// get optional bool attribute value from current node
    bool GetOptBool(const char* attr, bool defaultValue) const;
    /// get optional int attribute value from current node
    int GetOptInt(const char* attr, int defaultValue) const;
    /// get optional float attribute value from current node
    float GetOptFloat(const char* attr, float defaultValue) const;

    /// get float2 attribute value from current node
    Math::float2 GetOptFloat2(const char* attr, const Math::float2& defaultValue) const;
    /// get optional float4 attribute value from current node
    Math::float4 GetOptFloat4(const char* attr, const Math::float4& defaultValue) const;
    /// get optional matrix44 attribute value from current node
    Math::matrix44 GetOptMatrix44(const char* attr, const Math::matrix44& defaultValue) const;


	TiXmlElement* GetCurrentNode(void) const;

	void SetCurrentNode( TiXmlElement* node );

   

private:
    /// find a node by path, handles relativ paths as well
    TiXmlNode* FindNode(const Util::String& path) const;

    /// static helper object for TinyXml-Initialization at application startup
    class TinyXmlInitHelper
    {
    public:
        /// constructor
        TinyXmlInitHelper()
        {
            TiXmlBase::SetCondenseWhiteSpace(true);
        }
    };

    static TinyXmlInitHelper initTinyXml;
    TiXmlDocument* xmlDocument;
    TiXmlElement* curNode;
	
	protected:

};

//------------------------------------------------------------------------
inline
TiXmlElement* XmlReader::GetCurrentNode(void) const
{
	return curNode;
}
//------------------------------------------------------------------------
inline 
void 
XmlReader::SetCurrentNode(TiXmlElement* node)
{
	curNode = node;
}



} // namespace IO
//------------------------------------------------------------------------------
