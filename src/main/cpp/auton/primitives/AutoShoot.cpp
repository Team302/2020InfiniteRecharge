//====================================================================================================================================================
// Copyright 2019 Lake Orion Robotics FIRST Team 302
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

/*====================================================================================================================================================
*     File name: AutonShoot.cpp
*       
*     Task: Runs Intake, Impeller, Ball Transfer, Shooter Hood and Turret to shoot durring auton.
*      
====================================================================================================================================================*/



// C++ Includes
#include <memory>

// FRC includes

// Team 302 includes
#include <auton/primitives/IPrimitive.h>
#include <auton/primitives/AutoShoot.h>
#include <auton/PrimitiveParams.h>
#include <states/BallManipulator.h>

#include <utils/Logger.h>

using namespace std;

// Third Party Includes

AutoShoot::AutoShoot
(

):  m_ballManipulator( BallManipulator::GetInstance())
{

}

void AutoShoot::Init(PrimitiveParams* params)
{
    Logger::GetLogger()->LogError("AutoShoot", "AutoShootInitialized");
    auto ballManipulatorState = params -> GetBallState();
    m_ballManipulator->SetCurrentState( ballManipulatorState , params->GetTurretAngle());
    if ( ballManipulatorState == BallManipulator::BALL_MANIPULATOR_STATE::GET_READY_TO_SHOOT )
    {
        BallManipulator::GetInstance()->SetApproxAngle( params->GetTurretAngle());
    }
}

/// @brief run the primitive (periodic routine)
/// @return void
void AutoShoot::Run()
{
    m_ballManipulator -> RunCurrentState();
} 

bool AutoShoot::IsDone()
{
    return false;
}