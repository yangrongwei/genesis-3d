#pragma once
//------------------------------------------------------------------------------
/**
    This file was generated with Nebula3's idlc compiler tool.
    DO NOT EDIT
*/
#include "messaging/message.h"
#include "io/ioprotocoldef.h"

//------------------------------------------------------------------------------
namespace IO
{
//------------------------------------------------------------------------------
class CopyFile : public Messaging::Message
{
    __DeclareClass(CopyFile);
    __DeclareMsgId;
public:
    CopyFile() :
        result(false)
    { };
public:
    void SetFromURI(const IO::URI& val)
    {
        n_assert(!this->handled);
        this->fromuri = val;
    };
    const IO::URI& GetFromURI() const
    {
        return this->fromuri;
    };
private:
    IO::URI fromuri;
public:
    void SetToURI(const IO::URI& val)
    {
        n_assert(!this->handled);
        this->touri = val;
    };
    const IO::URI& GetToURI() const
    {
        return this->touri;
    };
private:
    IO::URI touri;
public:
    void SetResult(bool val)
    {
        n_assert(!this->handled);
        this->result = val;
    };
    bool GetResult() const
    {
        return this->result;
    };
private:
    bool result;
};
//------------------------------------------------------------------------------
class IOMessage : public Messaging::Message
{
    __DeclareClass(IOMessage);
    __DeclareMsgId;
public:
    IOMessage() :
        result(false)
    { };
public:
    void SetFileName(const Util::StringAtom& val)
    {
        n_assert(!this->handled);
        this->filename = val;
    };
    const Util::StringAtom& GetFileName() const
    {
        return this->filename;
    };
private:
    Util::StringAtom filename;
public:
    void SetResult(bool val)
    {
        n_assert(!this->handled);
        this->result = val;
    };
    bool GetResult() const
    {
        return this->result;
    };
private:
    bool result;
};
//------------------------------------------------------------------------------
class CreateDirectory : public IOMessage
{
    __DeclareClass(CreateDirectory);
    __DeclareMsgId;
public:
    CreateDirectory() 
    { };
};
//------------------------------------------------------------------------------
class DeleteDirectory : public IOMessage
{
    __DeclareClass(DeleteDirectory);
    __DeclareMsgId;
public:
    DeleteDirectory() 
    { };
};
//------------------------------------------------------------------------------
class DeleteFile : public IOMessage
{
    __DeclareClass(DeleteFile);
    __DeclareMsgId;
public:
    DeleteFile() 
    { };
};
//------------------------------------------------------------------------------
class MountArchive : public IOMessage
{
    __DeclareClass(MountArchive);
    __DeclareMsgId;
public:
    MountArchive() 
    { };
};
//------------------------------------------------------------------------------
class ReadStream : public IOMessage
{
    __DeclareClass(ReadStream);
    __DeclareMsgId;
public:
    ReadStream() 
    { };
public:
    void SetStream(const GPtr<IO::Stream>& val)
    {
        n_assert(!this->handled);
        this->stream = val;
    };
    const GPtr<IO::Stream>& GetStream() const
    {
        return this->stream;
    };
private:
    GPtr<IO::Stream> stream;
};
//------------------------------------------------------------------------------
class WriteStream : public IOMessage
{
    __DeclareClass(WriteStream);
    __DeclareMsgId;
public:
    WriteStream() 
    { };
public:
    void SetStream(const GPtr<IO::Stream>& val)
    {
        n_assert(!this->handled);
        this->stream = val;
    };
    const GPtr<IO::Stream>& GetStream() const
    {
        return this->stream;
    };
private:
    GPtr<IO::Stream> stream;
public:
    void SetURI(const IO::URI& val)
    {
        n_assert(!this->handled);
        this->uri = val;
    };
    const IO::URI& GetURI() const
    {
        return this->uri;
    };
private:
    IO::URI uri;
};
//------------------------------------------------------------------------------
class UseFileService : public IOMessage
{
    __DeclareClass(UseFileService);
    __DeclareMsgId;
public:
    UseFileService() :
        usefileservice(false)
    { };
public:
    void SetUseFileService(bool val)
    {
        n_assert(!this->handled);
        this->usefileservice = val;
    };
    bool GetUseFileService() const
    {
        return this->usefileservice;
    };
private:
    bool usefileservice;
public:
    void SetFileServiceDir(const Util::String& val)
    {
        n_assert(!this->handled);
        this->fileservicedir = val;
    };
    const Util::String& GetFileServiceDir() const
    {
        return this->fileservicedir;
    };
private:
    Util::String fileservicedir;
public:
    void SetServerAddress(const Util::String& val)
    {
        n_assert(!this->handled);
        this->serveraddress = val;
    };
    const Util::String& GetServerAddress() const
    {
        return this->serveraddress;
    };
private:
    Util::String serveraddress;
public:
    void SetCacheDir(const Util::String& val)
    {
        n_assert(!this->handled);
        this->cachedir = val;
    };
    const Util::String& GetCacheDir() const
    {
        return this->cachedir;
    };
private:
    Util::String cachedir;
};
} // namespace IO
//------------------------------------------------------------------------------
