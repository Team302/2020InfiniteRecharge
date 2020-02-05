
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
#include <vector>

// FRC includes
#include <frc/PowerDistributionPanel.h>
#include <frc/SpeedController.h>

// Team 302 includes
#include <hw/DragonFalcon.h>
#include <hw/DragonPDP.h>
#include <hw/usages/MotorControllerUsage.h>
#include <utils/Logger.h>

// Third Party Includes
#include <ctre/phoenix/motorcontrol/can/WPI_TalonFX.h>


using namespace frc;
using namespace std;
using namespace ctre::phoenix;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;

DragonFalcon::DragonFalcon
(
	MotorControllerUsage::MOTOR_CONTROLLER_USAGE deviceType, 
	int deviceID, 
    int pdpID, 
	int countsPerRev, 
	double gearRatio 
) : m_talon( make_shared<WPI_TalonFX>(deviceID)),
	m_controlMode(ctre::phoenix::motorcontrol::ControlMode::PercentOutput),
	m_type(deviceType),
	m_id(deviceID),
	m_pdp( pdpID ),
	m_countsPerRev(countsPerRev),
	m_tickOffset(0),
	m_gearRatio(gearRatio)
{
	// m_tickOffset
	// m_talon->GetSelectedSensorPo
	m_tickOffset = m_talon->GetSelectedSensorPosition();
}

double DragonFalcon::GetRotations() const
{
    return ((m_talon->GetSelectedSensorPosition() - m_tickOffset) / (double) m_countsPerRev) * m_gearRatio;
}

double DragonFalcon::GetRPS() const
{
    return m_talon->GetSelectedSensorVelocity() / (double) m_countsPerRev;
}

void DragonFalcon::SetControlMode(ControlModes::CONTROL_TYPE mode)
{ 
    switch (mode)
    {
        case ControlModes::CONTROL_TYPE::PERCENT_OUTPUT:
		case ControlModes::CONTROL_TYPE::VOLTAGE:
            m_controlMode = ctre::phoenix::motorcontrol::ControlMode::PercentOutput;
        	break;

        case ControlModes::CONTROL_TYPE::POSITION_DEGREES:
        case ControlModes::CONTROL_TYPE::POSITION_INCH:
            m_controlMode = ctre::phoenix::motorcontrol::ControlMode::Position;
        	break;
        
        case ControlModes::CONTROL_TYPE::VELOCITY_DEGREES:
        case ControlModes::CONTROL_TYPE::VELOCITY_INCH:
            m_controlMode = ctre::phoenix::motorcontrol::ControlMode::Velocity;
        	break;

		case ControlModes::CONTROL_TYPE::CURRENT:
			m_controlMode = ctre::phoenix::motorcontrol::ControlMode::Current;
			break;

		case ControlModes::CONTROL_TYPE::MOTION_PROFILE:
			m_controlMode = ctre::phoenix::motorcontrol::ControlMode::MotionProfile;
			break;

		case ControlModes::CONTROL_TYPE::MOTION_PROFILE_ARC:
			m_controlMode = ctre::phoenix::motorcontrol::ControlMode::MotionProfileArc;
			break;

		case ControlModes::CONTROL_TYPE::TRAPEZOID:
			m_controlMode = ctre::phoenix::motorcontrol::ControlMode::MotionMagic;
			break;

        default:
            Logger::GetLogger()->LogError( string("DragonFalcon::SetControlMode"), string("Invalid Control Mode"));
        	m_controlMode = ctre::phoenix::motorcontrol::ControlMode::PercentOutput;
        	break;
    }
}

shared_ptr<SpeedController> DragonFalcon::GetSpeedController() const
{
	return m_talon;
}

double DragonFalcon::GetCurrent() const
{
	PowerDistributionPanel* pdp = DragonPDP::GetInstance()->GetPDP();
    return ( pdp != nullptr ) ? pdp->GetCurrent( m_pdp ) : 0.0;
}


void DragonFalcon::Set(double value)
{
    switch (m_controlMode)
    {
        case ctre::phoenix::motorcontrol::ControlMode::PercentOutput:
			m_talon->Set( m_controlMode, value );
			break;

        case ctre::phoenix::motorcontrol::ControlMode::Position:
			m_talon->Set(m_controlMode, (value * m_countsPerRev / m_gearRatio) + m_tickOffset);
        	break;

        case ctre::phoenix::motorcontrol::ControlMode::Velocity:
            m_talon->Set(m_controlMode, value * m_gearRatio / 600.0);
        	break;
			
		case ctre::phoenix::motorcontrol::ControlMode::Current:
            m_talon->Set(m_controlMode, value );
        	break;

		case ctre::phoenix::motorcontrol::ControlMode::MotionProfile:
			m_talon->Set(m_controlMode, value );
			break;

		case ctre::phoenix::motorcontrol::ControlMode::MotionProfileArc:
			m_talon->Set(m_controlMode, value );
			break;

		case ctre::phoenix::motorcontrol::ControlMode::MotionMagic:
            m_talon->Set(m_controlMode, (value * m_countsPerRev / m_gearRatio) + m_tickOffset);
        break;

        default:
            m_talon->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
        break;
    }
}

void DragonFalcon::SetRotationOffset(double rotations)
{
    // m_tickOffset = (rotations * m_countsPerRev * m_gearRatio);
	double newRotations = -rotations + DragonFalcon::GetRotations();
	m_tickOffset += (int) (newRotations * m_countsPerRev / m_gearRatio);
}

void DragonFalcon::SetVoltageRamping(double ramping, double rampingClosedLoop)
{
    m_talon->ConfigOpenloopRamp(ramping);

	if (rampingClosedLoop >= 0)
	{
		m_talon->ConfigClosedloopRamp(rampingClosedLoop);
	}
}


void DragonFalcon::EnableCurrentLimiting(bool enabled)
{
//    m_talon->Enable(enabled);
}

void DragonFalcon::EnableBrakeMode(bool enabled)
{
    m_talon->SetNeutralMode(enabled ? ctre::phoenix::motorcontrol::NeutralMode::Brake : ctre::phoenix::motorcontrol::NeutralMode::Coast);
}

void DragonFalcon::Invert(bool inverted)
{
    m_talon->SetInverted(inverted);
}

void DragonFalcon::SetSensorInverted(bool inverted)
{
    m_talon->SetSensorPhase(inverted);
}

MotorControllerUsage::MOTOR_CONTROLLER_USAGE DragonFalcon::GetType() const
{
	return m_type;
}

int DragonFalcon::GetID() const
{
	return m_id;
}

//------------------------------------------------------------------------------
// Method:		SelectClosedLoopProfile
// Description:	Selects which profile slot to use for closed-loop control
// Returns:		void
//------------------------------------------------------------------------------
void DragonFalcon::SelectClosedLoopProfile
(
	int	   slot,			// <I> - profile slot to select
	int    pidIndex			// <I> - 0 for primary closed loop, 1 for cascaded closed-loop
)
{
	m_talon->SelectProfileSlot( slot, pidIndex );
}

int DragonFalcon::ConfigSelectedFeedbackSensor
(
	FeedbackDevice feedbackDevice,
	int pidIdx,
	int timeoutMs
)
{
	int error = 0;
	if ( m_talon != nullptr )
	{
		error = m_talon->ConfigSelectedFeedbackSensor( feedbackDevice, pidIdx, timeoutMs );
	}
	else
	{
        Logger::GetLogger()->LogError( string("DragonFalcon::ConfigSelectedFeedbackSensor"), string("m_talon is a nullptr"));
	}
	return error;
}

int DragonFalcon::ConfigSelectedFeedbackSensor
(
	RemoteFeedbackDevice feedbackDevice,
	int pidIdx,
	int timeoutMs
)
{
	int error = 0;
	if ( m_talon != nullptr )
	{
		error = m_talon->ConfigSelectedFeedbackSensor( feedbackDevice, pidIdx, timeoutMs );
	}
	else
	{
        Logger::GetLogger()->LogError( string("DragonFalcon::ConfigSelectedFeedbackSensor"), string("m_talon is a nullptr"));
	}
	return error;
}

int DragonFalcon::ConfigPeakCurrentLimit
(
	int amps,
	int timeoutMs
)
{
	int error = 0;
	if ( m_talon != nullptr )
	{
        // todo need to contruct other objects
		//error = m_talon->ConfigStatorCurrentLimit( amps, timeoutMs );
        //error = m_talon->ConfigSupplyCurrentLimit( amps, timeoutMs );
	}
	else
	{
        Logger::GetLogger()->LogError( string("DragonFalcon::ConfigPeakCurrentLimit"), string("m_talon is a nullptr"));
	}
	return error;
}

int DragonFalcon::ConfigPeakCurrentDuration
(
	int milliseconds,
	int timeoutMs
)
{
	int error = 0;
	if ( m_talon != nullptr )
	{
		//error = m_talon->ConfigPeakCurrentDuration( milliseconds, timeoutMs );
	}
	else
	{
        Logger::GetLogger()->LogError( string("DragonFalcon::ConfigPeakCurrentDuration"), string("m_talon is a nullptr"));
	}
	return error;
}

int DragonFalcon::ConfigContinuousCurrentLimit
(
	int amps,
	int timeoutMs
)
{
	int error = 0;
	if ( m_talon != nullptr )
	{
	//	error = m_talon->ConfigContinuousCurrentLimit( amps, timeoutMs );
	}
	else
	{
        Logger::GetLogger()->LogError( string("DragonFalcon::ConfigContinuousCurrentLimit"), string("m_talon is a nullptr"));
	}
	return error;
}

void DragonFalcon::SetAsSlave
(
    int         masterCANID         // <I> - master motor
)
{
    m_talon->Set( ControlMode::Follower, masterCANID );
}


/// @brief  Set the control constants (e.g. PIDF values).
/// @param [in] ControlData*   pid - the control constants
/// @return void
void DragonFalcon::SetControlConstants(ControlData* controlInfo)
{
	m_talon->Config_kP(0, controlInfo->GetP());
    m_talon->Config_kI(0, controlInfo->GetI());
    m_talon->Config_kD(0, controlInfo->GetD());
    m_talon->Config_kF(0, controlInfo->GetF());
}

void DragonFalcon::SetForwardLimitSwitch
( 
	bool normallyOpen
)
{
	LimitSwitchNormal type = normallyOpen ? LimitSwitchNormal::LimitSwitchNormal_NormallyOpen : LimitSwitchNormal::LimitSwitchNormal_NormallyClosed;
	m_talon->ConfigForwardLimitSwitchSource( LimitSwitchSource::LimitSwitchSource_FeedbackConnector, type, 0  );
}

void DragonFalcon::SetReverseLimitSwitch
(
	bool normallyOpen
)
{
	LimitSwitchNormal type = normallyOpen ? LimitSwitchNormal::LimitSwitchNormal_NormallyOpen : LimitSwitchNormal::LimitSwitchNormal_NormallyClosed;
	m_talon->ConfigReverseLimitSwitchSource( LimitSwitchSource::LimitSwitchSource_FeedbackConnector, type, 0  );
}


