@echo #****************************************************************************
@echo  Copyright (c) 2011-2013,WebJet Business Division,CYOU
@echo   
@echo  http://www.genesis-3d.com.cn
@echo  
@echo  Permission is hereby granted, free of charge, to any person obtaining a copy
@echo  of this software and associated documentation files (the "Software"), to deal
@echo  in the Software without restriction, including without limitation the rights
@echo  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
@echo  copies of the Software, and to permit persons to whom the Software is
@echo  furnished to do so, subject to the following conditions:

@echo  The above copyright notice and this permission notice shall be included in
@echo  all copies or substantial portions of the Software.
@echo  
@echo  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
@echo  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
@echo  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
@echo  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
@echo  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
@echo  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
@echo  THE SOFTWARE.
@echo ****************************************************************************



if "%1%"=="becalled" (
@rem
)else (
cd My_Android_Build

)
set curPath=%cd%
%curPath%/../extlibs\NDK\android-ndk-r8b-windows\prebuilt\windows\bin\make.exe -j4

pause

