/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <hw/DragonSparkMax.h>


class TestChassis {
 public:
  TestChassis();
  void SetLeftRightPower(double leftPower, double rightPower);
  double GetVelocity(bool left);
  double GetRotations();

 private:
  DragonSparkMax* m_leftFront;
  DragonSparkMax* m_leftBack;
  DragonSparkMax* m_rightFront;
  DragonSparkMax* m_rightBack;
};
