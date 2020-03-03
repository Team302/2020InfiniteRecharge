/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "states/turret/HoldTurretPosition.h"
#include "subsys/MechanismFactory.h"
#include "subsys/IMechanism.h"
#include "subsys/Turret.h"
#include "controllers/ControlData.h"
#include "states/MechanismState.h"
#include "controllers/MechanismTargetData.h"

HoldTurretPosition::HoldTurretPosition(ControlData* controlData, double target, MechanismTargetData::SOLENOID solenoid) : 
    MechanismState(MechanismFactory::GetMechanismFactory()->GetIMechanism(MechanismTypes::TURRET),controlData, 0.0, solenoid)
{
}
