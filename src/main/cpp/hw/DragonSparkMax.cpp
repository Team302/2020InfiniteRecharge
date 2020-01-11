#include "hw/DragonSparkMax.h"
#include <hw/usages/MotorControllerUsage.h>
#include <hw/DragonPDP.h>

#include <memory>
#include <frc/SpeedController.h>
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/PowerDistributionPanel.h>

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
    m_controlMode(DRAGON_CONTROL_MODE::PERCENT_OUTPUT),
    m_outputRotationOffset(0.0),
    m_gearRatio(gearRatio),
    m_deviceType(deviceType)
{
    m_spark->GetPIDController().SetOutputRange(-1.0, 1.0, 0);
    m_spark->GetPIDController().SetOutputRange(-1.0, 1.0, 1);
    // m_spark->GetEncoder()
    // m_spark->
    // m_spark->SetParameter(CANSparkMaxLowLevel::ConfigParameter::kHallOffset, 0);
    // m_spark->RestoreFactoryDefaults();
    // m_spark->SetReverse(true);
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
void DragonSparkMax::SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE mode)
{
    if (m_controlMode != mode)
    {
        m_controlMode = mode;
        switch (mode)
        {
            case DRAGON_CONTROL_MODE::PERCENT_OUTPUT:
                m_spark->Set(0); // init to zero just to be safe
                break;
            
            case DRAGON_CONTROL_MODE::ROTATIONS:
                // m_spark->GetPIDController().SetReference(0, rev::ControlType::kPosition, 0);
                break;

            case DRAGON_CONTROL_MODE::RPS:
                // m_spark->GetPIDController().SetReference(0, rev::ControlType::kVelocity, 1);
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
    switch (m_controlMode)
    {
        case DRAGON_CONTROL_MODE::PERCENT_OUTPUT:
            m_spark->Set(value);
            break;

        case DRAGON_CONTROL_MODE::ROTATIONS:
            // (rot * gear ratio) - m_outputRotationOffset
            m_spark->GetPIDController().SetReference((value + m_outputRotationOffset) / m_gearRatio, rev::ControlType::kPosition, 0); // position is slot 0
            break;

        case DRAGON_CONTROL_MODE::RPS: //inches per second
            m_spark->GetPIDController().SetReference((value / 60.0) / m_gearRatio, rev::ControlType::kVelocity, 1);
            break;

        default:
            // bad news if we are in the default branch... stop the motor
            m_spark->Set(0);
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

void DragonSparkMax::SetPIDF(double p, double i, double d, double f, int slot)
{
    m_spark->GetPIDController().SetP(p, slot);
    m_spark->GetPIDController().SetI(i, slot);
    m_spark->GetPIDController().SetD(d, slot);
    m_spark->GetPIDController().SetFF(f, slot);
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

void DragonSparkMax::InvertEncoder(bool inverted)
{
    // m_spark->SetInverted()
    // m_spark->GetEncoder().SetInverted(inverted);
}

shared_ptr<CANSparkMax> DragonSparkMax::GetSparkMax() const
{
    return m_spark;
}

void DragonSparkMax::SetSmartCurrentLimiting(int limit)
{
    m_spark->SetSmartCurrentLimit(limit);
}