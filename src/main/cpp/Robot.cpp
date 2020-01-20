
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

// Team 302 Includes
#include <Robot.h>
#include <xmlhw/RobotDefn.h>
#include <auton/CyclePrimitives.h>
#include <controllers/teleopdrive/ArcadeDrive.h>
#include <controllers/teleopdrive/GTADrive.h>
#include <controllers/teleopdrive/TankDrive.h>

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
    
    // pick drive mode
    m_driveModeChooser.SetDefaultOption( m_driveModeArcade, m_driveModeArcade);
    m_driveModeChooser.AddOption( m_driveModeGTA, m_driveModeGTA );
    m_driveModeChooser.AddOption( m_driveModeTank, m_driveModeTank );


    // Create a TeleopDrive Object passing the chasis and controller objects
    m_arcade = make_unique<ArcadeDrive>();
    m_tank = make_unique<TankDrive>();
    m_gta = make_unique<GTADrive>();
    m_currentDrive = m_arcade;

    SmartDashboard::PutData("Drive Mode", &m_driveModeChooser);
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
    m_driveModeSelected = m_driveModeChooser.GetSelected();
    if(m_driveModeSelected == m_driveModeArcade) 
    {
        m_currentDrive == m_arcade;
    }
    else if ( m_driveModeSelected == m_driveModeGTA )
    {
        m_currentDrive = m_gta;
    }
    else if ( m_driveModeSelected == m_driveModeTank )
    {
        m_currentDrive = m_tank;
    }
    else
    {
        m_currentDrive = m_arcade;
    }
    m_currentDrive->Init();
    m_currentDrive->Run();
}


///-----------------------------------------------------------------------
/// Method:      TeleopPeriodic
/// Description: Runs every 20 milliseconds when the teleoperated state is 
///              active.
///-----------------------------------------------------------------------
void Robot::TeleopPeriodic() 
{
    m_currentDrive->Run();
}


///-----------------------------------------------------------------------
/// Method:      TestInit
/// Description: This initializes the test state
///-----------------------------------------------------------------------
void Robot::TestInit() 
{

}


///-----------------------------------------------------------------------
/// Method:      TestPeriodic
/// Description: Runs every 20 milliseconds when the test state is 
///              active.
///-----------------------------------------------------------------------
void Robot::TestPeriodic() 
{

}

#ifndef RUNNING_FRC_TESTS
int main() 
{
    return frc::StartRobot<Robot>(); 
}
#endif
