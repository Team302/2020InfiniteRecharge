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

// FRC includes

// Team 302 includes
#include <states/BallManipulator.h>
#include <states/balltransfer/BallTransferStateMgr.h>
#include <states/impeller/ImpellerStateMgr.h>
#include <states/intake/IntakeStateMgr.h>
#include <states/shooter/ShooterStateMgr.h>
#include <states/shooterhood/ShooterHoodStateMgr.h>
#include <states/turret/TurretStateMgr.h>
#include <utils/Logger.h>

// Third Party Includes

using namespace std;

BallManipulator* BallManipulator::m_instance = nullptr;

/// @brief Get the ball manipulator (singleton) class
/// @return BallManipulator*  singleton class
BallManipulator* BallManipulator::GetInstance()
{
	if ( BallManipulator::m_instance == nullptr )
	{
		BallManipulator::m_instance = new BallManipulator();
	}
	return BallManipulator::m_instance;
}


/// @brief    initialize the state manager, parse the configuration file and create the states.
BallManipulator::BallManipulator() : m_currentState( BALL_MANIPULATOR_STATE::OFF),
                                     m_intake( IntakeStateMgr::GetInstance() ),
                                     m_impeller( ImpellerStateMgr::GetInstance() ),
                                     m_transfer( BallTransferStateMgr::GetInstance() ),
                                     m_turret ( TurretStateMgr::GetInstance() ),
                                     m_shooter( ShooterStateMgr::GetInstance() ), 
                                     m_hood( ShooterHoodStateMgr::GetInstance() )
                                    
{
    m_intake->SetCurrentState( IntakeStateMgr::INTAKE_STATE::OFF, false );
    m_impeller->SetCurrentState( ImpellerStateMgr::IMPELLER_STATE::OFF, false );
    m_transfer->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::OFF, false );
    m_turret->SetCurrentState( TurretStateMgr::TURRET_STATE::HOLD, false );
    m_shooter->SetCurrentState( ShooterStateMgr::SHOOTER_STATE::OFF, false );
    m_hood->SetCurrentState( ShooterHoodStateMgr::SHOOTER_HOOD_STATE::HOLD_POSITION, false );
    
}

/// @brief  run the current state
/// @return void
void BallManipulator::RunCurrentState()
{
    // run the current state
    m_intake->RunCurrentState();
    m_impeller->RunCurrentState();
    m_transfer->RunCurrentState();
    m_turret->RunCurrentState();
    m_shooter->RunCurrentState();
    m_hood->RunCurrentState();

}

/// @brief  set the current state, initialize it and run it
/// @return void
void BallManipulator::SetCurrentState
(
    BALL_MANIPULATOR_STATE  state
)
{
    m_currentState = state;
    switch ( state )
    {
        case BALL_MANIPULATOR_STATE::OFF:
            m_intake->SetCurrentState( IntakeStateMgr::INTAKE_STATE::OFF, false );
            m_impeller->SetCurrentState( ImpellerStateMgr::IMPELLER_STATE::OFF, false );
            m_transfer->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::OFF, false );
            m_turret->SetCurrentState( TurretStateMgr::TURRET_STATE::HOLD, false );
            m_shooter->SetCurrentState( ShooterStateMgr::SHOOTER_STATE::OFF, false );
            m_hood->SetCurrentState( ShooterHoodStateMgr::SHOOTER_HOOD_STATE::HOLD_POSITION, false );
            break;

        case BALL_MANIPULATOR_STATE::INTAKE:
            m_intake->SetCurrentState( IntakeStateMgr::INTAKE_STATE::ON, false );
            if ( m_impeller->GetCurrentState() == ImpellerStateMgr::IMPELLER_STATE::OFF )
            {
                m_impeller->SetCurrentState( ImpellerStateMgr::IMPELLER_STATE::HOLD, false );
            }
            if ( m_transfer->GetCurrentState() == BallTransferStateMgr::BALL_TRANSFER_STATE::OFF )
            {
                m_transfer->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::TO_IMPELLER , false );
            }
            break;

        case BALL_MANIPULATOR_STATE::INTAKE_HUMAN_PLAYER:
            m_intake->SetCurrentState( IntakeStateMgr::INTAKE_STATE::HUMANPLAYER, false );  
            if ( m_impeller->GetCurrentState() == ImpellerStateMgr::IMPELLER_STATE::OFF )
            {
                m_impeller->SetCurrentState( ImpellerStateMgr::IMPELLER_STATE::HOLD, false );
            }
            if ( m_transfer->GetCurrentState() == BallTransferStateMgr::BALL_TRANSFER_STATE::OFF )
            {
                m_transfer->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::TO_IMPELLER , false );
            }
            break;

        case BALL_MANIPULATOR_STATE::HOLD:
            m_intake->SetCurrentState( IntakeStateMgr::INTAKE_STATE::OFF, false );
            m_impeller->SetCurrentState( ImpellerStateMgr::IMPELLER_STATE::OFF, false );
            m_transfer->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::TO_IMPELLER , false );
            m_turret->SetCurrentState( TurretStateMgr::TURRET_STATE::LIMELIGHT_AIM, false );
            m_shooter->SetCurrentState( ShooterStateMgr::SHOOTER_STATE::SHOOT, false );
            m_hood->SetCurrentState( ShooterHoodStateMgr::SHOOTER_HOOD_STATE::HOLD_POSITION, false );  // todo auto aim is needed
            break;

        case BALL_MANIPULATOR_STATE::GET_READY_TO_SHOOT:
            m_impeller->SetCurrentState( ImpellerStateMgr::IMPELLER_STATE::HOLD, false );
            m_transfer->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::TO_IMPELLER, false );
            m_turret->SetCurrentState( TurretStateMgr::TURRET_STATE::LIMELIGHT_AIM, false );
            m_shooter->SetCurrentState( ShooterStateMgr::SHOOTER_STATE::GET_READY, false );
            m_hood->SetCurrentState( ShooterHoodStateMgr::SHOOTER_HOOD_STATE::HOLD_POSITION, false );  // todo auto aim is needed
            break;

        case BALL_MANIPULATOR_STATE::SHOOT:
            m_impeller->SetCurrentState( ImpellerStateMgr::IMPELLER_STATE::TO_SHOOTER, false );
            m_transfer->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::TO_SHOOTER, false );
            m_turret->SetCurrentState( TurretStateMgr::TURRET_STATE::LIMELIGHT_AIM, false );
            m_shooter->SetCurrentState( ShooterStateMgr::SHOOTER_STATE::SHOOT, false );
            m_hood->SetCurrentState( ShooterHoodStateMgr::SHOOTER_HOOD_STATE::HOLD_POSITION, false );  // todo auto aim is needed
            break;

        case BALL_MANIPULATOR_STATE::TURRET_MANUAL:
            m_turret->SetCurrentState( TurretStateMgr::TURRET_STATE::MANUAL_AIM, false);
            break;

        case BALL_MANIPULATOR_STATE::IMPELLER_MANUAL:
            m_impeller->SetCurrentState( ImpellerStateMgr::IMPELLER_STATE::MANUAL, false); //PUT IN NEW IMPELLER STATE
            break;

        case BALL_MANIPULATOR_STATE::BALL_TRANSFER_UP:
            m_transfer->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::TO_SHOOTER, false); 
            break;
        
        case BALL_MANIPULATOR_STATE::BALL_TRANSFER_DOWN:
            m_transfer->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::TO_IMPELLER, false);

        case BALL_MANIPULATOR_STATE::SHOOTER_WHEELS_TO_SPEED:
            m_shooter->SetCurrentState( ShooterStateMgr::SHOOTER_STATE::GET_READY, false); 
            break;

        case BALL_MANIPULATOR_STATE::SHOOTER_WHEELS_STOP:
            m_shooter->SetCurrentState( ShooterStateMgr::SHOOTER_STATE::OFF, false);
            break;

        default:
            break;
    }
    RunCurrentState();

}

void BallManipulator::SetApproxAngle
(
    double angle
)
{
    if ( m_turret != nullptr )
    {
        m_turret->SetApproxTargetAngle( angle );
    }
}

void BallManipulator::teleop()
{
    auto control = TeleopControl::GetInstance();
    if (control != nullptr)
    {
        auto isHumanPlayerPressed = control ->IsButtonPressed(TeleopControl::INTAKE_HUMAN_PLAYER);
        auto isIntakePressed = control -> IsButtonPressed(TeleopControl::FLOOR_PICKUP);
        auto isReadyToShootPressed = control -> IsButtonPressed(TeleopControl::GET_READY_TO_SHOOT);
        auto turretManual = control -> GetAxisValue(TeleopControl::TURRET_MANUAL_AXIS);
        auto impellerManual = control -> GetAxisValue(TeleopControl::IMPELLER_MANUAL);
        auto ballTransferUp = control -> IsButtonPressed(TeleopControl::BALL_TRANSFER_WHEELS_UP);
        auto ballTransferDown = control -> IsButtonPressed(TeleopControl::BALL_TRANSFER_WHEELS_DOWN);
        auto isShooterWheelsToSpeedPressed = control -> IsButtonPressed(TeleopControl::SHOOTER_WHEELS_TO_SPEED);
        auto isShooterWheelsStoppedPressed = control -> IsButtonPressed(TeleopControl::SHOOTER_WHEELS_STOP);
        if (isHumanPlayerPressed)
        {
            SetCurrentState(BallManipulator::BALL_MANIPULATOR_STATE::INTAKE_HUMAN_PLAYER);
        }
        else if (isIntakePressed)
        {
            SetCurrentState(BallManipulator::BALL_MANIPULATOR_STATE::INTAKE);
        }
        else if (isReadyToShootPressed)
        {
            SetCurrentState(BallManipulator::BALL_MANIPULATOR_STATE::SHOOT);
        }
        else if (turretManual)
        {
            SetCurrentState(BallManipulator::BALL_MANIPULATOR_STATE::TURRET_MANUAL);
        }
        else if (impellerManual)
        {
            SetCurrentState(BallManipulator::BALL_MANIPULATOR_STATE::IMPELLER_MANUAL);
        }
        else if (ballTransferUp)
        {
            SetCurrentState(BallManipulator::BALL_MANIPULATOR_STATE::BALL_TRANSFER_UP);
        }
        else if (ballTransferDown)
        {
            SetCurrentState(BallManipulator::BALL_MANIPULATOR_STATE::BALL_TRANSFER_DOWN);
        }
        else if (isShooterWheelsToSpeedPressed)
        {
            SetCurrentState(BallManipulator::BALL_MANIPULATOR_STATE::SHOOTER_WHEELS_TO_SPEED);
        }
        else if (isShooterWheelsStoppedPressed)
        {
            SetCurrentState(BallManipulator::BALL_MANIPULATOR_STATE::SHOOTER_WHEELS_STOP);
        }
    }
}
