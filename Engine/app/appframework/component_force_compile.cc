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
#ifndef __component_force_compiler__
#define __component_force_compiler__


#include "stdneb.h"

//#include "app/scriptfeature/inc/script_utility.h"
//#include "app/scriptfeature/inc/script_instance.h"
//#include "app/scriptfeature/inc/script_fwd_decl.h"
#include "appframework/actor.h"

#define __no_compile__
#ifdef __no_compile__

#include "component.h"

namespace App
{
	//------------------------------------------------------------------------
	template<typename T>
	void Component::SendMessageToScript(const Util::String& name,T& pair)
	{
		if (mActor != NULL)
		{
			mActor->ThrowMessageToScript<T>(name, pair);
		}
	}
	 void Component::Component_force_compiler()
	{
		return; // forbid to call me

		//GPtr<PhysicsShapeComponent> pTemp;
		//SendMessageToScript<PhysicsShapeComponent>("", pTemp,pTemp);
	}

	
	
}

#endif
#endif
