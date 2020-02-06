
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

// c++ includes
#include <string>

// wpilib includes
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

// team 302 includes
#include <auton/CyclePrimitives.h>
#include <controllers/chassis/ChassisStateMgr.h>
#include <controllers/BallManipulator.h>
//#include <controllers/controlPanel/ControlPanelStateMgr.h>
//#include <controllers/climber/ClimberStateMgr.h>
#include <controllers/intake/IntakeStateMgr.h>

#include <test/ButtonBoxDisplay.h>
#include <test/XboxDisplay.h>
#include <test/IntakeStateMgrTest.h>
#include <test/ImpellerStateMgrTest.h>
#include <test/BallTransferStateMgrTest.h>
#include <test/ShooterStateMgrTest.h>

// third party includes

/// @class Robot
/// @brief Top-level robot code that controls the various states of the robot.  It is our specific 
///        implementation of the frc::TimedRobot.
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
      CyclePrimitives* m_cyclePrims;
      ChassisStateMgr* m_chassisStateMgr;
      //IntakeStateMgr* m_intake;
      BallManipulator* m_powerCells;
      // ControlPanelStateMgr* m_control;
      // ClimberStateMgr* m_climer;


      ButtonBoxDisplay* m_buttonBoxDisplay;
      XboxDisplay* m_xBoxDisplay;
	  IntakeStateMgrTest* m_intakeStateMgrTest;
	  ImpellerStateMgrTest* m_impellerStateMgrTest;
	  BallTransferStateMgrTest* m_ballTransferStateMgrTest;
	  ShooterStateMgrTest* m_shooterStateMgrTest;

      frc::SendableChooser<std::string>   m_testChooser;                    
      const std::string                   m_noTest = "No Test";      
      const std::string                   m_buttonBoxTest = "Button Box";      
      const std::string                   m_dragonXBoxTest = "Dragon XBox";      
	  const std::string                   m_intakeTest = "Intake";
	  const std::string                   m_impellerTest = "Impeller";
	  const std::string                   m_ballTransferTest = "Ball Transfer";
	  const std::string                   m_shooterTest = "Shooter";
      std::string                         m_testSelected; 

      enum TEST_TO_RUN
      {
          NONE,
          BUTTON_BOX,
          XBOX,
		  INTAKE,
		  IMPELLER,
		  TRANSFER,
		  SHOOTER
      };
      TEST_TO_RUN   m_currentTest;      


};
