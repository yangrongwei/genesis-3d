# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# For each target create a dummy rule so the target does not have to exist
/Volumes/MacDisk2/thirdlib/hlsl2glslfork/Debug/libhlsl2glsl.a:
/Volumes/MacDisk2/thirdlib/hlsl2glslfork/MinSizeRel/libhlsl2glsl.a:
/Volumes/MacDisk2/thirdlib/hlsl2glslfork/RelWithDebInfo/libhlsl2glsl.a:
/Volumes/MacDisk2/thirdlib/hlsl2glslfork/Release/libhlsl2glsl.a:


# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.hlsl2glsl.Debug:
PostBuild.hlsl2glsltest.Debug:
PostBuild.hlsl2glsl.Debug: /Volumes/MacDisk2/thirdlib/hlsl2glslfork/Debug/hlsl2glsltest
/Volumes/MacDisk2/thirdlib/hlsl2glslfork/Debug/hlsl2glsltest:\
	/Volumes/MacDisk2/thirdlib/hlsl2glslfork/Debug/libhlsl2glsl.a
	/bin/rm -f /Volumes/MacDisk2/thirdlib/hlsl2glslfork/Debug/hlsl2glsltest


PostBuild.hlsl2glsl.Release:
PostBuild.hlsl2glsltest.Release:
PostBuild.hlsl2glsl.Release: /Volumes/MacDisk2/thirdlib/hlsl2glslfork/Release/hlsl2glsltest
/Volumes/MacDisk2/thirdlib/hlsl2glslfork/Release/hlsl2glsltest:\
	/Volumes/MacDisk2/thirdlib/hlsl2glslfork/Release/libhlsl2glsl.a
	/bin/rm -f /Volumes/MacDisk2/thirdlib/hlsl2glslfork/Release/hlsl2glsltest


PostBuild.hlsl2glsl.MinSizeRel:
PostBuild.hlsl2glsltest.MinSizeRel:
PostBuild.hlsl2glsl.MinSizeRel: /Volumes/MacDisk2/thirdlib/hlsl2glslfork/MinSizeRel/hlsl2glsltest
/Volumes/MacDisk2/thirdlib/hlsl2glslfork/MinSizeRel/hlsl2glsltest:\
	/Volumes/MacDisk2/thirdlib/hlsl2glslfork/MinSizeRel/libhlsl2glsl.a
	/bin/rm -f /Volumes/MacDisk2/thirdlib/hlsl2glslfork/MinSizeRel/hlsl2glsltest


PostBuild.hlsl2glsl.RelWithDebInfo:
PostBuild.hlsl2glsltest.RelWithDebInfo:
PostBuild.hlsl2glsl.RelWithDebInfo: /Volumes/MacDisk2/thirdlib/hlsl2glslfork/RelWithDebInfo/hlsl2glsltest
/Volumes/MacDisk2/thirdlib/hlsl2glslfork/RelWithDebInfo/hlsl2glsltest:\
	/Volumes/MacDisk2/thirdlib/hlsl2glslfork/RelWithDebInfo/libhlsl2glsl.a
	/bin/rm -f /Volumes/MacDisk2/thirdlib/hlsl2glslfork/RelWithDebInfo/hlsl2glsltest


