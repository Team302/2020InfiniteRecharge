
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

    // Create the Chassis Control (state) modes which puts the auton choices and teleop drive modes 
    // on the dashboard for selection.
    m_chassisStateMgr = new ChassisStateMgr();

    m_hook = HookDeliveryStateMgr::GetInstance();
    m_winch = ClimberStateMgr::GetInstance();


    m_powerCells = BallManipulator::GetInstance();
    m_shooterHood = MechanismFactory::GetMechanismFactory()->GetIMechanism(MechanismTypes::SHOOTER_HOOD);
    m_turret = MechanismFactory::GetMechanismFactory()->GetIMechanism(MechanismTypes::TURRET);
    m_impeller = MechanismFactory::GetMechanismFactory()->GetIMechanism(MechanismTypes::IMPELLER);
    m_shooter = MechanismFactory::GetMechanismFactory()->GetIMechanism(MechanismTypes::SHOOTER);
    m_controller = TeleopControl::GetInstance();

    // pick test mode
    m_testChooser.SetDefaultOption( m_noTest, m_noTest);
    m_testChooser.AddOption( m_buttonBoxTest, m_buttonBoxTest );
    m_testChooser.AddOption( m_dragonXBoxTest, m_dragonXBoxTest );    
    m_testChooser.AddOption( m_intakeTest, m_intakeTest );
    m_testChooser.AddOption( m_impellerTest, m_impellerTest );
    m_testChooser.AddOption( m_ballTransferTest, m_ballTransferTest );
    //m_testChooser.AddOption( m_shooterTest, m_shooterTest );

    SmartDashboard::PutData("Test", &m_testChooser);

    m_buttonBoxDisplay = nullptr;
    m_xBoxDisplay = nullptr;
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
}


/// @brief Runs every 20 milliseconds when the autonomous state is active.
/// @return void
void Robot::AutonomousPeriodic() 
{
    //Real auton magic right here:
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
    m_powerCells->RunCurrentState();
    frc::SmartDashboard::PutNumber("Turret position", m_turret->GetCurrentPosition());

    m_winch->RunCurrentState();
    m_hook->RunCurrentState();
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
