/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "controllers/turret/TurretAutoAim.h"
#include "subsys/IMechanism.h"
#include "subsys/Turret.h"
#include "controllers/ControlData.h"
#include "subsys/MechanismTypes.h"
#include "hw/DragonLimelight.h"
#include "subsys/MechanismFactory.h"

TurretAutoAim::TurretAutoAim(ControlData* controlData, DragonLimelight* limelight): m_controlData(controlData),
    m_atTarget(false),
    m_targetPosition(0.0),
    m_limelight(limelight)
{
    auto factory = MechanismFactory::GetMechanismFactory();
    m_turret = factory->GetIMechanism(MechanismTypes::TURRET);
}

void TurretAutoAim::Init()
{
    m_turret->SetControlConstants(m_controlData);
}

void TurretAutoAim::Run()
{
    double targetHorizontalOffset = m_limelight->GetTargetHorizontalOffset();
    double m_targetPosition = m_turret->GetCurrentPosition() - targetHorizontalOffset;
    m_turret->SetOutput(m_controlData->GetMode(), m_targetPosition);
    if(m_targetPosition - 5 < m_turret->GetCurrentPosition() < m_targetPosition + 5) //arbitrary tolerance for now will change later
    {
        m_atTarget = true;
    }
}

bool TurretAutoAim::AtTarget() const
{
    return m_atTarget;
}
