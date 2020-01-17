/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <subsys/IMechanism.h>
#include <subsys/MechanismTypes.h>
#include <controllers/ControlModes.h>
#include <controllers/ControlData.h>
#include <hw/interfaces/IDragonMotorController.h>

class Turret : public IMechanism{
 public:
  Turret
  (
    IDragonMotorController* motorController
  );
  MechanismTypes::MECHANISM_TYPE GetType() const override;
  void SetOutput
  (
    ControlModes::CONTROL_TYPE controlType,
    double                                   value       
  ) override;

  void ActivateSolenoid
  (
    bool     activate
  ) override;

  bool IsSolenoidActivated() override;

  double GetCurrentPosition();

  double GetTargetPosition();

  double GetCurrentSpeed();

  double GetTargetSpeed();

  void SetControlConstants
  (
    ControlData*                                pid                 
  );
 private:
  IDragonMotorController* m_turretMotor;
  double m_targetSpeed;
  double m_targetPosition;
  double m_initialPosition;

};
