/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsys/Shooter.h"
#include "hw/interfaces/IDragonMotorController.h"
#include "subsys/MechanismTypes.h"
#include "controllers/ControlModes.h"
Shooter::Shooter(std::shared_ptr<IDragonMotorController> motor1,
std::shared_ptr<IDragonMotorController> motor2
): m_motor1(motor1),
m_motor2(motor2),
m_targetSpeed(0.0)
{}

MechanismTypes::MECHANISM_TYPE Shooter::GetType() const
{
    return MechanismTypes::MECHANISM_TYPE::SHOOTER;
}

void Shooter::SetOutput(ControlModes::CONTROL_TYPE controlType, double value)
{
    switch(controlType)
    {
        case ControlModes::CONTROL_TYPE::PERCENT_OUTPUT:
            m_targetSpeed = value;
            break;
        case ControlModes::CONTROL_TYPE::VELOCITY_DEGREES:
            m_targetSpeed = value;
            break;
        default:
            break;
        
    }
    m_motor1.get()->SetControlMode(controlType);
    m_motor1.get()->Set(value);
    m_motor2.get()->SetControlMode(controlType);
    m_motor2.get()->Set(value);
}

void Shooter::SetOutput(ControlModes::CONTROL_TYPE controlType, double motor1Value, double motor2Value)
{
    switch(controlType)
    {
        case ControlModes::CONTROL_TYPE::PERCENT_OUTPUT:
            m_targetSpeed = motor1Value;
            m_secondTargetSpeed = motor2Value;
            break;
        case ControlModes::CONTROL_TYPE::VELOCITY_DEGREES:
            m_targetSpeed = motor1Value;
            m_secondTargetSpeed = motor2Value;
            break;
        default:
            break;
        
    }
    m_motor1.get()->SetControlMode(controlType);
    m_motor1.get()->Set(motor1Value);
    m_motor2.get()->SetControlMode(controlType);
    m_motor2.get()->Set(motor2Value);
}
void Shooter::ActivateSolenoid(bool activate)
{}

bool Shooter::IsSolenoidActivated()
{
    return false;
}

double Shooter::GetCurrentPosition() const
{
    return m_motor1.get()->GetRotations() * 360.0;
}

double Shooter::GetCurrentSpeed() const 
{
    m_motor1.get()->GetRPS();
}


void Shooter::SetControlConstants(ControlData* pid)
{
    m_motor1.get()->SetControlConstants(pid);
}