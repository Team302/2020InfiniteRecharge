/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsys/Turret.h"
#include <subsys/IMechanism.h>
#include <subsys/MechanismTypes.h>
#include <controllers/ControlModes.h>
#include <controllers/ControlData.h>

Turret::Turret(IDragonMotorController* motorController): m_targetPosition(0.0),
m_targetSpeed(0.0)
{
    m_turretMotor = motorController;
    m_initialPosition = m_turretMotor->GetRotations();
}

MechanismTypes::MECHANISM_TYPE Turret::GetType() const
{
    return MechanismTypes::TURRET;
}

void Turret::SetOutput(ControlModes::CONTROL_TYPE controlType, double value)
{
  m_turretMotor->SetControlMode(controlType);
  m_turretMotor->Set(value);
}

void Turret::ActivateSolenoid(bool activate)
{

}

bool Turret::IsSolenoidActivated()
{
    return false;
}

double Turret::GetCurrentPosition() 
{
    return m_turretMotor->GetRotations();
}

double Turret::GetTargetPosition() 
{
    return m_targetPosition;
}

double Turret::GetCurrentSpeed() 
{
    return m_turretMotor->GetRPS();
}

double Turret::GetTargetSpeed()  
{
    return m_targetSpeed;
}

void Turret::SetControlConstants(ControlData* pid)
{
    m_turretMotor->SetPIDF(pid->GetP(),pid->GetI(),pid->GetD(),pid->GetF());
}

