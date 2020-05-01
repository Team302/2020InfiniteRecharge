/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

// C++ Includes
#include <memory>

// FRC includes

// Team 302 includes
#include <states/IState.h>
#include <subsys/IMechanism.h>
#include <subsys/MechanismFactory.h>
#include <subsys/ControlPanel.h>

// Third Party Includes

class ControlPanelColorTurn : public IState
{
    public:
    
    ControlPanelColorTurn
    (
        ControlData*    control,
        double          target
    );

    ControlPanelColorTurn() = delete;
    ~ControlPanelColorTurn() = default;

    void Init() override;
    void Run() override;
    bool AtTarget() const override;
    int colorUnits = 0;
    double rotations = 0;
    bool rescan = false;

    private:

    ControlPanel* m_controlPanel;
    ControlData* m_control;
    double       m_target;
};