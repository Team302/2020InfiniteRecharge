
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

// C++ Includes
#include <iostream>
#include <memory>

// FRC includes
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/smartdashboard/SendableChooser.h>

// Team 302 Includes
#include <Robot.h>
#include <xmlhw/RobotDefn.h>
#include <auton/CyclePrimitives.h>
#include <states/chassis/ChassisStateMgr.h>
#include <states/BallManipulator.h>
#include <states/intake/IntakeStateMgr.h>
#include <gamepad/TeleopControl.h>
//#include <states/controlPanel/ControlPanelStateMgr.h>
//#include <states/climber/ClimberStateMgr.h>
#include <hw/factories/LimelightFactory.h>
#include <hw/DragonLimelight.h>

#include <ctre/Phoenix.h>


#include <test/ButtonBoxDisplay.h>
#include <test/XboxDisplay.h>
#include <test/IntakeStateMgrTest.h>
#include <test/ImpellerStateMgrTest.h>
#include <test/BallTransferStateMgrTest.h>
#include <test/ShooterStateMgrTest.h>
#include <ctre/Phoenix.h>
#include <subsys/MechanismFactory.h>
#include <subsys/MechanismTypes.h>
#include <subsys/ChassisFactory.h>
#include <subsys/IChassis.h>
#include <hw/factories/PigeonFactory.h>
#include <frc/Solenoid.h>
#include <states/hookdelivery/HookDeliveryStateMgr.h>

using namespace std;
using namespace frc;

/// @brief  The main robot code.  The Init methods get called when that state gets entered and then the 
///     Periodic methods get called every 20 milliseconds.

/// @brief When the robot gets created this gets called.  It initializes the robot subsystems (hardware).
/// @return void
void Robot::RobotInit() 
{
    // Read the robot definition from the xml configuration files and
    // create the hardware (chassis + mechanisms along with their talons,
    // solenoids, digital inputs, analog inputs, etc.
    unique_ptr<RobotDefn>  robotXml = make_unique<RobotDefn>();
    robotXml->ParseXML();

    // Display the autonomous choices on the dashboard for selection.
    // comment out for now since auton hasn't been implemented
    //m_cyclePrims = new CyclePrimitives();

    // Create the Chassis Control (state) modes which puts the auton choices and teleop drive modes 
    // on the dashboard for selection.
    m_chassisStateMgr = new ChassisStateMgr();

    m_hook = HookDeliveryStateMgr::GetInstance();
    m_winch = ClimberStateMgr::GetInstance();

    /*m_leftMaster = new TalonFX(12);
    m_leftSlave = new TalonFX(13);
    m_rightMaster = new TalonFX(15);
    m_rightSlave = new TalonFX(14);

    m_leftMaster->ConfigFactoryDefault();
    m_leftSlave->ConfigFactoryDefault();
    m_rightMaster->ConfigFactoryDefault();
    m_rightSlave->ConfigFactoryDefault();

    m_leftSlave->SetInverted(false);
    m_leftMaster->SetInverted(false);
    m_rightMaster->SetInverted(true);
    m_rightSlave->SetInverted(true);

    m_leftSlave->Set(ControlMode::Follower, 12);
    m_rightSlave->Set(ControlMode::Follower, 15);*/

    //m_intake = new IntakeStateMgr();

    //m_cpm = new TalonSRX( 6 );
    //m_climber = new TalonSRX( 2 );

  
    //m_cpmSolenoid = new frc::Solenoid( 9, 6);
    //m_climberSolenoid = new frc::Solenoid( 9, 5 );

   // m_cpm = MechanismFactory::GetMechanismFactory()->GetIMechanism(MechanismTypes::CONTROL_TABLE_MANIPULATOR);
    //m_climber = MechanismFactory::GetMechanismFactory()->GetIMechanism(MechanismTypes::CLIMBER);
    m_powerCells = BallManipulator::GetInstance();
    m_shooterHood = MechanismFactory::GetMechanismFactory()->GetIMechanism(MechanismTypes::SHOOTER_HOOD);
    m_turret = MechanismFactory::GetMechanismFactory()->GetIMechanism(MechanismTypes::TURRET);
    m_impeller = MechanismFactory::GetMechanismFactory()->GetIMechanism(MechanismTypes::IMPELLER);
    m_shooter = MechanismFactory::GetMechanismFactory()->GetIMechanism(MechanismTypes::SHOOTER);
    m_controller = TeleopControl::GetInstance();
    //m_chassis = ChassisFactory::GetChassisFactory()->GetIChassis(); 

    // m_control = new ControlPanelStateMgr();
    // m_climber = new ClimberStateMgr();

        // pick test mode
    m_testChooser.SetDefaultOption( m_noTest, m_noTest);
    m_testChooser.AddOption( m_buttonBoxTest, m_buttonBoxTest );
    m_testChooser.AddOption( m_dragonXBoxTest, m_dragonXBoxTest );    
    m_testChooser.AddOption( m_intakeTest, m_intakeTest );
    m_testChooser.AddOption( m_impellerTest, m_impellerTest );
    m_testChooser.AddOption( m_ballTransferTest, m_ballTransferTest );
//    m_testChooser.AddOption( m_shooterTest, m_shooterTest );

    SmartDashboard::PutData("Test", &m_testChooser);

    m_buttonBoxDisplay = nullptr;
    m_xBoxDisplay = nullptr;

    //m_climberState = false;
    //m_cpmState = false;

    //m_climberSolenoidState = m_climberSolenoid->Get();
    //m_cpmSolenoidState = m_cpmSolenoid->Get();
    //m_limelight = LimelightFactory::GetLimelightFactory()->GetLimelight(IDragonSensor::SENSOR_USAGE::MAIN_LIMELIGHT );
    /*if (m_limelight.get() != nullptr )
    {
        m_limelight.get()->SetLEDMode( DragonLimelight::LED_MODE::LED_OFF);
    } */  
}

/// @brief This function is called every robot packet, no matter the  mode. This is used for items like diagnostics that run 
///        during disabled, autonomous, teleoperated and test modes (states).  THis runs after the specific state periodic 
///        methods and before the LiveWindow and SmartDashboard updating.
/// @return void
void Robot::RobotPeriodic() 
{

}


/// @brief This initializes the autonomous state
/// @return void
void Robot::AutonomousInit() 
{
    m_chassisStateMgr->SetState( ChassisStateMgr::CHASSIS_STATE::AUTON );

    // run selected auton option
    //m_cyclePrims->Init();

}


/// @brief Runs every 20 milliseconds when the autonomous state is active.
/// @return void
void Robot::AutonomousPeriodic() 
{
    //Real auton magic right here:
    //m_cyclePrims->RunCurrentPrimitive();

    m_chassisStateMgr->RunCurrentState();
}


/// @brief This initializes the teleoperated state
/// @return void
void Robot::TeleopInit() 
{
    m_chassisStateMgr->SetState( ChassisStateMgr::CHASSIS_STATE::TELEOP );
    m_chassisStateMgr->Init();
    m_powerCells->SetCurrentState(BallManipulator::BALL_MANIPULATOR_STATE::OFF, 0.0);
    m_powerCells->RunCurrentState();
    

}


/// @brief Runs every 20 milliseconds when the teleoperated state is active.
/// @return void
void Robot::TeleopPeriodic() 
{
    m_chassisStateMgr->RunCurrentState();
    //m_turret->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, m_controller->GetAxisValue(TeleopControl::FUNCTION_IDENTIFIER::TURRET_MANUAL_AXIS) * .5);
    //m_shooterHood->SetOutput(ControlModes::PERCENT_OUTPUT, .5* m_controller->GetAxisValue(TeleopControl::SHOOTER_HOOD_MANUAL_AXIS));
    //m_intake->RunCurrentState();
   m_powerCells->RunCurrentState();
   frc::SmartDashboard::PutNumber("Turret position", m_turret->GetCurrentPosition());


    m_winch->RunCurrentState();
    m_hook->RunCurrentState();

    // m_control->RunCurrentState();
    //double leftSpeed = m_controller->GetAxisValue(TeleopControl::FUNCTION_IDENTIFIER::TANK_DRIVE_LEFT_CONTROL);
    //double rightSpeed = m_controller->GetAxisValue(TeleopControl::FUNCTION_IDENTIFIER::TANK_DRIVE_RIGHT_CONTROL);
    //m_chassis.get()->SetOutput(ControlModes::PERCENT_OUTPUT, leftSpeed, rightSpeed);
    // m_climber->RunCurrentState();
    //m_rightMaster->Set(ControlMode::PercentOutput, rightSpeed);
    //m_leftMaster->Set(ControlMode::PercentOutput, leftSpeed);
    //frc::SmartDashboard::PutNumber("leftSpeed", leftSpeed);
    //frc::SmartDashboard::PutNumber("rightSpeed", rightSpeed);
    /*frc::SmartDashboard::PutNumber("Turret position", m_turret->GetCurrentPosition());
    frc::SmartDashboard::PutNumber("Shooter Hood position", m_shooterHood->GetCurrentPosition());
    frc::SmartDashboard::PutNumber("Impeller speed", m_impeller->GetCurrentSpeed());*/
    frc::SmartDashboard::PutNumber("Shooter speed", m_shooter->GetCurrentSpeed());
    //frc::SmartDashboard::PutNumber("Limelight tx", m_limelight.get()->GetTargetHorizontalOffset());
    /*if(m_controller->IsButtonPressed(TeleopControl::CONTROL_PANEL_SPIN_WHEEL))
    {
        m_cpmState = !m_cpmState;
    }

    
    if(m_controller->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::CONTROL_PANEL_RAISE))
    {
        m_cpmSolenoidState = true;
    }
    else
    {
        m_cpmSolenoidState = false;
    }
    

    if(m_controller->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::CLIMBER_LIFT))
    {
        m_climberState = !m_climberState;
    }



    if(m_controller->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::CLIMBER_EXTEND))
    {
        m_climberSolenoidState = true;
    }
    else
    {
        m_climberSolenoidState = false;
    }

    if(m_cpmState)
    {
        m_cpm->Set(ControlMode::PercentOutput, 1.0);
    }
    else
    {
         m_cpm->Set(ControlMode::PercentOutput, 0.0);
    }

    if(m_climberState)
    {
        m_climber->Set(ControlMode::PercentOutput, 1.0);
    }
    else
    {
        m_climber->Set(ControlMode::PercentOutput, 0.0);
    }

    if(m_climberSolenoidState)
    {
        m_climberSolenoid->Set(!m_climberSolenoid->Get());
    }
    else
    {
        
    }

    if(m_cpmSolenoidState)
    {
        m_cpmSolenoid->Set(!m_cpmSolenoid->Get());
    }
    {

    }
    

    
    
    frc::SmartDashboard::PutBoolean("left trigger", m_controller->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::TRANSFER_DOWN));
    */
}



/// @brief This initializes the test state
/// @return void
void Robot::TestInit() 
{
    m_testSelected = m_testChooser.GetSelected();
    if ( m_testSelected == m_buttonBoxTest )
    {
        m_currentTest = BUTTON_BOX;
        m_buttonBoxDisplay = new ButtonBoxDisplay();
    }
    else if ( m_testSelected == m_dragonXBoxTest )
    {
        m_currentTest = XBOX;
        m_xBoxDisplay = new XboxDisplay();
    }
	else if ( m_testSelected == m_intakeTest )
	{
        m_currentTest = INTAKE;
		m_intakeStateMgrTest = new IntakeStateMgrTest();
	}
	else if ( m_testSelected == m_impellerTest )
	{
        m_currentTest = IMPELLER;
		m_impellerStateMgrTest = new ImpellerStateMgrTest();
	}
	else if ( m_testSelected == m_ballTransferTest )
	{
        m_currentTest = TRANSFER;
		m_ballTransferStateMgrTest = new BallTransferStateMgrTest();
	}
    /**
	else if ( m_testSelected == m_shooterTest )
	{
        m_currentTest = SHOOTER;
		m_shooterStateMgrTest = new ShooterStateMgrTest();
	}
    **/
    else
    {
        m_currentTest = NONE;
    }
}


/// @brief Runs every 20 milliseconds when the test state is active.
/// @return void
void Robot::TestPeriodic() 
{
    switch ( m_currentTest )
    {
        case BUTTON_BOX:
            m_buttonBoxDisplay->periodic();
            break;

        case XBOX:
            m_xBoxDisplay->periodic();
            break;
			
		case INTAKE: 
			if ( !m_intakeStateMgrTest->IsDone() )
			{
				m_intakeStateMgrTest->Periodic();
			}
			break;
			
		case IMPELLER: 
			if ( !m_impellerStateMgrTest->IsDone() )
			{
				m_impellerStateMgrTest->Periodic();
			}
			break;
			
		case TRANSFER: 
			if ( !m_ballTransferStateMgrTest->IsDone() )
			{
				m_ballTransferStateMgrTest->Periodic();
			}
			break;
		/**
		case SHOOTER: 
			if ( !m_shooterStateMgrTest->IsDone() )
			{
				m_shooterStateMgrTest->Periodic();
			}
			break;
        **/
        default:
            break;
    }
}

#ifndef RUNNING_FRC_TESTS
int main() 
{
    return StartRobot<Robot>(); 
}
#endif
