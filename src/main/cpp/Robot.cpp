
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

// Team 302 Includes
#include <Robot.h>
#include <xmlhw/RobotDefn.h>
#include <auton/CyclePrimitives.h>
#include <hw/DragonFalcon.h>
#include <hw/usages/MotorControllerUsage.h>
#include <ctre/Phoenix.h>
#include <gamepad/DragonXBox.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include <controllers/ControlData.h>


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
    //unique_ptr<RobotDefn>  robotXml = make_unique<RobotDefn>();
    //robotXml->ParseXML();

    // Display the autonomous choices on the dashboard for selection.
    // comment out for now since auton hasn't been implemented
    // m_cyclePrims = new CyclePrimitives();
    m_falcon1 = new DragonFalcon(MotorControllerUsage::SHOOTER_1, 1, 1, 2048, 1.0);
    m_falcon2 = new DragonFalcon(MotorControllerUsage::SHOOTER_2, 3, 2, 2048, 1.0);
    m_xbox = new DragonXBox(0);

    m_falcon1->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor,0,50);
    m_falcon1->EnableBrakeMode(false );
    m_falcon1->Invert(false );
    m_falcon1->SetSensorInverted(false);

    m_falcon2->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor,0,50);
    m_falcon2->EnableBrakeMode(false );
    m_falcon2->Invert(true);
    m_falcon2->SetSensorInverted(false);

    //m_falcon2->SetAsSlave(1);

    //m_falcon1->SetControlMode(ControlModes::CONTROL_TYPE::VELOCITY_DEGREES);
    //m_falcon2->SetControlMode(ControlModes::CONTROL_TYPE::VELOCITY_DEGREES);

    m_initialSpeed = 3000;
    ControlData* controlData = new ControlData(ControlModes::VELOCITY_DEGREES,"  ",10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,1.0,0.0);
    m_falcon1->SetControlConstants(controlData);
    m_falcon1->SetControlMode(ControlModes::PERCENT_OUTPUT);
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
    //m_chassisStateMgr->Init();

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
    //m_chassisStateMgr->SetState( ChassisStateMgr::CHASSIS_STATE::TELEOP );
}


///-----------------------------------------------------------------------
/// Method:      TeleopPeriodic
/// Description: Runs every 20 milliseconds when the teleoperated state is 
///              active.
///-----------------------------------------------------------------------
void Robot::TeleopPeriodic() 
{
    m_falcon1->Set(.60); //bottom
    m_falcon2->Set(.40); //top
    double speed1 = m_falcon1->GetRPS();
    double speed2 = m_falcon2->GetRPS();
    SmartDashboard::PutNumber("speed1", speed1);
    SmartDashboard::PutNumber("speed2", speed2);
    /*double speed = m_initialSpeed;
    //m_chassisStateMgr->RunCurrentState();
    m_falcon1->SetControlMode(ControlModes::CONTROL_TYPE::VELOCITY_DEGREES);
    m_falcon2->SetControlMode(ControlModes::CONTROL_TYPE::VELOCITY_DEGREES);

    if(m_xbox->IsButtonPressed(IDragonGamePad::A_BUTTON))
    {
        speed += 500;
        m_falcon1->Set(speed * 6);
    } vf                        
    else if(m_xbox->IsButtonPressed(IDragonGamePad::B_BUTTON))
    {
        speed -= 500;
        m_falcon1->Set(speed * 6);
    }
    else
    {
        m_falcon1->Set(speed * 6);
    }

    SmartDashboard::PutNumber("Speed", speed);
    */
    
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
