#pragma once 

#include <states/balltransfer/BallTransferStateMgr.h>
//#include <states/chassis/ChassisStateMgr.h>
#include <states/controlPanel/ControlPanelStateMgr.h>
#include <states/impeller/ImpellerStateMgr.h>
#include <states/intake/IntakeStateMgr.h>
#include <states/shooter/ShooterStateMgr.h>
#include <states/shooterHood/ShooterHoodStateMgr.h>
#include <states/turret/TurretStateMgr.h>


class DriverFeedback 
{
    public: 
    void periodic();
    DriverFeedback();
    ~DriverFeedback() = delete;

    private:
    BallTransferStateMgr* m_ballTransfer;
    //ChassisStateMgr* m_chassis;
    ControlPanelStateMgr* m_controlPanel;
    ImpellerStateMgr* m_impeller;
    IntakeStateMgr* m_intake;
    ShooterStateMgr* m_shooter;
    ShooterHoodStateMgr* m_shooterHood;
    TurretStateMgr* m_turret;
   
};