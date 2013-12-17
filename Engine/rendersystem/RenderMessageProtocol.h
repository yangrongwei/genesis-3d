#pragma once
//------------------------------------------------------------------------------
/**
    This file was generated with Nebula3's idlc compiler tool.
    DO NOT EDIT
*/
#include "messaging/message.h"
#include "core/rtti.h"
#include "threading/objectref.h"
#include "math/matrix44.h"
#include "math/float4.h"
#include "base/RenderDeviceTypes.h"
#include "base/RenderStateDesc.h"
#include "RenderSystem.h"

//------------------------------------------------------------------------------
namespace RenderBase
{
//------------------------------------------------------------------------------
class StartRenderSystemMSG : public Messaging::Message
{
    __DeclareClass(StartRenderSystemMSG);
    __DeclareMsgId;
public:
    StartRenderSystemMSG() 
    { };
};
//------------------------------------------------------------------------------
class BeginFrameMSG : public Messaging::Message
{
    __DeclareClass(BeginFrameMSG);
    __DeclareMsgId;
public:
    BeginFrameMSG() 
    { };
};
//------------------------------------------------------------------------------
class EndFrameMSG : public Messaging::Message
{
    __DeclareClass(EndFrameMSG);
    __DeclareMsgId;
public:
    EndFrameMSG() 
    { };
};
//------------------------------------------------------------------------------
class SetViewPortMSG : public Messaging::Message
{
    __DeclareClass(SetViewPortMSG);
    __DeclareMsgId;
public:
    SetViewPortMSG() 
    { };
public:
    void SetX(SizeT val)
    {
        n_assert(!this->handled);
        this->x = val;
    };
    SizeT GetX() const
    {
        return this->x;
    };
private:
    SizeT x;
public:
    void SetY(SizeT val)
    {
        n_assert(!this->handled);
        this->y = val;
    };
    SizeT GetY() const
    {
        return this->y;
    };
private:
    SizeT y;
public:
    void SetWidth(SizeT val)
    {
        n_assert(!this->handled);
        this->width = val;
    };
    SizeT GetWidth() const
    {
        return this->width;
    };
private:
    SizeT width;
public:
    void SetHeight(SizeT val)
    {
        n_assert(!this->handled);
        this->height = val;
    };
    SizeT GetHeight() const
    {
        return this->height;
    };
private:
    SizeT height;
public:
    void SetMinZ(float val)
    {
        n_assert(!this->handled);
        this->minz = val;
    };
    float GetMinZ() const
    {
        return this->minz;
    };
private:
    float minz;
public:
    void SetMaxZ(float val)
    {
        n_assert(!this->handled);
        this->maxz = val;
    };
    float GetMaxZ() const
    {
        return this->maxz;
    };
private:
    float maxz;
};
//------------------------------------------------------------------------------
class CreateTextureMSG : public Messaging::Message
{
    __DeclareClass(CreateTextureMSG);
    __DeclareMsgId;
public:
    CreateTextureMSG() 
    { };
public:
    void SetTexture(GPtr<Texture> val)
    {
        n_assert(!this->handled);
        this->texture = val;
    };
    GPtr<Texture> GetTexture() const
    {
        return this->texture;
    };
private:
    GPtr<Texture> texture;
public:
    void SetHandle(TextureHandle val)
    {
        n_assert(!this->handled);
        this->handle = val;
    };
    TextureHandle GetHandle() const
    {
        n_assert(this->handled);
        return this->handle;
    };
private:
    TextureHandle handle;
};
//------------------------------------------------------------------------------
class CreateShaderProgramMSG : public Messaging::Message
{
    __DeclareClass(CreateShaderProgramMSG);
    __DeclareMsgId;
public:
    CreateShaderProgramMSG() 
    { };
public:
    void SetProgram(GPtr<GPUProgram> val)
    {
        n_assert(!this->handled);
        this->program = val;
    };
    GPtr<GPUProgram> GetProgram() const
    {
        return this->program;
    };
private:
    GPtr<GPUProgram> program;
public:
    void SetHandle(GPUProgramHandle val)
    {
        n_assert(!this->handled);
        this->handle = val;
    };
    GPUProgramHandle GetHandle() const
    {
        n_assert(this->handled);
        return this->handle;
    };
private:
    GPUProgramHandle handle;
};
//------------------------------------------------------------------------------
class CreatePrimitiveGroupMSG : public Messaging::Message
{
    __DeclareClass(CreatePrimitiveGroupMSG);
    __DeclareMsgId;
public:
    CreatePrimitiveGroupMSG() 
    { };
public:
    void SetPrimitiveGroup(GPtr<PrimitiveGroup> val)
    {
        n_assert(!this->handled);
        this->primitivegroup = val;
    };
    GPtr<PrimitiveGroup> GetPrimitiveGroup() const
    {
        return this->primitivegroup;
    };
private:
    GPtr<PrimitiveGroup> primitivegroup;
public:
    void SetHandle(PrimitiveHandle val)
    {
        n_assert(!this->handled);
        this->handle = val;
    };
    PrimitiveHandle GetHandle() const
    {
        n_assert(this->handled);
        return this->handle;
    };
private:
    PrimitiveHandle handle;
};
//------------------------------------------------------------------------------
class CreateRenderTargetMSG : public Messaging::Message
{
    __DeclareClass(CreateRenderTargetMSG);
    __DeclareMsgId;
public:
    CreateRenderTargetMSG() 
    { };
public:
    void SetRenderTarget(GPtr<RenderTarget> val)
    {
        n_assert(!this->handled);
        this->rendertarget = val;
    };
    GPtr<RenderTarget> GetRenderTarget() const
    {
        return this->rendertarget;
    };
private:
    GPtr<RenderTarget> rendertarget;
public:
    void SetHandle(RenderTargetHandle val)
    {
        n_assert(!this->handled);
        this->handle = val;
    };
    RenderTargetHandle GetHandle() const
    {
        n_assert(this->handled);
        return this->handle;
    };
private:
    RenderTargetHandle handle;
public:
    void SetTextureHandle(TextureHandle val)
    {
        n_assert(!this->handled);
        this->texturehandle = val;
    };
    TextureHandle GetTextureHandle() const
    {
        n_assert(this->handled);
        return this->texturehandle;
    };
private:
    TextureHandle texturehandle;
};
//------------------------------------------------------------------------------
class UpdatePrimitiveGroupMSG : public Messaging::Message
{
    __DeclareClass(UpdatePrimitiveGroupMSG);
    __DeclareMsgId;
public:
    UpdatePrimitiveGroupMSG() 
    { };
public:
    void SetPrimitiveGroup(GPtr<PrimitiveGroup> val)
    {
        n_assert(!this->handled);
        this->primitivegroup = val;
    };
    GPtr<PrimitiveGroup> GetPrimitiveGroup() const
    {
        return this->primitivegroup;
    };
private:
    GPtr<PrimitiveGroup> primitivegroup;
public:
    void SetHandle(PrimitiveHandle val)
    {
        n_assert(!this->handled);
        this->handle = val;
    };
    PrimitiveHandle GetHandle() const
    {
        return this->handle;
    };
private:
    PrimitiveHandle handle;
};
//------------------------------------------------------------------------------
class SetTextureMSG : public Messaging::Message
{
    __DeclareClass(SetTextureMSG);
    __DeclareMsgId;
public:
    SetTextureMSG() 
    { };
public:
    void SetHandle(TextureHandle val)
    {
        n_assert(!this->handled);
        this->handle = val;
    };
    TextureHandle GetHandle() const
    {
        return this->handle;
    };
private:
    TextureHandle handle;
public:
    void SetTexUnit(SizeT val)
    {
        n_assert(!this->handled);
        this->texunit = val;
    };
    SizeT GetTexUnit() const
    {
        return this->texunit;
    };
private:
    SizeT texunit;
};
//------------------------------------------------------------------------------
class SetRenderStateMSG : public Messaging::Message
{
    __DeclareClass(SetRenderStateMSG);
    __DeclareMsgId;
public:
    SetRenderStateMSG() 
    { };
public:
    void SetObject(GPtr<RenderStateDesc> val)
    {
        n_assert(!this->handled);
        this->object = val;
    };
    GPtr<RenderStateDesc> GetObject() const
    {
        return this->object;
    };
private:
    GPtr<RenderStateDesc> object;
};
//------------------------------------------------------------------------------
class SetGPUProgramMSG : public Messaging::Message
{
    __DeclareClass(SetGPUProgramMSG);
    __DeclareMsgId;
public:
    SetGPUProgramMSG() 
    { };
public:
    void SetHandle(GPUProgramHandle val)
    {
        n_assert(!this->handled);
        this->handle = val;
    };
    GPUProgramHandle GetHandle() const
    {
        return this->handle;
    };
private:
    GPUProgramHandle handle;
};
//------------------------------------------------------------------------------
class SetVertexShaderConstantVectorFMSG : public Messaging::Message
{
    __DeclareClass(SetVertexShaderConstantVectorFMSG);
    __DeclareMsgId;
public:
    SetVertexShaderConstantVectorFMSG() 
    { };
public:
    void SetReg(SizeT val)
    {
        n_assert(!this->handled);
        this->reg = val;
    };
    SizeT GetReg() const
    {
        return this->reg;
    };
private:
    SizeT reg;
public:
    void SetValueRef(float* val)
    {
        n_assert(!this->handled);
        this->valueref = val;
    };
    float* GetValueRef() const
    {
        return this->valueref;
    };
private:
    float* valueref;
public:
    void SetVec4count(SizeT val)
    {
        n_assert(!this->handled);
        this->vec4count = val;
    };
    SizeT GetVec4count() const
    {
        return this->vec4count;
    };
private:
    SizeT vec4count;
};
//------------------------------------------------------------------------------
class SetPixelShaderConstantVectorFMSG : public Messaging::Message
{
    __DeclareClass(SetPixelShaderConstantVectorFMSG);
    __DeclareMsgId;
public:
    SetPixelShaderConstantVectorFMSG() 
    { };
public:
    void SetReg(SizeT val)
    {
        n_assert(!this->handled);
        this->reg = val;
    };
    SizeT GetReg() const
    {
        return this->reg;
    };
private:
    SizeT reg;
public:
    void SetValueRef(float* val)
    {
        n_assert(!this->handled);
        this->valueref = val;
    };
    float* GetValueRef() const
    {
        return this->valueref;
    };
private:
    float* valueref;
public:
    void SetVec4count(SizeT val)
    {
        n_assert(!this->handled);
        this->vec4count = val;
    };
    SizeT GetVec4count() const
    {
        return this->vec4count;
    };
private:
    SizeT vec4count;
};
//------------------------------------------------------------------------------
class SetVertexShaderConstantFloatMSG : public Messaging::Message
{
    __DeclareClass(SetVertexShaderConstantFloatMSG);
    __DeclareMsgId;
public:
    SetVertexShaderConstantFloatMSG() 
    { };
public:
    void SetReg(SizeT val)
    {
        n_assert(!this->handled);
        this->reg = val;
    };
    SizeT GetReg() const
    {
        return this->reg;
    };
private:
    SizeT reg;
public:
    void SetValueRef(float* val)
    {
        n_assert(!this->handled);
        this->valueref = val;
    };
    float* GetValueRef() const
    {
        return this->valueref;
    };
private:
    float* valueref;
};
//------------------------------------------------------------------------------
class SetPixelShaderConstantFloatMSG : public Messaging::Message
{
    __DeclareClass(SetPixelShaderConstantFloatMSG);
    __DeclareMsgId;
public:
    SetPixelShaderConstantFloatMSG() 
    { };
public:
    void SetReg(SizeT val)
    {
        n_assert(!this->handled);
        this->reg = val;
    };
    SizeT GetReg() const
    {
        return this->reg;
    };
private:
    SizeT reg;
public:
    void SetValueRef(float* val)
    {
        n_assert(!this->handled);
        this->valueref = val;
    };
    float* GetValueRef() const
    {
        return this->valueref;
    };
private:
    float* valueref;
};
//------------------------------------------------------------------------------
class SetVertexShaderConstantMatrixFMSG : public Messaging::Message
{
    __DeclareClass(SetVertexShaderConstantMatrixFMSG);
    __DeclareMsgId;
public:
    SetVertexShaderConstantMatrixFMSG() 
    { };
public:
    void SetReg(SizeT val)
    {
        n_assert(!this->handled);
        this->reg = val;
    };
    SizeT GetReg() const
    {
        return this->reg;
    };
private:
    SizeT reg;
public:
    void SetValueRef(float* val)
    {
        n_assert(!this->handled);
        this->valueref = val;
    };
    float* GetValueRef() const
    {
        return this->valueref;
    };
private:
    float* valueref;
public:
    void SetmatrixCount(SizeT val)
    {
        n_assert(!this->handled);
        this->matrixcount = val;
    };
    SizeT GetmatrixCount() const
    {
        return this->matrixcount;
    };
private:
    SizeT matrixcount;
};
//------------------------------------------------------------------------------
class SetPixelShaderConstantMatrixFMSG : public Messaging::Message
{
    __DeclareClass(SetPixelShaderConstantMatrixFMSG);
    __DeclareMsgId;
public:
    SetPixelShaderConstantMatrixFMSG() 
    { };
public:
    void SetReg(SizeT val)
    {
        n_assert(!this->handled);
        this->reg = val;
    };
    SizeT GetReg() const
    {
        return this->reg;
    };
private:
    SizeT reg;
public:
    void SetValueRef(float* val)
    {
        n_assert(!this->handled);
        this->valueref = val;
    };
    float* GetValueRef() const
    {
        return this->valueref;
    };
private:
    float* valueref;
public:
    void SetmatrixCount(SizeT val)
    {
        n_assert(!this->handled);
        this->matrixcount = val;
    };
    SizeT GetmatrixCount() const
    {
        return this->matrixcount;
    };
private:
    SizeT matrixcount;
};
//------------------------------------------------------------------------------
class SetRenderTargetMSG : public Messaging::Message
{
    __DeclareClass(SetRenderTargetMSG);
    __DeclareMsgId;
public:
    SetRenderTargetMSG() 
    { };
public:
    void SetHandle(RenderTargetHandle val)
    {
        n_assert(!this->handled);
        this->handle = val;
    };
    RenderTargetHandle GetHandle() const
    {
        return this->handle;
    };
private:
    RenderTargetHandle handle;
public:
    void SetIndex(SizeT val)
    {
        n_assert(!this->handled);
        this->index = val;
    };
    SizeT GetIndex() const
    {
        return this->index;
    };
private:
    SizeT index;
public:
    void SetClearFlag(uint val)
    {
        n_assert(!this->handled);
        this->clearflag = val;
    };
    uint GetClearFlag() const
    {
        return this->clearflag;
    };
private:
    uint clearflag;
};
//------------------------------------------------------------------------------
class DrawMSG : public Messaging::Message
{
    __DeclareClass(DrawMSG);
    __DeclareMsgId;
public:
    DrawMSG() 
    { };
public:
    void SetHandle(PrimitiveHandle val)
    {
        n_assert(!this->handled);
        this->handle = val;
    };
    PrimitiveHandle GetHandle() const
    {
        return this->handle;
    };
private:
    PrimitiveHandle handle;
public:
    void SetStartVertice(SizeT val)
    {
        n_assert(!this->handled);
        this->startvertice = val;
    };
    SizeT GetStartVertice() const
    {
        return this->startvertice;
    };
private:
    SizeT startvertice;
public:
    void SetEndVertice(SizeT val)
    {
        n_assert(!this->handled);
        this->endvertice = val;
    };
    SizeT GetEndVertice() const
    {
        return this->endvertice;
    };
private:
    SizeT endvertice;
public:
    void SetStartIndice(SizeT val)
    {
        n_assert(!this->handled);
        this->startindice = val;
    };
    SizeT GetStartIndice() const
    {
        return this->startindice;
    };
private:
    SizeT startindice;
public:
    void SetEndIndice(SizeT val)
    {
        n_assert(!this->handled);
        this->endindice = val;
    };
    SizeT GetEndIndice() const
    {
        return this->endindice;
    };
private:
    SizeT endindice;
};
//------------------------------------------------------------------------------
class RemoveRenderResourceMSG : public Messaging::Message
{
    __DeclareClass(RemoveRenderResourceMSG);
    __DeclareMsgId;
public:
    RemoveRenderResourceMSG() 
    { };
public:
    void SetHandle(RenderResourceHandle val)
    {
        n_assert(!this->handled);
        this->handle = val;
    };
    RenderResourceHandle GetHandle() const
    {
        return this->handle;
    };
private:
    RenderResourceHandle handle;
};
//------------------------------------------------------------------------------
class FXSetClipPlaneMSG : public Messaging::Message
{
    __DeclareClass(FXSetClipPlaneMSG);
    __DeclareMsgId;
public:
    FXSetClipPlaneMSG() 
    { };
public:
    void SetIndex(SizeT val)
    {
        n_assert(!this->handled);
        this->index = val;
    };
    SizeT GetIndex() const
    {
        return this->index;
    };
private:
    SizeT index;
public:
    void SetPlane(const Math::float4& val)
    {
        n_assert(!this->handled);
        this->plane = val;
    };
    const Math::float4& GetPlane() const
    {
        return this->plane;
    };
private:
    Math::float4 plane;
};
} // namespace RenderBase
//------------------------------------------------------------------------------
