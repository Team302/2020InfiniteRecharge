
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

// C++ includes
#include <string>
#include <memory>

// frc includes
#include <frc/smartdashboard/SmartDashboard.h>

// team 302 includes
#include <states/chassis/ChassisStateMgr.h>
#include <states/chassis/ArcadeDrive.h>
#include <states/chassis/GTADrive.h>
#include <states/chassis/TankDrive.h>
#include <utils/Logger.h>
#include <auton/CyclePrimitives.h>

using namespace std;
using namespace frc;

ChassisStateMgr::ChassisStateMgr() : m_arcade(make_shared<ArcadeDrive>()),
                                     m_gta(make_shared<GTADrive>()),
                                     m_tank(make_shared<TankDrive>()),
                                     m_currentDrive(m_arcade),
                                     m_cyclePrims(make_unique<CyclePrimitives>()),
                                     m_currentState( ChassisStateMgr::CHASSIS_STATE::AUTON)
{
    
    // pick drive mode
    m_driveModeChooser.SetDefaultOption( m_driveModeArcade, m_driveModeArcade);
    m_driveModeChooser.AddOption( m_driveModeArcadeCurve, m_driveModeArcadeCurve );
    m_driveModeChooser.AddOption( m_driveModeGTA, m_driveModeGTA );
    m_driveModeChooser.AddOption( m_driveModeGTACurve, m_driveModeGTACurve );
    m_driveModeChooser.AddOption( m_driveModeTank, m_driveModeTank );

    SmartDashboard::PutData("Drive Mode", &m_driveModeChooser);

}

void ChassisStateMgr::Init()
{
    if ( m_currentState == CHASSIS_STATE::TELEOP )
    {
        m_driveModeSelected = m_driveModeChooser.GetSelected();
        Logger::GetLogger()->LogError( string("ChassisStateMgr"), m_driveModeSelected );
        if( m_driveModeSelected == m_driveModeArcade || m_driveModeSelected == m_driveModeArcadeCurve ) 
        {
            m_currentDrive = m_arcade;
            m_arcade->SetCurvatureBased( ( m_driveModeSelected == m_driveModeArcadeCurve ) );
            Logger::GetLogger()->LogError(string("ChassisStateMgr"), string("arcade"));
        }
        else if ( m_driveModeSelected == m_driveModeGTA || m_driveModeSelected == m_driveModeGTACurve )
        {
            m_currentDrive = m_gta;
            m_gta->SetCurvatureBased( ( m_driveModeSelected == m_driveModeGTACurve ) );
            Logger::GetLogger()->LogError(string("ChassisStateMgr"), string("gta"));
        }
        else if ( m_driveModeSelected == m_driveModeTank )
        {
            m_currentDrive = m_tank;
            Logger::GetLogger()->LogError(string("ChassisStateMgr"), string("tank"));
        }
        else
        {
            m_currentDrive = m_arcade;
            Logger::GetLogger()->LogError(string("ChassisStateMgr"), string("arcade2"));
        }

        m_currentDrive.get()->Init();
//        m_currentDrive->Run();
   }
    else if ( m_currentState == CHASSIS_STATE::AUTON )
    {
        m_cyclePrims.get()->Init();
 //       m_cyclePrims.get()->Run();
    }
}

void ChassisStateMgr::RunCurrentState()
{
    if ( m_currentState == CHASSIS_STATE::TELEOP )
    {
        if ( m_currentDrive.get() != nullptr )
        {
            m_currentDrive.get()->Run();
        }
        else
        {
            Logger::GetLogger()->LogError( string("ChassisStateMgr::RunCurrentState"), string("unsupported state"));
        }
    }
    else if ( m_currentState == CHASSIS_STATE::AUTON )
    {
        m_cyclePrims.get()->Run();
    }
    else
    {
        Logger::GetLogger()->LogError( string("ChassisStateMgr::RunCurrentState"), string("current drive mode is not selected"));
    }
    
}

void ChassisStateMgr::SetState( ChassisStateMgr::CHASSIS_STATE state )
{
    m_currentState = state;
    
    if ( m_currentState == CHASSIS_STATE::TELEOP )
    {
        m_currentDrive->Run();
    }
    else if ( m_currentState == CHASSIS_STATE::AUTON )
    {
        m_cyclePrims.get()->Init();
        m_cyclePrims.get()->Run();
    }
    else
    {
        Logger::GetLogger()->LogError( string("ChassisStateMgr::SetState"), string("unsupported state"));
    }
    
}