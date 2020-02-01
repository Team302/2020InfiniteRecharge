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
#include <controllers/shooter/ShooterStateMgr.h>
#include <xmlmechdata/StateDataDefn.h>
#include <controllers/MechanismTargetData.h>
#include <utils/Logger.h>
#include <gamepad/TeleopControl.h>


// Third Party Includes

using namespace std;

/// @brief    initialize the state manager, parse the configuration file and create the states.
ShooterStateMgr::ShooterStateMgr() : m_stateMap(),
                                     m_currentState()
{
    // Parse the configuration file 
    auto stateXML = make_unique<StateDataDefn>();
    vector<MechanismTargetData*> targetData = stateXML.get()->ParseXML( MechanismTypes::MECHANISM_TYPE::SHOOTER );

    // initialize the xml string to state map
    map<string, SHOOTER_STATE> stateMap;
    stateMap["SHOOTEROFF"] = SHOOTER_STATE::OFF;
    stateMap["SHOOTERGETREADY"]  = SHOOTER_STATE::GET_READY;
    stateMap["SHOOTERSHOOT"] = SHOOTER_STATE::SHOOT;

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
                    case SHOOTER_STATE::OFF:
                    {   
                        /** auto thisState = new ShooterOff( controlData, target );
                        m_stateMap[stateEnum] = thisState;
                        m_currentState = thisState;
                        m_currentStateEnum = stateEnum;
                        m_currentState->Init();
                        **/
                    }
                    break;

                    case SHOOTER_STATE::GET_READY:
                    {   
                        /** auto thisState = new ShooterGetReady( controlData, target );
                        m_stateMap[stateEnum] = thisState;
                        **/
                    }
                    break;

                    case SHOOTER_STATE::SHOOT:
                    {   
                        /** auto thisState = new ShooterShoot( controlData, target );
                        m_stateMap[stateEnum] = thisState;
                        **/
                    }
                    break;

                    default:
                    {
                        Logger::GetLogger()->LogError( string("ShooterStateMgr::ShooterStateMgr"), string("unknown state"));
                    }
                    break;
                }
            }
            Logger::GetLogger()->LogError( string("ShooterStateMgr::ShooterStateMgr"), string("multiple mechanism state info for state"));
        }
        else
        {
            Logger::GetLogger()->LogError( string("ShooterStateMgr::ShooterStateMgr"), string("state not found"));
        }
    }
}

/// @brief  run the current state
/// @return void
void ShooterStateMgr::RunCurrentState()
{
    // process teleop/manual interrupts
    auto controller = TeleopControl::GetInstance();
    if ( controller != nullptr )
    {
        if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::SHOOTER_PREPARE_TO_SHOOT ) && 
             m_currentStateEnum != SHOOTER_STATE::GET_READY )
        {
            SetCurrentState( SHOOTER_STATE::GET_READY, false );
        }
        else if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::SHOOTER_MANUAL_SHOOT ) &&
                  m_currentStateEnum != SHOOTER_STATE::SHOOT )
        {
            SetCurrentState( SHOOTER_STATE::SHOOT, false );
        }
        // todo add all states/conditions here
    }

    // run the current state
    if ( m_currentState != nullptr )
    {
        m_currentState->Run();
    }

}

/// @brief  set the current state, initialize it and run it
/// @return void
void ShooterStateMgr::SetCurrentState
(
    SHOOTER_STATE  stateEnum,
    bool            run
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

