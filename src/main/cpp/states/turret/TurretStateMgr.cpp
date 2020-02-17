/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "states/turret/TurretStateMgr.h"
#include <states/IState.h>
#include <states/shooterHood/ShooterHoodStateMgr.h>
#include <xmlmechdata/StateDataDefn.h>
#include <controllers/MechanismTargetData.h>
#include <utils/Logger.h>
#include <gamepad/TeleopControl.h>

#include <states/turret/ManualAim.h>
#include <states/turret/LimelightAim.h>
#include <states/turret/HoldTurretPosition.h>
#include <hw/factories/LimelightFactory.h>

using namespace std;

TurretStateMgr::TurretStateMgr() : m_stateMap(),
                            m_currentState()
{
    // Parse the configuration file 
    auto stateXML = make_unique<StateDataDefn>();
    vector<MechanismTargetData*> targetData = stateXML.get()->ParseXML( MechanismTypes::MECHANISM_TYPE::TURRET );

    map<string, TURRET_STATE> stateMap;
    stateMap["TURRETHOLD"] = TURRET_STATE::HOLD;
    stateMap["TURRETAUTOAIM"] = TURRET_STATE::LIMELIGHT_AIM;
    stateMap["TURRETMANUALAIM"] = TURRET_STATE::MANUAL_AIM;

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
                auto fbControlData = td->GetFailoverController(); // todo pass through to the states
                auto fbTarget = td->GetFailoverTarget();  // todo pass through to the states

                switch ( stateEnum )
                {
                    case TURRET_STATE::HOLD:
                    {
                        auto thisState = new HoldTurretPosition(controlData, target, MechanismTargetData::SOLENOID::NONE);
                        m_stateMap[TURRET_STATE::HOLD] = thisState;
                        m_currentState = thisState;
                        m_currentStateEnum = stateEnum;
                        m_currentState->Init();
                    }
                    break;

                    case TURRET_STATE::LIMELIGHT_AIM:
                    {
                        auto thisState = new LimelightAim(controlData);
                        m_stateMap[TURRET_STATE::LIMELIGHT_AIM] = thisState;
                    }
                    break;

                    case TURRET_STATE::MANUAL_AIM:
                    {
                        auto thisState = new ManualAim(controlData);
                        m_stateMap[TURRET_STATE::MANUAL_AIM] = thisState;
                    }
                    break;

                    default:
                    {
                        Logger::GetLogger()->LogError( string("TurretHoodStateMgr::TurretHoodStateMgr"), string("unknown state"));
                    }
                    break;
                }
            }
            {
                
            }
            
        }
    }
}

void TurretStateMgr::RunCurrentState()
{
    // process teleop/manual interrupts
    auto controller = TeleopControl::GetInstance();
    if ( controller != nullptr )
    {
        if (controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::TURRET_MANUAL_BUTTON))
        {
            SetCurrentState( TURRET_STATE::MANUAL_AIM, false ); 
        }
    }
    Logger::GetLogger()->OnDash(string("Turret State"), to_string(m_currentStateEnum));
    if ( m_currentState != nullptr )
    {
        m_currentState->Run();
    }
}
void TurretStateMgr::SetCurrentState
(
    TURRET_STATE stateEnum,
    bool         run
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