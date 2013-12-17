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

#ifndef __PACKAGESYSTEM__
#define __PACKAGESYSTEM__
#include "core/refcounted.h"
#include "core/ptr.h"
#include "packageTool/PackDef.h"
#include "io/stream.h"
namespace Pack
{
typedef void (*WarningCallBack)(const char* msg);
class PackageSystem
{
public:

	static void SetWarningCallBack(WarningCallBack callBack);

	static bool OpenPackage();

	static void Close();

#if __ANDROID__
	static bool OpenPackageInAPK(const char* apkpath);
#endif

	static bool PackageIsOpened();

	static bool GetFileInPackage(const char* fileName, GPtr<IO::Stream> pMemStream);

	static bool GetFileInPackageThreadSafe(const char* fileName, GPtr<IO::Stream> pMemStream);

	static bool IsFileExit(const char* fileName);
private:
	PackageSystem();
};

}

#endif