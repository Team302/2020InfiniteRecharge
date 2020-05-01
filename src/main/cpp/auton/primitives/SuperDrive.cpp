
//====================================================================================================================================================
// Copyright 2020 Lake Orion Robotics FIRST Team 302
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
#include <auton/PrimitiveParams.h>
#include <auton/primitives/IPrimitive.h>
#include <auton/primitives/SuperDrive.h>
#include <controllers/ControlData.h>
#include <controllers/ControlModes.h>
#include <hw/factories/PigeonFactory.h>
#include <subsys/ChassisFactory.h>

// Third Party Includes


using namespace std;
using namespace frc;


SuperDrive::SuperDrive() : m_chassis( ChassisFactory::GetChassisFactory()->GetIChassis()),
						   m_timer( make_unique<Timer>() ),
						   m_targetSpeed(0),
						   m_currentSpeed(0),
						   m_speedOffset(0),
						   m_leftSpeed(0),
						   m_rightSpeed(0),
						   m_currentHeading(0),
						   m_startHeading(0),
						   m_slowingDown(false),
						   m_reachedTargetSpeed(false),
						   m_accelDecelTime(0),
						   m_currentTime(0),
						   m_minSpeedSlowdown(0)
{
}

void SuperDrive::Init(PrimitiveParams* params) 
{
	m_targetSpeed = params->GetDriveSpeed();
	m_leftSpeed = params->GetDriveSpeed();
	m_rightSpeed = params->GetDriveSpeed();

	if (params->GetEndDriveSpeed() > MIN_SPEED_SLOWDOWN) 
	{
		m_minSpeedSlowdown = params->GetEndDriveSpeed();
	}
	else 
	{
		m_minSpeedSlowdown = MIN_SPEED_SLOWDOWN;
	}

	//Reset some variables
	m_currentTime = 0;
	m_slowingDown = false;
	m_reachedTargetSpeed = false;
	m_accelDecelTime = 0;

	m_currentSpeed = m_chassis->GetCurrentSpeed();

	//Double check that the current speed matches the sign of the target speed (if not, thats bad. make it 0)
	if (m_targetSpeed > 0) 
	{
		if (m_currentSpeed < 0) 
		{
			m_currentSpeed = 0;
		}
	} 
	else 
	{ //target speed negative
		if (m_currentSpeed > 0)
		{
			m_currentSpeed = 0;
		}
	}

	//m_startHeading = m_chassis->GetHeading();
	m_startHeading = 0.0;
	auto pigeon = PigeonFactory::GetFactory()->GetPigeon();
	if ( pigeon != nullptr )
	{
		m_startHeading = pigeon->GetYaw();
	}
	/**
	auto cd = make_shared<ControlData>( ControlModes::CONTROL_TYPE::PERCENT_OUTPUT, 
							   			ControlModes::CONTROL_RUN_LOCS::MOTOR_CONTROLLER,
							   			string("SuperDrive"),
							   			12.0,
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
	m_leftSpeed = m_targetSpeed > 0.0 ? 0.2 : -0.2;
	m_rightSpeed = m_targetSpeed > 0.0 ? 0.2 : -0.2;
	m_chassis->SetOutput( ControlModes::CONTROL_TYPE::PERCENT_OUTPUT, m_leftSpeed, m_rightSpeed );

    //m_chassis->SetVelocityParams(PROPORTIONAL_COEFF, INTREGRAL_COEFF, DERIVATIVE_COEFF, FEET_FORWARD_COEFF,
    //		m_leftSpeed, m_rightSpeed);

    m_speedOffset = m_targetSpeed > 0.0 ? GYRO_CORRECTION_CONSTANT : -GYRO_CORRECTION_CONSTANT;
}

void SuperDrive::Run() 
{
	auto pigeon = PigeonFactory::GetFactory()->GetPigeon();
	if ( pigeon != nullptr )
	{
		m_currentHeading = pigeon->GetYaw() - m_startHeading;
	}
	//m_currentHeading = m_chassis->GetHeading() - m_chassis->GetTargetHeading(); //Calculate target heading

	//Calculate ramp up speed if we are not already slowing down
	/*
	if (!m_slowingDown) 
	{
		if (std::abs(m_currentSpeed) < std::abs(m_targetSpeed)) 
		{
			if (m_targetSpeed > 0) 
			{
				m_currentSpeed += INCHES_PER_SECOND_SECOND * IPrimitive::LOOP_LENGTH;
			} else 
			{
				m_currentSpeed -= INCHES_PER_SECOND_SECOND * IPrimitive::LOOP_LENGTH;
			}
		} 
		else 
		{
			m_currentSpeed = m_targetSpeed;
			if (!m_reachedTargetSpeed)
			{
				m_accelDecelTime = m_currentTime;
			}
			m_reachedTargetSpeed = true;
		}
	} 
	else 
	{
		if (!m_reachedTargetSpeed)
		{
			m_accelDecelTime = m_currentTime;
		}
		m_reachedTargetSpeed = true;

		if (m_currentSpeed > 0) 
		{
			if (m_currentSpeed > m_minSpeedSlowdown) 
			{
				m_currentSpeed -= INCHES_PER_SECOND_SECOND * IPrimitive::LOOP_LENGTH;
			} 
			else 
			{
				m_currentSpeed = m_minSpeedSlowdown;
			}
		} 
		else 
		{
			//current speed is negative
			if (m_currentSpeed < -m_minSpeedSlowdown) 
			{
				m_currentSpeed += INCHES_PER_SECOND_SECOND * IPrimitive::LOOP_LENGTH;
			} 
			else 
			{
				m_currentSpeed = -m_minSpeedSlowdown;
			}
		}
	}
	*/

	m_rightSpeed = m_currentSpeed;
	m_leftSpeed = m_currentSpeed;

	m_leftSpeed -= m_currentHeading * GYRO_CORRECTION_CONSTANT;
	m_rightSpeed += m_currentHeading * GYRO_CORRECTION_CONSTANT;

	m_chassis->SetOutput( ControlModes::CONTROL_TYPE::PERCENT_OUTPUT, m_leftSpeed, m_rightSpeed );

	//m_chassis->SetVelocityParams(PROPORTIONAL_COEFF, INTREGRAL_COEFF, DERIVATIVE_COEFF, FEET_FORWARD_COEFF, m_leftSpeed, m_rightSpeed);

	m_currentTime += IPrimitive::LOOP_LENGTH;
}

bool SuperDrive::IsDone() 
{
	return false;
}

void SuperDrive::SlowDown() 
{
	m_slowingDown = true;
}

bool SuperDrive::ReachedTargetSpeed() 
{
	return m_reachedTargetSpeed;
}

