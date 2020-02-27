/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Solenoid.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonFX.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <frc/XboxController.h>
#include <frc/GenericHID.h>

#include <ctre/phoenix/motorcontrol/SupplyCurrentLimitConfiguration.h>


using namespace frc;
using namespace std;
using namespace ctre::phoenix;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  auto limit = SupplyCurrentLimitConfiguration( true, 40.0, 50.0, 15.0 );

  m_left1 = new WPI_TalonFX( 12 );
  m_left1->SetInverted( true );
  m_left1->ConfigSupplyCurrentLimit( limit, 50 );

  m_left2 = new WPI_TalonFX( 13 );
  m_left2->SetInverted( true );
  m_left2->ConfigSupplyCurrentLimit( limit, 50 );

  m_right1 = new WPI_TalonFX( 14 );
  m_right1->ConfigSupplyCurrentLimit( limit, 50 );

  m_right2 = new WPI_TalonFX( 15 );
  m_right2->ConfigSupplyCurrentLimit( limit, 50  );

  m_shooter1 = new WPI_TalonFX( 1 );
  m_shooter1->SetInverted( true );
  m_shooter1->ConfigSupplyCurrentLimit( limit, 50 );

  m_shooter2 = new WPI_TalonFX( 16 );
  m_shooter2->ConfigSupplyCurrentLimit( limit, 50 );

  m_intake = new WPI_TalonSRX( 11 );

  m_impeller = new WPI_TalonSRX( 7 );
  m_transfer = new WPI_TalonSRX( 3 );
  m_shooterHood = new WPI_TalonSRX( 4 );
  m_turret = new WPI_TalonSRX( 5 );
  m_cpm = new WPI_TalonSRX( 6 );
  m_winch = new WPI_TalonSRX( 2 );

  
  m_intakeSol = new Solenoid( 9, 4 );
  m_cpmSol = new Solenoid( 9, 5 );
  m_climberSol = new Solenoid( 9, 6 );

  m_driver = new XboxController( 0 );
  m_pilot = new XboxController( 1 );





}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() 
{
  auto y = -m_driver->GetY( GenericHID::JoystickHand::kLeftHand );
  auto x = m_driver->GetX( GenericHID::JoystickHand::kRightHand );

  auto left = x+y;
  auto right = y-x;
  auto maxValue = max(abs( left ), abs( right ) );
  if ( maxValue > 1.0 )
  {
      left /= maxValue;
      right /= maxValue;
  }

  m_left1->Set( ControlMode::PercentOutput, left );
  m_left2->Set( ControlMode::PercentOutput, left );
  m_right1->Set( ControlMode::PercentOutput, right );
  m_right2->Set( ControlMode::PercentOutput, right );

  m_climberSol->Set( m_driver->GetAButton( ) );
  m_cpmSol->Set( m_driver->GetBButton( ) );
  if ( m_driver->GetYButton( ) )
  {
    m_cpm->Set(ControlMode::PercentOutput, 0.5);
  }
  else
  {
    m_cpm->Set( ControlMode::PercentOutput, 0.0 );
  }
  
  if ( m_driver->GetXButton( ) )
  {
    m_winch->Set(ControlMode::PercentOutput, 1.0);
  }
  else
  {
    m_winch->Set( ControlMode::PercentOutput, 0.0 );
  }


  m_intakeSol->Set( m_pilot->GetAButton() );
  if ( m_pilot->GetAButton() )
  {
    m_intake->Set( ControlMode::PercentOutput, 0.7 );
    m_impeller->Set( ControlMode::PercentOutput, 0.5 );    
    m_transfer->Set( ControlMode::PercentOutput, 0.3 );

  }
  else if ( m_pilot->GetBButton() )
  {
    m_intake->Set( ControlMode::PercentOutput, -0.5 );
    m_impeller->Set( ControlMode::PercentOutput, -0.5 );    
    m_transfer->Set( ControlMode::PercentOutput, -1.0 );
    m_shooter1->Set( ControlMode::PercentOutput, 0.75 );
    m_shooter2->Set( ControlMode::PercentOutput, 0.75 );
  }
  else
  {
    m_intake->Set( ControlMode::PercentOutput, 0.0 );
    m_impeller->Set( ControlMode::PercentOutput, 0.0 );    
    m_transfer->Set( ControlMode::PercentOutput, 0.0 );
  }

  if ( m_pilot->GetXButton() )
  {
    m_shooter1->Set( ControlMode::PercentOutput, m_shooterSpeed );
    m_shooter2->Set( ControlMode::PercentOutput, m_shooterSpeed );
  }
  else 
  {
    m_shooter1->Set( ControlMode::PercentOutput, 0.0 );
    m_shooter2->Set( ControlMode::PercentOutput, 0.0 );

  }

  if ( m_pilot->GetBumper( GenericHID::JoystickHand::kLeftHand ) )
  {
    m_shooterSpeed *= 0.9;
  }
  else if ( m_pilot->GetBumper( GenericHID::JoystickHand::kRightHand) )
  {
    m_shooterSpeed *= 1.1;
  }
  SmartDashboard::PutNumber( "Shooter Percent ", m_shooterSpeed );


  auto turretSpeed = m_pilot->GetX( GenericHID::JoystickHand::kLeftHand ) * 0.75;
  m_turret->Set( ControlMode::PercentOutput, turretSpeed );
  
  auto hoodSpeed = -m_pilot->GetY( GenericHID::JoystickHand::kLeftHand ) * 0.5;
  m_shooterHood->Set( ControlMode::PercentOutput, hoodSpeed );

}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
