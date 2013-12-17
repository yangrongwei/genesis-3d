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
#include "stdneb.h"

#include "../spritebacth/DrawTextManager.h"
#include "appframework/profiletool.h"
#include "FontFeature.h"


namespace App
{
	__ImplementClass(App::FontFeature, 'FFAP' , App::Feature);
	__ImplementImageSingleton(App::FontFeature);

FontFeature::FontFeature()
{
	__ConstructImageSingleton;

	mFeatureName = "Font";
}

FontFeature::~FontFeature()
{
	__DestructImageSingleton;
}

void FontFeature::OnActivate()
{
	Feature::OnActivate();
	
	// applicate
	mDrawTextManager = DrawTextManager::Create();
	mDrawTextManager->SetFontName(mFontPath);
	mDrawTextManager->SetShaderName(mShaderPath);
	this->AttachManager(mDrawTextManager.upcast<App::Manager>());

	GPtr<ProfileManager> pm = ProfileManager::Create();
	this->AttachManager(pm.upcast<App::Manager>());
}

void FontFeature::OnDeactivate()
{
	this->RemoveManager(mDrawTextManager.upcast<App::Manager>());
	mDrawTextManager = NULL;
}


void FontFeature::OnBeginFrame()
{
	
}

void FontFeature::OnFrame()
{
	Feature::OnFrame();

}
void FontFeature::OnEndFrame()
{
	
}












}
