#****************************************************************************
# Copyright (c) 2011-2013,WebJet Business Division,CYOU
#  
# http://www.genesis-3d.com.cn
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#****************************************************************************


##################################################################################
# Build foundation
##################################################################################

#app folder
SET ( APP_HEADER_FILES 
	app/application.h
)

SET ( APP_SOURCE_FILES
	app/application.cc
)

SET ( CORE_HEADER_FILES
#core folder	
	core/config.h
	#debug folder
	core/debug/corepagehandler.h
	core/debug/stringatompagehandler.h
	#osx folder
	#core/osx/osxsingleton.h
	#core/osx/osxsysfunc.h
	#core/osx/precompiled.h
	#win32 folder
	core/win32/precompiled.h
	core/win32/win32singleton.h
	core/win32/win32sysfunc.h
	core/android/precompiled.h
	core/android/androidsysfunc.h
	core/android/androidsingleton.h
	core/config.h
	core/coreserver.h
	core/debug.h
	core/exithandler.h
	core/factory.h
	core/ptr.h
	core/refcounted.h
	core/refcountedlist.h
	core/rtti.h
	core/rttimacros.h
	core/singleton.h
	core/sysfunc.h
	core/types.h
	core/weakptr.h
	core/scopedptr.h	
)

SET ( CORE_SOURCE_FILES
#core folder
	#debug folder
	core/debug/corepagehandler.cc
	core/debug/stringatompagehandler.cc
	#win32 folder
	core/win32/win32sysfunc.cc
	core/android/androidsysfunc.cc
	core/coreserver.cc
	core/debug.cc
	core/exithandler.cc
	core/factory.cc
	core/refcounted.cc
	core/refcountedlist.cc
	core/rtti.cc	
)

SET ( DEBUG_HEADER_FILES 
#debug folder
	#win32 folder
	debug/win32/win32minidump.h
	debug/debugcounter.h
	debug/debugfloat.h
	debug/debughandler.h
	debug/debuginterface.h
	debug/debugpagehandler.h
	debug/debugserver.h
	debug/debugtimer.h
	debug/minidump.h
)

SET ( DEBUG_SOURCE_FILES
#debug folder
	#win32 folder
	debug/win32/win32minidump.cc
	debug/debugcounter.cc
	debug/debughandler.cc
	debug/debuginterface.cc
	debug/debugpagehandler.cc
	debug/debugserver.cc
	debug/debugtimer.cc
)

SET ( DELEGATE_HEADER_FILES 
#delegates folder
	delegates/delegate_implement.h
	delegates/delegatetype.h
)

SET ( FRAMESYNC_HEADER_FILES 
#framesync folder
	framesync/framesynchandlerthread.h
	framesync/framesyncshareddata.h
	framesync/framesynctimer.h
)

SET ( FRAMESYNC_SOURCE_FILES
#framesync folder
	framesync/framesynchandlerthread.cc
	framesync/framesyncshareddata.cc
	framesync/framesynctimer.cc	
)

SET ( HTTP_HEADER_FILES 
#http folder
	#debug foler
	http/debug/helloworldrequesthandler.h
	http/debug/svgtestpagehandler.h
	#html folder
	http/html/htmlelement.h
	http/html/htmlpagewriter.h
	#svg folder
	http/svg/svglinechartwriter.h
	http/svg/svgpagewriter.h
	http/defaulthttprequesthandler.h
	http/httpclient.h
	http/httpclientregistry.h
	http/httpinterface.h
	http/httpmessagehandler.h
	http/httpmethod.h
	http/httpnzstream.h
	#http/httpprotocol.h
	http/httprequest.h
	http/httprequesthandler.h
	http/httprequestreader.h
	http/httprequestwriter.h
	http/httpresponsereader.h
	http/httpresponsewriter.h
	http/httpserver.h
	http/httpserverproxy.h
	http/httpstatus.h
	http/httpstream.h
)

SET ( HTTP_SOURCE_FILES
#http folder
	#debug foler
	http/debug/helloworldrequesthandler.cc
	http/debug/svgtestpagehandler.cc
	#html folder
	http/html/htmlelement.cc
	http/html/htmlpagewriter.cc	
	#svg folder
	http/svg/svglinechartwriter.cc
	http/svg/svgpagewriter.cc
	
	http/defaulthttprequesthandler.cc
	http/httpclient.cc
	http/httpclientregistry.cc
	http/httpinterface.cc
	http/httpmessagehandler.cc
	http/httpnzstream.cc
	http/httprequest.cc
	http/httprequesthandler.cc
	http/httprequestreader.cc
	http/httprequestwriter.cc
	http/httpresponsereader.cc
	http/httpresponsewriter.cc
	http/httpserver.cc
	http/httpserverproxy.cc
	http/httpstatus.cc
	http/httpstream.cc	
)

SET ( INTERFACE_HEADER_FILES 
#interface folder
	interface/interfacebase.h
	interface/interfacehandlerbase.h
)

SET ( INTERFACE_SOURCE_FILES
#interface folder
	interface/interfacebase.cc
	interface/interfacehandlerbase.cc
)

SET ( IO_HEADER_FILES 
#io folder
	#archfs
	io/archfs/archive.h
	io/archfs/archivebase.h
	io/archfs/archivefilesystem.h
	io/archfs/archivefilesystembase.h
	#base
	io/base/gamecontentserverbase.h	
	#debug
	io/debug/consolepagehandler.h
	io/debug/iopagehandler.h
	#osx
	#io/osx/osxconsolehandler.h
	#io/osx/osxfiletime.h
	#io/osx/osxfswrapper.h	
	#util
	io/util/bxmlfilestructs.h
	io/util/bxmlloaderutil.h	
	#win32
	io/win32/win32consolehandler.h
	#win360
	io/win360/win360filetime.h
	io/win360/win360fswrapper.h
	#android
	io/android/androidconsolehandler.h
	io/android/androidfiletime.h
	io/android/androidfswrapper.h
	#zipfs
	io/zipfs/ziparchive.h
	io/zipfs/zipdirentry.h
	io/zipfs/zipfileentry.h
	io/zipfs/zipfilestream.h
	io/zipfs/zipfilesystem.h	
	#FileService
	fsapi/lfs_api.h
	io/FileService/fileservicesystem.h
	#general
	io/assign.h
	io/assignregistry.h
	io/binaryreader.h
	io/binarywriter.h
	io/bxmlreader.h
	io/console.h
	io/consolehandler.h
	io/excelxmlreader.h
	io/filestream.h
	io/filetime.h
	io/fswrapper.h
	io/gamecontentserver.h
	io/historyconsolehandler.h
	io/iointerface.h
	io/ioprotocoldef.h
	io/iointerfacehandler.h
	#io/iointerfaceprotocol.h
	io/ioserver.h
	io/logfileconsolehandler.h
	io/mediatype.h
	io/memorystream.h
	io/schemeregistry.h
	io/stream.h
	io/streamreader.h
	io/streamwriter.h
	io/memoryreader.h
	io/textreader.h
	io/textwriter.h
	io/uri.h
	io/xmlreader.h
	io/xmlwriter.h
	io/android/androidarchive.h
	io/android/androidarchivefilesystem.h
	io/osx/osxarchive.h
	io/osx/osxarchivefilesystem.h
)

SET ( IO_SOURCE_FILES
#IO folder
	io/archfs/archive.cc
	io/archfs/archivebase.cc
	io/archfs/archivefilesystem.cc
	io/archfs/archivefilesystembase.cc
	io/base/gamecontentserverbase.cc
	io/debug/consolepagehandler.cc
	io/debug/iopagehandler.cc
	#osx folder
	#io/osx/osxconsolehandler.cc
	#io/osx/osxfswrapper.cc
	#util folder
	io/util/bxmlloaderutil.cc
	#win32 folder
	io/win32/win32consolehandler.cc
	#win360 folder
	io/win360/win360filetime.cc
	io/win360/win360fswrapper.cc
	#android folder
	io/android/androidfswrapper.cc
	#zipfs folder
	io/zipfs/ziparchive.cc
	io/zipfs/zipdirentry.cc
	io/zipfs/zipfileentry.cc
	io/zipfs/zipfilestream.cc
	io/zipfs/zipfilesystem.cc
	#FileService
	io/FileService/fileservicesystem.cc
	#general
	io/assignregistry.cc
	io/binaryreader.cc
	io/binarywriter.cc
	io/bxmlreader.cc
	io/console.cc
	io/consolehandler.cc
	io/excelxmlreader.cc
	io/filestream.cc
	io/gamecontentserver.cc
	io/historyconsolehandler.cc
	io/iointerface.cc
	io/iointerfacehandler.cc
	io/ioserver.cc
	io/logfileconsolehandler.cc
	io/memorystream.cc
	io/schemeregistry.cc
	io/stream.cc
	io/streamreader.cc
	io/streamwriter.cc
	io/memoryreader.cc
	io/textreader.cc
	io/textwriter.cc
	io/uri.cc
	io/xmlreader.cc
	io/xmlwriter.cc
	io/android/androidarchive.cc
	io/android/androidarchivefilesystem.cc
	io/android/androidconsolehandler.cc
	io/osx/osxarchive.cc
	io/osx/osxarchivefilesystem.cc
)

SET ( JOBS_HEADER_FILES 
#jobs			
	jobs/job.h
	jobs/jobdatadesc.h
	jobs/jobfunccontext.h
	jobs/jobfuncdesc.h
	jobs/jobport.h
	jobs/jobsystem.h
	jobs/jobuniformdesc.h
	jobs/stdjob.h
	jobs/base/jobbase.h
	jobs/base/jobfuncdescbase.h
	jobs/base/jobportbase.h
	jobs/base/jobsystembase.h
	jobs/tp/tpjob.h
	jobs/tp/tpjobcommand.h
	jobs/tp/tpjobfuncdesc.h
	jobs/tp/tpjobport.h
	jobs/tp/tpjobslice.h
	jobs/tp/tpjobsystem.h
	jobs/tp/tpjobthreadpool.h
	jobs/tp/tpworkerthread.h
)

SET ( JOBS_SOURCE_FILES
#jobs
	jobs/job.cc
	jobs/jobport.cc
	jobs/jobsystem.cc
	jobs/base/jobbase.cc
	jobs/base/jobportbase.cc
	jobs/base/jobsystembase.cc
	jobs/tp/tpjob.cc
	jobs/tp/tpjobport.cc
	jobs/tp/tpjobslice.cc
	jobs/tp/tpjobsystem.cc
	jobs/tp/tpjobthreadpool.cc
	jobs/tp/tpworkerthread.cc
)

SET ( MATH_HEADER_FILES 
#math
	math/newMath/new_vector.h
	math/newMath/new_scalar.h
	math/newMath/new_quaternion.h
	math/newMath/new_point.h
	math/newMath/new_plane.h
	math/newMath/new_matrix44.h
	math/newMath/new_float4.h
	math/OgreMath/OgreVector4.h
	math/OgreMath/OgreVector3.h
	math/OgreMath/OgreQuaternion.h
	math/OgreMath/OgrePrerequisites.h
	math/OgreMath/OgreMatrix4.h
	math/OgreMath/OgreMatrix3.h
	math/OgreMath/OgreMath.h
	math/OgreMath/asm_math.h
	math/bbox.h
	math/clipstatus.h
	math/color.h
	math/curve.h
	math/PolyCurve.h
	math/float2.h
	math/float3.h
	math/float4.h
	math/frustum.h
	math/intersection.h
	math/line.h
	math/matrix44.h
	math/MinMaxCurve.h
	math/noise.h
	math/plane.h
	math/point.h
	math/polar.h
	math/quaternion.h
	math/ray.h
	math/rectangle.h
	math/scalar.h
	math/sphere_.h
	math/transform44.h
	math/vector.h
	math/size.h
	math/point2d.h
)

SET ( MATH_SOURCE_FILES
#math
	math/newMath/new_quaternion.cc
	math/newMath/new_plane.cc
	math/newMath/new_matrix44.cc
	math/newMath/new_float4.cc
	math/OgreMath/OgreVector4.cc
	math/OgreMath/OgreVector3.cc
	math/OgreMath/OgreQuaternion.cc
	math/OgreMath/OgreMath.cc	
	math/OgreMath/OgreMatrix4.cc
	math/OgreMath/OgreMatrix3.cc
	math/bbox.cc
	math/MinMaxCurve.cc
	math/intersection.cc
	math/line.cc
	math/sphere_.cc	
	math/float3.cc	
	math/size.cc
)

SET ( MESHBUILDER_HEADER_FILES
#meshbuilder	
	meshbuilder/meshbuilder.h
	meshbuilder/parallelogrambuilder.h
	meshbuilder/conebuilder.h
	meshbuilder/boxbuilder.h
)

SET ( MESHBUILDER_SOURCE_FILES
#meshbuilder
	meshbuilder/meshbuilder.cc
	meshbuilder/parallelogrambuilder.cc
	meshbuilder/conebuilder.cc
	meshbuilder/boxbuilder.cc
)



SET ( MEMORY_HEADER_FILES 
#memory
	memory/debug/memorypagehandler.h
	#memory/osx/osxheap.h
	#memory/osx/osxmemory.h
	#memory/osx/osxmemoryconfig.h
	#memory/osx/osxmemorypool.h
	memory/android/androidmemory.h
	memory/android/androidmemoryconfig.h
	memory/win32/win32memory.h
	memory/win360/win360heap.h
	memory/win360/win360memory.h
	memory/win360/win360memoryconfig.h
	memory/win360/win360memorypool.h
	memory/android/androidheap.h
	memory/android/androidmemory.h
	memory/android/androidmemoryconfig.h
	memory/android/androidmemorypool.h
	memory/heap.h
	memory/memory.h
	memory/memorypool.h
	memory/poolarrayallocator.h
)

SET ( MEMORY_SOURCE_FILES
#memory
	memory/debug/memorypagehandler.cc
	#memory/osx/osxheap.cc
	#memory/osx/osxmemory.cc
	#memory/osx/osxmemoryconfig.cc
	#memory/osx/osxmemorypool.cc
	memory/android/androidmemory.cc
	memory/android/androidmemoryconfig.cc
	memory/android/androidheap.cc
	memory/android/androidmemorypool.cc
	memory/win360/win360heap.cc
	memory/win360/win360memory.cc
	memory/win360/win360memoryconfig.cc
	memory/win360/win360memorypool.cc
	memory/poolarrayallocator.cc
)

SET ( MESSAGE_HEADER_FILES 
#messaging
	messaging/asyncport.h
	messaging/batchmessage.h
	messaging/blockinghandlerthread.h
	messaging/asynhandlerthread.h
	messaging/delegatetable.h
	messaging/dispatcher.h
	messaging/handler.h
	messaging/handlerthreadbase.h
	messaging/id.h
	messaging/message.h
	messaging/messagereader.h
	messaging/messagewriter.h
	messaging/port.h
	messaging/runthroughhandlerthread.h
	messaging/staticmessagehandler.h	
)

SET ( MESSAGE_SOURCE_FILES
#messaging	
	messaging/asyncport.cc
	messaging/batchmessage.cc
	messaging/blockinghandlerthread.cc
	messaging/asynhandlerthread.cc
	messaging/delegatetable.cc
	messaging/dispatcher.cc
	messaging/handler.cc
	messaging/handlerthreadbase.cc
	messaging/message.cc
	messaging/messagereader.cc
	messaging/messagewriter.cc
	messaging/port.cc
	messaging/runthroughhandlerthread.cc
	messaging/staticmessagehandler.cc	
)

SET ( NET_HEADER_FILES 
#net folder
	net/socket/ipaddress.h
	net/socket/socket.h
	net/tcp/stdtcpclient.h
	net/tcp/stdtcpclientconnection.h
	net/tcp/stdtcpserver.h
	net/win360/win360ipaddress.h
	net/win360/win360socket.h
	net/android/androidipaddress.h
	net/android/androidsocket.h
	net/debugmessage.h
	net/debugpacket.h
	net/messageclient.h
	net/messageclientconnection.h
	net/tcpclient.h
	net/tcpclientconnection.h
	net/tcpmessagecodec.h
	net/tcpserver.h
)

SET ( NET_SOURCE_FILES
#net
	net/socket/socket.cc	
	net/tcp/stdtcpclient.cc
	net/tcp/stdtcpclientconnection.cc
	net/tcp/stdtcpserver.cc
	net/win360/win360ipaddress.cc
	net/win360/win360socket.cc
	net/android/androidipaddress.cc
	net/android/androidsocket.cc
	net/debugpacket.cc
	net/messageclient.cc
	net/messageclientconnection.cc
	net/tcpclient.cc
	net/tcpclientconnection.cc
	net/tcpmessagecodec.cc
	net/tcpserver.cc
)

SET ( SYSTEM_HEADER_FILES 
#system folder
	system/base/systeminfobase.h
	#system/osx/osxcpu.h
	system/win32/win32cpu.h
	system/win32/win32environment.h
	system/win32/win32registry.h
	system/win32/win32systeminfo.h
	system/android/androidcpu.h
	system/android/androidsysteminfo.h
	system/appentry.h
	system/byteorder.h
	system/cpu.h
	system/systeminfo.h
)

SET ( SYSTEM_SOURCE_FILES
#system	
	system/base/systeminfobase.cc	
	system/win32/win32environment.cc
	system/win32/win32registry.cc
	system/win32/win32systeminfo.cc
	system/android/androidsysteminfo.cc
)

SET ( THREADING_HEADER_FILES 
#threading folder
	threading/debug/threadpagehandler.h
	#threading/osx/osxcriticalsection.h
	#threading/osx/osxinterlocked.h
	#threading/osx/osxthread.h
	#threading/osx/osxthreadid.h
	#threading/osx/osxthreadlocalptr.h
	threading/win360/win360barrier.h
	threading/win360/win360criticalsection.h
	threading/win360/win360event.h
	threading/win360/win360interlocked.h
	threading/win360/win360thread.h
	threading/win360/win360threadbarrier.h
	threading/win360/win360threadid.h
	threading/android/androidBarrier.h
	threading/android/androidCriticalsection.h
	threading/android/androidEvent.h
	threading/android/androidInterlocked.h
	threading/android/androidThread.h
	threading/android/androidThreadbarrier.h
	threading/android/androidThreadid.h
	threading/android/androidthreadlocalptr.h
	threading/android/linuxevent.h
	threading/barrier.h
	threading/criticalsection.h
	threading/event.h
	threading/interlocked.h
	threading/objectref.h
	threading/safeflag.h
	threading/safepriorityqueue.h
	threading/safequeue.h
	threading/thread.h
	threading/threadbarrier.h
	threading/threadid.h
	threading/ThreadRuntimeInfo.h
)

SET ( THREADING_SOURCE_FILES
#threading
	threading/debug/threadpagehandler.cc
	#threading/osx/osxthread.cc
	threading/win360/win360criticalsection.cc
	threading/win360/win360thread.cc
	threading/android/androidCriticalsection.cc
	threading/android/androidThread.cc
	threading/android/linuxevent.cc
	threading/objectref.cc
	threading/thread.cc
	threading/ThreadRuntimeInfo.cpp
)

SET ( TIMING_HEADER_FILES 
#timing
	timing/base/calendartimebase.h
	timing/win360/win360calendartime.h
	timing/win360/win360timer.h
	timing/android/androidcalendartime.h
	timing/android/androidtimer.h
	timing/calendartime.h
	timing/time.h
	timing/timer.h
)

SET ( TIMING_SOURCE_FILES
#timing
	timing/base/calendartimebase.cc
	timing/win360/win360calendartime.cc
	timing/win360/win360timer.cc
	timing/android/androidcalendartime.cc
	timing/android/androidtimer.cc
)

SET ( UTIL_HEADER_FILES 
#util
	#util/osx/osxguid.h
	util/win32/win32guid.h
	util/win32/win32stringconverter.h
	util/stringconvert.h
	util/algorithm.h
	util/array.h
	util/bitfield.h
	util/blob.h
	util/commandlineargs.h
	util/crc.h
	util/delegate.h
	util/dictionary.h
	util/fixedarray.h
	util/fixedarray2d.h
	util/mipmaparray.h
	util/fixedtable.h
	util/fourcc.h
	util/globalstringatomtable.h
	util/guid.h
	util/hashtable.h
	util/keyvaluepair.h
	util/list.h
	util/localstringatomtable.h
	util/priorityarray.h
	util/quadtree.h
	util/queue.h
	util/randomnumbertable.h
	util/ringbuffer.h
	util/round.h
	util/runlengthcodec.h
	util/stl.h
	util/simpletree.h
	util/sparsetable.h
	util/stack.h
	util/string.h
	util/stringatom.h
	util/stringatomtablebase.h
	util/stringbuffer.h
	util/typepunning.h
	util/variant.h
	util/scriptbind.h
	util/monoapi.h
	util/monotypes.h
	util/android/androidguid.h
	util/android/androidstringconverter.h
	util/assetpath.h
)

SET ( UTIL_SOURCE_FILES
#util
	#util/osx/osxguid.cc
	util/win32/win32guid.cc
	util/win32/win32stringconverter.cc
	util/stringconvert.cc
	util/blob.cc
	util/commandlineargs.cc
	util/crc.cc
	util/globalstringatomtable.cc
	util/localstringatomtable.cc
	util/randomnumbertable.cc
	util/runlengthcodec.cc
	util/string.cc
	util/stringatom.cc
	util/stringatomtablebase.cc
	util/stringbuffer.cc
	util/scriptbind.cc
	util/android/androidguid.cc
	util/android/androidstringconverter.cc
)

SET ( EXCEPTION_HEADER_FILES	
	exception/exceptionbase.h
	exception/exceptions.h
)

SET ( EXCEPTION_SOURCE_FILES
	exception/exceptionbase.cc
	exception/exceptions.cc
)	

SET ( _HEADER_FILES	
	genesisfoundation.h
	stdneb.h	
)

SET ( _SOURCE_FILES
	stdneb.cc
)	

SET ( DOX_FILES
#app folder
	app/app.dox
	#win32 folder
	core/win32/win32.dox
	core/base.dox
	core/core.dox	
#debug
	debug/debug.dox
#http
	http/http.dox
	interface/interface.dox

	io/io.dox
)

#<--------nidl fils------------------>
SET ( _NIDL_FILES
#http
	http/httpprotocol.nidl
	io/iointerfaceprotocol.nidl	
)

#<--------generated fils------------------>
Set ( GENERATED_FILES
	#header
	io/iointerfaceprotocol.h
	http/httpprotocol.h
	#source
	io/iointerfaceprotocol.cc
	http/httpprotocol.cc
)	

 #<-------- Source Group ------------------>
SOURCE_GROUP( 
	app
	FILES 
	${APP_HEADER_FILES}
	#source
	${APP_SOURCE_FILES}
)

SOURCE_GROUP( 
	core
	FILES 
	${CORE_HEADER_FILES}
	${CORE_SOURCE_FILES}
)

SOURCE_GROUP( 
	debug
	FILES 
	${DEBUG_HEADER_FILES}
	${DEBUG_SOURCE_FILES}
)
SOURCE_GROUP( 
	delegates
	FILES 
	${DELEGATE_HEADER_FILES}
)

SOURCE_GROUP( 
	framesync
	FILES 
	${FRAMESYNC_HEADER_FILES} 
	${FRAMESYNC_SOURCE_FILES}
)

SOURCE_GROUP( 
	http
	FILES 
	${HTTP_HEADER_FILES}
	${HTTP_SOURCE_FILES}
)

SOURCE_GROUP( 
	interface
	FILES 
	${INTERFACE_HEADER_FILES} 
	${INTERFACE_SOURCE_FILES} 
)

SOURCE_GROUP( 
	io
	FILES
	${IO_HEADER_FILES}
	${IO_SOURCE_FILES}
)

SOURCE_GROUP( 
	jobs
	FILES 
	${JOBS_HEADER_FILES} 
	${JOBS_SOURCE_FILES}
)

SOURCE_GROUP( 
	math
	FILES
	${MATH_HEADER_FILES}
	${MATH_SOURCE_FILES} 
)

SOURCE_GROUP( 
	meshbuilder
	FILES
	${MESHBUILDER_HEADER_FILES}
	${MESHBUILDER_SOURCE_FILES} 
)

SOURCE_GROUP( 
	memory
	FILES 
	${MEMORY_HEADER_FILES} 
	${MEMORY_SOURCE_FILES}
)

SOURCE_GROUP( 
	message
	FILES 
	${MESSAGE_HEADER_FILES}
	${MESSAGE_SOURCE_FILES}
)

SOURCE_GROUP( 
	net
	FILES 
	${NET_HEADER_FILES} 
	${NET_SOURCE_FILES}
)

SOURCE_GROUP( 
	system
	FILES
	${SYSTEM_HEADER_FILES}
	${SYSTEM_SOURCE_FILES}
)

SOURCE_GROUP( 
	threading
	FILES 
	${THREADING_HEADER_FILES} 
	${THREADING_SOURCE_FILES}
)

SOURCE_GROUP( 
	timing
	FILES 
	${TIMING_HEADER_FILES}
	${TIMING_SOURCE_FILES}
)

SOURCE_GROUP( 
	util
	FILES 
	${UTIL_HEADER_FILES} 
	${UTIL_SOURCE_FILES}	
)

SOURCE_GROUP( 
	exception
	FILES 
	${EXCEPTION_HEADER_FILES} 
	${EXCEPTION_SOURCE_FILES}	
)
ADD_LIBRARY(
	Foundation 
	STATIC 
	#header
	${APP_HEADER_FILES}
	${CORE_HEADER_FILES}
	${DEBUG_HEADER_FILES}
	${DELEGATE_HEADER_FILES}
	${FRAMESYNC_HEADER_FILES} 
	${HTTP_HEADER_FILES}
	${INTERFACE_HEADER_FILES} 
	${IO_HEADER_FILES}
	${JOBS_HEADER_FILES} 
	${MATH_HEADER_FILES}
	${MESHBUILDER_HEADER_FILES}
	${MEMORY_HEADER_FILES} 
	${MESSAGE_HEADER_FILES}
	${NET_HEADER_FILES} 
	${SYSTEM_HEADER_FILES}
	${THREADING_HEADER_FILES} 
	${TIMING_HEADER_FILES}
	${UTIL_HEADER_FILES} 
	${_HEADER_FILES}
	${EXCEPTION_HEADER_FILES} 
	#source
	${APP_SOURCE_FILES}
	${CORE_SOURCE_FILES}
	${DEBUG_SOURCE_FILES}
	${FRAMESYNC_SOURCE_FILES}
	${HTTP_SOURCE_FILES}
	${INTERFACE_SOURCE_FILES} 
	${IO_SOURCE_FILES}
	${JOBS_SOURCE_FILES}
	${MATH_SOURCE_FILES} 
	${MESHBUILDER_SOURCE_FILES}
	${MEMORY_SOURCE_FILES}
	${MESSAGE_SOURCE_FILES}
	${NET_SOURCE_FILES}
	${SYSTEM_SOURCE_FILES}
	${THREADING_SOURCE_FILES}
	${TIMING_SOURCE_FILES}
	${UTIL_SOURCE_FILES}
	${EXCEPTION_SOURCE_FILES}	
	${_SOURCE_FILES}
	#generate files
	${GENERATED_FILES}
 )

#Organize projects into folders
SET_PROPERTY(TARGET Foundation PROPERTY FOLDER "2.Foundation")

#Compile properties
_MACRO_TREAT_WARRINGS_AS_ERRORS( Foundation )
 
 #<--------dependencies------------------>
 ADD_DEPENDENCIES(
	Foundation
#dependencies
	TinyXML
	Foundation_nidls
	ZLib
 )

#<-------- Additional Include Directories ------------------>
INCLUDE_DIRECTORIES( 
	#TODO:Make this clear and simple
	${CMAKE_SOURCE_DIR}/extlibs
	${CMAKE_SOURCE_DIR}/extlibs/boostWraper

	# should remove later	
	${CMAKE_SOURCE_DIR}/foundation 

###############fileservice tempcode, remove it later 2011.11.21#########################################
	${CMAKE_SOURCE_DIR}/
###############fileservice tempcode, remove it later 2011.11.21#########################################	
)

###################################3
#add Foundation_nidls projct
#TODO: use parameters 
#TODO:clear generated files before build 
 ADD_CUSTOM_TARGET( 
	Foundation_nidls 
	ALL 
	COMMAND ${CMAKE_SOURCE_DIR}/tools/idlcompiler/IdlcCompiler.exe ${CMAKE_SOURCE_DIR}/foundation/http/httpprotocol.nidl ${CMAKE_SOURCE_DIR}/foundation/io/iointerfaceprotocol.nidl
	SOURCES ${_NIDL_FILES}
)

#Organize projects into folders
SET_PROPERTY(TARGET Foundation_nidls PROPERTY FOLDER "2.Foundation")

 #<--------dependencies------------------>
 ADD_DEPENDENCIES(
	Foundation_nidls
#dependencies
	IdlcCompiler
 )
#####################################
	