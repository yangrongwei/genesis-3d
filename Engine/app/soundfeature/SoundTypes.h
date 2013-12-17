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
#ifndef __SoundTypes_H__
#define __SoundTypes_H__

#include "OpenAL/EFX-Util.h"


namespace App
{
	static EFXEAXREVERBPROPERTIES ReverbPresets [] =
	{
		EFX_REVERB_PRESET_OFF,
		EFX_REVERB_PRESET_GENERIC,         
		EFX_REVERB_PRESET_PADDEDCELL,    
		EFX_REVERB_PRESET_ROOM,         
		EFX_REVERB_PRESET_BATHROOM,        
		EFX_REVERB_PRESET_STONEROOM,       
		EFX_REVERB_PRESET_AUDITORIUM,      
		EFX_REVERB_PRESET_CONCERTHALL,     
		EFX_REVERB_PRESET_CAVE,           
		EFX_REVERB_PRESET_ARENA,           
		EFX_REVERB_PRESET_HANGAR,          
		EFX_REVERB_PRESET_HALLWAY,         
		EFX_REVERB_PRESET_STONECORRIDOR,   
		EFX_REVERB_PRESET_ALLEY,           
		EFX_REVERB_PRESET_FOREST,          
		EFX_REVERB_PRESET_CITY,            
		EFX_REVERB_PRESET_MOUNTAINS,       
		EFX_REVERB_PRESET_QUARRY,          
		EFX_REVERB_PRESET_PLAIN,           
		EFX_REVERB_PRESET_PARKINGLOT,      
		EFX_REVERB_PRESET_SEWERPIPE,       
		EFX_REVERB_PRESET_UNDERWATER,      
	};

}

#endif //__SoundTypes_H__
