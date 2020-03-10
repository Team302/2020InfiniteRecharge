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
): m_topMotor(motor1),
m_bottomMotor(motor2),
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
    m_topMotor.get()->SetControlMode(controlType);
    m_bottomMotor.get()->SetControlMode(controlType);
    m_topMotor.get()->Set(value);
    m_bottomMotor.get()->Set(value);
}

void Shooter::SetOutput(ControlModes::CONTROL_TYPE controlType, double upperValue, double lowerValue)
{
    switch(controlType)
    {
        case ControlModes::CONTROL_TYPE::PERCENT_OUTPUT:
            m_targetSpeed1 = upperValue;
            m_targetSpeed2 = lowerValue;
            break;
        case ControlModes::CONTROL_TYPE::VELOCITY_DEGREES:
            m_targetSpeed1 = upperValue;
            m_targetSpeed2 = lowerValue;
            break;
        default:
            break;
    }
    m_topMotor.get()->SetControlMode(controlType);
    m_bottomMotor.get()->SetControlMode(controlType);
    m_topMotor.get()->Set(upperValue);
    m_bottomMotor.get()->Set(lowerValue);
}

void Shooter::ActivateSolenoid(bool activate)
{}

bool Shooter::IsSolenoidActivated()
{
    return false;
}

double Shooter::GetCurrentPosition() const
{
    return m_topMotor.get()->GetRotations() * 360.0;
}

double Shooter::GetCurrentSpeed() const 
{
    return m_topMotor.get()->GetRPS();
}


void Shooter::SetControlConstants(ControlData* pid)
{
    m_topMotor.get()->SetControlConstants(pid);
    m_bottomMotor.get()->SetControlConstants(pid);
}