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
#include <map>
#include <memory>
#include <vector>

// FRC includes

// Team 302 includes
#include <states/IState.h>
#include <states/hookdelivery/HookDeliveryStateMgr.h>
#include <xmlmechdata/StateDataDefn.h>
#include <controllers/MechanismTargetData.h>
#include <utils/Logger.h>
#include <gamepad/TeleopControl.h>
#include <states/hookdelivery/HookDeliveryState.h>
#include <subsys/MechanismFactory.h>
#include <subsys/MechanismTypes.h>


// Third Party Includes

using namespace std;


HookDeliveryStateMgr* HookDeliveryStateMgr::m_instance = nullptr;
HookDeliveryStateMgr* HookDeliveryStateMgr::GetInstance()
{
	if ( HookDeliveryStateMgr::m_instance == nullptr )
	{
		HookDeliveryStateMgr::m_instance = new HookDeliveryStateMgr();
	}
	return HookDeliveryStateMgr::m_instance;
}


/// @brief    initialize the state manager, parse the configuration file and create the states.
HookDeliveryStateMgr::HookDeliveryStateMgr() : m_currentState(),
                                               m_stateVector(),
                                               m_currentStateEnum(HOOK_DELIVERY_STATE::DOWN)
{
    // Parse the configuration file 
    auto stateXML = make_unique<StateDataDefn>();
    vector<MechanismTargetData*> targetData = stateXML.get()->ParseXML( MechanismTypes::MECHANISM_TYPE::HOOK_DELIVERY );

    // initialize the xml string to state map
    map<string, HOOK_DELIVERY_STATE> stateMap;
    /*stateMap["HOOKDELIVERYSTOW"] = HOOK_DELIVERY_STATE::DOWN;
    stateMap["HOOKDELIVERYRAISE"]  = HOOK_DELIVERY_STATE::RAISE;
    stateMap["HOOKDELIVERYHOLD"]  = HOOK_DELIVERY_STATE::HIGH;
    stateMap["HOOKDELIVERYLOWER"] = HOOK_DELIVERY_STATE::LOWER;
    stateMap["HOOKDELIVERYMANUAL"] = HOOK_DELIVERY_STATE::MANUAL;
    */
    stateMap["HOOKDELIVERYOFF"]  = HOOK_DELIVERY_STATE::OFF;
    stateMap["HOOKDELIVERYUP"]  = HOOK_DELIVERY_STATE::UP;
    stateMap["HOOKDELIVERYDOWN"] = HOOK_DELIVERY_STATE::DOWN;
    m_stateVector.resize(3);
    // create the states passing the configuration data
    for ( auto td: targetData )
    {
        auto stateString = td->GetStateString();
        auto stateStringToEnumItr = stateMap.find( stateString );
        if ( stateStringToEnumItr != stateMap.end() )
        {
            auto stateEnum = stateStringToEnumItr->second;
            if ( m_stateVector[stateEnum] == nullptr )
            {
                auto controlData = td->GetController();
                auto target = td->GetTarget();
                auto solState = td->GetSolenoidState();
                auto fbControlData = td->GetFailoverController(); // todo pass through to the states
                auto fbTarget = td->GetFailoverTarget();  // todo pass through to the states
                switch ( stateEnum )
                {
                    case HOOK_DELIVERY_STATE::OFF:
                    {   
                        auto thisState = new HookDeliveryState( controlData, target, solState );
                        m_stateVector[stateEnum] = thisState;
                        m_currentState = thisState;
                        m_currentStateEnum = stateEnum;
                        m_currentState->Init();
                    }
                    break;

                    case HOOK_DELIVERY_STATE::UP:
                    {   
                        auto thisState = new HookDeliveryState( controlData, target, solState );
                        m_stateVector[stateEnum] = thisState;
                    }
                    break;

                    case HOOK_DELIVERY_STATE::DOWN:
                    {   
                        auto thisState = new HookDeliveryState( controlData, target, solState );
                        m_stateVector[stateEnum] = thisState;
                    }
                    break;

                    /*case HOOK_DELIVERY_STATE::RAISE:
                    {   
                        auto thisState = new HookDeliveryState( controlData, target, solState );
                        m_stateVector[stateEnum] = thisState;
                    }
                    break;

                    case HOOK_DELIVERY_STATE::HIGH:
                    {   
                        auto thisState = new HookDeliveryState( controlData, target, solState );
                        m_stateVector[stateEnum] = thisState;
                    }
                    break;

                    case HOOK_DELIVERY_STATE::LOWER:
                    {
                        auto thisState = new HookDeliveryState(controlData, target, solState);
                        m_stateVector[stateEnum] = thisState;
                    
                    }
                    break;

                    case HOOK_DELIVERY_STATE::MANUAL:
                    {
                        auto thisState = new HookDeliveryState(controlData, target, solState);
                        m_stateVector[stateEnum] = thisState;
                    
                    }
                    break;
                    */
                    default:
                    {
                        Logger::GetLogger()->LogError( string("HookDeliveryStateMgr::HookDeliveryStateMgr"), string("unknown state"));
                    }
                    break;
                }
            }
            else
            {
                Logger::GetLogger()->LogError( string("HookDeliveryStateMgr::HookDeliveryStateMgr"), string("multiple mechanism state info for state"));
            }
        }
        else
        {
            Logger::GetLogger()->LogError( string("HookDeliveryStateMgr::HookDeliveryStateMgr"), string("state not found"));
        }
    }
}

/// @brief  run the current state
/// @return void
void HookDeliveryStateMgr::RunCurrentState()
{
    if ( MechanismFactory::GetMechanismFactory()->GetIMechanism( MechanismTypes::MECHANISM_TYPE::HOOK_DELIVERY ) != nullptr )
    {
        // process teleop/manual interrupts
        
        auto controller = TeleopControl::GetInstance();
        if ( controller != nullptr )
        {
            if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::HOOK_DELIVERY_UP))
            {
                SetCurrentState( HOOK_DELIVERY_STATE::UP, false );
            }
            if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::HOOK_DELIVERY_DOWN))
            {
                SetCurrentState( HOOK_DELIVERY_STATE::DOWN, false );
            }
            else
            {
                SetCurrentState( HOOK_DELIVERY_STATE::OFF, false);
            }
            /*if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::CLIMBER_EXTEND ) &&
                    m_currentStateEnum != HOOK_DELIVERY_STATE::RAISE )
            {
                SetCurrentState( HOOK_DELIVERY_STATE::RAISE, false );
            }
            else if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::CLIMBER_HOLD ) &&
                    m_currentStateEnum != HOOK_DELIVERY_STATE::HIGH )
            {
                SetCurrentState( HOOK_DELIVERY_STATE::HIGH, false );
            }
            else if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::CLIMBER_LIFT ) &&
                    m_currentStateEnum != HOOK_DELIVERY_STATE::LOWER )
            {
                SetCurrentState( HOOK_DELIVERY_STATE::LOWER, false );
            }
            else
            {
                SetCurrentState( HOOK_DELIVERY_STATE::DOWN, false );
            }*/
        }
        
        // run the current state
        if ( m_currentState != nullptr )
        {
            m_currentState->Run();
        }
    }

}

/// @brief  set the current state, initialize it and run it
/// @return void
void HookDeliveryStateMgr::SetCurrentState
(
    HOOK_DELIVERY_STATE     stateEnum,
    bool                    run
)
{
   
    
    
    Logger::GetLogger()->LogError( string("about to set state current "), to_string(stateEnum));
    auto state = m_stateVector[stateEnum];
    if ( state != nullptr && state != m_currentState)
    {    
        m_currentState = state;
        m_currentStateEnum = stateEnum;
        m_currentState->Init();
        if ( run )
        {
            if ( MechanismFactory::GetMechanismFactory()->GetIMechanism( MechanismTypes::MECHANISM_TYPE::HOOK_DELIVERY ) != nullptr )
            {
                m_currentState->Run();
            }
        }
        
    }
}

