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
#ifndef __PHYSX_COMMIT__
#include "stdneb.h"
#include "profilesystem/ProfileSystem.h"
#include "PhysicsFeature.h"
#include "physXfeature/physicsCore/PhysicsServer.h"
#include "basegamefeature/managers/timesource.h"

namespace App
{
	__ImplementClass(App::PhysicsFeature, 'PFAP' , App::Feature);
	__ImplementImageSingleton(App::PhysicsFeature);

PhysicsFeature::PhysicsFeature()
{
	__ConstructImageSingleton;

	mFeatureName = "Physics";
}

PhysicsFeature::~PhysicsFeature()
{
	__DestructImageSingleton;
}

void PhysicsFeature::OnActivate()
{
	Feature::OnActivate();

	m_PhysXServer = PhysicsServer::Create();

	m_PhysXServer->InitPhysXSDK();
	m_PhysXServer->InitScene();
#ifdef _DEBUG
	ConnectDebugger();
#endif
	
}

void PhysicsFeature::OnDeactivate()
{
	m_PhysXServer = NULL;

	Feature::OnDeactivate();
}

void PhysicsFeature::OnBeginFrame()
{
	PROFILER_ADDDTICKBEGIN(physicsTime);
	m_PhysXServer->Update( (float)GameTime::Instance()->GetFrameTime() );
	PROFILER_ADDDTICKEND(physicsTime);
}

void PhysicsFeature::OnFrame()
{
}

void PhysicsFeature::OnStart()
{
	EnableSimulate();
}

void PhysicsFeature::OnStop()
{
	DisableSimulate();
}

void PhysicsFeature::EnableSimulate()
{
	m_PhysXServer->EnablePhysicsSimulate();
}

void PhysicsFeature::DisableSimulate()
{
	m_PhysXServer->DisablePhysicsSimulate();
}
	
void PhysicsFeature::ConnectDebugger()
{
	//m_PhysXServer->ConnectToVRD();
}

}
#endif
