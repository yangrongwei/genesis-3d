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
#ifndef __APP_PhysicsDeclaration_H__
#define __APP_PhysicsDeclaration_H__

#ifdef min
#undef min
#undef max
#endif

#define NOMINMAX

namespace App
{
	enum PhysicsType
	{
		PHYSICSDYNAMIC = 1<<0,
		PHYSICSSTATIC = 1<<1,
		PHYSICSCONTROLLER = 1<<2,
		PHYSICSNONE = 1<<31
	};

	enum PhysicsForceType
	{
		Physics_Force,
		Physics_Impulse,
		Physics_VelocityChange,
	};

	enum PhyXShapeType
	{
		BOXSHAPE=0,
		CAPSULESHAPE,
		SPHERESHAPE,
		MESHSHAPE,
		CONVEXSHAPE,
		TERRAINSHAPE,
		PLANESHAPE,
		SHAPECOUNT,
		PRIMITIVE
	};

	enum ShapeFlag
	{
		eSIMULATION_SHAPE	 = (1<<0),
		eSCENE_QUERY_SHAPE	 = (1<<1),
		eTRIGGER_SHAPE		 = (1<<2),
		eVISUALIZATION		 = (1<<3),
		ePARTICLE_DRAIN		 = (1<<4),
		eUSE_SWEPT_BOUNDS	 = (1<<6),
	};
}

namespace physx
{
	class PxFoundation;
	class PxProfileZone;
	class PxProfileZoneManager;
	class PxPhysics;
	class PxCooking;
	class PxDefaultCpuDispatcher;
	class PxScene;
	class PxMaterial;
	class PxControllerManager;
	class PxShape;
	class PxGeometry;
	class PxHeightField;
	class PxRigidActor;
	class PxRigidBody;
	class PxRigidStatic;
	class PxRigidDynamic;
	class PxArticulationLink;
	class PxParticleBase;
	class PxParticleSystem;
	class PxParticleFluid;
	class PxTriangleMesh;
	class PxConvexMesh;
	class PxCloth;
	class PxController;
	class PxBoxController;
	class PxCapsuleController;
	class PxCapsuleControllerDesc;
	class PxUserControllerHitReport;
	namespace debugger{namespace comm{class PvdConnectionHandler; class PvdConnection;}	}
	namespace pxtask{ 
		class CudaContextManager;
	}
}

#endif
