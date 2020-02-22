
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

// C++ Includes
#include <memory>

// FRC includes

// Team 302 Includes
#include <states/chassis/ArcadeDrive.h>
#include <gamepad/IDragonGamePad.h>
#include <subsys/IChassis.h>
#include <gamepad/TeleopControl.h>
#include <states/IState.h>
#include <subsys/ChassisFactory.h>
#include <utils/Logger.h>


using namespace std;

/// @brief initialize the object and validate the necessary items are not nullptrs
ArcadeDrive::ArcadeDrive() : IState(),
							 m_chassis( ChassisFactory::GetChassisFactory()->GetIChassis() ),
						     m_controller( TeleopControl::GetInstance() ),
							 m_curvatureBased( false ),
							 m_quickStopAccumulator(0.0),
							 m_quickStopAlpha(0.0)
{
    if ( m_controller == nullptr  )
    {
        Logger::GetLogger()->LogError( string( "ArcadeDrive::ArcadeDrive"), string("TelopControl is nullptr"));
    }

    if ( m_chassis.get() == nullptr )
    {
        Logger::GetLogger()->LogError( string( "ArcadeDrive::ArcadeDrive"), string("Chassis is nullptr"));
    }

}

/// @brief toggle between curvature and normal modes
/// @param [in] true - use curvature-based driving, false use normal (default) drive mode
/// @return void
void ArcadeDrive::SetCurvatureBased
( 
	bool 	curvatureBased
)
{
	m_curvatureBased = curvatureBased;
}


/// @brief initialize the profiles for the various gamepad inputs
/// @return void
void ArcadeDrive::Init()
{
    auto controller = GetController();
    if ( controller != nullptr )
    {
        controller->SetAxisProfile( TeleopControl::FUNCTION_IDENTIFIER::ARCADE_DRIVE_THROTTLE, IDragonGamePad::AXIS_PROFILE::CUBED );
        controller->SetAxisProfile( TeleopControl::FUNCTION_IDENTIFIER::ARCADE_DRIVE_STEER, IDragonGamePad::AXIS_PROFILE::CUBED );
    }
}

/// @brief calculate the output for the wheels on the chassis from the throttle and steer components
/// @return void
void ArcadeDrive::Run( )
{
    // Get throttle and steer values
    auto throttle = GetThrottle();
    auto steer = GetSteer();
	
	double left = 0.0;
	double right = 0.0;
	if ( m_curvatureBased )
	{
		CurvatureDrive( throttle, steer, &left, &right );
	}
	else
	{
		NormalDrive( throttle, steer, &left, &right );
	}


    // Set the percentages
    m_chassis.get()->SetOutput( ControlModes::PERCENT_OUTPUT, left, right );
}

/// @brief indicates that we are not at our target
/// @return bool
 bool ArcadeDrive::AtTarget() const
 {
     return false;
 }


/// @brief get the throttle component from the game controller
/// @return double - throttle value between -1.0 and 1.0
double ArcadeDrive::GetThrottle()
{
    auto controller = GetController();
    return ( ( controller != nullptr ) ? controller->GetAxisValue( TeleopControl::FUNCTION_IDENTIFIER::ARCADE_DRIVE_THROTTLE) : 0.0 );
}

/// @brief get the steer component from the game controller
/// @return double - steer value between -1.0 and 1.0
double ArcadeDrive::GetSteer()
{
    auto controller = GetController();
    return ( ( controller != nullptr ) ? controller->GetAxisValue( TeleopControl::FUNCTION_IDENTIFIER::ARCADE_DRIVE_STEER) : 0.0 );
}

/// @brief calculate the normal output values for the wheels on the chassis from the throttle and steer components
/// @param [in] thtottie - forward/backward value between -1.0 and 1.0
/// @param [in] steer - turning value between -1.0 and 1.0
/// @param [out] left - calculated value to set to the left wheels
/// @param [out] right - calculated value to set to the right wheels
/// @return void
void ArcadeDrive::NormalDrive
(
	double 	throttle,
	double  steer,
	double* left,
	double* right
)
{
    // convert throttle  / steer values to left / right values
    *left = (throttle + steer);
    *right = (throttle - steer);

    // make sure the values are within -1.0 to 1.0
    auto maxValue = max(abs( *left ), abs( *right ) );
    if ( maxValue > 1.0 )
    {
        *left /= maxValue;
        *right /= maxValue;
    }
}


/// @brief calculate the curvature-based output values for the wheels on the chassis from the throttle and steer components as well as the quick turn input
/// @param [in] thtottie - forward/backward value between -1.0 and 1.0
/// @param [in] steer - turning value between -1.0 and 1.0
/// @param [out] left - calculated value to set to the left wheels
/// @param [out] right - calculated value to set to the right wheels
/// @return void
void ArcadeDrive::CurvatureDrive
(
	double 	throttle,
	double  steer,
	double* left,
	double* right
)
{
	auto isQuickTurn = GetController() != nullptr ? GetController()->IsButtonPressed( TeleopControl::FUNCTION_IDENTIFIER::CURVATURE_DRIVE_QUICK_TURN ) : false;

	double angularPower = steer;

	if (isQuickTurn) 
	{
		if (abs(throttle) < m_quickStopThreshold) 
		{
			m_quickStopAccumulator = (1 - m_quickStopAlpha) * m_quickStopAccumulator + m_quickStopAlpha * steer * 2;
		}
	} 
	else 
	{
		angularPower = abs(throttle) * steer - m_quickStopAccumulator;

		if (m_quickStopAccumulator > 1.0) 
		{
			m_quickStopAccumulator -= 1.0;
		} 
		else if (m_quickStopAccumulator < -1.0) 
		{
			m_quickStopAccumulator += 1.0;
		} 
		else 
		{
			m_quickStopAccumulator = 0.0;
		}
	}

	*left = throttle + angularPower;
	*right = throttle - angularPower;

	// If rotation is overpowered, reduce both outputs to within acceptable range
	if (isQuickTurn) 
	{
		if (*left > 1.0) 
		{
			*right -= *left - 1.0;
			*left = 1.0;
		} 
		else if (*right > 1.0) 
		{
			*left -= *right - 1.0;
			*right = 1.0;
		} 
		else if (*left < -1.0) 
		{
		  *right -= *left + 1.0;
		  *left = -1.0;
		} 
		else if (*right < -1.0) 
		{
		  *left -= *right + 1.0;
		  *right = -1.0;
		}
	}

    // make sure the values are within -1.0 to 1.0
    auto maxValue = max(abs( *left ), abs( *right ) );
    if ( maxValue > 1.0 )
    {
        *left /= maxValue;
        *right /= maxValue;
    }  

}


