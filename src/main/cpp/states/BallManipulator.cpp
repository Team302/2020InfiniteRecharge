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
#include <gamepad/TeleopControl.h>
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
    m_turret->SetCurrentState( TurretStateMgr::TURRET_STATE::HOLD, false, 0.0 );
    m_shooter->SetCurrentState( ShooterStateMgr::SHOOTER_STATE::OFF, false );
    m_hood->SetCurrentState( ShooterHoodStateMgr::SHOOTER_HOOD_STATE::HOLD_POSITION, false );
}

/// @brief  run the current state
/// @return void
void BallManipulator::RunCurrentState()
{
    auto controller = TeleopControl::GetInstance();

    // process teleop/manual interrupts
       
        if ( controller != nullptr )
        {
            if (controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::OFF))
            {
                SetCurrentState( BALL_MANIPULATOR_STATE::OFF, 0.0); 
            }
            if (controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::INTAKE))
            {
                SetCurrentState(BALL_MANIPULATOR_STATE::INTAKE, 0.0);
            }
            if (controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::INTAKE_HUMAN_PLAYER))
            {
                SetCurrentState( BALL_MANIPULATOR_STATE::INTAKE_HUMAN_PLAYER, 0.0); 
            }
            if (controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::GET_READY_TO_SHOOT))
            {
                SetCurrentState(BALL_MANIPULATOR_STATE ::GET_READY_TO_SHOOT, 0.0);
            }
            if (controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::SHOOT))
            {
                SetCurrentState(BALL_MANIPULATOR_STATE::SHOOT, 0.0); 
            }
            if (controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::UNJAM_CLOCKWISE))
            {
                SetCurrentState(BALL_MANIPULATOR_STATE::UNJAM_CLOCKWISE, 0.0); 
            }
            if (controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::UNJAM_COUNTERCLOCKWISE))
            {
                SetCurrentState(BALL_MANIPULATOR_STATE::UNJAM_COUNTERCLOCKWISE, 0.0); 
            }     
            if (controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::TRANSFER_UP)) 
            {
                SetCurrentState(BALL_MANIPULATOR_STATE::TRANSFER_UP, 0.0);
            } 
            if (controller->IsButtonPressed (TeleopControl::FUNCTION_IDENTIFIER::TRANSFER_DOWN))
            {
                SetCurrentState(BALL_MANIPULATOR_STATE::TRANSFER_DOWN, 0.0);
            }    
    
        }
    
    //SetCurrentState(m_currentState);
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
    BALL_MANIPULATOR_STATE  state,
    double turretAngle
)
{
    m_currentState = state;
    switch ( state )
    {
        case BALL_MANIPULATOR_STATE::OFF:
            m_intake->SetCurrentState( IntakeStateMgr::INTAKE_STATE::OFF, false );
            m_impeller->SetCurrentState( ImpellerStateMgr::IMPELLER_STATE::OFF, false );
            m_transfer->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::OFF, false );
            m_turret->SetCurrentState( TurretStateMgr::TURRET_STATE::HOLD, false , 0.0);
            //m_shooter->SetCurrentState( ShooterStateMgr::SHOOTER_STATE::OFF, false );
            m_hood->SetCurrentState( ShooterHoodStateMgr::SHOOTER_HOOD_STATE::HOLD_POSITION, false );
            break;

        case BALL_MANIPULATOR_STATE::INTAKE:
            m_intake->SetCurrentState( IntakeStateMgr::INTAKE_STATE::ON, false );
            m_impeller->SetCurrentState( ImpellerStateMgr::IMPELLER_STATE::OFF, false );
            m_transfer->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::TO_IMPELLER , false );
            break;

        case BALL_MANIPULATOR_STATE::INTAKE_HUMAN_PLAYER:
            m_intake->SetCurrentState( IntakeStateMgr::INTAKE_STATE::HUMANPLAYER, false );  
            m_impeller->SetCurrentState( ImpellerStateMgr::IMPELLER_STATE::HOLD, false );
            m_transfer->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::TO_IMPELLER , false );
            break;

        case BALL_MANIPULATOR_STATE::HOLD:
            m_intake->SetCurrentState( IntakeStateMgr::INTAKE_STATE::OFF, false );
            m_impeller->SetCurrentState( ImpellerStateMgr::IMPELLER_STATE::OFF, false );
            m_transfer->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::TO_IMPELLER , false );
            m_turret->SetCurrentState( TurretStateMgr::TURRET_STATE::HOLD, false , 0.0);
            //m_shooter->SetCurrentState( ShooterStateMgr::SHOOTER_STATE::OFF, false );
            m_hood->SetCurrentState( ShooterHoodStateMgr::SHOOTER_HOOD_STATE::HOLD_POSITION, false );  // todo auto aim is needed
            break;

        case BALL_MANIPULATOR_STATE::GET_READY_TO_SHOOT:
            m_impeller->SetCurrentState( ImpellerStateMgr::IMPELLER_STATE::OFF, false );
            m_transfer->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::OFF, false );
            m_turret->SetCurrentState( TurretStateMgr::TURRET_STATE::LIMELIGHT_AIM, false, 0.0 );
            m_shooter->SetCurrentState( ShooterStateMgr::SHOOTER_STATE::SHOOT, false );
            m_hood->SetCurrentState( ShooterHoodStateMgr::SHOOTER_HOOD_STATE::HOLD_POSITION, false );  // todo auto aim is needed
            break;

        case BALL_MANIPULATOR_STATE::SHOOT:
            m_impeller->SetCurrentState( ImpellerStateMgr::IMPELLER_STATE::TO_SHOOTER, false );
            m_transfer->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::TO_SHOOTER, false );
            m_turret->SetCurrentState( TurretStateMgr::TURRET_STATE::HOLD, false,0.0 );
            m_shooter->SetCurrentState( ShooterStateMgr::SHOOTER_STATE::SHOOT, false );
            m_hood->SetCurrentState( ShooterHoodStateMgr::SHOOTER_HOOD_STATE::HOLD_POSITION, false );  // todo auto aim is needed
            break;
        
        case BALL_MANIPULATOR_STATE::UNJAM_CLOCKWISE:
            //m_intake->SetCurrentState( IntakeStateMgr::INTAKE_STATE::OFF, false );
            m_impeller->SetCurrentState( ImpellerStateMgr::IMPELLER_STATE::TO_SHOOTER, false );
            //m_transfer->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::TO_IMPELLER, false );
            //m_turret->SetCurrentState( TurretStateMgr::TURRET_STATE::HOLD, false );
            //m_shooter->SetCurrentState( ShooterStateMgr::SHOOTER_STATE::OFF, false );
            //m_hood->SetCurrentState( ShooterHoodStateMgr::SHOOTER_HOOD_STATE::HOLD_POSITION, false );
            break;
        
        case BALL_MANIPULATOR_STATE::UNJAM_COUNTERCLOCKWISE:
            //m_intake->SetCurrentState( IntakeStateMgr::INTAKE_STATE::OFF, false );
            m_impeller->SetCurrentState( ImpellerStateMgr::IMPELLER_STATE::HOLD, false );
            //m_transfer->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::TO_IMPELLER, false );
            //m_turret->SetCurrentState( TurretStateMgr::TURRET_STATE::HOLD, false );
            //m_shooter->SetCurrentState( ShooterStateMgr::SHOOTER_STATE::OFF, false );
            //m_hood->SetCurrentState( ShooterHoodStateMgr::SHOOTER_HOOD_STATE::HOLD_POSITION, false );
            break;

        case BALL_MANIPULATOR_STATE::SHOOT_AUTON:
            m_impeller->SetCurrentState( ImpellerStateMgr::IMPELLER_STATE::TO_SHOOTER, false );
            m_transfer->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::TO_SHOOTER, false );
            m_turret->SetCurrentState( TurretStateMgr::TURRET_STATE::HOLD, false,0.0 );
            m_shooter->SetCurrentState( ShooterStateMgr::SHOOTER_STATE::SHOOT, false );
            m_hood->SetCurrentState( ShooterHoodStateMgr::SHOOTER_HOOD_STATE::HOLD_POSITION, false );  
            break;// todo auto aim is needed
        
        case BALL_MANIPULATOR_STATE::TRANSFER_UP:
            m_transfer->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::TO_SHOOTER, false);
            break;
        
        case BALL_MANIPULATOR_STATE::TRANSFER_DOWN:
            m_transfer->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::EJECT, false);
            break;
        
        case BALL_MANIPULATOR_STATE::AUTO_AIM:
            m_intake->SetCurrentState( IntakeStateMgr::INTAKE_STATE::OFF, false );
            m_impeller->SetCurrentState( ImpellerStateMgr::IMPELLER_STATE::OFF, false );
            m_transfer->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::OFF, false );
            m_turret->SetCurrentState( TurretStateMgr::TURRET_STATE::LIMELIGHT_AIM, false ,0.0);
            m_shooter->SetCurrentState( ShooterStateMgr::SHOOTER_STATE::OFF, false );
            m_hood->SetCurrentState( ShooterHoodStateMgr::SHOOTER_HOOD_STATE::HOLD_POSITION, false );
            break;
        
        case BALL_MANIPULATOR_STATE::TURRET_TURN_ANGLE:
            m_intake->SetCurrentState( IntakeStateMgr::INTAKE_STATE::ON, false );
            m_impeller->SetCurrentState( ImpellerStateMgr::IMPELLER_STATE::OFF, false );
            m_transfer->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::OFF, false );
            m_turret->SetCurrentState( TurretStateMgr::TURRET_STATE::TURN_ANGLE, false , turretAngle);
            m_shooter->SetCurrentState( ShooterStateMgr::SHOOTER_STATE::SHOOT, false );
            m_hood->SetCurrentState( ShooterHoodStateMgr::SHOOTER_HOOD_STATE::HOLD_POSITION, false );
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
