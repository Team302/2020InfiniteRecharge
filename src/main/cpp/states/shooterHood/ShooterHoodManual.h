#pragma once
#include <states/IState.h>
#include <subsys/IMechanism.h>
#include <controllers/ControlData.h>
#include <gamepad/TeleopControl.h>

class ShooterHoodManual : public IState
{
    public:
    ShooterHoodManual
    (
        ControlData* control,
        double target
    );
    ShooterHoodManual() = delete;
    ~ShooterHoodManual() = default;

    void Init() override;
    void Run() override;
    bool AtTarget() const;


    private:
    IMechanism* m_shooterHood;
    ControlData* m_control;
    double m_target;
    TeleopControl* m_gamepad;


};