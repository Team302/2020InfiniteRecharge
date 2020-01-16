
//====================================================================================================================================================
/// Copyright 2019 Lake Orion Robotics FIRST Team 302
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
/// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
/// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
/// OR OTHER DEALINGS IN THE SOFTWARE.
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

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

#include <auton/CyclePrimitives.h>

#include <gamepad/DragonXBox.h>

#include <ctre/Phoenix.h>
#include <frc/XboxController.h>




class Robot : public frc::TimedRobot 
{
  public:
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
      CyclePrimitives* m_cyclePrims;

    TalonSRX* m_turretTalon;
    DragonXBox* m_xbox;
    const int TURRET_ID = 0;
    const int K_P = 10.0;
    const int K_I = 0.0;
    const int K_D = 0.0;
    const int K_F = 0.0;
    double m_initialPosition;

};
