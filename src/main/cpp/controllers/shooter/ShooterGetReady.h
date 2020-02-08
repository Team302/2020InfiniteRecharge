/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <controllers/ControlData.h>
#include <controllers/IState.h>
#include <subsys/IMechanism.h>
#include <controllers/MechanismState.h>

class ShooterGetReady : public MechanismState
{
 public:
  ShooterGetReady
  (
    ControlData* controlData,
    double target
  );
  ShooterGetReady() = delete;
  ~ShooterGetReady() = default;
  /*void Init() override;
  void Run() override;
  bool AtTarget() const override;
 private:
  ControlData* m_controlData;
  double m_target;
  bool m_atTarget;
  IMechanism* m_shooter;
  */
};
