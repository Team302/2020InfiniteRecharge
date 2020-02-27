/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonFX.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <frc/Solenoid.h>
#include <frc/XboxController.h>

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

  ctre::phoenix::motorcontrol::can::WPI_TalonFX* m_left1;
  ctre::phoenix::motorcontrol::can::WPI_TalonFX* m_left2;
  ctre::phoenix::motorcontrol::can::WPI_TalonFX* m_right1;
  ctre::phoenix::motorcontrol::can::WPI_TalonFX* m_right2;

  ctre::phoenix::motorcontrol::can::WPI_TalonFX* m_shooter1;
  ctre::phoenix::motorcontrol::can::WPI_TalonFX* m_shooter2;
  
  ctre::phoenix::motorcontrol::can::WPI_TalonSRX* m_intake;
  ctre::phoenix::motorcontrol::can::WPI_TalonSRX* m_impeller;
  ctre::phoenix::motorcontrol::can::WPI_TalonSRX* m_transfer;  
  ctre::phoenix::motorcontrol::can::WPI_TalonSRX* m_turret;  
  ctre::phoenix::motorcontrol::can::WPI_TalonSRX* m_shooterHood;

  ctre::phoenix::motorcontrol::can::WPI_TalonSRX* m_cpm;
  ctre::phoenix::motorcontrol::can::WPI_TalonSRX* m_winch;

  frc::Solenoid* m_intakeSol;
  frc::Solenoid* m_cpmSol;
  frc::Solenoid* m_climberSol;

  frc::XboxController* m_driver;
  frc::XboxController* m_pilot;

  double m_shooterSpeed = 0.75;


};
