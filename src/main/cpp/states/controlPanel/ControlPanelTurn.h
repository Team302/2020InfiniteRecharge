#pragma once
#include <states/IState.h>
#include <subsys/IMechanism.h>
#include <subsys/MechanismFactory.h>
#include <controllers/ControlData.h>

class ControlPanelTurn : public IState
{
    public:
    ControlPanelTurn(ControlData* control_data, double target);
    ControlPanelTurn() = delete;
    ~ControlPanelTurn() = default;

    void Init() override;
    void Run() override;
    bool AtTarget() const override;

    private:

    IMechanism* m_control_panel_manipulator;
    double m_target;
    ControlData* m_control_data;
    double m_offset;
    double m_current_position;

};