#ifndef ALDEVICELIST_H
#define ALDEVICELIST_H

#ifdef __ANDROID__
#define _stricmp strcasecmp 
#define _strnicmp strncasecmp 
#define _strdup strdup 
#endif //__ANDROID__

#pragma warning(disable: 4786)  //disable warning "identifier was truncated to '255' characters in the browser information"
#include <vector>
#include <string>
#include "LoadOAL.h"
#include "foundation/util/string.h"
#include "foundation/util/array.h"


using namespace std;

typedef struct
{
	Util::String	strDeviceName;
	int				iMajorVersion;
	int				iMinorVersion;
	unsigned int	uiSourceCount;
	Util::Array<Util::String>	*pvstrExtensions;
	bool			bSelected;
} ALDEVICEINFO, *LPALDEVICEINFO;

class ALDeviceList
{
private:
	OPENALFNTABLE	ALFunction;
	Util::Array<ALDEVICEINFO> vDeviceInfo;
	int defaultDeviceIndex;
	int filterIndex;

public:
	ALDeviceList ();
	~ALDeviceList ();
	int GetNumDevices();
	char *GetDeviceName(int index);
	void GetDeviceVersion(int index, int *major, int *minor);
	unsigned int GetMaxNumSources(int index);
	bool IsExtensionSupported(int index, char *szExtName);
	int GetDefaultDevice();
	void FilterDevicesMinVer(int major, int minor);
	void FilterDevicesMaxVer(int major, int minor);
	void FilterDevicesExtension(char *szExtName);
	void ResetFilters();
	int GetFirstFilteredDevice();
	int GetNextFilteredDevice();

private:
	unsigned int GetMaxNumSources();
};

#endif // ALDEVICELIST_H
