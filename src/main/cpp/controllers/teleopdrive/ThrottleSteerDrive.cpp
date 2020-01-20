
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
#include <cmath>

// FRC includes

// Team 302 Includes
#include <controllers/teleopdrive/ThrottleSteerDrive.h>
#include <gamepad/TeleopControl.h>
#include <subsys/IChassis.h>
#include <subsys/ChassisFactory.h>
#include <controllers/ControlModes.h>
#include <utils/Logger.h>

using namespace std;

/// @class ThrottleSteerDrive
/// @brief Drive differential chassis using a throttle input and a sheer (turn) input

/// @brief initialize the object 
ThrottleSteerDrive::ThrottleSteerDrive() : IState(),
                                           m_chassis( ChassisFactory::GetChassisFactory()->GetIChassis() ),
                                           m_controller( TeleopControl::GetInstance() )
{
    if ( m_controller == nullptr  )
    {
        Logger::GetLogger()->LogError( string( "ThrottleSteerDrive::ThrottleSteerDrive"), string("TelopControl is nullptr"));
    }

    if ( m_chassis.get() == nullptr )
    {
        Logger::GetLogger()->LogError( string( "ThrottleSteerDrive::ThrottleSteerDrive"), string("Chassis is nullptr"));
    }

}

void ThrottleSteerDrive::Run( )
{
    // Get throttle and steer values from the subclasses
    auto throttle = GetThrottle();
    auto steer = GetSteer();

    // convert throttle  / steer values to left / right values
    auto left = throttle + steer;
    auto right = throttle - steer;

    // make sure the values are within -1.0 to 1.0
    auto maxValue = abs( left );
    if ( abs(right) > maxValue )
    {
        maxValue = abs( right );
    }
    if ( maxValue > 1.0 )
    {
        left /= maxValue;
        right /= maxValue;
    }

    // Set the percentages
    m_chassis.get()->SetOutput( ControlModes::PERCENT_OUTPUT, left, right );
}

 bool ThrottleSteerDrive::AtTarget() const
 {
     return false;
 }


