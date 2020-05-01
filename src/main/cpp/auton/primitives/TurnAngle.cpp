
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
#include <algorithm>
#include <cmath>
#include <memory>
#include <string>

// FRC includes
#include <frc/Timer.h>

// Team 302 includes
#include <auton/primitives/TurnAngle.h>
#include <auton/PrimitiveParams.h>
#include <auton/primitives/IPrimitive.h>
#include <subsys/ChassisFactory.h>
#include <controllers/ControlModes.h>
#include <subsys/IChassis.h>
#include <utils/Logger.h>
#include <hw/factories/PigeonFactory.h>
#include <hw/DragonPigeon.h>

// Third Party Includes


using namespace std;
using namespace frc;

//Team302 includes

TurnAngle::TurnAngle() : m_chassis( ChassisFactory::GetChassisFactory()->GetIChassis()),
						 m_timer( make_unique<Timer>() ),
						 m_targetAngle(0.0),
						 m_maxTime(0.0),
						 m_leftPos(0.0),
						 m_rightPos(0.0),
						 m_isDone(false)
{
}

void TurnAngle::Init(PrimitiveParams* params) 
{
	m_isDone = false;
	auto pigeon = PigeonFactory::GetFactory()->GetPigeon();
	if ( pigeon != nullptr )
	{
		auto startHeading = pigeon->GetYaw();
		m_targetAngle = startHeading + params->GetHeading();
	}


	/**
	auto cd = make_shared<ControlData>( ControlModes::CONTROL_TYPE::POSITION_INCH, 
									ControlModes::CONTROL_RUN_LOCS::MOTOR_CONTROLLER,
									string("TurnAngle"),
									3.0,
									0.0,
									0.0,
									0.0,
									0.0,
									0.0,
									0.0,
									1.0,
									0.0   );
									**/
	//m_chassis->SetControlConstants( cd.get() );

	// todo re-work
	/*
	m_chassis->SetTalonMode(DragonTalon::POSITION); 													//Set the talon mode to position
	m_targetAngle = m_chassis->GetTargetHeading() + params->GetHeading();								//Set the target angle to the current angle plus the heading param
	m_chassis->SetTargetHeading(m_targetAngle);															//Set the internal chassis target heading to the target heading

	m_leftPos = m_chassis->GetLeftMasterMotorRotationCount();											//init left and right position to the current wheel positions
	m_rightPos = m_chassis->GetRightMasterMotorRotationCount();

	m_maxTimeout = 99999;																					//Initialize the

	m_chassis->SetPIDParams(PROPORTIONAL_COEFF, INTREGRAL_COEFF, DERIVATIVE_COEFF, FEET_FORWARD_COEFF); //Set parameters
	*/
	m_maxTime = params->GetTime();
	m_timer->Reset();
	m_timer->Start();
}

void TurnAngle::Run() //best method ever. Does nothing, and should do nothing... NOT ANYMORE, BUDDY!
{
	auto heading = 0.0;
	auto pigeon = PigeonFactory::GetFactory()->GetPigeon();
	if ( pigeon != nullptr )
	{
		heading = pigeon->GetYaw();
	}

	float deltaAngle = m_targetAngle - heading;

	bool sign = deltaAngle > 0;
	double leftSpeed;
	double rightSpeed;

	if(!sign)
	{
		leftSpeed = .2 * deltaAngle / m_targetAngle + .03;
		rightSpeed = -leftSpeed;
	}
	else
	{
		rightSpeed = .2 * deltaAngle / m_targetAngle + .03;
		leftSpeed = -rightSpeed;
	}
	
	m_chassis->SetOutput(ControlModes::PERCENT_OUTPUT, leftSpeed, rightSpeed);

	/*float velocity = deltaAngle * ANGLE_DIFFERENCE_VELOCITY_MULTIPLIER;
	bool sign = velocity > 0;	//Store sign of velocity as positive = true
	velocity = clamp(abs(velocity), MIN_VELOCITY, MAX_VELOCITY);
	if (!sign)  				//If the sign was negative...
	{
		velocity = -velocity; 	//... make it negative again :)
	}

	m_leftPos  += (velocity * 0.02) / (m_chassis->GetWheelDiameter() * M_PI);
	m_rightPos -= (velocity * 0.02) / (m_chassis->GetWheelDiameter() * M_PI);

	//m_chassis->SetLeftRightMagnitudes(m_leftPos, m_rightPos);
	m_chassis->SetOutput( ControlModes::CONTROL_TYPE::POSITION_INCH, m_leftPos, m_rightPos );
	*/
}

bool TurnAngle::IsDone() 
{
	if (!m_isDone) 
	{
		auto heading = 0.0;
		auto pigeon = PigeonFactory::GetFactory()->GetPigeon();
		if ( pigeon != nullptr )
		{
			heading = pigeon->GetYaw();
		}
		float absDeltaAngle = abs(m_targetAngle - heading);
		if (absDeltaAngle < ANGLE_THRESH) {
			m_isDone = true;
			m_chassis->SetOutput( ControlModes::PERCENT_OUTPUT, 0.0, 0.0 );
			//m_chassis->SetTalonMode(DragonTalon::PERCENT);
			//m_chassis->SetLeftRightMagnitudes(0, 0);
		}
	}
	return m_isDone; //|| m_timer->HasPeriodPassed( m_maxTime );
}
