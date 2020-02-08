#include <map>
#include <memory>

// FRC includes

// Team 302 includes
#include <controllers/IState.h>
#include <controllers/controlPanel/ControlPanelStateMgr.h>
#include <xmlmechdata/StateDataDefn.h>
#include <controllers/MechanismTargetData.h>
#include <utils/Logger.h>
#include <gamepad/TeleopControl.h>
//Put in shooter hood state includes
#include <controllers/controlPanel/ControlPanelColorTurn.h>
#include <controllers/controlPanel/ControlPanelRaise.h>
#include <controllers/controlPanel/ControlPanelStow.h>
#include <controllers/controlPanel/ControlPanelTurn.h>

// Third Party Includes

using namespace std;

/// @brief    initialize the state manager, parse the configuration file and create the states.
ControlPanelStateMgr::ControlPanelStateMgr() : m_stateMap(),
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
                auto solState = td->GetSolenoidState();
                switch ( stateEnum )
                {
                    case CONTROL_PANEL_STATE::RAISE:
                    {   // todo update the constructor take in controlData and target
                        auto thisState = new ControlPanelRaise();
                        m_stateMap[CONTROL_PANEL_STATE::RAISE] = thisState;
                        m_currentState = thisState;
                        m_currentStateEnum = stateEnum;
                        m_currentState->Init();
                    }
                    break;

                    case CONTROL_PANEL_STATE::STOW:
                    {   // todo update the constructor take in controlData and target
                        auto thisState = new ControlPanelStow();
                        m_stateMap[CONTROL_PANEL_STATE::STOW] = thisState;
                    }
                    break;

                    case CONTROL_PANEL_STATE::TURN:
                    {   // todo update the constructor take in controlData and target
                        auto thisState = new ControlPanelTurn(controlData, target);
                        m_stateMap[CONTROL_PANEL_STATE::TURN] = thisState;
                    }
                    break;

                    case CONTROL_PANEL_STATE::COLOR_TURN:
                    {
                        auto thisState = new ControlPanelColorTurn(controlData, target);
                        m_stateMap[CONTROL_PANEL_STATE::COLOR_TURN] = thisState;
                    }
                    break;

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

/// @brief  set the current state, initialize it and run it
/// @return void
void ControlPanelStateMgr::SetCurrentState
(
    CONTROL_PANEL_STATE  stateEnum,
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


