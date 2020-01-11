
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

// FRC includes

// Team 302 includes

// Third Party Includes
#include <string>
#include <frc/GenericHID.h>
#include <gamepad/IDragonGamePad.h>
#include <gamepad/DragonXBox.h>
#include <gamepad/DragonGamePad.h>
#include <gamepad/TeleopControl.h>
#include <frc/DriverStation.h>
#include <utils/Logger.h>

using namespace frc;
using namespace std;

//----------------------------------------------------------------------------------
// Method:      GetInstance
// Description: If there isn't an instance of this class, it will create one.  The
//              single class instance will be returned.
// Returns:     OperatorInterface*  instance of this class
//----------------------------------------------------------------------------------
TeleopControl* TeleopControl::m_instance = nullptr; // initialize the instance variable to nullptr
TeleopControl* TeleopControl::GetInstance()
{
    if ( TeleopControl::m_instance == nullptr )
    {
        TeleopControl::m_instance = new TeleopControl();
    }
    return TeleopControl::m_instance;
}
//----------------------------------------------------------------------------------
// Method:      OperatorInterface <<constructor>>
// Description: This will construct and initialize the object.
//              It maps the functions to the buttons/axis.
//---------------------------------------------------------------------------------
TeleopControl::TeleopControl() : m_axisIDs(),
								 m_buttonIDs(),
								 m_controllerIndex(),
								 m_controllers(),
								 m_count( 0 )
{
	DriverStation* ds = &DriverStation::GetInstance();
	for ( int inx=0; inx<DriverStation::kJoystickPorts; ++inx )
	{
		m_controllers[inx] = nullptr;
		if ( ds->GetJoystickIsXbox( inx ) )
		{
            auto xbox = new DragonXBox( inx );
			m_controllers[inx] = xbox;
		}
		else if ( ds->GetJoystickType( inx ) == GenericHID::kHIDJoystick )
		{
            auto gamepad = new DragonGamepad( inx );
			m_controllers[inx] = gamepad;
		}
	}


    // Initialize the items to not defined
    for ( int inx=0; inx<m_maxFunctions; ++inx )
    {
        m_axisIDs[inx]    		= IDragonGamePad::UNDEFINED_AXIS;
        m_buttonIDs[inx]  		= IDragonGamePad::UNDEFINED_BUTTON;
        m_controllerIndex[inx]  = -1;
    }

    if ( m_controllers[0] != nullptr && ds->GetJoystickIsXbox(0) )
    {
		m_controllerIndex[ TANK_DRIVE_LEFT_CONTROL ] 	= 0;
		m_axisIDs[ TANK_DRIVE_LEFT_CONTROL ]    		= IDragonGamePad::LEFT_JOYSTICK_Y;
		m_controllerIndex[ TANK_DRIVE_RIGHT_CONTROL ] 	= 0;
		m_axisIDs[ TANK_DRIVE_RIGHT_CONTROL ]   		= IDragonGamePad::RIGHT_JOYSTICK_Y;

		m_controllerIndex[ ARCADE_DRIVE_THROTTLE ] 		= 0;
		m_axisIDs[ ARCADE_DRIVE_THROTTLE ]      		= IDragonGamePad::LEFT_JOYSTICK_Y;
		m_controllerIndex[ ARCADE_DRIVE_STEER ] 		= 0;
		m_axisIDs[ ARCADE_DRIVE_STEER ]         		= IDragonGamePad::RIGHT_JOYSTICK_X;

		m_controllerIndex[ GTA_DRIVE_FORWARD ] 		    = 0;
		m_axisIDs[ GTA_DRIVE_FORWARD ]      		    = IDragonGamePad::RIGHT_TRIGGER;
		m_controllerIndex[ GTA_DRIVE_BACKWARD ] 		= 0;
		m_axisIDs[ GTA_DRIVE_BACKWARD ]         		= IDragonGamePad::LEFT_TRIGGER;
		m_controllerIndex[ GTA_DRIVE_STEER ] 		    = 0;
		m_axisIDs[ GTA_DRIVE_STEER ]         		    = IDragonGamePad::LEFT_JOYSTICK_X;

		m_controllerIndex[ SWITCH_DRIVE_MODE ]          = 0;
		m_buttonIDs[ SWITCH_DRIVE_MODE ]                = IDragonGamePad::A_BUTTON;

    }
    else
    {
        Logger::GetLogger()->LogError( string("TeleopControl::TeleopControl"), string("No controller plugged into port 0"));
    }

    if ( m_controllers[1] != nullptr && ds->GetJoystickIsXbox(1) )
    {
	}
    else if ( m_controllers[1] != nullptr )
    {
	}
	else
	{
        Logger::GetLogger()->LogError( string("TeleopControl::TeleopControl"), string("Controller 1 not handled"));
    }

    if ( m_controllers[2] != nullptr && ds->GetJoystickIsXbox(2) )
    {
	}
    else if ( m_controllers[2] != nullptr )
    {
	}
	else
	{
        Logger::GetLogger()->LogError( string("TeleopControl::TeleopControl"), string("Controller 2 not handled"));
    }

    if ( m_controllers[3] != nullptr && ds->GetJoystickIsXbox(3) )
    {
	}
    else if ( m_controllers[3] != nullptr )
    {
	}
	else
	{
		Logger::GetLogger()->LogError( string("TeleopControl::TeleopControl"), string("Controller 3 not handled"));

	}

    if ( m_controllers[4] != nullptr && ds->GetJoystickIsXbox(4) )
    {
	}
    else if ( m_controllers[4] != nullptr )
    {
	}
	else
	{
        Logger::GetLogger()->LogError( string("TeleopControl::TeleopControl"), string("Controller 4 not handled"));
    }

    if ( m_controllers[5] != nullptr && ds->GetJoystickIsXbox(5) )
    {
	}
    else if ( m_controllers[5] != nullptr )
    {
	}
	else
	{
        Logger::GetLogger()->LogError( string("TeleopControl::TeleopControl"), string("Controller 5 not handled"));
    }
}


//------------------------------------------------------------------
// Method:      SetAxisScaleFactor
// Description: Allow the range of values to be set smaller than
//              -1.0 to 1.0.  By providing a scale factor between 0.0
//              and 1.0, the range can be made smaller.  If a value
//              outside the range is provided, then the value will
//              be set to the closest bounding value (e.g. 1.5 will
//              become 1.0)
// Returns:     void
//------------------------------------------------------------------
void TeleopControl::SetAxisScaleFactor
(
    TeleopControl::FUNCTION_IDENTIFIER  	function,      // <I> - function that will update an axis
    float                                   scaleFactor    // <I> - scale factor used to limit the range
)
{
	int ctlIndex = m_controllerIndex[ function];
	IDragonGamePad::AXIS_IDENTIFIER axis = m_axisIDs[ function ];
    if ( ctlIndex > -1 && axis != IDragonGamePad::AXIS_IDENTIFIER::UNDEFINED_AXIS  )
    {
    	if (m_controllers[ ctlIndex ] != nullptr)
    	{
    		m_controllers[ ctlIndex ]->SetAxisScale( axis,scaleFactor);
    	}
    }
}

//------------------------------------------------------------------
// Method:      SetAxisProfile
// Description: Sets the axis profile for the specifed axis
// Returns:     void
//------------------------------------------------------------------
void TeleopControl::SetAxisProfile
(
    TeleopControl::FUNCTION_IDENTIFIER  function,       // <I> - function that will update an axis
    IDragonGamePad::AXIS_PROFILE        profile         // <I> - profile to use
)
{
	int ctlIndex = m_controllerIndex[ function];
	IDragonGamePad::AXIS_IDENTIFIER axis = m_axisIDs[ function ];
    if ( ctlIndex > -1 && axis != IDragonGamePad::AXIS_IDENTIFIER::UNDEFINED_AXIS  )
    {
    	if (m_controllers[ ctlIndex ] != nullptr)
    	{
    		m_controllers[ ctlIndex ]->SetAxisProfile( axis,profile);
    	}
    }
}

//------------------------------------------------------------------
// Method:      GetAxisValue
// Description: Reads the joystick axis, removes any deadband (small
//              value) and then scales as requested.
// Returns:     float   -  scaled axis value
//------------------------------------------------------------------
float TeleopControl::GetAxisValue
(
    TeleopControl::FUNCTION_IDENTIFIER  function    // <I> - function that whose axis will be read
) const
{
    float value = 0.0;
	int ctlIndex = m_controllerIndex[ function];
	IDragonGamePad::AXIS_IDENTIFIER axis = m_axisIDs[ function ];
    if ( ctlIndex > -1 && axis != IDragonGamePad::AXIS_IDENTIFIER::UNDEFINED_AXIS  )
    {
    	if (m_controllers[ ctlIndex ] != nullptr)
    	{
    		value = m_controllers[ ctlIndex ]->GetAxisValue( axis );
    	}
    }
    return value;
}

//------------------------------------------------------------------
// Method:      IsButtonPressed
// Description: Reads the button value.  Also allows POV, bumpers,
//              and triggers to be treated as buttons.
// Returns:     bool   -  scaled axis value
//------------------------------------------------------------------
bool TeleopControl::IsButtonPressed
(
    TeleopControl::FUNCTION_IDENTIFIER  function    // <I> - function that whose button will be read
) const
{
    bool isSelected = false;
	int ctlIndex = m_controllerIndex[ function];
	IDragonGamePad::BUTTON_IDENTIFIER btn = m_buttonIDs[ function ];
    if ( ctlIndex > -1 && btn != IDragonGamePad::BUTTON_IDENTIFIER::UNDEFINED_BUTTON  )
    {
    	if (m_controllers[ ctlIndex ] != nullptr)
    	{
    		isSelected = m_controllers[ ctlIndex ]->IsButtonPressed( btn );
    	}
    }
    return isSelected;
}


