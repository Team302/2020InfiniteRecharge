/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <states/MechanismState.h>
#include <controllers/MechanismTargetData.h>
#include <controllers/ControlData.h> 

class TurretTurnAngle : public MechanismState{
 public:
  TurretTurnAngle() = delete;
  TurretTurnAngle
  (
    ControlData* controlData,
    double target,
    MechanismTargetData::SOLENOID solenoid
  );

  ControlData* GetControlData();
 private:
  ControlData* m_controlData;
};
