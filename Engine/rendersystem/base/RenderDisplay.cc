/****************************************************************************
Copyright (C) 2007 Radon Labs GmbH

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
#include "RenderDisplay.h"

namespace RenderBase
{
__ImplementClass(RenderDisplay, 'DSDB', Core::RefCounted);
//__ImplementThreadSingleton(RenderDisplay);



//------------------------------------------------------------------------------
/**
*/
RenderDisplay::RenderDisplay() :
    adapter(Adapter::Primary),
    antiAliasQuality(AntiAliasQuality::None),
    fullscreen(false),
	m_bWebVersion(false),
    modeSwitchEnabled(true),
    tripleBufferingEnabled(false),
    alwaysOnTop(false),
    verticalSync(true),
    isOpen(false),
    windowTitle("Genesis Application Window"),
    iconName("GenesisIcon"),
    parentWindow(0),
	m_hWebWindow(0),
    inNotifyEventHandlers(false)
{
    //__ConstructThreadSingleton;
}

//------------------------------------------------------------------------------
/**
*/
RenderDisplay::~RenderDisplay()
{
    n_assert(!this->IsOpen());
    //__DestructThreadSingleton;
}

//------------------------------------------------------------------------------
/**
    Set the window title. An application should be able to change the
    window title at any time, that's why this is a virtual method, so that
    a subclass may override it.
*/
void
RenderDisplay::SetWindowTitle(const Util::String& str)
{
    this->windowTitle = str;
}

//------------------------------------------------------------------------------
/**
    Open the display.
*/
bool
RenderDisplay::Open()
{
    n_assert(!this->IsOpen());

    this->isOpen = true;
    return true;
}

//------------------------------------------------------------------------------
/**
    Close the display.
*/
void
RenderDisplay::Close()
{
    n_assert(this->IsOpen());

    this->isOpen = false;
}

//------------------------------------------------------------------------------
/**
    Process window system messages. Override this method in a subclass.
*/
void
RenderDisplay::ProcessWindowMessages()
{
	
}

//------------------------------------------------------------------------------
/**
    Returns the display modes on the given adapter in the given pixel format.
*/
Util::Array<DisplayMode>
RenderDisplay::GetAvailableDisplayModes(Adapter::Code adapter, PixelFormat::Code pixelFormat)
{
    // override this method in a subclass to do something useful
    Util::Array<DisplayMode> emptyArray;
    return emptyArray;
}

//------------------------------------------------------------------------------
/**
    This method checks the available display modes on the given adapter
    against the requested display modes and returns true if the display mode
    exists.
*/
bool
RenderDisplay::SupportsDisplayMode(Adapter::Code adapter, const DisplayMode& requestedMode)
{
    return false;
}

//------------------------------------------------------------------------------
/**
    This method returns the current adapter display mode. It can be used
    to get the current desktop display mode.
*/
DisplayMode
RenderDisplay::GetCurrentAdapterDisplayMode(Adapter::Code adapter)
{
    DisplayMode emptyMode;
    return emptyMode;
}

//------------------------------------------------------------------------------
/**
    Checks if the given adapter exists.
*/
bool
RenderDisplay::AdapterExists(Adapter::Code adapter)
{
    return false;
}

//------------------------------------------------------------------------------
/**
    Returns information about the provided adapter.
*/
AdapterInfo
RenderDisplay::GetAdapterInfo(Adapter::Code adapter)
{
    AdapterInfo emptyAdapterInfo;
    return emptyAdapterInfo;
}

//------------------------------------------------------------------------------
	/**
	*/
	Adapter::Code
		Adapter::FromString(const Util::String& str)
	{
		if ("None" == str) return None;
		else if ("Primary" == str) return Primary;
		else if ("Secondary" == str) return Secondary;
		else
		{
			n_error("Invalid adapter string '%s'!", str.AsCharPtr());
			return Primary;
		}
	}

	//------------------------------------------------------------------------------
	/**
	*/
	Util::String
		Adapter::ToString(Code code)
	{
		switch (code)
		{
		case None:      return "None";
		case Primary:   return "Primary";
		case Secondary: return "Secondary";
		default:
			n_error("Invalid adapter code!");
			return "";
		}
	}
} // namespace RenderBase
