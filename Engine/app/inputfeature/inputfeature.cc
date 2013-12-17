/****************************************************************************
Copyright (c) 2007	   ,Radon Labs GmbH
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
#include "inputfeature/inputfeature.h"
#include "input/inputkeyboard.h"
#include "input/inputmouse.h"
#include "input/inputgamepad.h"
#include "input/inputhardwaresource.h"


namespace App
{
	__ImplementClass(App::InputFeature, 'INPF' , App::Feature);
    __ImplementThreadSingleton(App::InputFeature);

	using namespace Input;
	using namespace Math;

//------------------------------------------------------------------------------
/**
*/
InputFeature::InputFeature()
{
    __ConstructThreadSingleton;

	mFeatureName = "Input";
}

//------------------------------------------------------------------------------
/**
*/
InputFeature::~InputFeature()
{
    __DestructThreadSingleton;
}
//------------------------------------------------------------------------
void 
InputFeature::InitSource( const InputSourceList& inputSourceList )
{
	n_assert( !IsActive() );
	n_assert( mInputSourceList.IsEmpty() );
	if ( !IsActive() && mInputSourceList.IsEmpty() )
	{
		mInputSourceList.AppendArray( inputSourceList );
	}
}
//------------------------------------------------------------------------------
/**
*/
void
InputFeature::OnActivate()
{
	Super::OnActivate();
    
	// setup input subsystem
	this->m_inputServer = Input::InputServer::Create();

	SizeT count = mInputSourceList.Size();
	for ( IndexT i = 0; i < count; ++i)
	{
		this->m_inputServer->AttachInputSource( mInputSourceList[i] );
	}

	this->m_inputServer->Open();
}

//------------------------------------------------------------------------------
/**
*/
void
InputFeature::OnDeactivate()
{
	SizeT count = mInputSourceList.Size();
	for ( IndexT i = 0; i < count; ++i)
	{
		this->m_inputServer->RemoveInputSource( mInputSourceList[i] );
	}
	mInputSourceList.Clear();

	this->m_inputServer->Close();
	this->m_inputServer = 0;

    Super::OnDeactivate();
}


void InputFeature::OnBeginFrame()
{
	// first processInput
	m_inputServer->BeginFrame();
	m_inputServer->OnFrame();

	Super::OnBeginFrame();
}

//------------------------------------------------------------------------------
/**
*/
void
InputFeature::OnEndFrame()
{
    Super::OnEndFrame();

	// clear the input of this frame
	m_inputServer->EndFrame();
}

} // namespace Game
