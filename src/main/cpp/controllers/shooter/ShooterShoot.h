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
#include <controllers/MechanismState.h>

class ShooterShoot : public MechanismState
{
 public:
  ShooterShoot
  (
    ControlData* controlData,
    double target
  );

  ShooterShoot() = delete;
  ~ShooterShoot() = default;
 /* void Init() override;
  void Run() override;
  bool AtTarget() const override;
 private:
  IMechanism* m_shooter;
  ControlData* m_controlData;
  bool m_atTarget;
  double m_target;
  */
};
