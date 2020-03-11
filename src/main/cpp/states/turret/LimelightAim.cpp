//====================================================================================================================================================
// Copyright 2020 Lake Orion Robotics FIRST Team 302
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================

#include "states/turret/LimelightAim.h"
#include "subsys/MechanismFactory.h"
#include "subsys/IMechanism.h"
#include "subsys/Turret.h"
#include "controllers/ControlData.h"
#include "subsys/MechanismTypes.h"
#include "hw/DragonLimelight.h"
#include "hw/factories/LimelightFactory.h"
#include "frc/smartdashboard/SmartDashboard.h"

using namespace std;

LimelightAim::LimelightAim(ControlData* controlData, double target): m_controlData(controlData),
    m_atTarget(false),
    m_target(target),
    m_turret( MechanismFactory::GetMechanismFactory()->GetIMechanism( MechanismTypes::TURRET) ),
    m_limelight(new DragonLimelight(IDragonSensor::MAIN_LIMELIGHT, "limelight", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)),
    m_targetPosition(0.0),
    m_start(false)
{
}

void LimelightAim::Init()
{
    m_turret->SetControlConstants(m_controlData);
    m_limelight->SetLEDMode(DragonLimelight::LED_ON);
}

void LimelightAim::Run()
{
    /*if(!m_start)
    {
        m_turret->SetOutput(m_controlData->GetMode(), m_target);
        m_start = true;
    }
    double targetHorizontalOffset = m_limelight->GetTargetHorizontalOffset();
    double power = -targetHorizontalOffset / 20 *.5;
    m_turret->SetOutput(m_controlData->GetMode(), power);
//    if(m_targetPosition - 5 < m_turret->GetCurrentPosition() < m_targetPosition + 5) //arbitrary tolerance for now will change later
    if( abs( m_targetPosition - m_turret->GetCurrentPosition() ) <  5.0 ) //arbitrary tolerance for now will change later
    {
        m_atTarget = true;
    }
    //frc::SmartDashboard::PutNumber("Target Position", targetPosition);
    frc::SmartDashboard::PutNumber("limelight position", targetHorizontalOffset);
    */
   //m_turret->SetOutput(m_controlData->GetMode(), 90.0);
   double targetHorizontalOffset = m_limelight->GetTargetHorizontalOffset();
   frc::SmartDashboard::PutNumber("horizontal offset", targetHorizontalOffset);
   double currentPosition = m_turret->GetCurrentPosition();
   /*double scaledOffset;
   if(targetHorizontalOffset < 0)
   {
       scaledOffset = targetHorizontalOffset - 2.0 - (targetHorizontalOffset/28.0) * 5.0;
   }
   else
   {
       scaledOffset = targetHorizontalOffset + 2.0 + (targetHorizontalOffset/28.0) * 5.0;
   }*/
   m_turret->SetOutput(ControlModes::POSITION_DEGREES, currentPosition + targetHorizontalOffset + 2.0);
}

bool LimelightAim::AtTarget() const
{
    return m_atTarget;
}

void LimelightAim::UpdateTarget
( 
    double target
)
{
    m_target = target;
}