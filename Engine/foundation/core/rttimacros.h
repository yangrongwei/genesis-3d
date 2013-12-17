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
#pragma once
/**
    Declaration macro. Put this into the class declaration.
*/
#define __DeclareClass(type) \
public: \
    void* operator new(size_t size) \
    { \
        return RTTI.AllocInstanceMemory(); \
    }; \
    void operator delete(void* p) \
    { \
        RTTI.FreeInstanceMemory(p); \
    }; \
    static Core::Rtti RTTI; \
    static Core::RefCounted* FactoryCreator(); \
    static type* Create(); \
    static bool RegisterWithFactory(); \
    virtual Core::Rtti* GetRtti() const; \
private:

/**
    Declaration macro. If your class is a subclass and wanted to use Super macro,
	put this into the class declaration instead of __DeclareClass.
*/
#define __DeclareSubClass(type, baseType) \
public: \
	typedef baseType Super; \
	__DeclareClass(type)

#define __DeclareAbstractClass(class_name) \
public: \
    static Core::Rtti RTTI; \
    virtual Core::Rtti* GetRtti() const; \
private:

//------------------------------------------------------------------------------
/**
    Register a class with the factory. This is only necessary for classes
    which can create objects by name or fourcc.must be in head file( **.h )
	this force Linker to link, No optimize

	不在使用这个宏了。需要注册的类，请在运行期动态注册
*/
//#define __RegisterDynamicClass(type) \
//    static const bool type##_registered = type::RegisterWithFactory(); \

//------------------------------------------------------------------------------
/**
    Implementation macro for default memory pool sizes. Put this into the source file.
*/
#if NEBULA3_DEBUG
#define __ImplementClass(type, fourcc, baseType) \
    Core::Rtti type::RTTI(#type, fourcc, type::FactoryCreator, &baseType::RTTI, sizeof(type)); \
    Core::Rtti* type::GetRtti() const { return &this->RTTI; } \
    Core::RefCounted* type::FactoryCreator() { return type::Create(); } \
    type* type::Create() \
    { \
        RefCounted::criticalSection.Enter(); \
        ++RefCounted::isInCreate; \
        type* newObject = n_new(type); \
        --RefCounted::isInCreate; \
        RefCounted::criticalSection.Leave(); \
        return newObject; \
    }\
    bool type::RegisterWithFactory() \
    { \
        Core::SysFunc::Setup(); \
        if (!Core::Factory::Instance()->ClassExists(#type)) \
        { \
            Core::Factory::Instance()->Register(&type::RTTI, #type, fourcc); \
        } \
        return true; \
    }
#else
#define __ImplementClass(type, fourcc, baseType) \
    Core::Rtti type::RTTI(#type, fourcc, type::FactoryCreator, &baseType::RTTI, sizeof(type)); \
    Core::Rtti* type::GetRtti() const { return &this->RTTI; } \
    Core::RefCounted* type::FactoryCreator() { return type::Create(); } \
    type* type::Create() \
    { \
        return n_new(type); \
    }\
    bool type::RegisterWithFactory() \
    { \
        Core::SysFunc::Setup(); \
        if (!Core::Factory::Instance()->ClassExists(#type)) \
        { \
            Core::Factory::Instance()->Register(&type::RTTI, #type, fourcc); \
        } \
        return true; \
    }
#endif

#define __ImplementAbstractClass(type, fourcc, baseType) \
    Core::Rtti type::RTTI(#type, fourcc, 0, &baseType::RTTI, 0); \
    Core::Rtti* type::GetRtti() const { return &this->RTTI; }

//------------------------------------------------------------------------------
/**
    Type implementation of topmost type in inheritance hierarchy (source file).
*/
#if NEBULA3_DEBUG
#define __ImplementRootClass(type, fourcc) \
    Core::Rtti type::RTTI(#type, fourcc, type::FactoryCreator, 0, sizeof(type)); \
    Core::Rtti* type::GetRtti() const { return &this->RTTI; } \
    Core::RefCounted* type::FactoryCreator() { return type::Create(); } \
    type* type::Create() \
    { \
        RefCounted::criticalSection.Enter(); \
        ++RefCounted::isInCreate; \
        type* newObject = n_new(type); \
        --RefCounted::isInCreate; \
        RefCounted::criticalSection.Leave(); \
        return newObject; \
    }\
    bool type::RegisterWithFactory() \
    { \
        if (!Core::Factory::Instance()->ClassExists(#type)) \
        { \
            Core::Factory::Instance()->Register(&type::RTTI, #type, fourcc); \
        } \
        return true; \
    }
#else
#define __ImplementRootClass(type, fourcc) \
    Core::Rtti type::RTTI(#type, fourcc, type::FactoryCreator, 0, sizeof(type)); \
    Core::Rtti* type::GetRtti() const { return &this->RTTI; } \
    Core::RefCounted* type::FactoryCreator() { return type::Create(); } \
    type* type::Create() \
    { \
        return n_new(type); \
    }\
    bool type::RegisterWithFactory() \
    { \
        if (!Core::Factory::Instance()->ClassExists(#type)) \
        { \
            Core::Factory::Instance()->Register(&type::RTTI, #type, fourcc); \
        } \
        return true; \
    }
#endif
//------------------------------------------------------------------------------
    