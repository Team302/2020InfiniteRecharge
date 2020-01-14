/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "TestChassis.h"

#include <hw/usages/MotorControllerUsage.h>
#include <hw/interfaces/IDragonMotorController.h>

#include <hw/DragonSparkMax.h>

using namespace rev;
using namespace std;
TestChassis::TestChassis():
    m_leftFront(new DragonSparkMax(1,0,MotorControllerUsage::FRONT_LEFT_DRIVE,CANSparkMax::MotorType::kBrushless,0.0)),
    m_leftBack(new DragonSparkMax(4,3,MotorControllerUsage::BACK_LEFT_DRIVE,CANSparkMax::MotorType::kBrushless,0.0)),
    m_rightFront(new DragonSparkMax(3,15,MotorControllerUsage::FRONT_RIGHT_DRIVE,CANSparkMax::MotorType::kBrushless,0.0)),
    m_rightBack(new DragonSparkMax(2,12,MotorControllerUsage::BACK_RIGHT_DRIVE,CANSparkMax::MotorType::kBrushless,0.0))
{
    m_leftFront->Invert(true);
    m_rightFront->Invert(false);

    m_leftBack->Follow(m_leftFront);
    m_rightBack->Follow(m_rightFront);
}

void TestChassis::SetLeftRightPower(double leftPower, double rightPower)
{
    m_leftFront->SetControlMode(IDragonMotorController::PERCENT_OUTPUT);
    m_rightFront->SetControlMode(IDragonMotorController::PERCENT_OUTPUT);

    m_leftFront->Set(leftPower);
    m_rightFront->Set(rightPower);
}

double TestChassis::GetVelocity(bool left)
{
    if(left)
    {
        return m_leftFront->GetRPS();
    }
    else
    {
        return m_rightFront->GetRPS();
    }

}

double TestChassis::GetRotations()
{
    return 0.0;
}

