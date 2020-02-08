/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <controllers/MechanismState.h>
#include <controllers/MechanismTargetData.h>

class ControlData;

class ShooterOff : public MechanismState
{
    public:
        ShooterOff
        (
            ControlData*                  controlData,
            double                        target,
            MechanismTargetData::SOLENOID solState
        );
        ShooterOff() = delete;
        ~ShooterOff() = default;
};
