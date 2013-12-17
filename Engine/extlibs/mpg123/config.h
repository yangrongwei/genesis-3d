/*#define strcasecmp _strcmpi
上个语句会产生如下的链接错误，可能是因为调用的_strcmpi函数是比较旧的函数，新的c运行时库已经没有该函数的实现了
5>libmpg123.lib(optimize.obj) : error LNK2019: unresolved external symbol __imp___strcmpi referenced in function _INT123_dectype
所以换成了以下的的调用*/
#ifdef __WIN32__
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#define strdup _strdup
#endif //__WIN32__
#define HAVE_STRERROR 1
#define HAVE_SYS_TYPES_H 1

#define HAVE_STRDUP
#define HAVE_STDLIB_H
#define HAVE_STRING_H

/* We want some frame index, eh? */
#define FRAME_INDEX 1
#define INDEX_SIZE 1000

/* also gapless playback! */
#define GAPLESS 1
/* #ifdef GAPLESS
#undef GAPLESS
#endif */

/* #define DEBUG
#define EXTRA_DEBUG */

#define REAL_IS_FLOAT

#define inline __inline

/* we are on win32 */
#define HAVE_WINDOWS_H

/* use the unicode support within libmpg123 */
#ifdef UNICODE
	#define WANT_WIN32_UNICODE
#endif
