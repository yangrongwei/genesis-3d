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
#ifndef __SOUND_COMMIT__
#include "stdneb.h"
#include "SoundSystemDSPOpenAL.h"
#include "OpenAL/EFX-Util.h"
#include "soundsystem/Framework.h"
#include "soundsystem/SoundSystemSourceOpenAL.h"

namespace Sound
{
	__ImplementClass(Sound::SoundSystemDSPOpenAL, 'SSDO', Sound::SoundSystemDSP);

	//------------------------------------------------------------------------------
	SoundSystemDSPOpenAL::SoundSystemDSPOpenAL()
		: m_uiFilter(NULL)
		, m_uiEffectSlot(NULL)
		, m_type(NULL)
		, m_sendIndex(0)
	{}
	//------------------------------------------------------------------------------
	SoundSystemDSPOpenAL::~SoundSystemDSPOpenAL()
	{
		uninit();
	}
	//------------------------------------------------------------------------------
	bool SoundSystemDSPOpenAL::remove()
	{
		return false;
	}
	//------------------------------------------------------------------------------
	bool SoundSystemDSPOpenAL::setParameter( int index, float value , bool integer)
	{
		if ( m_type != AL_FILTER_LOWPASS )
		{
			if (integer)
				alEffecti( m_uiFilter, index, (int)value);
			else
				alEffectf( m_uiFilter, index, value);

			if( alIsAuxiliaryEffectSlot( m_uiEffectSlot ) )
				alAuxiliaryEffectSloti( m_uiEffectSlot, AL_EFFECTSLOT_EFFECT, m_uiFilter);	
		}
		else
		{
			if (integer)
				alFilteri( m_uiFilter, index, (int)value);
			else
				alFilterf( m_uiFilter, index, value);
		}

		return true;
	}
	//------------------------------------------------------------------------------
	bool SoundSystemDSPOpenAL::setParameters( int index, float* pan)
	{
		alEffectfv( m_uiFilter, index, pan);
		return true;
	}

	//------------------------------------------------------------------------------
	bool SoundSystemDSPOpenAL::init(ALuint type)
	{
		// Clear AL Error State
		alGetError();

		ALboolean result = ALFWIsEFXSupported();
		n_assert(result == AL_TRUE);

		alGenAuxiliaryEffectSlots(1, &m_uiEffectSlot);
		if ( alGetError() != AL_NO_ERROR )
			return false;

		if ( type != AL_FILTER_LOWPASS )
		{
			// effect
			alGenEffects(1, &m_uiFilter);

			if( alGetError () == AL_NO_ERROR )
			{
				alEffecti(m_uiFilter, AL_EFFECT_TYPE, type);

				if (alGetError() == AL_NO_ERROR)
				{
					m_type = type;
					return true;
				}
				else
				{
					alDeleteEffects(1, &m_uiFilter);	
					return false;
				}
			}
			else
				return false;
		}
		else
		{
			// filter
			alGenFilters( 1, &m_uiFilter);

			if( alGetError () == AL_NO_ERROR )
			{
				alFilteri( (m_uiFilter), AL_FILTER_TYPE, type );

				if (alGetError() == AL_NO_ERROR)
				{
					m_type = type;
					return true;
				}
				else
				{
					alDeleteFilters(1, &m_uiFilter);	
					return false;
				}
			}
			else
				return false;
		}
	}

	//------------------------------------------------------------------------------
	bool SoundSystemDSPOpenAL::uninit()
	{
		if ( alIsFilter(m_uiFilter) )
			alDeleteFilters( 1, &m_uiFilter );

		if ( alIsEffect(m_uiFilter))
			alDeleteEffects( 1, &m_uiFilter);

		if ( alIsAuxiliaryEffectSlot(m_uiEffectSlot) )
			alDeleteAuxiliaryEffectSlots( 1, &m_uiEffectSlot );

		m_type = NULL;

		return true;
	}

	bool SoundSystemDSPOpenAL::apply( SoundSystemSource* sss, int sendIndex)
	{
		m_sendIndex = sendIndex;

		if(sss)
		{
			ALuint uiSource = NULL;
			uiSource = sss->GetSource();

			if (alIsSource(uiSource))
			{
				if (m_type == AL_FILTER_LOWPASS)
					alSourcei(uiSource, AL_DIRECT_FILTER, m_uiFilter);
				else
				{
					if( alIsAuxiliaryEffectSlot( m_uiEffectSlot ) )
					{
						alAuxiliaryEffectSloti( m_uiEffectSlot, AL_EFFECTSLOT_EFFECT, m_uiFilter);	
					}
					ALenum ret = alGetError();
					if (ret != AL_NO_ERROR)
					{
						return false;
					}

					alSource3i(uiSource, AL_AUXILIARY_SEND_FILTER, m_uiEffectSlot, m_sendIndex, AL_FILTER_NULL); // ???
					ret = alGetError();
					if (ret != AL_NO_ERROR)
					{
						return false;
					}
				}

				return true;
			}
			else
			{
				return false;
			}

		}
		else
			return false;
	}

	bool SoundSystemDSPOpenAL::unapply( SoundSystemSource* sss )
	{
		if(sss)
		{
			ALuint uiSource = NULL;
			uiSource = sss->GetSource();

			if (alIsSource(uiSource))
			{
				if (m_type == AL_FILTER_LOWPASS)
					alSourcei( sss->GetSource(), AL_DIRECT_FILTER, AL_FILTER_NULL);
				else
					alSource3i( sss->GetSource(), AL_AUXILIARY_SEND_FILTER, AL_EFFECTSLOT_NULL, m_sendIndex, AL_FILTER_NULL);

				return true;
			}
		}

		return false;
	}
}
#endif // __SOUND_COMMIT__