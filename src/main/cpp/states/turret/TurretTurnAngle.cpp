/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "states/turret/TurretTurnAngle.h"
#include "controllers/ControlData.h"
#include "states/MechanismState.h"
#include "subsys/MechanismFactory.h"

TurretTurnAngle::TurretTurnAngle(ControlData* controlData, double target, MechanismTargetData::SOLENOID solenoid) : 
    MechanismState(MechanismFactory::GetMechanismFactory()->GetIMechanism(MechanismTypes::TURRET),controlData, target, solenoid),
    m_controlData(controlData)
{
}

ControlData* TurretTurnAngle::GetControlData()
{
    return m_controlData;
}