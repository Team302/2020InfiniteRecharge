//====================================================================================================================================================
// Copyright 2019 Lake Orion Robotics FIRST Team 302
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

#include <string>

#include <controllers/DriverFeedback.h>
#include <states/balltransfer/BallTransferStateMgr.h>
//#include <states/chassis/ChassisStateMgr.h>
#include <states/controlPanel/ControlPanelStateMgr.h>
#include <states/impeller/ImpellerStateMgr.h>
#include <states/intake/IntakeStateMgr.h>
#include <states/shooter/ShooterStateMgr.h>
#include <states/shooterHood/ShooterHoodStateMgr.h>
#include <states/turret/TurretStateMgr.h>
#include <frc/SmartDashboard/SmartDashboard.h>

using namespace frc;
using namespace std;

DriverFeedback::DriverFeedback()
{
    m_ballTransfer = BallTransferStateMgr::GetInstance();
    //m_chassis = ChassisStateMgr::GetInstance();
    m_controlPanel = ControlPanelStateMgr::GetInstance();
    m_impeller = ImpellerStateMgr::GetInstance();
    m_intake = IntakeStateMgr::GetInstance();
    m_shooter = ShooterStateMgr::GetInstance();
    m_shooterHood = ShooterHoodStateMgr::GetInstance();
    m_turret = TurretStateMgr::GetInstance();
}

void DriverFeedback::periodic()
{
    auto ballTransferState = m_ballTransfer -> GetCurrentState();
    SmartDashboard::PutString( string("Ball Transfer State") ,to_string(ballTransferState));

    auto controlPanelState = m_controlPanel -> GetCurrentState();
    SmartDashboard::PutString( string("Control Panel State"), to_string(controlPanelState));

    auto impellerState = m_impeller -> GetCurrentState();
    SmartDashboard::PutString( string("Impeller State"), to_string(impellerState));

    auto intakeState = m_intake -> GetCurrentState();
    SmartDashboard::PutString( string("Intake State"), to_string(intakeState));

    auto shooterState = m_shooter -> GetCurrentState();
    SmartDashboard::PutString( string("Shooter State"), to_string(shooterState));

    auto shooterHoodState = m_shooterHood -> GetCurrentState();
    SmartDashboard::PutString( string("Shooter Hood State"), to_string(shooterHoodState));

    auto turretState = m_turret -> GetCurrentState();
    SmartDashboard::PutString( string("Turret State"), to_string(turretState));
}