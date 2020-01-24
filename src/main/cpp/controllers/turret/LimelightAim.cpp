/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "controllers/turret/LimelightAim.h"
#include "subsys/MechanismFactory.h"
#include "subsys/IMechanism.h"
#include "subsys/MechanismParameters.h"
#include "subsys/Turret.h"
#include "controllers/ControlData.h"
#include "subsys/MechanismTypes.h"
#include "hw/DragonLimelight.h"

LimelightAim::LimelightAim(ControlData* controlData, DragonLimelight* limelight): m_controlData(controlData),
    m_atTarget(false),
    m_targetPosition(0.0),
    m_limelight(limelight)
{
    auto factory = MechanismFactory::GetMechanismFactory();
    m_turret = factory->GetIMechanism(MechanismTypes::TURRET);
    m_turret->SetControlConstants(m_controlData);
}

void LimelightAim::Init()
{
    double targetHorizontalOffset = m_limelight->GetTargetHorizontalOffset();
    double m_targetPosition = m_turret->GetCurrentPosition() - targetHorizontalOffset;
    m_turret->SetOutput(ControlModes::CONTROL_TYPE::TRAPEZOID, m_targetPosition);
}

void LimelightAim::Run()
{

}

bool LimelightAim::AtTarget() const
{
    return m_atTarget;
}
