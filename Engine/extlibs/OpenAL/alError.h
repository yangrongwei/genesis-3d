#ifndef _AL_ERROR_H_
#define _AL_ERROR_H_

#include "al.h"
#include "alc.h"

#ifdef __cplusplus
extern "C" {
#endif

ALvoid alSetError(ALCcontext *Context, ALenum errorCode);

#ifdef __cplusplus
}
#endif

#endif
