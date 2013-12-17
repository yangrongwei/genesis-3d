# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# For each target create a dummy rule so the target does not have to exist


# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.FreeType.Debug:
PostBuild.FreeType.Release:
PostBuild.FreeType.MinSizeRel:
PostBuild.FreeType.RelWithDebInfo:
