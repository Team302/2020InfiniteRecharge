/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <subsys/IMechanism.h>
#include <states/MechanismState.h>
#include <controllers/MechanismTargetData.h>

class ClimberWinch : public MechanismState
{
 public:
  ClimberWinch() = delete;
  ClimberWinch
  (
      ControlData*                    control,
      double                          target,
      MechanismTargetData::SOLENOID   solState
  );

  ~ClimberWinch() = default;
};
