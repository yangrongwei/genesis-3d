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
#ifndef __inputfeature_H__
#define __inputfeature_H__

#include "appframework/feature.h"
#include "input/inputsource.h"
#include "input/inputserver.h"



//------------------------------------------------------------------------------
namespace App
{
	typedef Util::Array< GPtr<Input::InputSource> > InputSourceList;

	class InputFeature : public App::Feature    
	{
		__DeclareSubClass(InputFeature,Feature);
		__DeclareThreadSingleton(InputFeature);    

	public:

		/// constructor
		InputFeature();
		/// destructor
		virtual ~InputFeature();

		// add the input source. make out all kinds of input state from input source
		void InitSource( const InputSourceList& inputSourceList );

		// catch the input service. we can get the keyboard,mouse and rock's state info
		const GPtr<Input::InputServer>& GetInputServer(void) const;

		/// @Feature::OnActivate called from InputFeature::ActivateProperties()
		virtual void OnActivate();
		/// @Feature::OnDeactivate called from InputFeature::DeactivateProperties()
		virtual void OnDeactivate();
		/// @Feature::OnBeginFrame called at the start of the feature trigger cycle
		virtual void OnBeginFrame();
		/// @Feature::OnEndFrame called at the end of the feature trigger cycle
		virtual void OnEndFrame();

	protected:
		// input Server
		GPtr<Input::InputServer> m_inputServer;
		InputSourceList mInputSourceList;
	};

	//------------------------------------------------------------------------
	inline
	const GPtr<Input::InputServer>& 
	InputFeature::GetInputServer(void) const
	{
		return m_inputServer;
	}
} // namespace InputFeature
//------------------------------------------------------------------------------










#endif // __InputFeature_H__



