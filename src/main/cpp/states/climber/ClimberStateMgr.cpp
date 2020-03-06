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
#include <vector>

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
#include <states/climber/ClimberWinch.h>
//Put in climber crawl file when done
#include <frc/smartdashboard/SmartDashboard.h>


// Third Party Includes

using namespace std;

ClimberStateMgr* ClimberStateMgr::m_instance = nullptr;
ClimberStateMgr* ClimberStateMgr::GetInstance()
{
	if ( ClimberStateMgr::m_instance == nullptr )
	{
		ClimberStateMgr::m_instance = new ClimberStateMgr();
	}
	return ClimberStateMgr::m_instance;
}


/// @brief    initialize the state manager, parse the configuration file and create the states.
ClimberStateMgr::ClimberStateMgr() : m_stateVector(),
                                   m_currentState()
{
    // Parse the configuration file 
    auto stateXML = make_unique<StateDataDefn>();
    vector<MechanismTargetData*> targetData = stateXML.get()->ParseXML( MechanismTypes::MECHANISM_TYPE::INTAKE );

    // initialize the xml string to state map
    map<string, CLIMBER_STATE> stateStringToEnumMap;
    stateStringToEnumMap["CLIMBERHOLD"] = CLIMBER_STATE::HOLD;
    stateStringToEnumMap["CLIMBERRAISE"]  = CLIMBER_STATE::RAISE;
    stateStringToEnumMap["CLIMBERSTOWED"] = CLIMBER_STATE::STOWED;
    stateStringToEnumMap["CLIMBERWINCH"] = CLIMBER_STATE::WINCH;
    //stateStringToEnumMap["CRAWL"] = CLIMBER_STATE::CRAWL;
    //m_stateVector.resize(4);

    // create the states passing the configuration data
    for ( auto td: targetData )
    {
        auto stateString = td->GetStateString();
        auto stateStringToEnumItr = stateStringToEnumMap.find( stateString );
        if ( stateStringToEnumItr != stateStringToEnumMap.end() )
        {
            auto stateEnum = stateStringToEnumItr->second;
            if ( m_stateVector[stateEnum] == nullptr)
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
                        m_stateVector[stateEnum] = thisState;
                    }
                    break;

                    case CLIMBER_STATE::RAISE:
                    {   
                        auto thisState = new ClimberRaise( controlData, target, solState );
                        m_stateVector[stateEnum] = thisState;
                    }
                    break;

                    case CLIMBER_STATE::STOWED:
                    {   
                        auto thisState = new ClimberStowed( controlData, target, solState );
                        m_stateVector[stateEnum] = thisState;
                        m_currentState = thisState;
                        m_currentStateEnum = stateEnum;
                        m_currentState->Init();
                    }
                    break;

                    case CLIMBER_STATE::WINCH:
                    {
                        auto thisState = new ClimberWinch( controlData, target, solState );
                        m_stateVector[stateEnum] = thisState;
                    }

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
        else if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::CLIMBER_RAISE ) )
        {
            SetCurrentState( CLIMBER_STATE::RAISE, false );
        }
        else if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::CLIMBER_STOW ) )
        {
            SetCurrentState( CLIMBER_STATE::STOWED, false );
        }
        else if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::CLIMBER_WINCH ) )
        {
            SetCurrentState( CLIMBER_STATE::WINCH, false );
        }
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
    auto state = m_stateVector[stateEnum];
    if ( state != nullptr && state != m_currentState  )
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


