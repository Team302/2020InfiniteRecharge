
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

// Team 302 Includes
#include <controllers/teleopdrive/ArcadeDrive.h>
#include <gamepad/IDragonGamePad.h>
#include <subsys/IChassis.h>
#include <gamepad/TeleopControl.h>

using namespace std;

ArcadeDrive::ArcadeDrive() : ThrottleSteerDrive()
{
    auto controller = GetController();
    if ( controller != nullptr )
    {
        controller->SetAxisProfile( TeleopControl::FUNCTION_IDENTIFIER::ARCADE_DRIVE_THROTTLE, IDragonGamePad::AXIS_PROFILE::CUBED );
        controller->SetAxisProfile( TeleopControl::FUNCTION_IDENTIFIER::ARCADE_DRIVE_STEER, IDragonGamePad::AXIS_PROFILE::CUBED );
    }
}

//=======================================================================
double ArcadeDrive::GetThrottle()
{
    auto controller = GetController();
    return ( ( controller != nullptr ) ? controller->GetAxisValue( TeleopControl::FUNCTION_IDENTIFIER::ARCADE_DRIVE_THROTTLE) : 0.0 );
}

//=======================================================================
double ArcadeDrive::GetSteer()
{
    auto controller = GetController();
    return ( ( controller != nullptr ) ? controller->GetAxisValue( TeleopControl::FUNCTION_IDENTIFIER::ARCADE_DRIVE_STEER) : 0.0 );
}


