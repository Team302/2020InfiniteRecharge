#include <hw/DragonTalon.h>
#include <hw/DragonPDP.h>
#include <hw/usages/MotorControllerUsage.h>
#include <frc/PowerDistributionPanel.h>
#include <frc/SpeedController.h>
#include <memory>
#include <ctre/phoenix/motorcontrol/LimitSwitchType.h>


using namespace frc;
using namespace std;
using namespace ctre::phoenix::motorcontrol::can;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix;

DragonTalon::DragonTalon
(
	MotorControllerUsage::MOTOR_CONTROLLER_USAGE deviceType, 
	int deviceID, 
    int pdpID, 
	int countsPerRev, 
	double gearRatio 
) : m_talon( make_shared<WPI_TalonSRX>(deviceID)),
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

double DragonTalon::GetRotations() const
{
    return ((m_talon->GetSelectedSensorPosition() - m_tickOffset) / (double) m_countsPerRev) * m_gearRatio;
}

double DragonTalon::GetRPS() const
{
    return m_talon->GetSelectedSensorVelocity() / (double) m_countsPerRev;
}

void DragonTalon::SetControlMode(ControlModes::CONTROL_TYPE mode)
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
            // bad place to be
			printf("SCREAMIN!!!!!111 invalid controlmode set in DragonTalon SetControlMode\n");
        	m_controlMode = ctre::phoenix::motorcontrol::ControlMode::PercentOutput;
        	break;
    }
}

shared_ptr<SpeedController> DragonTalon::GetSpeedController() const
{
	return m_talon;
}

double DragonTalon::GetCurrent() const
{
	PowerDistributionPanel* pdp = DragonPDP::GetInstance()->GetPDP();
    return ( pdp != nullptr ) ? pdp->GetCurrent( m_pdp ) : 0.0;
}


void DragonTalon::Set(double value)
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

void DragonTalon::SetRotationOffset(double rotations)
{
    // m_tickOffset = (rotations * m_countsPerRev * m_gearRatio);
	double newRotations = -rotations + DragonTalon::GetRotations();
	m_tickOffset += (int) (newRotations * m_countsPerRev / m_gearRatio);
}

void DragonTalon::SetVoltageRamping(double ramping, double rampingClosedLoop)
{
    m_talon->ConfigOpenloopRamp(ramping);

	if (rampingClosedLoop >= 0)
	{
		m_talon->ConfigClosedloopRamp(rampingClosedLoop);
	}
}


void DragonTalon::EnableCurrentLimiting(bool enabled)
{
    m_talon->EnableCurrentLimit(enabled);
}

void DragonTalon::EnableBrakeMode(bool enabled)
{
    m_talon->SetNeutralMode(enabled ? ctre::phoenix::motorcontrol::NeutralMode::Brake : ctre::phoenix::motorcontrol::NeutralMode::Coast);
}

void DragonTalon::Invert(bool inverted)
{
    m_talon->SetInverted(inverted);
}

void DragonTalon::SetSensorInverted(bool inverted)
{
    m_talon->SetSensorPhase(inverted);
}

MotorControllerUsage::MOTOR_CONTROLLER_USAGE DragonTalon::GetType() const
{
	return m_type;
}

int DragonTalon::GetID() const
{
	return m_id;
}

//------------------------------------------------------------------------------
// Method:		SelectClosedLoopProfile
// Description:	Selects which profile slot to use for closed-loop control
// Returns:		void
//------------------------------------------------------------------------------
void DragonTalon::SelectClosedLoopProfile
(
	int	   slot,			// <I> - profile slot to select
	int    pidIndex			// <I> - 0 for primary closed loop, 1 for cascaded closed-loop
)
{
	m_talon->SelectProfileSlot( slot, pidIndex );
}


int DragonTalon::ConfigSelectedFeedbackSensor
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
//		printf( "DragonTalon::ConfigSelectedFeedbackSensor: m_talon not initialized \n" );
	}
	return error;
}

int DragonTalon::ConfigSelectedFeedbackSensor
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
//		printf( "DragonTalon::ConfigSelectedFeedbackSensor: m_talon not initialized \n" );
	}
	return error;
}

int DragonTalon::ConfigPeakCurrentLimit
(
	int amps,
	int timeoutMs
)
{
	int error = 0;
	if ( m_talon != nullptr )
	{
		error = m_talon->ConfigPeakCurrentLimit( amps, timeoutMs );
	}
	else
	{
//		printf( "DragonTalon::ConfigPeakCurrentLimit: m_talon not initialized \n" );
	}
	return error;
}

int DragonTalon::ConfigPeakCurrentDuration
(
	int milliseconds,
	int timeoutMs
)
{
	int error = 0;
	if ( m_talon != nullptr )
	{
		error = m_talon->ConfigPeakCurrentDuration( milliseconds, timeoutMs );
	}
	else
	{
//		printf( "DragonTalon::ConfigPeakCurrentDuration: m_talon not initialized \n" );
	}
	return error;
}

int DragonTalon::ConfigContinuousCurrentLimit
(
	int amps,
	int timeoutMs
)
{
	int error = 0;
	if ( m_talon != nullptr )
	{
		error = m_talon->ConfigContinuousCurrentLimit( amps, timeoutMs );
	}
	else
	{
//		printf( "DragonTalon::ConfigContinuousCurrentLimit: m_talon not initialized \n" );
	}
	return error;
}

void DragonTalon::SetAsSlave
(
    int         masterCANID         // <I> - master motor
)
{
    m_talon->Set( ControlMode::Follower, masterCANID );
}


/// @brief  Set the control constants (e.g. PIDF values).
/// @param [in] ControlData*   pid - the control constants
/// @return void
void DragonTalon::SetControlConstants(ControlData* controlInfo)
{
	
	m_talon->Config_kP(0, controlInfo->GetP());
    m_talon->Config_kI(0, controlInfo->GetI());
    m_talon->Config_kD(0, controlInfo->GetD());
    m_talon->Config_kF(0, controlInfo->GetF());

	int sensorUnitsPer100msPerSec = static_cast<int>( (controlInfo->GetMaxAcceleration() / 360.0) * (m_countsPerRev / 10.0) / m_gearRatio ) ;
	m_talon->ConfigMotionAcceleration( sensorUnitsPer100msPerSec );

	sensorUnitsPer100msPerSec = static_cast<int>( (controlInfo->GetCruiseVelocity() / 360.0) * (m_countsPerRev / 10.0) / m_gearRatio );
	m_talon->ConfigMotionCruiseVelocity( sensorUnitsPer100msPerSec, 0);

	auto peak = controlInfo->GetPeakValue();
	m_talon->ConfigPeakOutputForward(peak);
	m_talon->ConfigPeakOutputReverse(-1.0*peak);

	auto nom = controlInfo->GetNominalValue();
	m_talon->ConfigPeakOutputForward(nom);
	m_talon->ConfigPeakOutputReverse(-1.0*nom);
	
}

void DragonTalon::SetForwardLimitSwitch
( 
	bool normallyOpen
)
{
	LimitSwitchNormal type = normallyOpen ? LimitSwitchNormal::LimitSwitchNormal_NormallyOpen : LimitSwitchNormal::LimitSwitchNormal_NormallyClosed;
	m_talon->ConfigForwardLimitSwitchSource( LimitSwitchSource::LimitSwitchSource_FeedbackConnector, type, 0  );
}

void DragonTalon::SetReverseLimitSwitch
(
	bool normallyOpen
)
{
	LimitSwitchNormal type = normallyOpen ? LimitSwitchNormal::LimitSwitchNormal_NormallyOpen : LimitSwitchNormal::LimitSwitchNormal_NormallyClosed;
	m_talon->ConfigReverseLimitSwitchSource( LimitSwitchSource::LimitSwitchSource_FeedbackConnector, type, 0  );
}


