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

namespace App
{ 
    static MonoObject* ICall_Component_GetOwner( MonoObject* self);

    static void ICall_Component_Release( MonoObject* self);

    static mono_bool ICall_Component_Active( MonoObject* self);

//********************************* Register func to mono ********************************************
	void ICallReg_ScriptRuntime_Component( void )
    {
        static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
             { "ScriptRuntime.Component::ICall_Component_GetOwner",                                 (void*)&ICall_Component_GetOwner},
             { "ScriptRuntime.Component::ICall_Component_Release",                                  (void*)&ICall_Component_Release},
             { "ScriptRuntime.Component::ICall_Component_Active",                                   (void*)&ICall_Component_Active},
        };
        int size = sizeof(s_cScriptBindInternalCallDetail) / sizeof(InternalCallDetail);
        for (int ii = 0; ii < size; ++ii)
        {
                mono_add_internal_call(s_cScriptBindInternalCallDetail[ii].__pScriptFunName,
                        s_cScriptBindInternalCallDetail[ii].__pCppFunPtr);
        }
    }
} 
