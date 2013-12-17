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
# Build Paticles 
##################################################################################

#targets folder
SET ( TARGETS_HEADER_FILES 
	targets/particlebillboardtarget.h
	targets/particleBeamTarget.h
	targets/particleTrailTarget.h
	targets/particleEntityTarget.h
	targets/particleRibbonTrailTarget.h
	targets/particleDecalTarget.h
)

#targets folder
SET ( TARGETS_SOURCE_FILES
	targets/particlebillboardtargetserialization.cc
	targets/particlebillboardtarget.cc
	targets/particleTrailTargetSerialization.cc
	targets/particleTrailTarget.cc
	targets/particleBeamTargetSerialization.cc
	targets/particleBeamTarget.cc
	targets/particleEntityTargetSerialization.cc
	targets/particleEntityTarget.cc
	targets/particleRibbonTrailTarget.cc
	targets/particleRibbonTrailTargetSerialization.cc
	targets/particleDecalTarget.cc
	targets/particleDecalTargetserialization.cc
)

#affectors folder
SET ( AFFECTORS_HEADER_FILES 
	affectors/particleColorAffector.h
	affectors/particleFollowerAffector.h
	affectors/particleLinearForceAffector.h
	affectors/particleRandomiserAffector.h
	affectors/particleScaleAffector.h
	affectors/particleTextureRotatorAffector.h
	affectors/particleVortexAffector.h
	affectors/particleTextureAnimatorAffector.h
	affectors/particleGravityAffector.h
	affectors/particleLimitAffector.h
	affectors/particleMovementAffector.h
)

#affectors folder
SET ( AFFECTORS_SOURCE_FILES
	affectors/particleColorAffector.cc
	affectors/particleFollowerAffector.cc
	affectors/particleLinearForceAffector.cc
	affectors/particleRandomiserAffector.cc
	affectors/particleScaleAffector.cc
	affectors/particleTextureRotatorAffector.cc
	affectors/particleVortexAffector.cc
	affectors/particleTextureAnimatorAffector.cc
	affectors/particleColorAffectorSerialization.cc
	affectors/particleFollowerAffectorSerialization.cc
	affectors/particleLinearForceAffectorSerialization.cc
	affectors/particleRandomiserAffectorSerialization.cc
	affectors/particleScaleAffectorSerialization.cc	
	affectors/particleTextureAnimatorAffectorSerialization.cc
	affectors/particleTextureRotatorAffectorSerialization.cc
	affectors/particleVortexAffectorSerialization.cc
	affectors/particleGravityAffector.cc
	affectors/particleGravityAffectorSerialization.cc
	affectors/particleLimitAffector.cc
	affectors/particleLimitAffectorSerialization.cc
	affectors/particleMovementAffector.cpp
	affectors/particleMovementAffectorSerialization.cc
)

#emitters folder
SET ( EMITTERS_HEADER_FILES 
	emitters/particleBoxEmitter.h
	emitters/particlePointEmitter.h
	emitters/particleSphereSurfaceEmitter.h
	emitters/particleConeEmitter.h
	emitters/particleModelEmitter.h
)

#emitters folder
SET ( EMITTERS_SOURCE_FILES
	emitters/particleBoxEmitter.cc
	emitters/particlePointEmitter.cc
	emitters/particleSphereSurfaceEmitter.cc
	emitters/particleBoxEmitterSerialization.cc
	emitters/particlePointEmitterSerialization.cc
	emitters/particleSphereSurfaceEmitterSerialization.cc
	emitters/particleConeEmitter.cc
	emitters/particleConeEmitterSerialization.cc
	emitters/particleModelEmitter.cc
	emitters/particleModelEmitterSerialization.cc	
)

# folder
SET ( _HEADER_FILES 
	pool.h
	particletechnique.h
	particletarget.h
	particlesystem.h
	particleserver.h
	particlepool.h
	particlejob.h
	particleemitter.h
	particleaffector.h
	particle_fwd_decl.h
	particle.h
)

# folder
SET ( _SOURCE_FILES
	particletechniqueserialization.cc
	particletechnique.cc
	particletargetserialization.cc
	particletarget.cc
	particlesystemserialization.cc
	particlesystem.cc
	particleserverserialization.cc
	particleserver.cc
	particlepool.cc
	particlejob.cc
	particleemitterserialization.cc
	particleemitter.cc
	particleaffectorserialization.cc
	particleaffector.cc
	particle_classregistry.cc
	particle.cc
)

#<-------- Source Group ------------------>
SOURCE_GROUP( 
	targets
	FILES 
	${TARGETS_HEADER_FILES}
	${TARGETS_SOURCE_FILES}	
)
SOURCE_GROUP( 
	affectors
	FILES 
	${AFFECTORS_HEADER_FILES}
	${AFFECTORS_SOURCE_FILES}	
)
SOURCE_GROUP( 
	emitters
	FILES 
	${EMITTERS_HEADER_FILES}
	${EMITTERS_SOURCE_FILES}	
)
#<-------- Additional Include Directories ------------------>
INCLUDE_DIRECTORIES(
	#TODO:Make this clear and simple
	${CMAKE_SOURCE_DIR}/foundation
	${CMAKE_SOURCE_DIR}/rendersystem
	${CMAKE_SOURCE_DIR}/extlibs	
	${CMAKE_SOURCE_DIR}/extlibs/boostWraper

	# should remove later
	${CMAKE_SOURCE_DIR}/graphicsystem
	${CMAKE_SOURCE_DIR}/addons/
	${CMAKE_SOURCE_DIR}/
)

ADD_LIBRARY(
	Paticles 
	STATIC 
	#header
	${TARGETS_HEADER_FILES}
	${AFFECTORS_HEADER_FILES}
 	${EMITTERS_HEADER_FILES}
	${_HEADER_FILES}
	#source
	${TARGETS_SOURCE_FILES}
	${AFFECTORS_SOURCE_FILES}
	${EMITTERS_SOURCE_FILES}
	${_SOURCE_FILES}

 )

#Organize projects into folders
SET_PROPERTY(TARGET Paticles PROPERTY FOLDER "3.Addons")

#Compile properties
_MACRO_TREAT_WARRINGS_AS_ERRORS( Paticles )
