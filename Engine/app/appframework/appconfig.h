/****************************************************************************
Copyright (c) 2007,Radon Labs GmbH
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
#ifndef __appconfig_H__
#define __appconfig_H__

// disabled, profilers cost to much performance
#define __Actor_STATS__ (0)
#define __MANAGERS_STATS__ (0)
#define __DEBUG_ACTIVE__ (1)
#define __REMOTE_ACTIVE__ (1)
#define __USE_XACT_AUDIO__ (1)
#define __DISABLE_AUDIO__ (0)
#if __USE_XACT_AUDIO__ && __DISABLE_AUDIO__
#error  Only one define allowed!!!
#endif
#define __XACT_AUDITIONING__ (0) //activate the auditioning server for the XACT remote tool. 
#define __USE_VEGETATION_MANAGER__ (0)

// soft assert messages will be displayed while playing
#define __SOFT_ASSERT_WITH_INGAME_MESSAGES_FOR_DIALOG_SUBSYSTEM__ (1)
#define __SOFT_ASSERT_WITH_INGAME_MESSAGES_FOR_QUEST_SUBSYSTEM__ (1)

// physics stuff
#if  __WII__
#define __USE_PHYSICS__ (0)
#else
#define __USE_PHYSICS__ (1)
#endif

//------------------------------------------------------------------------------
#endif //__appconfig_H__

