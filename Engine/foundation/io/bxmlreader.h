/****************************************************************************
Copyright (c) 2009, Radon Labs GmbH
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
    @class IO::BXmlReader
    
    Stream reader for binary XML files. The interface is similar
    to XmlReader so that it is easy to switch between the 2 classes.
    Use the N3 tool binaryxmlconverter3.exe to convert an XML file to
    a binary XML file.

*/
#include "io/streamreader.h"
#include "io/util/bxmlloaderutil.h"

//------------------------------------------------------------------------------
namespace IO
{
class BXmlReader : public StreamReader
{
    __DeclareClass(BXmlReader);
public:
    /// constructor
    BXmlReader();
    /// destructor
    virtual ~BXmlReader();
    
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

    /// get string attribute value from current node
    Util::String GetString(const char* attr) const;
    /// get bool attribute value from current node
    bool GetBool(const char* attr) const;
    /// get int attribute value from current node
    int GetInt(const char* attr) const;
    /// get float attribute value from current node
    float GetFloat(const char* attr) const;
    #if !__OSX__
	/// get float2 attribute value from current node
	Math::float2 GetFloat2(const char* attr) const;
    /// get float4 attribute value from current node
    Math::float4 GetFloat4(const char* attr) const;
    /// get matrix44 attribute value from current node
    Math::matrix44 GetMatrix44(const char* attr) const;
    #endif
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
    #if !__OSX__
    /// get float2 attribute value from current node
    Math::float2 GetOptFloat2(const char* attr, const Math::float2& defaultValue) const;
    /// get optional float4 attribute value from current node
    Math::float4 GetOptFloat4(const char* attr, const Math::float4& defaultValue) const;
    /// get optional matrix44 attribute value from current node
    Math::matrix44 GetOptMatrix44(const char* attr, const Math::matrix44& defaultValue) const;
    #endif
    
private:
    BXmlLoaderUtil loaderUtil;
};

} // namespace IO
//------------------------------------------------------------------------------
    