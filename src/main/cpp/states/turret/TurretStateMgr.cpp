/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <map>
#include <vector>

#include "states/turret/TurretStateMgr.h"
#include <states/IState.h>
#include <states/shooterHood/ShooterHoodStateMgr.h>
#include <xmlmechdata/StateDataDefn.h>
#include <controllers/MechanismTargetData.h>
#include <utils/Logger.h>
#include <gamepad/TeleopControl.h>

#include <states/turret/TurretTurnAngle.h>
#include <states/turret/ManualAim.h>
#include <states/turret/LimelightAim.h>
#include <states/turret/HoldTurretPosition.h>
#include <hw/factories/LimelightFactory.h>
#include <subsys/MechanismFactory.h>
#include <subsys/IMechanism.h>
#include <subsys/MechanismTypes.h>

using namespace std;

TurretStateMgr* TurretStateMgr::m_instance = nullptr;
TurretStateMgr* TurretStateMgr::GetInstance()
{
	if ( TurretStateMgr::m_instance == nullptr )
	{
		TurretStateMgr::m_instance = new TurretStateMgr();
	}
	return TurretStateMgr::m_instance;
}

TurretStateMgr::TurretStateMgr() : m_stateVector(),
                                   m_currentState(),
                                   m_approxTargetAngle( 0.0 )
{
    auto turret = MechanismFactory::GetMechanismFactory()->GetIMechanism( MechanismTypes::TURRET );
    m_approxTargetAngle = turret->GetCurrentPosition();

    // Parse the configuration file 
    auto stateXML = make_unique<StateDataDefn>();
    vector<MechanismTargetData*> targetData = stateXML.get()->ParseXML( MechanismTypes::MECHANISM_TYPE::TURRET );

    map<string, TURRET_STATE> stateMap;
    stateMap["TURRETHOLD"] = TURRET_STATE::HOLD;
    stateMap["TURRETAUTOAIM"] = TURRET_STATE::LIMELIGHT_AIM;
    stateMap["TURRETMANUALAIM"] = TURRET_STATE::MANUAL_AIM;
    stateMap["TURRETTURNANGLE"] = TURRET_STATE::TURN_ANGLE;
    m_stateVector.resize(4);

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
                    case TURRET_STATE::HOLD:
                    {
                        auto thisState = new HoldTurretPosition(controlData, m_approxTargetAngle, MechanismTargetData::SOLENOID::NONE);
                        m_stateVector[stateEnum] = thisState;
                        m_currentState = thisState;
                        m_currentStateEnum = stateEnum;
                        m_currentState->Init();
                    }
                    break;

                    case TURRET_STATE::LIMELIGHT_AIM:
                    {
                        auto thisState = new LimelightAim(controlData, target);
                        m_stateVector[stateEnum] = thisState;
                    }
                    break;

                    case TURRET_STATE::MANUAL_AIM:
                    {
                        auto thisState = new ManualAim(controlData);
                        m_stateVector[stateEnum] = thisState;
                    }
                    break;

                    case TURRET_STATE::TURN_ANGLE:
                    {
                        auto thisState = new TurretTurnAngle(controlData, td->GetTarget(), MechanismTargetData::SOLENOID::NONE);
                        m_stateVector[stateEnum] = thisState;
                    }

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
    if ( MechanismFactory::GetMechanismFactory()->GetIMechanism( MechanismTypes::MECHANISM_TYPE::TURRET) != nullptr )
    {
        // process teleop/manual interrupts
        auto controller = TeleopControl::GetInstance();
        if ( controller != nullptr )
        {
            if (controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::TURRET_MANUAL_BUTTON))
            {
                SetCurrentState( TURRET_STATE::MANUAL_AIM, false , 0.0); 
            }
            if (controller->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::TURRET_LIMELIGHT_AIM))
            {
                SetCurrentState( TURRET_STATE::LIMELIGHT_AIM, false, 0.0);
            }
        }
        Logger::GetLogger()->OnDash(string("Turret State"), to_string(m_currentStateEnum));
        if ( m_currentState != nullptr )
        {
            m_currentState->Run();
        }
    }
}
void TurretStateMgr::SetCurrentState
(
    TURRET_STATE stateEnum,
    bool         run,
    double       turretAngle
)
{
    auto state = m_stateVector[stateEnum];
    if ( state != nullptr && state != m_currentState )
    {
        if (stateEnum == TURN_ANGLE)
        {
            auto cdState = dynamic_cast<TurretTurnAngle*>(state);
            auto cd = cdState->GetControlData();
            m_stateVector[stateEnum] = new TurretTurnAngle(cd,turretAngle, MechanismTargetData::SOLENOID::NONE);
            state = m_stateVector[stateEnum];
        }
        m_currentState = state;
        m_currentStateEnum = stateEnum;
        m_currentState->Init();
        if ( stateEnum == LIMELIGHT_AIM )
        {
            auto llAim = dynamic_cast<LimelightAim*>(m_currentState);
            if ( llAim != nullptr )
            {
                llAim->UpdateTarget( m_approxTargetAngle );
            }
        }

        
        if ( run )
        {
            if ( MechanismFactory::GetMechanismFactory()->GetIMechanism( MechanismTypes::MECHANISM_TYPE::TURRET) != nullptr )
            {
                m_currentState->Run();
            }
        }
        
    }
}