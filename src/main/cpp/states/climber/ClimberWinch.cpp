/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "states/climber/ClimberWinch.h"
#include <states/MechanismState.h>
#include <subsys/IMechanism.h>
#include <subsys/MechanismFactory.h>
#include <controllers/MechanismTargetData.h>


ClimberWinch::ClimberWinch
(
    ControlData*                    control,
    double                          target,
    MechanismTargetData::SOLENOID   solState
) : MechanismState( MechanismFactory::GetMechanismFactory()->GetIMechanism(MechanismTypes::MECHANISM_TYPE::CLIMBER), control, target, solState )
{

}

