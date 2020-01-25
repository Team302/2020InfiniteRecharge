#include <controllers/IState.h>
#include <subsys/IMechanism.h>
#include <subsys/MechanismFactory.h>
#include <controllers/controlpanel/CPMTurnState.h>
#include <controllers/ControlData.h>

CPMTurnState::CPMTurnState(ControlData* control_data, double target)
{
    auto factory = MechanismFactory::GetMechanismFactory();
    m_control_panel_manipulator = factory -> GetIMechanism(MechanismTypes::MECHANISM_TYPE::CONTROL_TABLE_MANIPULATOR);

    m_target = target;
    m_control_data = control_data;
}

void CPMTurnState::Init()
{
    m_target = m_control_panel_manipulator -> GetCurrentPosition() + m_offset;
    m_control_panel_manipulator -> SetControlConstants(m_control_data);
}

void CPMTurnState::Run()
{
    m_control_panel_manipulator -> SetOutput(m_control_data -> GetMode(), m_target);
    m_current_position = m_control_panel_manipulator -> GetCurrentPosition();
}

bool CPMTurnState::AtTarget() const
{

}