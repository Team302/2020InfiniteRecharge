
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
#include <gamepad/DragonXBox.h>
#include <gamepad/IDragonGamePad.h>

// Team 302 Includes
#include <Robot.h>
#include <xmlhw/RobotDefn.h>
//#include <auton/CyclePrimitives.h>

#include <ctre/Phoenix.h>
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
    //std::unique_ptr<RobotDefn>  robotXml = std::make_unique<RobotDefn>();
    //robotXml->ParseXML();

    // Display the autonomous choices on the dashboard for selection.
    //m_cyclePrims = new CyclePrimitives();
  
    m_turretTalon = new TalonSRX(TURRET_ID);
    m_xbox = new DragonXBox(0);

    m_turretTalon->ConfigFactoryDefault();
    m_turretTalon->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder,
                                        0, 
                                        10);
    m_turretTalon->SetSensorPhase(false);
    //m_turretTalon->ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource::LimitSwitchSource_FeedbackConnector, ctre::phoenix::motorcontrol::LimitSwitchNormal::LimitSwitchNormal_NormallyOpen);
    //m_turretTalon->ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource::LimitSwitchSource_FeedbackConnector, ctre::phoenix::motorcontrol::LimitSwitchNormal::LimitSwitchNormal_NormallyClosed);
    m_turretTalon->SetStatusFramePeriod(StatusFrameEnhanced::Status_13_Base_PIDF0, 10, 10);
    m_turretTalon->SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, 10, 10);
    m_turretTalon->ConfigNominalOutputForward(0, 10);
    m_turretTalon->ConfigNominalOutputReverse(0, 10);
    m_turretTalon->ConfigPeakOutputForward(1,10);
    m_turretTalon->ConfigPeakOutputReverse(-1,10);

    m_turretTalon->SelectProfileSlot(0, 0);
    m_turretTalon->ConfigMotionCruiseVelocity(1500, 10);
    m_turretTalon->ConfigMotionAcceleration(1500, 10);
    

    m_turretTalon->Config_kP(0, K_P);
    m_turretTalon->Config_kI(0, K_I);
    m_turretTalon->Config_kD(0, K_I);
    m_turretTalon->Config_kF(0, K_F);



    
    
    m_turretTalon->SetInverted(false);

    m_initialPosition = m_turretTalon->GetSelectedSensorPosition();

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
    m_cyclePrims->Init();

    TeleopInit();
}


///-----------------------------------------------------------------------
/// Method:      AutonomousPeriodic
/// Description: Runs every 20 milliseconds when the autonomous state is 
///              active.
///-----------------------------------------------------------------------
void Robot::AutonomousPeriodic() 
{
        //Real auton magic right here:
    m_cyclePrims->RunCurrentPrimitive();

    TeleopPeriodic();
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
    double power = m_xbox->GetAxisValue(IDragonGamePad::LEFT_JOYSTICK_Y) * .5;
    double currentPosition = m_turretTalon->GetSelectedSensorPosition();
    if (m_xbox->IsButtonPressed(IDragonGamePad::A_BUTTON))
    {
        m_turretTalon->Set(ctre::phoenix::motorcontrol::ControlMode::MotionMagic, m_initialPosition + 1000.0);
        frc::SmartDashboard::PutBoolean("SetPosition", true);
    }

    else
    {
        m_turretTalon->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, power);
        frc::SmartDashboard::PutBoolean("SetPosition", false);
    }
    double position = m_turretTalon->GetSelectedSensorPosition();
    bool forwardLimitSwitch = m_turretTalon->GetSensorCollection().IsFwdLimitSwitchClosed();
    bool reverseLimitSwitch = m_turretTalon->GetSensorCollection().IsRevLimitSwitchClosed();
    frc::SmartDashboard::PutNumber("Current Position", position);
    frc::SmartDashboard::PutBoolean("forward Limit Switch", forwardLimitSwitch);
    frc::SmartDashboard::PutBoolean("Reverse limit switch", reverseLimitSwitch);
    frc::SmartDashboard::PutNumber("power", power);
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
