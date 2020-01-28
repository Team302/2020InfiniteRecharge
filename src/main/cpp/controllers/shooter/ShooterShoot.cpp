/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "controllers/shooter/ShooterShoot.h"
#include "controllers/ControlData.h"
#include "controllers/ControlModes.h"
#include "subsys/MechanismFactory.h"
#include "subsys/IMechanism.h"
#include "subsys/MechanismTypes.h"

ShooterShoot::ShooterShoot(ControlData* controlData, double target) : m_atTarget(false),
m_controlData(controlData),
m_target(target)
{
    auto factory = MechanismFactory::GetMechanismFactory();
    m_shooter = factory->GetIMechanism(MechanismTypes::SHOOTER);
}

void ShooterShoot::Init()
{
    m_shooter->SetControlConstants(m_controlData);
}

void ShooterShoot::Run()
{
    m_shooter->SetOutput(m_controlData->GetMode(), m_target);
    if(m_shooter->GetCurrentSpeed() >= m_target)
    {
        m_atTarget = true;
    }
}

bool ShooterShoot::AtTarget() const
{
    return m_atTarget;
}