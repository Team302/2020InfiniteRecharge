/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// C++ Includes
#include <map>
#include <memory>

// FRC includes

// Team 302 includes
#include <controllers/IState.h>
#include "controllers/turret/TurretStateMgr.h"
#include <xmlmechdata/StateDataDefn.h>
#include <controllers/MechanismTargetData.h>
#include <utils/Logger.h>
#include <gamepad/TeleopControl.h>
#include <controllers/turret/TurretHold.h>
#include <controllers/turret/TurretAutoAim.h>
#include <controllers/turret/TurretManualAim.h>
#include <hw/DragonLimelight.h>

using namespace std;

/// @brief    initialize the state manager, parse the configuration file and create the states.
TurretStateMgr::TurretStateMgr() : m_stateMap(),
                                   m_currentState()
{
    // Parse the configuration file 
    auto stateXML = make_unique<StateDataDefn>();
    vector<MechanismTargetData*> targetData = stateXML.get()->ParseXML( MechanismTypes::MECHANISM_TYPE::TURRET );

    // initialize the xml string to state map
    map<string, TURRET_STATE> stateMap; 
    stateMap["TURRETHOLD"] = TURRET_STATE::TURRET_HOLD;
    stateMap["TURRETAUTOAIM"] = TURRET_STATE::TURRET_AUTO_AIM;
    stateMap["TURRETMANUALAIM"] = TURRET_STATE::TURRET_MANUAL_AIM;

        // create the states passing the configuration data
    for ( auto td: targetData )
    {
        auto limelight = 
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
                    case TURRET_STATE::TURRET_HOLD
                    {   // todo update the constructor to take controlData and target
                        auto thisState = new TurretHold(controlData);
                        m_stateMap[TURRET_HOLD] = thisState;
                        m_currentState = thisState;
                        m_currentStateEnum = stateEnum;
                        m_currentState->Init();
                    }
                    break;

                    case TURRET_STATE::TURRET_AUTO_AIM:
                    {   // todo update the constructor to take controlData and target
                        auto thisState = new TurretAutoAim(controlData,);
                        m_stateMap[INTAKE_STATE::OFF] = thisState;
                    }
                    break;

                    default:
                    {
                        Logger::GetLogger()->LogError( string("TurretStateMgr::TurretStateMgr"), string("unknown state"));
                    }
                    break;
                }
            }
            Logger::GetLogger()->LogError( string("TurretStateMgr::TurretStateMgr"), string("multiple mechanism state info for state"));
        }
        else
        {
            Logger::GetLogger()->LogError( string("TurretStateMgr::TurretStateMgr"), string("state not found"));
        }
    }

}
