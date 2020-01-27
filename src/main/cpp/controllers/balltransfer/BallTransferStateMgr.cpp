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

// C++ Includes
#include <map>
#include <memory>

// FRC includes

// Team 302 includes
#include <controllers/IState.h>
#include <controllers/balltransfer/BallTransferStateMgr.h>
#include <xmlmechdata/StateDataDefn.h>
#include <controllers/MechanismTargetData.h>
#include <utils/Logger.h>
#include <gamepad/TeleopControl.h>
#include <controllers/balltransfer/BallTransferOff.h>
#include <controllers/balltransfer/BallTransferToImpeller.h>
#include <controllers/balltransfer/BallTransferToShooter.h>


// Third Party Includes

using namespace std;

/// @brief    initialize the state manager, parse the configuration file and create the states.
BallTransferStateMgr::BallTransferStateMgr() : m_currentState(),
                                               m_stateMap(),
                                               m_currentStateEnum(BALL_TRANSFER_STATE::OFF)
{
    // Parse the configuration file 
    auto stateXML = make_unique<StateDataDefn>();
    vector<MechanismTargetData*> targetData = stateXML.get()->ParseXML( MechanismTypes::MECHANISM_TYPE::BALL_TRANSFER );

    // initialize the xml string to state map
    map<string, BALL_TRANSFER_STATE> stateMap;
    stateMap["BALLTRANSFEROFF"] = BALL_TRANSFER_STATE::OFF;
    stateMap["BALLTRANSPORTTOIMPELLER"]  = BALL_TRANSFER_STATE::TO_IMPELLER;
    stateMap["BALLTRANSFERTOSHOOTER"]  = BALL_TRANSFER_STATE::TO_SHOOTER;

    // create the states passing the configuration data
    for ( auto td: targetData )
    {
        auto stateString = td->GetStateString();
        auto stateItr = stateMap.find( stateString );
        if ( stateItr != stateMap.end() )
        {
            auto stateEnum = stateItr->second;
            auto stateIt = m_stateMap.find( stateEnum );
            if ( stateIt == m_stateMap.end() )
            {
                auto controlData = td->GetController();
                auto target = td->GetTarget();
                switch ( stateEnum )
                {
                    case BALL_TRANSFER_STATE::OFF:
                    {   // todo update the constructor
                        auto thisState = new BallTransferOff( controlData, target );
                        m_stateMap[stateEnum] = thisState;
                        m_currentState = thisState;
                        m_currentStateEnum = stateEnum;
                        m_currentState->Init();
                    }
                    break;

                    case BALL_TRANSFER_STATE::TO_IMPELLER:
                    {   // todo update the constructor
                        auto thisState = new BallTransferToImpeller( controlData, target );
                        m_stateMap[stateEnum] = thisState;
                    }
                    break;

                    case BALL_TRANSFER_STATE::TO_SHOOTER:
                    {   // todo update the constructor
                        auto thisState = new BallTransferToShooter( controlData, target );
                        m_stateMap[stateEnum] = thisState;
                    }
                    break;

                    default:
                    {
                        Logger::GetLogger()->LogError( string("BallTransferStateMgr::BallTransferStateMgr"), string("unknown state"));
                    }
                    break;
                }
            }
            Logger::GetLogger()->LogError( string("BallTransferStateMgr::BallTransferStateMgr"), string("multiple mechanism state info for state"));
        }
        else
        {
            Logger::GetLogger()->LogError( string("BallTransferStateMgr::BallTransferStateMgr"), string("state not found"));
        }
    }
}

/// @brief  run the current state
/// @return void
void BallTransferStateMgr::RunCurrentState()
{
    // process teleop/manual interrupts
    auto controller = TeleopControl::GetInstance();
    if ( controller != nullptr )
    {
        if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::BALL_TRANSFER_OFF ) && 
             m_currentStateEnum != BALL_TRANSFER_STATE::OFF )
        {
            SetCurrentState( BALL_TRANSFER_STATE::OFF, false );
        }
        else if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::BALL_TRANSFER_TO_IMPELLER ) &&
                  m_currentStateEnum != BALL_TRANSFER_STATE::TO_IMPELLER )
        {
            SetCurrentState( BALL_TRANSFER_STATE::TO_IMPELLER, false );
        }
        else if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::BALL_TRANSFER_TO_SHOOTER ) &&
                  m_currentStateEnum != BALL_TRANSFER_STATE::TO_SHOOTER )
        {
            SetCurrentState( BALL_TRANSFER_STATE::TO_SHOOTER, false );
        }
    }

    // run the current state
    if ( m_currentState != nullptr )
    {
        m_currentState->Run();
    }

}

/// @brief  set the current state, initialize it and run it
/// @return void
void BallTransferStateMgr::SetCurrentState
(
    BALL_TRANSFER_STATE     stateEnum,
    bool                    run
)
{
    auto itr = m_stateMap.find( stateEnum );
    if ( itr != m_stateMap.end() )
    {
        auto state = itr->second;
        if ( state != m_currentState )
        {
            m_currentState = state;
            m_currentStateEnum = stateEnum;
            m_currentState->Init();
            if ( run )
            {
                m_currentState->Run();
            }
        }
    }
}

