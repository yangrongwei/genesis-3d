# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# For each target create a dummy rule so the target does not have to exist
/Volumes/MacDisk2/thirdlib/mojoshader/Debug/libmojoshader.a:
/Volumes/MacDisk2/thirdlib/mojoshader/MinSizeRel/libmojoshader.a:
/Volumes/MacDisk2/thirdlib/mojoshader/RelWithDebInfo/libmojoshader.a:
/Volumes/MacDisk2/thirdlib/mojoshader/Release/libmojoshader.a:


# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.finderrors.Debug:
PostBuild.mojoshader.Debug: /Volumes/MacDisk2/thirdlib/mojoshader/Debug/finderrors
/Volumes/MacDisk2/thirdlib/mojoshader/Debug/finderrors:\
	/Volumes/MacDisk2/thirdlib/mojoshader/Debug/libmojoshader.a
	/bin/rm -f /Volumes/MacDisk2/thirdlib/mojoshader/Debug/finderrors


PostBuild.lemon.Debug:
/Volumes/MacDisk2/thirdlib/mojoshader/Debug/lemon:
	/bin/rm -f /Volumes/MacDisk2/thirdlib/mojoshader/Debug/lemon


PostBuild.mojoshader.Debug:
PostBuild.mojoshader-compiler.Debug:
PostBuild.mojoshader.Debug: /Volumes/MacDisk2/thirdlib/mojoshader/Debug/mojoshader-compiler
/Volumes/MacDisk2/thirdlib/mojoshader/Debug/mojoshader-compiler:\
	/Volumes/MacDisk2/thirdlib/mojoshader/Debug/libmojoshader.a
	/bin/rm -f /Volumes/MacDisk2/thirdlib/mojoshader/Debug/mojoshader-compiler


PostBuild.testoutput.Debug:
PostBuild.mojoshader.Debug: /Volumes/MacDisk2/thirdlib/mojoshader/Debug/testoutput
/Volumes/MacDisk2/thirdlib/mojoshader/Debug/testoutput:\
	/Volumes/MacDisk2/thirdlib/mojoshader/Debug/libmojoshader.a
	/bin/rm -f /Volumes/MacDisk2/thirdlib/mojoshader/Debug/testoutput


PostBuild.testparse.Debug:
PostBuild.mojoshader.Debug: /Volumes/MacDisk2/thirdlib/mojoshader/Debug/testparse
/Volumes/MacDisk2/thirdlib/mojoshader/Debug/testparse:\
	/Volumes/MacDisk2/thirdlib/mojoshader/Debug/libmojoshader.a
	/bin/rm -f /Volumes/MacDisk2/thirdlib/mojoshader/Debug/testparse


PostBuild.finderrors.Release:
PostBuild.mojoshader.Release: /Volumes/MacDisk2/thirdlib/mojoshader/Release/finderrors
/Volumes/MacDisk2/thirdlib/mojoshader/Release/finderrors:\
	/Volumes/MacDisk2/thirdlib/mojoshader/Release/libmojoshader.a
	/bin/rm -f /Volumes/MacDisk2/thirdlib/mojoshader/Release/finderrors


PostBuild.lemon.Release:
/Volumes/MacDisk2/thirdlib/mojoshader/Release/lemon:
	/bin/rm -f /Volumes/MacDisk2/thirdlib/mojoshader/Release/lemon


PostBuild.mojoshader.Release:
PostBuild.mojoshader-compiler.Release:
PostBuild.mojoshader.Release: /Volumes/MacDisk2/thirdlib/mojoshader/Release/mojoshader-compiler
/Volumes/MacDisk2/thirdlib/mojoshader/Release/mojoshader-compiler:\
	/Volumes/MacDisk2/thirdlib/mojoshader/Release/libmojoshader.a
	/bin/rm -f /Volumes/MacDisk2/thirdlib/mojoshader/Release/mojoshader-compiler


PostBuild.testoutput.Release:
PostBuild.mojoshader.Release: /Volumes/MacDisk2/thirdlib/mojoshader/Release/testoutput
/Volumes/MacDisk2/thirdlib/mojoshader/Release/testoutput:\
	/Volumes/MacDisk2/thirdlib/mojoshader/Release/libmojoshader.a
	/bin/rm -f /Volumes/MacDisk2/thirdlib/mojoshader/Release/testoutput


PostBuild.testparse.Release:
PostBuild.mojoshader.Release: /Volumes/MacDisk2/thirdlib/mojoshader/Release/testparse
/Volumes/MacDisk2/thirdlib/mojoshader/Release/testparse:\
	/Volumes/MacDisk2/thirdlib/mojoshader/Release/libmojoshader.a
	/bin/rm -f /Volumes/MacDisk2/thirdlib/mojoshader/Release/testparse


PostBuild.finderrors.MinSizeRel:
PostBuild.mojoshader.MinSizeRel: /Volumes/MacDisk2/thirdlib/mojoshader/MinSizeRel/finderrors
/Volumes/MacDisk2/thirdlib/mojoshader/MinSizeRel/finderrors:\
	/Volumes/MacDisk2/thirdlib/mojoshader/MinSizeRel/libmojoshader.a
	/bin/rm -f /Volumes/MacDisk2/thirdlib/mojoshader/MinSizeRel/finderrors


PostBuild.lemon.MinSizeRel:
/Volumes/MacDisk2/thirdlib/mojoshader/MinSizeRel/lemon:
	/bin/rm -f /Volumes/MacDisk2/thirdlib/mojoshader/MinSizeRel/lemon


PostBuild.mojoshader.MinSizeRel:
PostBuild.mojoshader-compiler.MinSizeRel:
PostBuild.mojoshader.MinSizeRel: /Volumes/MacDisk2/thirdlib/mojoshader/MinSizeRel/mojoshader-compiler
/Volumes/MacDisk2/thirdlib/mojoshader/MinSizeRel/mojoshader-compiler:\
	/Volumes/MacDisk2/thirdlib/mojoshader/MinSizeRel/libmojoshader.a
	/bin/rm -f /Volumes/MacDisk2/thirdlib/mojoshader/MinSizeRel/mojoshader-compiler


PostBuild.testoutput.MinSizeRel:
PostBuild.mojoshader.MinSizeRel: /Volumes/MacDisk2/thirdlib/mojoshader/MinSizeRel/testoutput
/Volumes/MacDisk2/thirdlib/mojoshader/MinSizeRel/testoutput:\
	/Volumes/MacDisk2/thirdlib/mojoshader/MinSizeRel/libmojoshader.a
	/bin/rm -f /Volumes/MacDisk2/thirdlib/mojoshader/MinSizeRel/testoutput


PostBuild.testparse.MinSizeRel:
PostBuild.mojoshader.MinSizeRel: /Volumes/MacDisk2/thirdlib/mojoshader/MinSizeRel/testparse
/Volumes/MacDisk2/thirdlib/mojoshader/MinSizeRel/testparse:\
	/Volumes/MacDisk2/thirdlib/mojoshader/MinSizeRel/libmojoshader.a
	/bin/rm -f /Volumes/MacDisk2/thirdlib/mojoshader/MinSizeRel/testparse


PostBuild.finderrors.RelWithDebInfo:
PostBuild.mojoshader.RelWithDebInfo: /Volumes/MacDisk2/thirdlib/mojoshader/RelWithDebInfo/finderrors
/Volumes/MacDisk2/thirdlib/mojoshader/RelWithDebInfo/finderrors:\
	/Volumes/MacDisk2/thirdlib/mojoshader/RelWithDebInfo/libmojoshader.a
	/bin/rm -f /Volumes/MacDisk2/thirdlib/mojoshader/RelWithDebInfo/finderrors


PostBuild.lemon.RelWithDebInfo:
/Volumes/MacDisk2/thirdlib/mojoshader/RelWithDebInfo/lemon:
	/bin/rm -f /Volumes/MacDisk2/thirdlib/mojoshader/RelWithDebInfo/lemon


PostBuild.mojoshader.RelWithDebInfo:
PostBuild.mojoshader-compiler.RelWithDebInfo:
PostBuild.mojoshader.RelWithDebInfo: /Volumes/MacDisk2/thirdlib/mojoshader/RelWithDebInfo/mojoshader-compiler
/Volumes/MacDisk2/thirdlib/mojoshader/RelWithDebInfo/mojoshader-compiler:\
	/Volumes/MacDisk2/thirdlib/mojoshader/RelWithDebInfo/libmojoshader.a
	/bin/rm -f /Volumes/MacDisk2/thirdlib/mojoshader/RelWithDebInfo/mojoshader-compiler


PostBuild.testoutput.RelWithDebInfo:
PostBuild.mojoshader.RelWithDebInfo: /Volumes/MacDisk2/thirdlib/mojoshader/RelWithDebInfo/testoutput
/Volumes/MacDisk2/thirdlib/mojoshader/RelWithDebInfo/testoutput:\
	/Volumes/MacDisk2/thirdlib/mojoshader/RelWithDebInfo/libmojoshader.a
	/bin/rm -f /Volumes/MacDisk2/thirdlib/mojoshader/RelWithDebInfo/testoutput


PostBuild.testparse.RelWithDebInfo:
PostBuild.mojoshader.RelWithDebInfo: /Volumes/MacDisk2/thirdlib/mojoshader/RelWithDebInfo/testparse
/Volumes/MacDisk2/thirdlib/mojoshader/RelWithDebInfo/testparse:\
	/Volumes/MacDisk2/thirdlib/mojoshader/RelWithDebInfo/libmojoshader.a
	/bin/rm -f /Volumes/MacDisk2/thirdlib/mojoshader/RelWithDebInfo/testparse


