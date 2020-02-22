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
#include <states/IState.h>
#include <states/climber/ClimberStateMgr.h>
#include <xmlmechdata/StateDataDefn.h>
#include <controllers/MechanismTargetData.h>
#include <utils/Logger.h>
#include <gamepad/TeleopControl.h>
#include <states/climber/ClimberHold.h>
#include <states/climber/ClimberRaise.h>
#include <states/climber/ClimberStowed.h>
//Put in climber crawl file when done
#include <frc/smartdashboard/SmartDashboard.h>


// Third Party Includes

using namespace std;

ClimberStateMgr* ClimberStateMgr::GetInstance()
{
	if ( ClimberStateMgr::m_instance == nullptr )
	{
		ClimberStateMgr::m_instance = new ClimberStateMgr();
	}
	return ClimberStateMgr::m_instance;
}


/// @brief    initialize the state manager, parse the configuration file and create the states.
ClimberStateMgr::ClimberStateMgr() : m_stateEnumToObjectMap(),
                                   m_currentState()
{
    // Parse the configuration file 
    auto stateXML = make_unique<StateDataDefn>();
    vector<MechanismTargetData*> targetData = stateXML.get()->ParseXML( MechanismTypes::MECHANISM_TYPE::INTAKE );

    // initialize the xml string to state map
    map<string, CLIMBER_STATE> stateStringToEnumMap;
    stateStringToEnumMap["HOLD"] = CLIMBER_STATE::HOLD;
    stateStringToEnumMap["RAISE"]  = CLIMBER_STATE::RAISE;
    stateStringToEnumMap["STOWED"] = CLIMBER_STATE::STOWED;
    //stateStringToEnumMap["CRAWL"] = CLIMBER_STATE::CRAWL;

    // create the states passing the configuration data
    for ( auto td: targetData )
    {
        auto stateString = td->GetStateString();
        auto stateStringToEnumItr = stateStringToEnumMap.find( stateString );
        if ( stateStringToEnumItr != stateStringToEnumMap.end() )
        {
            auto stateEnum = stateStringToEnumItr->second;
            auto stateEnumToObjectMapItr = m_stateEnumToObjectMap.find( stateEnum );
            if ( stateEnumToObjectMapItr == m_stateEnumToObjectMap.end() )
            {
                auto controlData = td->GetController();
                auto target = td->GetTarget();
                auto solState = td->GetSolenoidState();
                auto fbControlData = td->GetFailoverController(); // todo pass through to the states
                auto fbTarget = td->GetFailoverTarget();  // todo pass through to the states

                switch ( stateEnum )
                {
                    case CLIMBER_STATE::HOLD:
                    {   
                        auto thisState = new ClimberRaise( controlData, target, solState );
                        m_stateEnumToObjectMap[CLIMBER_STATE::HOLD] = thisState;
                    }
                    break;

                    case CLIMBER_STATE::RAISE:
                    {   
                        auto thisState = new ClimberRaise( controlData, target, solState );
                        m_stateEnumToObjectMap[CLIMBER_STATE::RAISE] = thisState;
                    }
                    break;

                    case CLIMBER_STATE::STOWED:
                    {   
                        auto thisState = new ClimberStowed( controlData, target, solState );
                        m_stateEnumToObjectMap[CLIMBER_STATE::STOWED] = thisState;
                        m_currentState = thisState;
                        m_currentStateEnum = stateEnum;
                        m_currentState->Init();
                    }
                    break;

                   /* case CLIMBER_STATE::CRAWL:
                    {   
                        auto thisState = new ClimberCrawl( controlData, target, solState );
                        m_stateEnumToObjectMap[CLIMBER_STATE::CRAWL] = thisState;
                        m_currentState = thisState;
                        m_currentStateEnum = stateEnum;
                        m_currentState->Init();
                    }
                    break; */

                    default:
                    {
                        Logger::GetLogger()->LogError( string("ClimberStateMgr::ClimberStateMgr"), string("unknown state"));
                    }
                    break;
                }
            }
            else
            {
                Logger::GetLogger()->LogError( string("ClimberStateMgr::ClimberStateMgr"), string("multiple mechanism state info for state"));                
            }
        }
        else
        {
            Logger::GetLogger()->LogError( string("ClimberStateMgr::ClimberStateMgr"), string("state not found"));
        }
    }
}

/// @brief  run the current state
/// @return void
void ClimberStateMgr::RunCurrentState()
{
    // process teleop/manual interrupts
    auto controller = TeleopControl::GetInstance();
    if ( controller != nullptr )
    {
        if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::CLIMBER_HOLD ) )
        {
            SetCurrentState( CLIMBER_STATE::HOLD, false );
        }
        else if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::CLIMBER_LIFT ) )
        {
            SetCurrentState( CLIMBER_STATE::RAISE, false );
        }
        else if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::CLIMBER_LIFT ) )
        {
            SetCurrentState( CLIMBER_STATE::STOWED, false );
        }
        /*else if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::CLIMBER_CRAWL ) )
        {
            SetCurrentState( CLIMBER_STATE::CRAWL, false );
        }*/
    }

    Logger::GetLogger()->OnDash(string("Climber State"), to_string(m_currentStateEnum));

    // run the current state
    if ( m_currentState != nullptr )
    {
        m_currentState->Run();
    }

}

/// @brief  set the current state, initialize it and run it
/// @return void
void ClimberStateMgr::SetCurrentState
(
    CLIMBER_STATE    stateEnum,
    bool            run
)
{
    auto itr = m_stateEnumToObjectMap.find( stateEnum );
    if ( itr != m_stateEnumToObjectMap.end() )
    {
        auto state = itr->second;
        
        
        m_currentState = state;
        m_currentStateEnum = stateEnum;
        m_currentState->Init();
        if ( run )
        {
            m_currentState->Run();
        }
        
    }
}


