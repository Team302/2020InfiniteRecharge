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

// C++ Includes
#include <memory>

// FRC includes

// Team 302 includes
#include <auton/primitives/IPrimitive.h>
#include <auton/primitives/AutoShoot.h>
#include <auton/PrimitiveParams.h>
#include <subsys/Shooter.h>

using namespace std;

// Third Party Includes

AutoShoot::AutoShoot
(

):  m_stateManager(new ShooterStateMgr())
{

}

void AutoShoot::Init(PrimitiveParams* params)
{
   bool shooterOn = params->IsShooterOn();
   auto state = ShooterStateMgr::SHOOTER_STATE::SHOOT;
   if (!shooterOn)
   {
       state = ShooterStateMgr::SHOOTER_STATE::OFF;
   }
   m_stateManager -> SetCurrentState(state, false);
}

/// @brief run the primitive (periodic routine)
/// @return void
void AutoShoot::Run()
{
    m_stateManager -> RunCurrentState();
}

bool AutoShoot::IsDone()
{
    return true;
}