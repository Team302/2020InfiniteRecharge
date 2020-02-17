/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <memory>

#include <states/IState.h>
#include <subsys/IMechanism.h>
#include <subsys/MechanismFactory.h>

class ControlPanelStow : public IState
{
 public:

  ControlPanelStow();
  ~ControlPanelStow() = default;

  void Init() override;
  void Run() override;
  bool AtTarget() const override;

  private:

  IMechanism* m_controlPanel;
};
