
//====================================================================================================================================================
// Copyright 2020 Lake Orion Robotics FIRST Team 302
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================

#pragma once

//========================================================================================================
/// Robot.h
//========================================================================================================
///
/// File Description:
///     Top-level robot code that controls the various states of the robot.  It is our specific 
///     implementation of the frc::TimedRobot.
///
//========================================================================================================

#pragma once

#include <string>

#include <frc/TimedRobot.h>

#include <auton/CyclePrimitives.h>
#include <controllers/chassis/ChassisStateMgr.h>
#include <test/ButtonBoxDisplay.h>
#include <test/XboxDisplay.h>
#include <hw/DragonTalon.h>

#include <frc/smartdashboard/SendableChooser.h>

class Robot : public frc::TimedRobot 
{
  public:
      Robot() = default;
      ~Robot() = default;

      void RobotInit() override;
      void RobotPeriodic() override;
      void AutonomousInit() override;
      void AutonomousPeriodic() override;
      void TeleopInit() override;
      void TeleopPeriodic() override;
      void TestInit() override;
      void TestPeriodic() override;

  private:  
      std::shared_ptr<IDragonMotorController> m_motor1;
      std::shared_ptr<IDragonMotorController> m_motor2;
      std::string IDENTIFIER = "";
      double K_P = 10.0;
      double K_I = 0.0;
      double K_D = 0.0;
      double K_F = 0.0;
      double INTEGRAL_ZONE = 0.0;
      double MAX_ACCEL = 0.0; 
      double CRUISE_VELOC = 0.0; 
      double PEAK = 1.0; 
      double NOMINAL = 0.0;
};
