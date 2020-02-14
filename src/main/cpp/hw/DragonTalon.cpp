#include <hw/DragonTalon.h>
#include <hw/DragonPDP.h>
#include <hw/usages/MotorControllerUsage.h>
#include <frc/PowerDistributionPanel.h>
#include <frc/SpeedController.h>
#include <memory>
#include <ctre/phoenix/motorcontrol/LimitSwitchType.h>
#include <utils/ConversionUtils.h>
#include <utils/Logger.h>


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
	// m_tickOffset
	// m_talon->GetSelectedSensorPo
	m_tickOffset = m_talon->GetSelectedSensorPosition();

}

double DragonTalon::GetRotations() const
{
	return (ConversionUtils::CountsToRevolutions( (m_talon->GetSelectedSensorPosition() - m_tickOffset), m_countsPerRev) * m_gearRatio);
}

double DragonTalon::GetRPS() const
{
	return (ConversionUtils::CountsPer100msToRPS( m_talon->GetSelectedSensorVelocity(), m_countsPerRev) * m_gearRatio);
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
			output = (ConversionUtils::DegreesToCounts(value,m_countsPerRev) / m_gearRatio) + m_tickOffset;
			break;
        case ControlModes::CONTROL_TYPE::POSITION_INCH:
            ctreMode = ctre::phoenix::motorcontrol::ControlMode::Position;
			output = (ConversionUtils::ConversionUtils::InchesToCounts(value, m_countsPerRev, m_diameter) / m_gearRatio) + m_tickOffset;
        	break;
        
        case ControlModes::CONTROL_TYPE::VELOCITY_DEGREES:
            ctreMode = ctre::phoenix::motorcontrol::ControlMode::Velocity;
			output = (ConversionUtils::DegreesPerSecondToCounts100ms( value, m_countsPerRev ) / m_gearRatio) + m_tickOffset;
        	break;

        case ControlModes::CONTROL_TYPE::VELOCITY_INCH:
            ctreMode = ctre::phoenix::motorcontrol::ControlMode::Velocity;
			output = (ConversionUtils::InchesPerSecondToCounts100ms( value, m_countsPerRev, m_diameter ) / m_gearRatio) + m_tickOffset;
        	break;

		case ControlModes::CONTROL_TYPE::VELOCITY_RPS:
            ctreMode = ctre::phoenix::motorcontrol::ControlMode::Velocity;
			output = (ConversionUtils::RPSToCounts100ms( value, m_countsPerRev ) / m_gearRatio) + m_tickOffset;
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
			output = (ConversionUtils::InchesToCounts(value, m_countsPerRev, m_diameter) / m_gearRatio) + m_tickOffset;
			break;

        default:
            Logger::GetLogger()->LogError( string("DragonTalon::SetControlMode"), string("Invalid Control Mode"));
        	ctreMode = ctre::phoenix::motorcontrol::ControlMode::PercentOutput;
			output = value;
        	break;
    }	

	m_talon->Set( ctreMode, output );
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

	auto accel = controlInfo->GetMaxAcceleration() / m_gearRatio;
	auto vel = controlInfo->GetCruiseVelocity() / m_gearRatio;
	switch ( controlInfo->GetMode() )
	{
		case ControlModes::CONTROL_TYPE::POSITION_DEGREES:
			accel = ConversionUtils::DegreesPerSecondToCounts100ms( accel, m_countsPerRev ); // todo this is velocity need accel
			vel = ConversionUtils::DegreesPerSecondToCounts100ms( vel, m_countsPerRev );
			break;

		case ControlModes::CONTROL_TYPE::POSITION_INCH:
			accel = ConversionUtils::InchesPerSecondToCounts100ms( accel, m_countsPerRev, m_diameter ); // todo this is velocity need accel
			vel = ConversionUtils::InchesPerSecondToCounts100ms( vel, m_countsPerRev, m_diameter );
			break;

		case ControlModes::CONTROL_TYPE::VELOCITY_DEGREES:
			accel = ConversionUtils::DegreesPerSecondToCounts100ms( accel, m_countsPerRev ); // todo this is velocity need accel
			vel = ConversionUtils::DegreesPerSecondToCounts100ms( vel, m_countsPerRev );
			break;

		case ControlModes::CONTROL_TYPE::VELOCITY_INCH:
			accel = ConversionUtils::InchesPerSecondToCounts100ms( accel, m_countsPerRev, m_diameter ); // todo this is velocity need accel
			vel = ConversionUtils::InchesPerSecondToCounts100ms( vel, m_countsPerRev, m_diameter );
			break;

		case ControlModes::CONTROL_TYPE::VELOCITY_RPS:
			accel = ConversionUtils::RPSToCounts100ms( accel, m_countsPerRev ); // todo this is velocity need accel
			vel = ConversionUtils::RPSToCounts100ms( vel, m_countsPerRev );
			break;

		default:
			break;

	}
	/*m_talon->ConfigMotionAcceleration( accel );
	m_talon->ConfigMotionCruiseVelocity( vel, 0);

	auto peak = controlInfo->GetPeakValue();
	m_talon->ConfigPeakOutputForward(peak);
	m_talon->ConfigPeakOutputReverse(-1.0*peak);

	auto nom = controlInfo->GetNominalValue();
	m_talon->ConfigPeakOutputForward(nom);
	m_talon->ConfigPeakOutputReverse(-1.0*nom);*/
	
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


void DragonTalon::SetRemoteSensor
(
    int                                             canID,
    ctre::phoenix::motorcontrol::RemoteSensorSource deviceType
)
{
	m_talon->ConfigRemoteFeedbackFilter( canID, deviceType, 0, 0.0 );
	m_talon->ConfigSelectedFeedbackSensor( RemoteFeedbackDevice::RemoteFeedbackDevice_RemoteSensor0, 0, 0 );
}

void DragonTalon::SetDiameter
(
	double 	diameter
)
{
	m_diameter = diameter;
}