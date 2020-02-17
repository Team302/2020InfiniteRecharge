/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <states/IState.h>
#include <controllers/mechanisms/IMechController.h>
#include <controllers/ControlData.h>  
#include <subsys/IMechanism.h>
#include <subsys/Turret.h>

class ManualAim : public IState
{
 public:
  ManualAim
  (
    ControlData* controlData
  );
  void Init() override;
  void Run() override;
  bool AtTarget() const override;

 private:
  
  ControlData* m_controlData;
  bool m_atTarget;
  IMechanism* m_turret;

};
