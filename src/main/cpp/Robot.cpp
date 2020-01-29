
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

//========================================================================================================
/// Robot.cpp
//========================================================================================================
///
/// File Description:
///     The main robot code.  The Init methods get called when that state gets entered and then the 
///     Periodic methods get called every 20 milliseconds.
///
//========================================================================================================

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
#include <controllers/chassis/ChassisStateMgr.h>

using namespace std;
using namespace frc;


///-----------------------------------------------------------------------
/// Method:      RobotInit
/// Description: When the robot gets created this gets called.  It initializes
///              the robot subsystems (hardware).
///-----------------------------------------------------------------------
void Robot::RobotInit() 
{
    // Read the robot definition from the xml configuration files and
    // create the hardware (chassis + mechanisms along with their talons,
    // solenoids, digital inputs, analog inputs, etc.
    unique_ptr<RobotDefn>  robotXml = make_unique<RobotDefn>();
    robotXml->ParseXML();

    // Display the autonomous choices on the dashboard for selection.
    // comment out for now since auton hasn't been implemented
    // m_cyclePrims = new CyclePrimitives();

    m_chassisStateMgr = new ChassisStateMgr();

        // pick test mode
    m_testChooser.SetDefaultOption( m_noTest, m_noTest);
    m_testChooser.AddOption( m_buttonBox, m_buttonBox );
    m_testChooser.AddOption( m_dragonXBox, m_dragonXBox );
    SmartDashboard::PutData("Test", &m_testChooser);

    m_buttonBoxDisplay = nullptr;
    m_xBoxDisplay = nullptr;

}

///-----------------------------------------------------------------------
/// Method:      RobotPeriodic
/// Description: This function is called every robot packet, no matter the 
///              mode. This is used for items like diagnostics that run 
///              during disabled, autonomous, teleoperated and test modes
///              (states).  THis runs after the specific state periodic 
///              methods and before the LiveWindow and SmartDashboard updating.
///-----------------------------------------------------------------------
void Robot::RobotPeriodic() 
{

}


///-----------------------------------------------------------------------
/// Method:      AutonomousInit
/// Description: This initializes the autonomous state
///-----------------------------------------------------------------------
void Robot::AutonomousInit() 
{
    m_chassisStateMgr->Init();

    // run selected auton option
    //m_cyclePrims->Init();

}


///-----------------------------------------------------------------------
/// Method:      AutonomousPeriodic
/// Description: Runs every 20 milliseconds when the autonomous state is 
///              active.
///-----------------------------------------------------------------------
void Robot::AutonomousPeriodic() 
{
    //Real auton magic right here:
    //m_cyclePrims->RunCurrentPrimitive();
}


///-----------------------------------------------------------------------
/// Method:      TeleopInit
/// Description: This initializes the teleoperated state
///-----------------------------------------------------------------------
void Robot::TeleopInit() 
{
    m_chassisStateMgr->SetState( ChassisStateMgr::CHASSIS_STATE::TELEOP );
}


///-----------------------------------------------------------------------
/// Method:      TeleopPeriodic
/// Description: Runs every 20 milliseconds when the teleoperated state is 
///              active.
///-----------------------------------------------------------------------
void Robot::TeleopPeriodic() 
{
    m_chassisStateMgr->RunCurrentState();
}


///-----------------------------------------------------------------------
/// Method:      TestInit
/// Description: This initializes the test state
///-----------------------------------------------------------------------
void Robot::TestInit() 
{
    m_testSelected = m_testChooser.GetSelected();
    if(m_testSelected == m_noTest) 
    {
        m_currentTest == NONE;
    }
    else if ( m_testSelected == m_buttonBox )
    {
        m_currentTest = BUTTON_BOX;
        m_buttonBoxDisplay = new ButtonBoxDisplay();
    }
    else if ( m_testSelected == m_buttonBox )
    {
        m_currentTest = XBOX;
        m_xBoxDisplay = new XboxDisplay();
    }
    else
    {
        m_currentTest = NONE;
    }
}


///-----------------------------------------------------------------------
/// Method:      TestPeriodic
/// Description: Runs every 20 milliseconds when the test state is 
///              active.
///-----------------------------------------------------------------------
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

        default:
            break;
    }
}

#ifndef RUNNING_FRC_TESTS
int main() 
{
    return frc::StartRobot<Robot>(); 
}
#endif
