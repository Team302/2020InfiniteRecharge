
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
#include <controllers/teleopdrive/GTADrive.h>
#include <gamepad/IDragonGamePad.h>
#include <subsys/IChassis.h>
#include <gamepad/TeleopControl.h>

using namespace std;

using namespace std;

GTADrive::GTADrive() : ThrottleSteerDrive()
{
    auto controller = GetController();
    if ( controller != nullptr )
    {
        controller->SetAxisProfile( TeleopControl::FUNCTION_IDENTIFIER::GTA_DRIVE_FORWARD, IDragonGamePad::AXIS_PROFILE::CUBED );
        controller->SetAxisProfile( TeleopControl::FUNCTION_IDENTIFIER::GTA_DRIVE_BACKWARD, IDragonGamePad::AXIS_PROFILE::CUBED );
        controller->SetAxisProfile( TeleopControl::FUNCTION_IDENTIFIER::GTA_DRIVE_STEER, IDragonGamePad::AXIS_PROFILE::CUBED );
    }
}

//=======================================================================
double GTADrive::GetThrottle()
{
    auto controller = GetController();
    double throttle = 0.0;
    if ( controller != nullptr )
    {
        auto forward = controller->GetAxisValue( TeleopControl::FUNCTION_IDENTIFIER::GTA_DRIVE_FORWARD);
        auto backward = controller->GetAxisValue( TeleopControl::FUNCTION_IDENTIFIER::GTA_DRIVE_BACKWARD);
        throttle = forward - backward;
    }
    return throttle;
}

//=======================================================================
double GTADrive::GetSteer()
{
    auto controller = GetController();
    return ( ( controller != nullptr ) ? controller->GetAxisValue( TeleopControl::FUNCTION_IDENTIFIER::GTA_DRIVE_STEER) : 0.0 );
}


