/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <states/controlPanel/ControlPanelStow.h>
#include <subsys/ControlPanel.h>
#include <subsys/MechanismFactory.h>
#include <subsys/IMechanism.h>
#include <states/IState.h>
#include <memory>

using namespace std;

ControlPanelStow::ControlPanelStow() 
{
    auto factory = MechanismFactory::GetMechanismFactory();

    m_controlPanel = factory -> GetIMechanism(MechanismTypes::MECHANISM_TYPE::CONTROL_TABLE_MANIPULATOR);
}

void ControlPanelStow::Init() 
{
    
}

void ControlPanelStow::Run() 
{
    m_controlPanel -> ActivateSolenoid( false ); 
    m_controlPanel -> SetOutput( ControlModes::PERCENT_OUTPUT, 0 );
}

bool ControlPanelStow::AtTarget() const
{
    return true;
} 
