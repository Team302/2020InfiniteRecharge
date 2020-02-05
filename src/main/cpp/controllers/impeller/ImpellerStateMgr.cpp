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
#include <controllers/impeller/ImpellerStateMgr.h>
#include <xmlmechdata/StateDataDefn.h>
#include <controllers/MechanismTargetData.h>
#include <utils/Logger.h>
#include <gamepad/TeleopControl.h>
#include <controllers/impeller/ImpellerOff.h>
#include <controllers/impeller/ImpellerHold.h>
#include <controllers/impeller/ImpellerAgitate.h>
#include <controllers/impeller/ImpellerToShooter.h>


// Third Party Includes

using namespace std;

/// @brief    initialize the state manager, parse the configuration file and create the states.
ImpellerStateMgr::ImpellerStateMgr() : m_stateMap(),
                                       m_currentState()
{
    // Parse the configuration file 
    auto stateXML = make_unique<StateDataDefn>();
    vector<MechanismTargetData*> targetData = stateXML.get()->ParseXML( MechanismTypes::MECHANISM_TYPE::IMPELLER );

    // initialize the xml string to state map
    map<string, IMPELLER_STATE> stateMap;
    stateMap["IMPELLEROFF"] = IMPELLER_STATE::OFF;
    stateMap["IMPELLERHOLD"] = IMPELLER_STATE::HOLD;
    stateMap["IMPELLERAGITATE"] = IMPELLER_STATE::AGITATE;
    stateMap["IMPELLERTOSHOOTER"]  = IMPELLER_STATE::TO_SHOOTER;

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
                    case IMPELLER_STATE::HOLD:
                    {   // todo update the constructor take in controlData and target
                        auto thisState = new ImpellerHold(controlData, target);
                        m_stateMap[IMPELLER_STATE::HOLD] = thisState;
                        Logger::GetLogger()->LogError("ImpellerStateMgr::ImpellerStateMgr", "Impeller Hold State added to Map");
                    }
                    break;

                    case IMPELLER_STATE::TO_SHOOTER:
                    {   // todo update the constructor take in controlData and target
                        auto thisState = new ImpellerToShooter(controlData, target);
                        m_stateMap[IMPELLER_STATE::OFF] = thisState;
                        Logger::GetLogger()->LogError("ImpellerStateMgr::ImpellerStateMgr", "Impeller To Shooter State added to Map");
                    }
                    break;

                    case IMPELLER_STATE::OFF:
                    {   // todo update the constructor take in controlData and target
                        auto thisState = new ImpellerOff(controlData, target);
                        m_stateMap[IMPELLER_STATE::OFF] = thisState;
                        m_currentState = thisState;
                        m_currentStateEnum = stateEnum;
                        m_currentState->Init();
                        Logger::GetLogger()->LogError("ImpellerStateMgr::ImpellerStateMgr", "Impeller Off State added to Map");
                    }
                    break;

                    case IMPELLER_STATE::AGITATE:
                    {   // todo update the constructor take in controlData and target
                        auto thisState = new ImpellerAgitate(controlData, target);
                        m_stateMap[IMPELLER_STATE::AGITATE] = thisState;
                        Logger::GetLogger()->LogError("ImpellerStateMgr::ImpellerStateMgr", "Impeller Agitate State added to Map");
                    }
                    break;

                    default:
                    {
                        Logger::GetLogger()->LogError( string("ImpellerStateMgr::ImpellerStateMgr"), string("unknown state"));
                    }
                    break;
                }
            }
            Logger::GetLogger()->LogError( string("ImpellerStateMgr::ImpellerStateMgr"), string("multiple mechanism state info for state"));
        }
        else
        {
            Logger::GetLogger()->LogError( string("ImpellerStateMgr::ImpellerStateMgr"), string("state not found"));
        }
    }
}

/// @brief  run the current state
/// @return void
void ImpellerStateMgr::RunCurrentState()
{
    // process teleop/manual interrupts
    auto controller = TeleopControl::GetInstance();
    if ( controller != nullptr )
    {
        if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::IMPELLER_SPIN ) )
        {
            SetCurrentState( IMPELLER_STATE::HOLD, false );
        }
        else if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::IMPELLER_STOP ) )
        {
            SetCurrentState( IMPELLER_STATE::OFF, false );
        }
        else if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::IMPELLER_AGITATE ) )
        {
            SetCurrentState( IMPELLER_STATE::AGITATE, false );
        }
        else if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::SHOOTER_AUTO_SHOOT ) )
        {
            SetCurrentState( IMPELLER_STATE::TO_SHOOTER, false );
        }
        else if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::SHOOTER_MANUAL_SHOOT ) )
        {
            SetCurrentState( IMPELLER_STATE::TO_SHOOTER, false );
        }
    }


    Logger::GetLogger()->OnDash(string("Impeller spin button"), (controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::IMPELLER_SPIN )));
    Logger::GetLogger()->OnDash(string("Impeller stop button"), (controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::IMPELLER_STOP )));
    Logger::GetLogger()->OnDash(string("Impeller aggitate button"), (controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::IMPELLER_AGITATE )));
    Logger::GetLogger()->OnDash(string("Impeller auto button"), (controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::SHOOTER_AUTO_SHOOT )));
    Logger::GetLogger()->OnDash(string("Impeller manual button"), (controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::SHOOTER_MANUAL_SHOOT )));
    Logger::GetLogger()->OnDash(string("Impeller State"), to_string(m_currentStateEnum));

    // run the current state
    if ( m_currentState != nullptr )
    {
        m_currentState->Run();
        Logger::GetLogger()->LogError("Logger::SetCurrentState", "Running Current State");
    }

}

/// @brief  set the current state, initialize it and run it
/// @return void
void ImpellerStateMgr::SetCurrentState
(
    IMPELLER_STATE  stateEnum,
    bool            run
)
{
    auto itr = m_stateMap.find( stateEnum );
    if ( itr != m_stateMap.end() )
    {
        auto state = itr->second;
        
        m_currentState = state;
        m_currentStateEnum = stateEnum;
        Logger::GetLogger()->LogError("ImpellerStateMgr::SetCurrentState", "Setting current state");
        m_currentState->Init();
        if ( run )
        {
            m_currentState->Run();
            
        }
    }
}


