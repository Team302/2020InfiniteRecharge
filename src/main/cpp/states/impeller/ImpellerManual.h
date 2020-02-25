#pragma once

#include <states/IState.h>
#include <subsys/IMechanism.h>
#include <controllers/ControlData.h>
#include <gamepad/TeleopControl.h>

class ImpellerManual : public IState
{
    public:
    ImpellerManual
    (
        ControlData* control,
        double target
    );
    ImpellerManual() = delete;
    ~ImpellerManual() = default;

    void Init() override;
    void Run() override;
    bool AtTarget() const;


    private:
    IMechanism* m_impeller;
    ControlData* m_control;
    double m_target;
    TeleopControl* m_gamepad;


};