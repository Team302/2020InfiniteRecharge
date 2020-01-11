
//====================================================================================================================================================
// Copyright 2019 Lake Orion Robotics FIRST Team 302
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================

// C++ Includes
#include <memory>
#include <string>

// FRC includes
#include <frc/Timer.h>

// Team 302 includes
#include <auton/primitives/DoNothing.h>
#include <auton/PrimitiveParams.h>
#include <auton/primitives/IPrimitive.h>
#include <subsys/ChassisFactory.h>
#include <controllers/ControlModes.h>
#include <subsys/IMechanism.h>
#include <utils/Logger.h>

// Third Party Includes


using namespace std;
using namespace frc;

//includes
#include <cmath>
#include <frc/SmartDashboard/SmartDashboard.h>
//team302 includes
#include <auton/primitives/HoldPosition.h>
#include <auton/PrimitiveParams.h>
#include <auton/PrimitiveFactory.h>
#include <auton/primitives/IPrimitive.h>
#include <subsys/MechanismFactory.h>

HoldPosition::HoldPosition() :
		m_chassis( ChassisFactory::GetChassisFactory()->GetIChassis()), //Get chassis from chassis factory
		m_timeRemaining(0.0)       //Value will be changed in init
{
}

void HoldPosition::Init(PrimitiveParams* params) {

	//Get timeRemaining from m_params
	m_timeRemaining = params->GetTime();
	/*
	m_chassis->SetTalonMode(DragonTalon::POSITION);
	m_chassis->EnableBrakeMode(true);

	//Set params
	m_chassis->SetVelocityParams(kP, kI, kD, kF, 0, 0);
	m_chassis->SetLeftRightMagnitudes(m_chassis->GetLeftMasterMotorRotationCount(), m_chassis->GetRightMasterMotorRotationCount());
	*/
}

void HoldPosition::Run() {
	//Decrement time remaining
	m_timeRemaining -= IPrimitive::LOOP_LENGTH;

}

bool HoldPosition::IsDone() {
	//Return true when the time runs out
	bool holdDone = ((m_timeRemaining <= (IPrimitive::LOOP_LENGTH / 2.0)));
//	return holdDone && m_placeCube->IsDone();
	return holdDone;
}
