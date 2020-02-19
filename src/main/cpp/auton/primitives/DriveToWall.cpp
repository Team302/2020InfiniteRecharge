
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
#include <subsys/MechanismFactory.h>
#include <controllers/ControlModes.h>
#include <subsys/IMechanism.h>
#include <utils/Logger.h>

// Third Party Includes


using namespace std;
using namespace frc;

//Includes
#include <cmath>
#include <iostream>

//Team302 includes
#include <auton/primitives/DriveToWall.h>
#include <subsys/ChassisFactory.h>
#include <subsys/IChassis.h>

DriveToWall::DriveToWall() :
	SuperDrive(),
	m_minimumTime(0),
	m_timeRemaining(0),
	m_underSpeedCounts(0)
{
}

void DriveToWall::Init(PrimitiveParams* params) 
{
	SuperDrive::Init(params);
	m_timeRemaining = params->GetTime();
	m_underSpeedCounts = 0;
	m_minimumTime = 0.3;
}

void DriveToWall::Run() 
{
	if (m_minimumTime <= 0) 
	{
		if (abs( ChassisFactory::GetChassisFactory()->GetIChassis()->GetCurrentSpeed()) < SPEED_THRESHOLD) 
		{
			m_underSpeedCounts++;
		}
	}

	m_minimumTime -= IPrimitive::LOOP_LENGTH;
	m_timeRemaining -= IPrimitive::LOOP_LENGTH;
}

bool DriveToWall::IsDone() 
{
	return (m_underSpeedCounts >= UNDER_SPEED_COUNT_THRESHOLD) && m_timeRemaining <= 0;
}

