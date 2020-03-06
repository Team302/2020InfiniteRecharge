//====================================================================================================================================================
/// Copyright 2019 Lake Orion Robotics FIRST Team 302
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
/// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
/// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
/// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================

#include <map>
#include <memory>
#include <vector>

// FRC includes

// Team 302 includes
#include <states/IState.h>
#include <states/shooterHood/ShooterHoodStateMgr.h>
#include <xmlmechdata/StateDataDefn.h>
#include <controllers/MechanismTargetData.h>
#include <utils/Logger.h>
#include <gamepad/TeleopControl.h>
//Put in shooter hood state includes
#include <states/shooterHood/ShooterHoodState.h>
#include <states/shooterHood/ShooterHoodManual.h>
#include <subsys/MechanismFactory.h>
#include <subsys/MechanismTypes.h>

// Third Party Includes

using namespace std;

ShooterHoodStateMgr* ShooterHoodStateMgr::m_instance = nullptr;
ShooterHoodStateMgr* ShooterHoodStateMgr::GetInstance()
{
	if ( ShooterHoodStateMgr::m_instance == nullptr )
	{
		ShooterHoodStateMgr::m_instance = new ShooterHoodStateMgr();
	}
	return ShooterHoodStateMgr::m_instance;
}

/// @brief    initialize the state manager, parse the configuration file and create the states.
ShooterHoodStateMgr::ShooterHoodStateMgr() : m_stateVector(),
                                       m_currentState()
{
    // Parse the configuration file 
    auto stateXML = make_unique<StateDataDefn>();
    vector<MechanismTargetData*> targetData = stateXML.get()->ParseXML( MechanismTypes::MECHANISM_TYPE::SHOOTER_HOOD );

    // initialize the xml string to state map
    map<string, SHOOTER_HOOD_STATE> stateMap;
    stateMap["SHOOTERHOODUP"] = SHOOTER_HOOD_STATE::MOVE_UP;
    stateMap["SHOOTERHOODDOWN"]  = SHOOTER_HOOD_STATE::MOVE_DOWN;
    stateMap["SHOOTERHOODHOLD"] = SHOOTER_HOOD_STATE::HOLD_POSITION;
    stateMap["SHOOTERHOODMANUAL"] = SHOOTER_HOOD_STATE::MANUAL;
    m_stateVector.resize(4);
    
    // create the states passing the configuration data
    for ( auto td: targetData )
    {
        auto stateString = td->GetStateString();
        auto stateItr = stateMap.find( stateString );
        if ( stateItr != stateMap.end() )
        {
            auto stateEnum = stateItr->second;
            if ( m_stateVector[stateEnum] == nullptr )
            {
                auto controlData = td->GetController();
                auto target = td->GetTarget();
                auto fbControlData = td->GetFailoverController(); // todo pass through to the states
                auto fbTarget = td->GetFailoverTarget();  // todo pass through to the states

                switch ( stateEnum )
                {
                    case SHOOTER_HOOD_STATE::MOVE_UP:
                    {   // todo update the constructor take in controlData and target
                        auto thisState = new ShooterHoodState(controlData, target, MechanismTargetData::SOLENOID::NONE);
                        m_stateVector[stateEnum] = thisState;
                    }
                    break;

                    case SHOOTER_HOOD_STATE::MOVE_DOWN:
                    {   // todo update the constructor take in controlData and target
                        auto thisState = new ShooterHoodState(controlData, target, MechanismTargetData::SOLENOID::NONE);
                        m_stateVector[stateEnum] = thisState;
                    }
                    break;

                    case SHOOTER_HOOD_STATE::HOLD_POSITION:
                    {   // todo update the constructor take in controlData and target
                        auto thisState = new ShooterHoodState(controlData, target, MechanismTargetData::SOLENOID::NONE);
                        m_stateVector[stateEnum] = thisState;
                        m_currentState = thisState;
                        m_currentStateEnum = stateEnum;
                        m_currentState->Init();
                    }
                    break;

                    case SHOOTER_HOOD_STATE::MANUAL:
                    {
                        auto thisState = new ShooterHoodManual(controlData, target);
                        m_stateVector[stateEnum] = thisState;
                    }
                    break;

                    default:
                    {
                        Logger::GetLogger()->LogError( string("ShooterHoodStateMgr::ShooterHoodStateMgr"), string("unknown state"));
                    }
                    break;
                }
            }
            else
            {
                Logger::GetLogger()->LogError( string("ShooterHoodStateMgr::ShooterHoodStateMgr"), string("multiple mechanism state info for state"));
            }
        }
        else
        {
            Logger::GetLogger()->LogError( string("ShooterHoodStateMgr::ShooterHoodStateMgr state not found"), stateString );
        }
    }
}

/// @brief  run the current state
/// @return void
void ShooterHoodStateMgr::RunCurrentState()
{
    if ( MechanismFactory::GetMechanismFactory()->GetIMechanism( MechanismTypes::MECHANISM_TYPE::SHOOTER_HOOD) != nullptr )
    {
        // process teleop/manual interrupts
        auto controller = TeleopControl::GetInstance();
        if ( controller != nullptr )
        {
            if (controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::SHOOTER_HOOD_MANUAL_BUTTON))
            {
                SetCurrentState( SHOOTER_HOOD_STATE::MANUAL, false ); 
                Logger::GetLogger()->LogError("ShootHoodStateMgr::SetCurrentState", "Shooter Hood State Manual Hood");
            }
            
            /*if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::SHOOTER_HOOD_MOVE_UP ) && 
                m_currentStateEnum != SHOOTER_HOOD_STATE::MOVE_UP )
            {
                SetCurrentState( SHOOTER_HOOD_STATE::MOVE_UP, false );
            }
            else if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::SHOOTER_HOOD_MOVE_DOWN ) &&
                    m_currentStateEnum != SHOOTER_HOOD_STATE::MOVE_DOWN )
            {
                SetCurrentState( SHOOTER_HOOD_STATE::MOVE_DOWN, false );
            }
            else if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::SHOOTER_HOOD_HOLD_POSITION ) &&
                    m_currentStateEnum != SHOOTER_HOOD_STATE::HOLD_POSITION )
            {
                SetCurrentState( SHOOTER_HOOD_STATE::HOLD_POSITION, false );
            }*/
        }

    Logger::GetLogger()->OnDash(string("Shooterhood State"), to_string(m_currentStateEnum));
        // run the current state
        if ( m_currentState != nullptr )
        {
            m_currentState->Run();
        }
    }
}

/// @brief  set the current state, initialize it and run it
/// @return void
void ShooterHoodStateMgr::SetCurrentState
(
    SHOOTER_HOOD_STATE  stateEnum,
    bool            run
)
{
    auto state = m_stateVector[stateEnum];
    if ( state != nullptr && state != m_currentState )
    {
        
        m_currentState = state;
        m_currentStateEnum = stateEnum;
        m_currentState->Init();
        if ( run )
        {
            if ( MechanismFactory::GetMechanismFactory()->GetIMechanism( MechanismTypes::MECHANISM_TYPE::SHOOTER_HOOD) != nullptr )
            {
                m_currentState->Run();
            }
        }
        
    }
}


