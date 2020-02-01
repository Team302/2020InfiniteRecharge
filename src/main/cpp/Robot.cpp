
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
#include <hw/DragonTalon.h>
#include <hw/usages/MotorControllerUsage.h>
#include <hw/factories/DragonMotorControllerFactory.h>
#include <controllers/ControlData.h>
#include <controllers/ControlModes.h>

#include <ctre/Phoenix.h>

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

    // Display the autonomous choices on the dashboard for selection.
    // comment out for now since auton hasn't been implemented
    // m_cyclePrims = new CyclePrimitives();
    auto factory = DragonMotorControllerFactory::GetInstance();
    m_motor1 = factory->CreateMotorController("TALONSRX",1,0,"SHOOTER_1",false, false, ctre::phoenix::motorcontrol::FeedbackDevice::QuadEncoder,1024, 1.0, false, -1, 10, 20, 40, false);
    m_motor2 = factory->CreateMotorController("TALONSRX",3,1,"SHOOTER_2",true, false, ctre::phoenix::motorcontrol::FeedbackDevice::QuadEncoder,1024, 1.0, false, -1, 10, 20, 40, false);

    ControlData* controlConstants = new ControlData(ControlModes::CONTROL_TYPE::VELOCITY_DEGREES,ControlModes::CONTROL_RUN_LOCS::MOTOR_CONTROLLER, IDENTIFIER, K_P, K_I, K_D, K_F, INTEGRAL_ZONE, MAX_ACCEL, CRUISE_VELOC, PEAK, NOMINAL);
    m_motor1->SetControlConstants(controlConstants);
    m_motor2->SetControlConstants(controlConstants);

    m_motor1->SetControlMode(ControlModes::CONTROL_TYPE::PERCENT_OUTPUT);
    m_motor2->SetControlMode(ControlModes::CONTROL_TYPE::VELOCITY_DEGREES);
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
    
}


///-----------------------------------------------------------------------
/// Method:      TeleopPeriodic
/// Description: Runs every 20 milliseconds when the teleoperated state is 
///              active.
///-----------------------------------------------------------------------
void Robot::TeleopPeriodic() 
{
    m_motor1->Set(1.0);
    m_motor2->Set(3000.0*6.0);

    frc::SmartDashboard::PutNumber("Position", m_motor1->GetRotations());
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
