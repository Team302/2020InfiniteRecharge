/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <controllers/IState.h>
#include <subsys/IMechanism.h>
#include <controllers/ControlData.h>

class ShooterShoot : public IState
{
 public:
  ShooterShoot
  (
    ControlData* controlData,
    double target
  );
  void Init() override;
  void Run() override;
  bool AtTarget() const override;
 private:
  IMechanism* m_shooter;
  ControlData* m_controlData;
  bool m_atTarget;
  double m_target;
};