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
#ifndef RENDERDISPLAY_H_
#define RENDERDISPLAY_H_
#include "../config/RenderDeviceConfig.h"
#include "core/refcounted.h"
//#include "core/singleton.h"
#include "RenderDeviceTypes.h"
//#include "RenderDisplayEvent.h"
//#include "util/guid.h"

namespace RenderBase
{
	class Adapter
	{
	public:
		/// enum
		enum Code
		{
			Primary = 0,
			Secondary,    
			None,
		};

		/// convert adapter code from string
		static Code FromString(const Util::String& str);
		/// convert adapter code to string
		static Util::String ToString(Code code);
	};

class DisplayMode
{
public:
    /// default constructor
    DisplayMode();
    /// windowed mode constructor
    DisplayMode(uint x, uint y, uint w, uint h);
    /// fullscreen constructor
    DisplayMode(uint w, uint h, PixelFormat::Code p);
    /// generic constructor
    DisplayMode(uint x, uint y, uint w, uint h, PixelFormat::Code p);
    /// equality operator
    bool operator==(const DisplayMode& rhs) const;
    /// inequality operator
    bool operator!=(const DisplayMode& rhs) const;
    /// set x position
    void SetXPos(uint x);
    /// get x position
    uint GetXPos() const;
    /// set y position
    void SetYPos(uint y);
    /// get y position
    uint GetYPos() const;
    /// set width
    void SetWidth(uint w);
    /// get width
    uint GetWidth() const;
    /// set height
    void SetHeight(uint h);
    /// get height
    uint GetHeight() const;
    /// set pixel format
    void SetPixelFormat(PixelFormat::Code p);
    /// get pixel format
    PixelFormat::Code GetPixelFormat() const;
    /// set aspect ratio
    void SetAspectRatio(float a);
    /// get aspect ratio
    float GetAspectRatio() const;

private:
    uint xPos;
    uint yPos;
    uint width;
    uint height;
    float aspectRatio;
    PixelFormat::Code pixelFormat;
};

//------------------------------------------------------------------------------
/**
*/
inline
DisplayMode::DisplayMode() :
    xPos(0),
    yPos(0),
    width(1024),
    height(768),
    aspectRatio(4.0f / 3.0f),
    pixelFormat(PixelFormat::X8R8G8B8)
{
    // empty
}

//------------------------------------------------------------------------------
/**
    This constructor is suitable for windowed modes.
*/
inline
DisplayMode::DisplayMode(uint x, uint y, uint w, uint h) :
    xPos(x),
    yPos(y),
    width(w),
    height(h),
    aspectRatio(float(w) / float(h)),
    pixelFormat(PixelFormat::InvalidPixelFormat)
{
    // empty
}

//------------------------------------------------------------------------------
/**
    This constructor is suitable for fullscreen modes.
*/
inline
DisplayMode::DisplayMode(uint w, uint h, PixelFormat::Code p) :
    xPos(0),
    yPos(0),
    width(w),
    height(h),
    aspectRatio(float(w) / float(h)),
    pixelFormat(p)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline
DisplayMode::DisplayMode(uint x, uint y, uint w, uint h, PixelFormat::Code p) :
    xPos(x),
    yPos(y),
    width(w),
    height(h),
    aspectRatio(float(w) / float(h)),
    pixelFormat(p)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline bool
DisplayMode::operator==(const DisplayMode& rhs) const
{
    return ((this->xPos == rhs.xPos) &&
            (this->yPos == rhs.yPos) &&
            (this->width == rhs.width) &&
            (this->height == rhs.height) &&
            (this->aspectRatio == rhs.aspectRatio) &&            
            (this->pixelFormat == rhs.pixelFormat));
}

//------------------------------------------------------------------------------
/**
*/
inline bool
DisplayMode::operator!=(const DisplayMode& rhs) const
{
    return !(*this == rhs); 
}

//------------------------------------------------------------------------------
/**
*/
inline void
DisplayMode::SetXPos(uint x)
{
    this->xPos = x;
}

//------------------------------------------------------------------------------
/**
*/
inline uint
DisplayMode::GetXPos() const
{
    return this->xPos;
}

//------------------------------------------------------------------------------
/**
*/
inline void
DisplayMode::SetYPos(uint y)
{
    this->yPos = y;
}

//------------------------------------------------------------------------------
/**
*/
inline uint
DisplayMode::GetYPos() const
{
    return this->yPos;
}

//------------------------------------------------------------------------------
/**
*/
inline void
DisplayMode::SetWidth(uint w)
{
    this->width = w;
}

//------------------------------------------------------------------------------
/**
*/
inline uint
DisplayMode::GetWidth() const
{
    return this->width;
}

//------------------------------------------------------------------------------
/**
*/
inline void
DisplayMode::SetHeight(uint h)
{
    this->height = h;
}

//------------------------------------------------------------------------------
/**
*/
inline uint
DisplayMode::GetHeight() const
{
    return this->height;
}

//------------------------------------------------------------------------------
/**
*/
inline void
DisplayMode::SetPixelFormat(PixelFormat::Code p)
{
    this->pixelFormat = p;
}

//------------------------------------------------------------------------------
/**
*/
inline PixelFormat::Code
DisplayMode::GetPixelFormat() const
{
    return this->pixelFormat;
}

//------------------------------------------------------------------------------
/**
*/
inline void
DisplayMode::SetAspectRatio(float a)
{
    this->aspectRatio = a;
}

//------------------------------------------------------------------------------
/**
*/
inline float
DisplayMode::GetAspectRatio() const
{
    return this->aspectRatio;
}



class AdapterInfo
{
public:
	/// constructor
	AdapterInfo();
	/// set driver name
	void SetDriverName(const Util::String& s);
	/// get human readable driver name
	const Util::String& GetDriverName() const;
	/// set description string
	void SetDescription(const Util::String& s);
	/// get human readable description
	const Util::String& GetDescription() const;
	/// set device name
	void SetDeviceName(const Util::String& s);
	/// get human readable device name
	const Util::String& GetDeviceName() const;
	/// set driver version low part
	void SetDriverVersionLowPart(uint v);
	/// get low part of driver version
	uint GetDriverVersionLowPart() const;
	/// set driver version high part
	void SetDriverVersionHighPart(uint v);
	/// get high part of driver version
	uint GetDriverVersionHighPart() const;
	/// set vendor id
	void SetVendorId(uint id);
	/// get vendor identifier
	uint GetVendorId() const;
	/// set device id
	void SetDeviceId(uint id);
	/// get device identifier
	uint GetDeviceId() const;
	/// set subsystem id
	void SetSubSystemId(uint id);
	/// get subsystem identifier
	uint GetSubSystemId() const;
	/// set hardware revision
	void SetRevision(uint r);
	/// get hardware revision identifier
	uint GetRevision() const;
	/// set driver/chipset pair guid
	void SetGuid(const Util::Guid& g);
	/// get guid for driver/chipset pair
	const Util::Guid& GetGuid() const;

private:
	Util::String driverName;
	Util::String description;
	Util::String deviceName;
	uint driverVersionLowPart;
	uint driverVersionHighPart;
	uint vendorId;
	uint deviceId;
	uint subSystemId;
	uint revision;
	Util::Guid guid;
};

//------------------------------------------------------------------------------
/**
*/
inline
AdapterInfo::AdapterInfo() :
driverVersionLowPart(0),
driverVersionHighPart(0),
vendorId(0),
deviceId(0),
subSystemId(0),
revision(0)
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
inline void
AdapterInfo::SetDriverName(const Util::String& s)
{
	this->driverName = s;
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::String&
AdapterInfo::GetDriverName() const
{
	return this->driverName;
}

//------------------------------------------------------------------------------
/**
*/
inline void
AdapterInfo::SetDescription(const Util::String& s)
{
	this->description = s;
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::String&
AdapterInfo::GetDescription() const
{
	return this->description;
}

//------------------------------------------------------------------------------
/**
*/
inline void
AdapterInfo::SetDeviceName(const Util::String& s)
{
	this->deviceName = s;
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::String&
AdapterInfo::GetDeviceName() const
{
	return this->deviceName;
}

//------------------------------------------------------------------------------
/**
*/
inline void
AdapterInfo::SetDriverVersionLowPart(uint v)
{
	this->driverVersionLowPart = v;
}

//------------------------------------------------------------------------------
/**
*/
inline uint
AdapterInfo::GetDriverVersionLowPart() const
{
	return this->driverVersionLowPart;
}

//------------------------------------------------------------------------------
/**
*/
inline void
AdapterInfo::SetDriverVersionHighPart(uint v)
{
	this->driverVersionHighPart = v;
}

//------------------------------------------------------------------------------
/**
*/
inline uint
AdapterInfo::GetDriverVersionHighPart() const
{
	return this->driverVersionHighPart;
}

//------------------------------------------------------------------------------
/**
*/
inline void
AdapterInfo::SetVendorId(uint id)
{
	this->vendorId = id;
}

//------------------------------------------------------------------------------
/**
*/
inline uint
AdapterInfo::GetVendorId() const
{
	return this->vendorId;
}

//------------------------------------------------------------------------------
/**
*/
inline void
AdapterInfo::SetDeviceId(uint id)
{
	this->deviceId = id;
}

//------------------------------------------------------------------------------
/**
*/
inline uint
AdapterInfo::GetDeviceId() const
{
	return this->deviceId;
}

//------------------------------------------------------------------------------
/**
*/
inline void
AdapterInfo::SetSubSystemId(uint id)
{
	this->subSystemId = id;
}

//------------------------------------------------------------------------------
/**
*/
inline uint
AdapterInfo::GetSubSystemId() const
{
	return this->subSystemId;
}

//------------------------------------------------------------------------------
/**
*/
inline void
AdapterInfo::SetRevision(uint r)
{
	this->revision = r;
}

//------------------------------------------------------------------------------
/**
*/
inline uint
AdapterInfo::GetRevision() const
{
	return this->revision;
}

//------------------------------------------------------------------------------
/**
*/
inline void
AdapterInfo::SetGuid(const Util::Guid& g)
{
	this->guid = g;
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::Guid&
AdapterInfo::GetGuid() const
{
	return this->guid;
}



class RenderDisplay : public Core::RefCounted
{
protected:

public:
	__DeclareClass(RenderDisplay);
	//__DeclareThreadSingleton(RenderDisplay);
public:
	/// constructor
	RenderDisplay();
	/// destructor
	virtual ~RenderDisplay();

	/// return true if adapter exists
	bool AdapterExists(Adapter::Code adapter);
	/// get available display modes on given adapter
	Util::Array<DisplayMode> GetAvailableDisplayModes(Adapter::Code adapter, PixelFormat::Code pixelFormat);
	/// return true if a given display mode is supported
	bool SupportsDisplayMode(Adapter::Code adapter, const DisplayMode& requestedMode);
	/// get current adapter display mode (i.e. the desktop display mode)
	DisplayMode GetCurrentAdapterDisplayMode(Adapter::Code adapter);
	/// get general info about display adapter
	AdapterInfo GetAdapterInfo(Adapter::Code adapter);

	/// set display adapter (make sure adapter exists!)
	void SetAdapter(Adapter::Code a);
	/// get display adapter
	Adapter::Code GetAdapter() const;
	/// set antialias quality
	void SetAntiAliasQuality(AntiAliasQuality::Code aa);
	/// get antialias quality
	AntiAliasQuality::Code GetAntiAliasQuality() const;

	/// set windowed/fullscreen mode
	void SetFullscreen(bool b);
	/// get windowed/fullscreen mode
	bool IsFullscreen() const;
	/// enable display mode switch when running fullscreen (default is true);
	void SetDisplayModeSwitchEnabled(bool b);
	/// is display mode switch enabled for fullscreen?
	bool IsDisplayModeSwitchEnabled() const;
	/// enable triple buffer for fullscreen (default is double buffering)
	void SetTripleBufferingEnabled(bool b);
	/// is triple buffer enabled for fullscreen?
	bool IsTripleBufferingEnabled() const;
	/// set always-on-top behaviour
	void SetAlwaysOnTop(bool b);
	/// get always-on-top behaviour
	bool IsAlwaysOnTop() const;
	/// turn vertical sync on/off
	void SetVerticalSyncEnabled(bool b);
	/// get vertical sync flag
	bool IsVerticalSyncEnabled() const;
	/// set optional window icon resource name
	void SetIconName(const Util::String& s);
	/// get optional window icon resource name
	const Util::String& GetIconName() const;
	/// set optional parent window handle
	void SetParentWindow(void* h);
	/// get optional parent window handle
	void* GetParentWindow() const;
	/// set started as web version
	void SetWebVersion(bool bWebVersion);
	/// get if started as web version
	bool GetWebVersion() const;
	/// set web window handle
	void SetWebWindow(void* h);
	/// get web window handle
	void* GetWebWindow() const;

	/// set window title string (can be changed anytime)
	void SetWindowTitle(const Util::String& t);
	/// get window title string
	const Util::String& GetWindowTitle() const;

	/// open the display
	bool Open();
	/// close the display
	void Close();
	/// return true if display is currently open
	bool IsOpen() const;
	/// process window system messages, call this method once per frame
	void ProcessWindowMessages();

protected:

	Adapter::Code adapter;
	//DisplayMode displayMode;
	AntiAliasQuality::Code antiAliasQuality;

	bool fullscreen;
	bool modeSwitchEnabled;
	bool tripleBufferingEnabled;
	bool alwaysOnTop;
	bool verticalSync;
	bool isOpen;
	bool m_bWebVersion;

	Util::String windowTitle;
	Util::String iconName;
	void* parentWindow;
	void* m_hWebWindow;

	bool inNotifyEventHandlers;
};

//------------------------------------------------------------------------------
/**
*/
inline bool
RenderDisplay::IsOpen() const
{
	return this->isOpen;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderDisplay::SetAntiAliasQuality(AntiAliasQuality::Code aa)
{
	this->antiAliasQuality = aa;
}

//------------------------------------------------------------------------------
/**
*/
inline AntiAliasQuality::Code
RenderDisplay::GetAntiAliasQuality() const
{
	return this->antiAliasQuality;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderDisplay::SetAdapter(Adapter::Code a)
{
	this->adapter = a;
}

//------------------------------------------------------------------------------
/**
*/
inline Adapter::Code
RenderDisplay::GetAdapter() const
{
	return this->adapter;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderDisplay::SetFullscreen(bool b)
{
	this->fullscreen = b;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
RenderDisplay::IsFullscreen() const
{
	return this->fullscreen;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderDisplay::SetDisplayModeSwitchEnabled(bool b)
{
	this->modeSwitchEnabled = b;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
RenderDisplay::IsDisplayModeSwitchEnabled() const
{
	return this->modeSwitchEnabled;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderDisplay::SetTripleBufferingEnabled(bool b)
{
	this->tripleBufferingEnabled = b;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
RenderDisplay::IsTripleBufferingEnabled() const
{
	return this->tripleBufferingEnabled;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderDisplay::SetAlwaysOnTop(bool b)
{
	this->alwaysOnTop = b;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
RenderDisplay::IsAlwaysOnTop() const
{
	return this->alwaysOnTop;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderDisplay::SetVerticalSyncEnabled(bool b)
{
	this->verticalSync = b;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
RenderDisplay::IsVerticalSyncEnabled() const
{
	return this->verticalSync;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderDisplay::SetIconName(const Util::String& s)
{
	this->iconName = s;
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::String&
RenderDisplay::GetIconName() const
{
	return this->iconName;
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::String&
RenderDisplay::GetWindowTitle() const
{
	return this->windowTitle;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderDisplay::SetParentWindow(void* h)
{
	this->parentWindow = h;
}

//------------------------------------------------------------------------------
/**
*/
inline void*
RenderDisplay::GetParentWindow() const
{
	return this->parentWindow;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderDisplay::SetWebVersion(bool bWebVersion)
{
	this->m_bWebVersion = bWebVersion;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
RenderDisplay::GetWebVersion() const
{
	return this->m_bWebVersion;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderDisplay::SetWebWindow(void* h)
{
	this->m_hWebWindow = h;
}

//------------------------------------------------------------------------------
/**
*/
inline void*
RenderDisplay::GetWebWindow() const
{
	return this->m_hWebWindow;
}


}
#endif