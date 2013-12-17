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
#include "RenderQueue.h"

namespace Graphic
{
	RenderQueue::RenderQueue()
	{
		queue_index = 0;
	}

	RenderQueue::~RenderQueue()
	{
	}

	RenderQueue::RenderQueue(QueueType type)
	{
		SetQueue(type);
	}

	RenderQueue::RenderQueue(QueueType type, int16 sort)
	{
		SetQueue(type, sort);
	}

	RenderQueue RenderQueue::FromString(Util::String str)
	{
		str.ToUpper();
		if (str == "BACKGROUND") 
			return RenderQueue(eRQTBackGround);
		else if (str == "OPAQUE") 
			return RenderQueue(eRQTOpaque);
		else if (str == "ALPHATEST") 
			return RenderQueue(eRQTAlphaTest);
		else if (str == "ALPHABLEND") 
			return RenderQueue(eRQTAlphaBlend);
		else if (str == "GLASS") 
			return RenderQueue(eRQTGlass);
		else if (str == "PARTICLEDECAL") 
			return RenderQueue(eRQParticleDecal);
		else if (str == "PARTICLEPOST") 
			return RenderQueue(eRQParticlePost);
		else if (str == "CUSTOMDRAW") 
			return RenderQueue(eRQTCustomDraw);
		else if (str == "DEBUGPRIMITIVE") 
			return RenderQueue(eRQTDebugPrimitive);
		else
		{
			return RenderQueue(eRQTNone);
		}

	}

	Util::String RenderQueue::ToString(RenderQueue mode)
	{
		switch (mode.GetQueueType())
		{
		case eRQTBackGround:     return "BACKGROUND";
		case eRQTOpaque:    return "OPAQUE";
		case eRQTAlphaTest:     return "ALPHATEST";
		case eRQTAlphaBlend: return "ALPHABLEND";
		case eRQTDebugPrimitive: return "DEBUGPRIMITIVE";
		case eRQParticleDecal: return "PARTICLEDECAL";
		case eRQParticlePost: return "PARTICLEPOST";
		case eRQTCustomDraw: return "CUSTOMDRAW";

		default:
			n_error("RenderQueue::ToString(): invalid render queue !");
			return "";
		}
	}
}