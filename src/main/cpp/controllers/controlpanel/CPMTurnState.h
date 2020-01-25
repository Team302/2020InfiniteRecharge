#pragma once
#include <controllers/IState.h>
#include <subsys/IMechanism.h>
#include <subsys/MechanismFactory.h>
#include <controllers/ControlData.h>

class CPMTurnState : public IState
{
    public:
    CPMTurnState(ControlData* control_data, double target);
    ~CPMTurnState();

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