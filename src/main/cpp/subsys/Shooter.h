/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <subsys/IMechanism.h>

#include <hw/interfaces/IDragonMotorController.h>

class Shooter : public IMechanism {
 public:
  Shooter
  (
    std::shared_ptr<IDragonMotorController> motor1,
    std::shared_ptr<IDragonMotorController> motor2
  );
  /// @brief          Indicates the type of mechanism this is
  /// @return         MechanismTypes::MECHANISM_TYPE
  MechanismTypes::MECHANISM_TYPE GetType() const override;


  /// @brief      Run mechanism as defined 
  /// @param [in] ControlModes::CONTROL_TYPE   controlType:  How are the item(s) being controlled
  /// @param [in] double                                     value:        Target (units are based on the controlType)
  /// @return     void
  void SetOutput
  (
      ControlModes::CONTROL_TYPE controlType,
      double                                   value       
  ) override;

  void SetOutput
  (
      ControlModes::CONTROL_TYPE controlType,
      double   upperValue,
      double   lowerValue
  );

  /// @brief      Activate/deactivate pneumatic solenoid
  /// @param [in] bool - true == extend, false == retract
  /// @return     void 
  void ActivateSolenoid
  (
      bool     activate
  ) override;

  /// @brief      Check if the pneumatic solenoid is activated
  /// @return     bool - true == extended, false == retract
  bool IsSolenoidActivated() override;


  /// @brief  Return the current position of the mechanism.  The value is in inches or degrees.
  /// @return double	position in inches (translating mechanisms) or degrees (rotating mechanisms)
  double GetCurrentPosition() const override;

  /// @brief  Get the current speed of the mechanism.  The value is in inches per second or degrees per second.
  /// @return double	speed in inches/second (translating mechanisms) or degrees/second (rotating mechanisms)
  double GetCurrentSpeed() const override;


  /// @brief  Set the control constants (e.g. PIDF values).
  /// @param [in] ControlData*                                   pid:  the control constants
  /// @return void
  void SetControlConstants
  (
      ControlData*                                pid                 
  ) override;

 private:
  std::shared_ptr<IDragonMotorController> m_topMotor;
  std::shared_ptr<IDragonMotorController> m_bottomMotor;
  double m_targetSpeed;
  double m_targetSpeed1;
  double m_targetSpeed2;
};
