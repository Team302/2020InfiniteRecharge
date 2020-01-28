/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "controllers/shooter/ShooterGetReady.h"
#include "controllers/ControlData.h"
#include "controllers/ControlModes.h"
#include "subsys/MechanismFactory.h"
#include "subsys/IMechanism.h"
#include "subsys/MechanismTypes.h"


ShooterGetReady::ShooterGetReady(ControlData* controlData, double target): m_controlData(controlData),
m_target(target),
m_atTarget(false)
{
    auto factory = MechanismFactory::GetMechanismFactory();
    m_shooter = factory->GetIMechanism(MechanismTypes::SHOOTER);
}

void ShooterGetReady::Init()
{
    m_shooter->SetControlConstants(m_controlData);
}

void ShooterGetReady::Run()
{
    m_shooter->SetOutput(m_controlData->GetMode(), m_target); //will take care of conversions when we get more info about shooter
    if(m_shooter->GetCurrentSpeed() >= m_target)
    {
        m_atTarget = true;
    }
}

bool ShooterGetReady::AtTarget() const
{
    return m_atTarget;
}
