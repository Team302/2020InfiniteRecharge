#include <states/IState.h>
#include <subsys/IMechanism.h>
#include <subsys/MechanismFactory.h>
#include <states/controlPanel/ControlPanelTurn.h>
#include <controllers/ControlData.h>

ControlPanelTurn::ControlPanelTurn(ControlData* control_data, double target)
{
    auto factory = MechanismFactory::GetMechanismFactory();
    m_control_panel_manipulator = factory -> GetIMechanism(MechanismTypes::MECHANISM_TYPE::CONTROL_TABLE_MANIPULATOR);

    m_target = target;
    m_control_data = control_data;
}

// Creates the desired target location for the spin to end at

void ControlPanelTurn::Init()
{
    m_target = m_control_panel_manipulator -> GetCurrentPosition() + m_offset;
    m_control_panel_manipulator -> SetControlConstants(m_control_data);
}

// Spins the wheel to the target

void ControlPanelTurn::Run()
{
    m_control_panel_manipulator -> SetOutput(m_control_data -> GetMode(), m_target);
}

// Performs a check to see if the panel has been spun to the target point yet

bool ControlPanelTurn::AtTarget() const
{
if (m_control_panel_manipulator ->  GetCurrentPosition() >= m_target )
{
    return true;
}
else
{
   return  false;
}

}