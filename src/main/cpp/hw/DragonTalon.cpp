#include <hw/DragonTalon.h>
#include <hw/DragonPDP.h>
#include <hw/usages/MotorControllerUsage.h>
#include <frc/PowerDistributionPanel.h>
#include <frc/SpeedController.h>
#include <memory>

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
	m_controlMode(TALON_CONTROL_MODE::PERCENT),
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

void DragonTalon::SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE mode)
{ 
    switch (mode)
    {
        case IDragonMotorController::DRAGON_CONTROL_MODE::PERCENT_OUTPUT:
            DragonTalon::SetControlMode(DragonTalon::TALON_CONTROL_MODE::PERCENT);
        break;

        case IDragonMotorController::DRAGON_CONTROL_MODE::ROTATIONS:
            DragonTalon::SetControlMode(DragonTalon::TALON_CONTROL_MODE::POSITION);
        break;
        
        case IDragonMotorController::DRAGON_CONTROL_MODE::RPS:
            DragonTalon::SetControlMode(DragonTalon::TALON_CONTROL_MODE::VELOCITY);
        break;
        
        default:
            // bad place to be
			printf("SCREAMIN!!!!!111 invalid controlmode set in DragonTalon SetControlMode\n");
            DragonTalon::SetControlMode(DragonTalon::TALON_CONTROL_MODE::PERCENT);
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

void DragonTalon::SetControlMode(DragonTalon::TALON_CONTROL_MODE mode)
{
    if (m_controlMode != mode)
    {
        m_controlMode = mode;
		// printf("mode changed \n");
        // DragonTalon::Set(0);
    }
    
}

void DragonTalon::Set(double value)
{
    switch (m_controlMode)
    {
        case TALON_CONTROL_MODE::PERCENT:
            m_talon->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, value);
        break;

        case TALON_CONTROL_MODE::POSITION:
		// return ((m_talon->GetSelectedSensorPosition() - m_tickOffset) / (double) m_countsPerRev) * m_gearRatio;
            // m_talon->Set(ctre::phoenix::motorcontrol::ControlMode::Position, (value + m_tickOffset) / ((double) m_countsPerRev * m_gearRatio));
			m_talon->Set(ctre::phoenix::motorcontrol::ControlMode::Position, (value * m_countsPerRev / m_gearRatio) + m_tickOffset);
        break;

        case TALON_CONTROL_MODE::VELOCITY:
            m_talon->Set(ctre::phoenix::motorcontrol::ControlMode::Velocity, value * m_gearRatio / 600.0);
        break;

        //TODO: 
        // case TALON_CONTROL_MODE::RPS:
        //     m_talon->Set(ctre::phoenix::motorcontrol::ControlMode::Velocity, value / m_countsPerRev);    
        // break;

        case TALON_CONTROL_MODE::FOLLOWER:
            m_talon->Set(ctre::phoenix::motorcontrol::ControlMode::Follower, value);
        break;

        case TALON_CONTROL_MODE::MOTION_MAGIC:
            m_talon->Set(ctre::phoenix::motorcontrol::ControlMode::MotionMagic, (value * m_countsPerRev / m_gearRatio) + m_tickOffset);
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

void DragonTalon::SetPIDF(double p, double i, double d, double f, int slot)
{
    m_talon->Config_kP(slot, p);
    m_talon->Config_kI(slot, i);
    m_talon->Config_kD(slot, d);
    m_talon->Config_kF(slot, f);
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

//hopefully this is correct
void DragonTalon::ConfigMotionAcceleration
(
	float maxMotionAcceleration
)
{
    int sensorUnitsPer100msPerSec = static_cast<int>( (maxMotionAcceleration / 360.0) * (m_countsPerRev / 10.0) / m_gearRatio );
	m_talon->ConfigMotionAcceleration( sensorUnitsPer100msPerSec, 0);
}

//need to change
void DragonTalon::ConfigMotionCruiseVelocity
(
	float maxMotionCruiseVelocity
)
{
    int sensorUnitsPer100msPerSec = static_cast<int>( (maxMotionCruiseVelocity / 360.0) * (m_countsPerRev / 10.0) / m_gearRatio );
	m_talon->ConfigMotionCruiseVelocity( sensorUnitsPer100msPerSec, 0);
}

void DragonTalon::ConfigPeakOutput
(
	double percentOutput
)
{
	m_talon->ConfigPeakOutputForward(percentOutput);
	m_talon->ConfigPeakOutputReverse(-percentOutput);
}

void DragonTalon::ConfigNominalOutput
(
	double nominalOutput
)
{
	m_talon->ConfigNominalOutputForward(nominalOutput);
	m_talon->ConfigNominalOutputReverse(-nominalOutput);
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

