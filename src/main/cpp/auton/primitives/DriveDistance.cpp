
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

//Includes
#include <cmath>
#include <frc/SmartDashboard/SmartDashboard.h>

//Team302 includes
#include <auton/primitives/DriveDistance.h>
#include <subsys/MechanismFactory.h>
#include <subsys/IChassis.h>
#include <hw/factories/PigeonFactory.h>
#include <hw/DragonPigeon.h>
#include <utils/Logger.h>

DriveDistance::DriveDistance() :
	SuperDrive(),
	m_params(nullptr),
	m_targetDistance(0),
	m_initialDistance(0),
	m_timeRemaining(0),
	m_minSpeedCountTime(0), //will be changed in init
	m_underSpeedCounts(0),
	m_startHeading(0),
	m_endHeading(0),
	m_minSpeed(0),
	m_arcing(false)
{
}

void DriveDistance::Init(PrimitiveParams* params) 
{
	SuperDrive::Init(params);
	
	m_arcing = abs(params->GetHeading()) > 0.1;
	//m_startHeading =  ChassisFactory::GetChassisFactory()->GetIChassis()->GetTargetHeading();
	m_endHeading = m_startHeading + params->GetHeading();

	m_minSpeedCountTime = MIN_SPEED_COUNT_TIME;
	m_underSpeedCounts = 0;
	m_params = params;
	//Get parameters from params
	m_targetDistance = params->GetDistance();
	m_initialDistance =  ChassisFactory::GetChassisFactory()->GetIChassis()->GetCurrentPosition();
	frc::SmartDashboard::PutNumber("Initial Distance", m_initialDistance);
}

void DriveDistance::Run() 
{
	Logger::GetLogger() -> LogError(string("DriveDistance::Run()"), string("Arrived!"));
	SuperDrive::Run();

	//if (m_arcing)
	//{
		//Calculate progress from 0 to 1
		//float progress = abs( ChassisFactory::GetChassisFactory()->GetIChassis()->GetCurrentPosition() - m_initialDistance);
		//progress /= abs(m_targetDistance); //progress = progress / targetDistance

		//float newTargetHeading = 0;
		//Linear interpolation between start heading and end heading based on progress
		//newTargetHeading += (1.0 - progress) * m_startHeading;// newTargetheading = newTargetHeading + (1.0 - progress) * m_startHeading
		//newTargetHeading += (progress) * m_endHeading;
		//ChassisFactory::GetChassisFactory()->GetIChassis()->SetTargetHeading(newTargetHeading);
	//}


	CalculateSlowDownDistance();

	if (m_minSpeedCountTime <= 0) 
	{
		if (abs( ChassisFactory::GetChassisFactory()->GetIChassis()->GetCurrentSpeed()) < SPEED_THRESHOLD) 
		{
			m_underSpeedCounts++;
		}
	}
	m_minSpeedCountTime -= IPrimitive::LOOP_LENGTH;
}

bool DriveDistance::IsDone() 
{
	float progress =  ChassisFactory::GetChassisFactory()->GetIChassis()->GetCurrentPosition() - m_initialDistance;
	bool reachedTarget = abs(progress) > abs(m_targetDistance);
	frc::SmartDashboard::PutNumber("current chassis dist", progress);
	frc::SmartDashboard::PutNumber("Target chassis distance", m_targetDistance);
	m_timeRemaining -= IPrimitive::LOOP_LENGTH;

	//bool notMoving = m_underSpeedCounts >= UNDER_SPEED_COUNT_THRESHOLD;
	bool done = reachedTarget;
	if (done) 
	{
		 //ChassisFactory::GetChassisFactory()->GetIChassis()->SetTargetHeading(m_endHeading);
	}
	return done;
}

void DriveDistance::CalculateSlowDownDistance() 
{

	float currentVel =  ChassisFactory::GetChassisFactory()->GetIChassis()->GetCurrentSpeed();
	float decelTime = currentVel / SuperDrive::INCHES_PER_SECOND_SECOND;
	float decelDist = abs(((currentVel - m_minSpeed)) * decelTime * DECEL_TIME_MULTIPLIER);
	float currentDistance = abs( ChassisFactory::GetChassisFactory()->GetIChassis()->GetCurrentPosition() - m_initialDistance);
	float distanceRemaining = abs(m_targetDistance - currentDistance);

	if (distanceRemaining <= decelDist)
	{
		SuperDrive::SlowDown();
	}
}

void DriveDistance::SetDistance
(
    double distance
)
{
    m_targetDistance = distance;
}

