#include <hw/DragonSparkMax.h>
#include <hw/usages/MotorControllerUsage.h>
#include <hw/DragonPDP.h>
#include <controllers/ControlModes.h>

#include <memory>
#include <string>
#include <frc/SpeedController.h>
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/PowerDistributionPanel.h>
#include <utils/ConversionUtils.h>
#include <utils/Logger.h>

using namespace frc;
using namespace std;
using namespace rev;

DragonSparkMax::DragonSparkMax
(
    int id, 
    int pdpID,
    MotorControllerUsage::MOTOR_CONTROLLER_USAGE deviceType, 
    CANSparkMax::MotorType motorType, 
    double gearRatio 
) : m_id(id),
    m_pdp( pdpID ),
    m_spark( make_shared<CANSparkMax>(id, motorType)),
    m_controlMode(ControlModes::CONTROL_TYPE::PERCENT_OUTPUT),
    m_outputRotationOffset(0.0),
    m_gearRatio(gearRatio),
	m_diameter( 1.0 ),
    m_deviceType(deviceType)
{
    m_spark->GetPIDController().SetOutputRange(-1.0, 1.0, 0);
    m_spark->GetPIDController().SetOutputRange(-1.0, 1.0, 1);
    m_spark->RestoreFactoryDefaults();
    m_spark->SetOpenLoopRampRate(0.09); //0.2 0.25
    m_spark->SetClosedLoopRampRate(0.02);
    m_spark->GetEncoder().SetPosition(0);
    SetRotationOffset(0);
}

double DragonSparkMax::GetRotations() const
{
    return GetRotationsWithGearNoOffset() - m_outputRotationOffset;
}

double DragonSparkMax::GetRPS() const
{
    return m_spark->GetEncoder().GetVelocity() / 60.0;
}

MotorControllerUsage::MOTOR_CONTROLLER_USAGE DragonSparkMax::GetType() const
{
    return m_deviceType;
}

int DragonSparkMax::GetID() const
{
    return m_id;
}

shared_ptr<SpeedController> DragonSparkMax::GetSpeedController() const
{
    return m_spark;
}

double DragonSparkMax::GetCurrent() const
{
	PowerDistributionPanel* pdp = DragonPDP::GetInstance()->GetPDP();
    return ( pdp != nullptr ) ? pdp->GetCurrent( m_pdp ) : 0.0;
}
void DragonSparkMax::SetControlMode(ControlModes::CONTROL_TYPE mode)
{
    if (m_controlMode != mode)
    {
        m_controlMode = mode;
        switch (mode)
        {
            case ControlModes::CONTROL_TYPE::PERCENT_OUTPUT:
                m_spark->Set(0); // init to zero just to be safe
                break;
            
            case ControlModes::CONTROL_TYPE::POSITION_DEGREES:
            case ControlModes::CONTROL_TYPE::POSITION_INCH:
                m_spark->GetPIDController().SetReference(0, rev::ControlType::kPosition, 0);
                break;

            case ControlModes::CONTROL_TYPE::VELOCITY_DEGREES:
            case ControlModes::CONTROL_TYPE::VELOCITY_INCH: 
			case ControlModes::CONTROL_TYPE::VELOCITY_RPS:
                m_spark->GetPIDController().SetReference(0, rev::ControlType::kVelocity, 1);
                break;

            case ControlModes::CONTROL_TYPE::CURRENT:
            case ControlModes::CONTROL_TYPE::MOTION_PROFILE:
            case ControlModes::CONTROL_TYPE::MOTION_PROFILE_ARC:
            case ControlModes::CONTROL_TYPE::TRAPEZOID:
                break;

   		    case ControlModes::CONTROL_TYPE::VOLTAGE:
               m_spark->GetPIDController().SetReference(0.0, rev::ControlType::kVoltage, 1);
               break;



            default:
                // danger11!!!!
                m_spark->Set(0);
                break;
        }
    }

}

void DragonSparkMax::Set(double value)
{
	auto output = value;
    switch (m_controlMode)
    {
        case ControlModes::CONTROL_TYPE::PERCENT_OUTPUT:
            m_spark->Set(value);
			break;
			
        case ControlModes::CONTROL_TYPE::POSITION_DEGREES:
			output = (ConversionUtils::DegreesToCounts(value,m_countsPerRev) / m_gearRatio) + m_outputRotationOffset;
			m_spark->GetPIDController().SetReference( output, rev::ControlType::kPosition, 0);
			break;
        case ControlModes::CONTROL_TYPE::POSITION_INCH:
			output = (ConversionUtils::InchesToCounts(value, m_countsPerRev, m_diameter) / m_gearRatio) + m_outputRotationOffset;
			m_spark->GetPIDController().SetReference( output, rev::ControlType::kPosition, 0);
        	break;
        
        case ControlModes::CONTROL_TYPE::VELOCITY_DEGREES:
			output = (ConversionUtils::DegreesPerSecondToCounts100ms( value, m_countsPerRev ) / m_gearRatio) + m_outputRotationOffset;
			m_spark->GetPIDController().SetReference( output/60.0, rev::ControlType::kVelocity, 0);
        	break;

        case ControlModes::CONTROL_TYPE::VELOCITY_INCH:
			output = (ConversionUtils::InchesPerSecondToCounts100ms( value, m_countsPerRev, m_diameter ) / m_gearRatio) + m_outputRotationOffset;
			m_spark->GetPIDController().SetReference( output/60.0, rev::ControlType::kVelocity, 0);
        	break;

		case ControlModes::CONTROL_TYPE::VELOCITY_RPS:
			output = (ConversionUtils::RPSToCounts100ms( value, m_countsPerRev ) / m_gearRatio) + m_outputRotationOffset;
			m_spark->GetPIDController().SetReference( output/60.0, rev::ControlType::kVelocity, 0);
        	break;

		case ControlModes::CONTROL_TYPE::CURRENT:
			output = value;
			m_spark->GetPIDController().SetReference( output, rev::ControlType::kCurrent, 0);
			break;

		case ControlModes::CONTROL_TYPE::MOTION_PROFILE:
			output = value;
			break;

		case ControlModes::CONTROL_TYPE::MOTION_PROFILE_ARC:
			output = value;
			break;

		case ControlModes::CONTROL_TYPE::TRAPEZOID:
			output = (ConversionUtils::InchesToCounts(value, m_countsPerRev, m_diameter) / m_gearRatio) + m_outputRotationOffset;
			m_spark->GetPIDController().SetReference( output, rev::ControlType::kSmartMotion, 0);
			break;

   		case ControlModes::CONTROL_TYPE::VOLTAGE:
		    output = (ConversionUtils::InchesToCounts(value, m_countsPerRev, m_diameter) / m_gearRatio) + m_outputRotationOffset;
            m_spark->GetPIDController().SetReference( value, rev::ControlType::kVoltage, 0);
            break;

        default:
            Logger::GetLogger()->LogError( string("DragonSparkMax::SetControlMode"), string("Invalid Control Mode"));
            m_spark->Set(value);
        	break;
    }	

}

void DragonSparkMax::SetRotationOffset(double rotations)
{
    m_outputRotationOffset = GetRotationsWithGearNoOffset() - rotations;
}

void DragonSparkMax::SetVoltageRamping(double ramping, double rampingClosedLoop)
{
    // m_spark->SetRampRate(ramping);
    m_spark->SetOpenLoopRampRate(ramping);
    // m_spark->SetClosedLoopRampRate(ramping); //TODO: should closed and open be separate

    if (rampingClosedLoop >= 0)
    {
        m_spark->SetClosedLoopRampRate(rampingClosedLoop);
    }
}

void DragonSparkMax::EnableCurrentLimiting(bool enabled)
{
    // TODO:
    // m_spark->SetSmart
}

void DragonSparkMax::EnableBrakeMode(bool enabled)
{
    m_spark->SetIdleMode(enabled ? rev::CANSparkMax::IdleMode::kBrake : rev::CANSparkMax::IdleMode::kCoast);
}

void DragonSparkMax::Invert(bool inverted)
{
    m_spark->SetInverted(inverted);
    // m_spark->GetEncoder().SetPositionConversionFactor(inverted ? -1.0 : 1.0);
}

CANError DragonSparkMax::Follow(DragonSparkMax* leader, bool invert)
{
    CANSparkMax* thisMax = m_spark.get();
    CANSparkMax* master  = leader->GetSparkMax().get();
    return thisMax->Follow( *master, invert);
}

double DragonSparkMax::GetRotationsWithGearNoOffset() const
{
    return m_spark->GetEncoder().GetPosition() * m_gearRatio;
}

void DragonSparkMax::SetSensorInverted(bool inverted)
{
    m_spark->GetEncoder().SetInverted( inverted );
}

shared_ptr<CANSparkMax> DragonSparkMax::GetSparkMax() const
{
    return m_spark;
}

void DragonSparkMax::SetSmartCurrentLimiting(int limit)
{
    m_spark->SetSmartCurrentLimit(limit);
}


/// @brief  Set the control constants (e.g. PIDF values).
/// @param [in] ControlData*   pid - the control constants
/// @return void
void DragonSparkMax::SetControlConstants(ControlData* controlInfo)
{
	m_spark->GetPIDController().SetP(controlInfo->GetP(), 0);
    m_spark->GetPIDController().SetI(controlInfo->GetI(), 0);
    m_spark->GetPIDController().SetD(controlInfo->GetD(), 0);
    m_spark->GetPIDController().SetFF(controlInfo->GetF(), 0);
}


void DragonSparkMax::SetRemoteSensor
(
    int                                             canID,
    ctre::phoenix::motorcontrol::RemoteSensorSource deviceType
)
{
    
}

void DragonSparkMax::SetDiameter
(
	double 	diameter
)
{
	m_diameter = diameter;
}
