#include <map>
#include <memory>
#include <vector>

// FRC includes

// Team 302 includes
#include <states/IState.h>
#include <states/controlPanel/ControlPanelStateMgr.h>
#include <xmlmechdata/StateDataDefn.h>
#include <controllers/MechanismTargetData.h>
#include <utils/Logger.h>
#include <gamepad/TeleopControl.h>
//Put in shooter hood state includes
#include <states/controlPanel/ControlPanelState.h>
#include <states/controlPanel/ControlPanelManual.h>
#include <subsys/MechanismFactory.h>
#include <subsys/MechanismTypes.h>

// Third Party Includes

using namespace std;

ControlPanelStateMgr* ControlPanelStateMgr::m_instance = nullptr;
ControlPanelStateMgr* ControlPanelStateMgr::GetInstance()
{
	if ( ControlPanelStateMgr::m_instance == nullptr )
	{
		ControlPanelStateMgr::m_instance = new ControlPanelStateMgr();
	}
	return ControlPanelStateMgr::m_instance;
}

/// @brief    initialize the state manager, parse the configuration file and create the states.
ControlPanelStateMgr::ControlPanelStateMgr() :m_stateVector(),
                                       m_currentState()
{
    // Parse the configuration file 
    auto stateXML = make_unique<StateDataDefn>();
    vector<MechanismTargetData*> targetData = stateXML.get()->ParseXML( MechanismTypes::MECHANISM_TYPE::CONTROL_TABLE_MANIPULATOR );

    // initialize the xml string to state map
    map<string, CONTROL_PANEL_STATE> stateMap;
    stateMap["RAISE"] = CONTROL_PANEL_STATE::RAISE;
    stateMap["STOW"]  = CONTROL_PANEL_STATE::STOW;
    stateMap["TURN"] = CONTROL_PANEL_STATE::TURN;
    stateMap["COLORTURN"] = CONTROL_PANEL_STATE::COLOR_TURN;
    stateMap["MANUAL"] = CONTROL_PANEL_STATE::MANUAL;
    m_stateVector.resize(5);

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
                auto solState = td->GetSolenoidState();
                auto fbControlData = td->GetFailoverController(); // todo pass through to the states
                auto fbTarget = td->GetFailoverTarget();  // todo pass through to the states
                switch ( stateEnum )
                {
                    case CONTROL_PANEL_STATE::RAISE:
                    {   // todo update the constructor take in controlData and target
                        auto thisState = new ControlPanelState(controlData, target, solState);
                        m_stateVector[stateEnum] = thisState;
                        m_currentState = thisState;
                        m_currentStateEnum = stateEnum;
                        m_currentState->Init();
                    }
                    break;

                    case CONTROL_PANEL_STATE::STOW:
                    {   // todo update the constructor take in controlData and target
                        auto thisState = new ControlPanelState(controlData, target, solState);
                        m_stateVector[stateEnum] = thisState;
                    }
                    break;

                    case CONTROL_PANEL_STATE::TURN:
                    {   // todo update the constructor take in controlData and target
                        auto thisState = new ControlPanelState(controlData, target, solState);
                        m_stateVector[stateEnum] = thisState;
                    }
                    break;

                    case CONTROL_PANEL_STATE::COLOR_TURN:
                    {
                        auto thisState = new ControlPanelState(controlData, target, solState);
                        m_stateVector[stateEnum] = thisState;
                    }
                    break;

                    case CONTROL_PANEL_STATE::MANUAL:
                    {
                        auto thisState = new ControlPanelManual(controlData, target);
                        m_stateVector[stateEnum] = thisState;
                    }

                    default:
                    {
                        Logger::GetLogger()->LogError( string("ControlPanelStateMgr::ControlPanelStateMgr"), string("unknown state"));
                    }
                    break;
                }
            }
            Logger::GetLogger()->LogError( string("ControlPanelStateMgr::ControlPanelStateMgr"), string("multiple mechanism state info for state"));
        }
        else
        {
            Logger::GetLogger()->LogError( string("ControlPanelStateMgr::ControlPanelStateMgr"), string("state not found"));
        }
    }
}

/// @brief  run the current state
/// @return void
void ControlPanelStateMgr::RunCurrentState()
{
    if ( MechanismFactory::GetMechanismFactory()->GetIMechanism(MechanismTypes::MECHANISM_TYPE::CONTROL_TABLE_MANIPULATOR) != nullptr )
    {
        // process teleop/manual interrupts
        auto controller = TeleopControl::GetInstance();
        if ( controller != nullptr )
        {
            if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::CONTROL_PANEL_RAISE ) && 
                m_currentStateEnum != CONTROL_PANEL_STATE::RAISE )
            {
                SetCurrentState( CONTROL_PANEL_STATE::RAISE, false );
            }
            else if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::CONTROL_PANEL_STOW ) &&
                    m_currentStateEnum != CONTROL_PANEL_STATE::STOW )
            {
                SetCurrentState( CONTROL_PANEL_STATE::STOW, false );
            }
            else if ( controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::CONTROL_PANEL_SPIN_WHEEL ) &&
                    m_currentStateEnum != CONTROL_PANEL_STATE::TURN )
            {
                SetCurrentState( CONTROL_PANEL_STATE::TURN, false );
            }
            else if ( controller->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::CONTROL_PANEL_TURN_TO_COLOR)  &&
                    m_currentStateEnum != CONTROL_PANEL_STATE::COLOR_TURN)
            {
                SetCurrentState(CONTROL_PANEL_STATE::COLOR_TURN, false);
            }
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
void ControlPanelStateMgr::SetCurrentState
(
    CONTROL_PANEL_STATE  stateEnum,
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
            if ( MechanismFactory::GetMechanismFactory()->GetIMechanism(MechanismTypes::MECHANISM_TYPE::CONTROL_TABLE_MANIPULATOR) != nullptr )
            {
                m_currentState->Run();
            }
        }
        
    }
}


