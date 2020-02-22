#include <hw/DragonTalon.h>
#include <hw/DragonPDP.h>
#include <hw/usages/MotorControllerUsage.h>
#include <frc/PowerDistributionPanel.h>
#include <frc/SpeedController.h>
#include <memory>
#include <ctre/phoenix/motorcontrol/LimitSwitchType.h>
#include <utils/ConversionUtils.h>
#include <utils/Logger.h>
#include <frc/smartdashboard/SmartDashboard.h>


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
	m_controlMode(ControlModes::CONTROL_TYPE::PERCENT_OUTPUT),
	m_type(deviceType),
	m_id(deviceID),
	m_pdp( pdpID ),
	m_countsPerRev(countsPerRev),
	m_tickOffset(0),
	m_gearRatio(gearRatio),
	m_diameter( 1.0 )
{
	//m_tickOffset = m_talon.get()->GetSelectedSensorPosition();
}

double DragonTalon::GetRotations() const
{
	return (ConversionUtils::CountsToRevolutions( (m_talon.get()->GetSelectedSensorPosition()), m_countsPerRev) * m_gearRatio);
}

double DragonTalon::GetRPS() const
{
	return (ConversionUtils::CountsPer100msToRPS( m_talon.get()->GetSelectedSensorVelocity(), m_countsPerRev) * m_gearRatio);
}

void DragonTalon::SetControlMode(ControlModes::CONTROL_TYPE mode)
{ 
	m_controlMode = mode;
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
	auto output = value;
	ctre::phoenix::motorcontrol::ControlMode ctreMode = ctre::phoenix::motorcontrol::ControlMode::PercentOutput;
    switch (m_controlMode)
    {
        case ControlModes::CONTROL_TYPE::PERCENT_OUTPUT:
			ctreMode = ctre::phoenix::motorcontrol::ControlMode::PercentOutput;
			output = value;
			break;
			
			
		case ControlModes::CONTROL_TYPE::VOLTAGE:
			ctreMode = ctre::phoenix::motorcontrol::ControlMode::PercentOutput;
			output = value;
			break;

        case ControlModes::CONTROL_TYPE::POSITION_DEGREES:
			ctreMode = ctre::phoenix::motorcontrol::ControlMode::Position;
			output = (ConversionUtils::DegreesToCounts(value,m_countsPerRev) / m_gearRatio);
			frc::SmartDashboard::PutNumber("Target counts", output);
			break;
        case ControlModes::CONTROL_TYPE::POSITION_INCH:
            ctreMode = ctre::phoenix::motorcontrol::ControlMode::Position;
			output = (ConversionUtils::ConversionUtils::InchesToCounts(value, m_countsPerRev, m_diameter) / m_gearRatio);
        	break;
        
        case ControlModes::CONTROL_TYPE::VELOCITY_DEGREES:
            ctreMode = ctre::phoenix::motorcontrol::ControlMode::Velocity;
			output = (ConversionUtils::DegreesPerSecondToCounts100ms( value, m_countsPerRev ) / m_gearRatio);
        	break;

        case ControlModes::CONTROL_TYPE::VELOCITY_INCH:
            ctreMode = ctre::phoenix::motorcontrol::ControlMode::Velocity;
			output = (ConversionUtils::InchesPerSecondToCounts100ms( value, m_countsPerRev, m_diameter ) / m_gearRatio);
        	break;

		case ControlModes::CONTROL_TYPE::VELOCITY_RPS:
            ctreMode = ctre::phoenix::motorcontrol::ControlMode::Velocity;
			output = (ConversionUtils::RPSToCounts100ms( value, m_countsPerRev ) / m_gearRatio);
			frc::SmartDashboard::PutNumber("output val", output);
        	break;

		case ControlModes::CONTROL_TYPE::CURRENT:
			ctreMode = ctre::phoenix::motorcontrol::ControlMode::Current;
			output = value;
			break;

		case ControlModes::CONTROL_TYPE::MOTION_PROFILE:
			ctreMode = ctre::phoenix::motorcontrol::ControlMode::MotionProfile;
			output = value;
			break;

		case ControlModes::CONTROL_TYPE::MOTION_PROFILE_ARC:
			ctreMode = ctre::phoenix::motorcontrol::ControlMode::MotionProfileArc;
			output = value;
			break;

		case ControlModes::CONTROL_TYPE::TRAPEZOID:
			ctreMode = ctre::phoenix::motorcontrol::ControlMode::MotionMagic;
			output = (ConversionUtils::InchesToCounts(value, m_countsPerRev, m_diameter) / m_gearRatio);
			break;

        default:
            Logger::GetLogger()->LogError( string("DragonTalon::SetControlMode"), string("Invalid Control Mode"));
        	ctreMode = ctre::phoenix::motorcontrol::ControlMode::PercentOutput;
			output = value;
        	break;
    }	

	m_talon.get()->Set( ctreMode, output );
}

void DragonTalon::SetRotationOffset(double rotations)
{
//	double newRotations = -rotations + DragonTalon::GetRotations();
//	m_tickOffset += (int) (newRotations * m_countsPerRev / m_gearRatio);
}

void DragonTalon::SetVoltageRamping(double ramping, double rampingClosedLoop)
{
    m_talon.get()->ConfigOpenloopRamp(ramping);

	if (rampingClosedLoop >= 0)
	{
		m_talon.get()->ConfigClosedloopRamp(rampingClosedLoop);
	}
}


void DragonTalon::EnableCurrentLimiting(bool enabled)
{
    m_talon.get()->EnableCurrentLimit(enabled);
}

void DragonTalon::EnableBrakeMode(bool enabled)
{
    m_talon.get()->SetNeutralMode(enabled ? ctre::phoenix::motorcontrol::NeutralMode::Brake : ctre::phoenix::motorcontrol::NeutralMode::Coast);
}

void DragonTalon::Invert(bool inverted)
{
    m_talon.get()->SetInverted(inverted);
}

void DragonTalon::SetSensorInverted(bool inverted)
{
    m_talon.get()->SetSensorPhase(inverted);
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
	m_talon.get()->SelectProfileSlot( slot, pidIndex );
}


int DragonTalon::ConfigSelectedFeedbackSensor
(
	FeedbackDevice feedbackDevice,
	int pidIdx,
	int timeoutMs
)
{
	int error = 0;
	if ( m_talon.get() != nullptr )
	{
		error = m_talon.get()->ConfigSelectedFeedbackSensor( feedbackDevice, pidIdx, timeoutMs );
	}
	else
	{
//		printf( "DragonTalon::ConfigSelectedFeedbackSensor: m_talon.get() not initialized \n" );
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
	if ( m_talon.get() != nullptr )
	{
		error = m_talon.get()->ConfigSelectedFeedbackSensor( feedbackDevice, pidIdx, timeoutMs );
	}
	else
	{
//		printf( "DragonTalon::ConfigSelectedFeedbackSensor: m_talon.get() not initialized \n" );
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
	if ( m_talon.get() != nullptr )
	{
		error = m_talon.get()->ConfigPeakCurrentLimit( amps, timeoutMs );
	}
	else
	{
//		printf( "DragonTalon::ConfigPeakCurrentLimit: m_talon.get() not initialized \n" );
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
	if ( m_talon.get() != nullptr )
	{
		error = m_talon.get()->ConfigPeakCurrentDuration( milliseconds, timeoutMs );
	}
	else
	{
//		printf( "DragonTalon::ConfigPeakCurrentDuration: m_talon.get() not initialized \n" );
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
	if ( m_talon.get() != nullptr )
	{
		error = m_talon.get()->ConfigContinuousCurrentLimit( amps, timeoutMs );
	}
	else
	{
//		printf( "DragonTalon::ConfigContinuousCurrentLimit: m_talon.get() not initialized \n" );
	}
	return error;
}

void DragonTalon::SetAsSlave
(
    int         masterCANID         // <I> - master motor
)
{
    m_talon.get()->Set( ControlMode::Follower, masterCANID );
}


/// @brief  Set the control constants (e.g. PIDF values).
/// @param [in] ControlData*   pid - the control constants
/// @return void
void DragonTalon::SetControlConstants(ControlData* controlInfo)
{
	auto peak = controlInfo->GetPeakValue();
	m_talon.get()->ConfigPeakOutputForward(peak);
	m_talon.get()->ConfigPeakOutputReverse(-1.0*peak);

	auto nom = controlInfo->GetNominalValue();
	m_talon.get()->ConfigPeakOutputForward(nom);
	m_talon.get()->ConfigPeakOutputReverse(-1.0*nom);

	switch ( controlInfo->GetMode() )
	{
		case ControlModes::CONTROL_TYPE::PERCENT_OUTPUT:
		{
		}
		break;

		case ControlModes::CONTROL_TYPE::POSITION_DEGREES:
		{
			m_talon.get()->Config_kP(0, controlInfo->GetP());
			m_talon.get()->Config_kI(0, controlInfo->GetI());
			m_talon.get()->Config_kD(0, controlInfo->GetD());
			m_talon.get()->Config_kF(0, controlInfo->GetF());
		}
		break;

		case ControlModes::CONTROL_TYPE::POSITION_INCH:
		{
			m_talon.get()->Config_kP(0, controlInfo->GetP());
			m_talon.get()->Config_kI(0, controlInfo->GetI());
			m_talon.get()->Config_kD(0, controlInfo->GetD());
			m_talon.get()->Config_kF(0, controlInfo->GetF());
		}
		break;

		case ControlModes::CONTROL_TYPE::VELOCITY_DEGREES:
		{
			m_talon.get()->Config_kP(0, controlInfo->GetP());
			m_talon.get()->Config_kI(0, controlInfo->GetI());
			m_talon.get()->Config_kD(0, controlInfo->GetD());
			m_talon.get()->Config_kF(0, controlInfo->GetF());
		}
		break;

		case ControlModes::CONTROL_TYPE::VELOCITY_INCH:
		{
			m_talon.get()->Config_kP(0, controlInfo->GetP());
			m_talon.get()->Config_kI(0, controlInfo->GetI());
			m_talon.get()->Config_kD(0, controlInfo->GetD());
			m_talon.get()->Config_kF(0, controlInfo->GetF());
		}
		break;

		case ControlModes::CONTROL_TYPE::VELOCITY_RPS:
		{
			m_talon.get()->Config_kP(0, controlInfo->GetP());
			m_talon.get()->Config_kI(0, controlInfo->GetI());
			m_talon.get()->Config_kD(0, controlInfo->GetD());
			m_talon.get()->Config_kF(0, controlInfo->GetF());
		}
		break;

		case ControlModes::CONTROL_TYPE::VOLTAGE:
		{
			m_talon.get()->Config_kP(0, controlInfo->GetP());
			m_talon.get()->Config_kI(0, controlInfo->GetI());
			m_talon.get()->Config_kD(0, controlInfo->GetD());
			m_talon.get()->Config_kF(0, controlInfo->GetF());
		}
		break;

		case ControlModes::CONTROL_TYPE::CURRENT:
		{
			m_talon.get()->Config_kP(0, controlInfo->GetP());
			m_talon.get()->Config_kI(0, controlInfo->GetI());
			m_talon.get()->Config_kD(0, controlInfo->GetD());
			m_talon.get()->Config_kF(0, controlInfo->GetF());
		}
		break;

		case ControlModes::CONTROL_TYPE::TRAPEZOID:
		{
			m_talon.get()->Config_kP(0, controlInfo->GetP());
			m_talon.get()->Config_kI(0, controlInfo->GetI());
			m_talon.get()->Config_kD(0, controlInfo->GetD());
			m_talon.get()->Config_kF(0, controlInfo->GetF());

			auto accel = controlInfo->GetMaxAcceleration() / m_gearRatio;
			m_talon.get()->ConfigMotionAcceleration( accel );

			auto vel = controlInfo->GetCruiseVelocity() / m_gearRatio;
			m_talon.get()->ConfigMotionCruiseVelocity( vel, 0);
		}
		break;

		case ControlModes::CONTROL_TYPE::MOTION_PROFILE:
		{

		}
		break;

		case ControlModes::CONTROL_TYPE::MOTION_PROFILE_ARC:
		{

		}
		break;

		default:
		{

		}
		break;
	}
}

void DragonTalon::SetForwardLimitSwitch
( 
	bool normallyOpen
)
{
	LimitSwitchNormal type = normallyOpen ? LimitSwitchNormal::LimitSwitchNormal_NormallyOpen : LimitSwitchNormal::LimitSwitchNormal_NormallyClosed;
	m_talon.get()->ConfigForwardLimitSwitchSource( LimitSwitchSource::LimitSwitchSource_FeedbackConnector, type, 0  );
}

void DragonTalon::SetReverseLimitSwitch
(
	bool normallyOpen
)
{
	LimitSwitchNormal type = normallyOpen ? LimitSwitchNormal::LimitSwitchNormal_NormallyOpen : LimitSwitchNormal::LimitSwitchNormal_NormallyClosed;
	m_talon.get()->ConfigReverseLimitSwitchSource( LimitSwitchSource::LimitSwitchSource_FeedbackConnector, type, 0  );
}


void DragonTalon::SetRemoteSensor
(
    int                                             canID,
    ctre::phoenix::motorcontrol::RemoteSensorSource deviceType
)
{
	m_talon.get()->ConfigRemoteFeedbackFilter( canID, deviceType, 0, 0.0 );
	m_talon.get()->ConfigSelectedFeedbackSensor( RemoteFeedbackDevice::RemoteFeedbackDevice_RemoteSensor0, 0, 0 );
}

void DragonTalon::SetDiameter
(
	double 	diameter
)
{
	m_diameter = diameter;
}