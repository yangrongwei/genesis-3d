LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := tests

unix_files = \
	gdate-unix.c  gdir-unix.c  gfile-unix.c  gmisc-unix.c	\
	gmodule-unix.c gtimer-unix.c

# some unices and windows do not have an implementation of vasprintf
# used by eglib, use provided implementation instead
#if NEED_VASPRINTF
vasprintf_files = vasprintf.c
#else
#vaprinttf_files = foo.c
#endif

os_files = $(unix_files)


LOCAL_SRC_FILES := \
	garray.c	\
	gbytearray.c	\
	gerror.c	\
	ghashtable.c 	\
	gmem.c       	\
	goutput.c    	\
	gstr.c       	\
	gslist.c     	\
	gstring.c    	\
	gptrarray.c     \
	glist.c		\
	gqueue.c	\
	gpath.c		\
	gshell.c	\
	gspawn.c	\
	gfile.c		\
	gfile-posix.c	\
	gpattern.c	\
	gmarkup.c	\
	gutf8.c		\
	gunicode.c	\
	$(os_files)	\
	$(vasprintf_files)

monodir := development/apps/mono-2.10.8
LOCAL_C_INCLUDES := \
		$(LOCAL_PATH) \
		$(monodir)/PlatformPatches \
		$(monodir)/eglib/src         \
		$(monodir)/eglib 

#self lib
LOCAL_STATIC_LIBRARIES := 
#sys lib
LOCAL_LDLIBS := -llog

LOCAL_SHARED_LIBRARIES :=

LOCAL_MODULE:= libeglib

include $(BUILD_STATIC_LIBRARY)
#include $(BUILD_SHARED_LIBRARY)
