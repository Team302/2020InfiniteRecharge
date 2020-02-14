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
ImpellerStateMgr::ImpellerStateMgr() : m_stateEnumToObjectMap(),
                                       m_currentState()
{
    // Parse the configuration file 
    auto stateXML = make_unique<StateDataDefn>();
    vector<MechanismTargetData*> targetData = stateXML.get()->ParseXML( MechanismTypes::MECHANISM_TYPE::IMPELLER );

    // initialize the xml string to state map
    map<string, IMPELLER_STATE> stateStringToEnumMap;
    stateStringToEnumMap["IMPELLEROFF"] = IMPELLER_STATE::OFF;
    stateStringToEnumMap["IMPELLERHOLD"] = IMPELLER_STATE::HOLD;
    stateStringToEnumMap["IMPELLERAGITATE"] = IMPELLER_STATE::AGITATE;
    stateStringToEnumMap["IMPELLERTOSHOOTER"]  = IMPELLER_STATE::TO_SHOOTER;

    // create the states passing the configuration data
    for ( auto td: targetData )
    {
        auto stateString = td->GetStateString();
        auto stateStringToEnumMapItr = stateStringToEnumMap.find( stateString );
        if ( stateStringToEnumMapItr != stateStringToEnumMap.end() )
        {
            auto stateEnum = stateStringToEnumMapItr->second;
            auto stateEnumToObjectMapItr = m_stateEnumToObjectMap.find( stateEnum );
            if ( stateEnumToObjectMapItr == m_stateEnumToObjectMap.end() )
            {
                auto controlData = td->GetController();
                auto target = td->GetTarget();
                auto solState = td->GetSolenoidState();

                switch ( stateEnum )
                {
                    case IMPELLER_STATE::HOLD:
                    {   
                        auto thisState = new ImpellerHold(controlData, target, solState );
                        m_stateEnumToObjectMap[IMPELLER_STATE::HOLD] = thisState;
                        Logger::GetLogger()->LogError("ImpellerStateMgr::ImpellerStateMgr", "Impeller Hold State added to Map");
                    }
                    break;

                    case IMPELLER_STATE::TO_SHOOTER:
                    {   
                        auto thisState = new ImpellerToShooter(controlData, target, solState );
                        m_stateEnumToObjectMap[IMPELLER_STATE::OFF] = thisState;
                        Logger::GetLogger()->LogError("ImpellerStateMgr::ImpellerStateMgr", "Impeller To Shooter State added to Map");
                    }
                    break;

                    case IMPELLER_STATE::OFF:
                    {   
                        auto thisState = new ImpellerOff(controlData, target, solState );
                        m_stateEnumToObjectMap[IMPELLER_STATE::OFF] = thisState;
                        m_currentState = thisState;
                        m_currentStateEnum = stateEnum;
                        m_currentState->Init();
                        Logger::GetLogger()->LogError("ImpellerStateMgr::ImpellerStateMgr", "Impeller Off State added to Map");
                    }
                    break;

                    case IMPELLER_STATE::AGITATE:
                    {   
                        auto thisState = new ImpellerAgitate(controlData, target, solState );
                        m_stateEnumToObjectMap[IMPELLER_STATE::AGITATE] = thisState;
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
            else
            {
                Logger::GetLogger()->LogError( string("ImpellerStateMgr::ImpellerStateMgr"), string("multiple mechanism state info for state"));
            }
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
        if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::IMPELLER_TO_SHOOTER ))
        {
            SetCurrentState( IMPELLER_STATE::TO_SHOOTER, false );
        }
        if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::IMPELLER_OFF ))
        {
            SetCurrentState( IMPELLER_STATE::OFF, false );
        }
        /*if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::IMPELLER_AGITATE  ) && m_currentStateEnum != IMPELLER_STATE::AGITATE)
        {
            SetCurrentState( IMPELLER_STATE::AGITATE, false );
        }*/
        
        if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::IMPELLER_HOLD ))
        {
            SetCurrentState( IMPELLER_STATE::HOLD, false );
        }
        
        /*else if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::SHOOTER_AUTO_SHOOT ) )
        {
            SetCurrentState( IMPELLER_STATE::TO_SHOOTER, false );
        }
        else if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::SHOOTER_MANUAL_SHOOT ) )
        {
            SetCurrentState( IMPELLER_STATE::TO_SHOOTER, false );
        }
        */
    }


    
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
    auto itr = m_stateEnumToObjectMap.find( stateEnum );
    if ( itr != m_stateEnumToObjectMap.end() )
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


