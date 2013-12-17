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
#ifndef __ResourceFeature_H__
#define __ResourceFeature_H__
#include "appframework/feature.h"

namespace App
{
	 /*! \class ResourceFeature ResourceFeature.h
	 *  \brief  This is a class.
	 *
	 * 该Feature用于资源的管理，包括资源调度，资源使用等
	 */
	class ResourceFeature : public App::Feature    
	{
		__DeclareClass(ResourceFeature);
		__DeclareImageSingleton(ResourceFeature);    
	public:

		/// constructor
		ResourceFeature();
		/// destructor
		virtual ~ResourceFeature();

		/// called from BaseGameFeature::ActivateProperties()
		virtual void OnActivate();
		/// called from BaseGameFeature::DeactivateProperties()
		virtual void OnDeactivate();

		/// called on begin of frame
		virtual void OnBeginFrame();    
		/// called at the end of the feature trigger cycle
		virtual void OnEndFrame();
		/// 
		virtual void OnFrame();
	};
}






#endif // __ResourceFeature_H__
