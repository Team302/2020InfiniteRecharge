/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <controllers/IState.h>
#include <controllers/mechanisms/IMechController.h>
#include <controllers/ControlData.h>  
#include <subsys/IMechanism.h>
#include <subsys/Turret.h>

class ManualAim : public IState
{
 public:
  ManualAim
  (
    ControlData* controlData,
    double mechData //to be changed to MechData type
  );
  void Init() override;
  void Run() override;
  bool AtTarget() const override;

 private:
  
  ControlData* m_controlData;
  double m_mechData;
  bool m_atTarget;
  IMechanism* m_turret;

};
