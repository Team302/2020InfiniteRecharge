
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
		else if ( ds->GetJoystickType( inx ) == GenericHID::kHID1stPerson )
		{
            auto gamepad = new DragonGamepad( inx );
			m_controllers[inx] = gamepad;
		}
	}


    // Initialize the items to not defined
	m_axisIDs.resize(FUNCTION_IDENTIFIER::MAX_FUNCTIONS);
	m_buttonIDs.resize(FUNCTION_IDENTIFIER::MAX_FUNCTIONS);
	m_controllerIndex.resize(FUNCTION_IDENTIFIER::MAX_FUNCTIONS);
    for ( int inx=0; inx<FUNCTION_IDENTIFIER::MAX_FUNCTIONS; ++inx )
    {
        m_axisIDs[inx]    		= IDragonGamePad::UNDEFINED_AXIS;
        m_buttonIDs[inx]  		= IDragonGamePad::UNDEFINED_BUTTON;
        m_controllerIndex[inx]  = -1;
    }

    auto ctrlNo = 0;
    if ( m_controllers[ctrlNo] != nullptr && ds->GetJoystickIsXbox(ctrlNo) )
    {
		m_controllerIndex[ TANK_DRIVE_LEFT_CONTROL ] 	= ctrlNo;
		m_axisIDs[ TANK_DRIVE_LEFT_CONTROL ]    		= IDragonGamePad::LEFT_JOYSTICK_Y;
		m_controllerIndex[ TANK_DRIVE_RIGHT_CONTROL ] 	= ctrlNo;
		m_axisIDs[ TANK_DRIVE_RIGHT_CONTROL ]   		= IDragonGamePad::RIGHT_JOYSTICK_Y;

		m_controllerIndex[ ARCADE_DRIVE_THROTTLE ] 		= ctrlNo;
		m_axisIDs[ ARCADE_DRIVE_THROTTLE ]      		= IDragonGamePad::LEFT_JOYSTICK_Y;
		m_controllerIndex[ ARCADE_DRIVE_STEER ] 		= ctrlNo;
		m_axisIDs[ ARCADE_DRIVE_STEER ]         		= IDragonGamePad::RIGHT_JOYSTICK_X;

		m_controllerIndex[ GTA_DRIVE_FORWARD ] 		    = ctrlNo;
		m_axisIDs[ GTA_DRIVE_FORWARD ]      		    = IDragonGamePad::RIGHT_TRIGGER;
		m_controllerIndex[ GTA_DRIVE_BACKWARD ] 		= ctrlNo;
		m_axisIDs[ GTA_DRIVE_BACKWARD ]         		= IDragonGamePad::LEFT_TRIGGER;
		m_controllerIndex[ GTA_DRIVE_STEER ] 		    = ctrlNo;
		m_axisIDs[ GTA_DRIVE_STEER ]         		    = IDragonGamePad::LEFT_JOYSTICK_X;

		m_controllerIndex[ CURVATURE_DRIVE_QUICK_TURN ]	= ctrlNo;
		m_buttonIDs[ CURVATURE_DRIVE_QUICK_TURN ]		= IDragonGamePad::RIGHT_BUMPER;

		m_controllerIndex[ SWITCH_DRIVE_MODE ]          = ctrlNo;
		m_buttonIDs[ SWITCH_DRIVE_MODE ]                = IDragonGamePad::A_BUTTON;

		/*m_controllerIndex[ CLIMBER_EXTEND ] = ctrlNo;
		m_buttonIDs[ CLIMBER_EXTEND ] = IDragonGamePad::A_BUTTON;*/

		m_controllerIndex[ CLIMBER_WINCH_UP ] = ctrlNo;
		m_buttonIDs[ CLIMBER_WINCH_UP ] = IDragonGamePad::X_BUTTON;

		m_controllerIndex[ HOOK_DELIVERY_UP] 	= ctrlNo;
		m_axisIDs[ HOOK_DELIVERY_UP]				= IDragonGamePad::RIGHT_TRIGGER;
		m_controllerIndex[ HOOK_DELIVERY_DOWN ] 	= ctrlNo;
		m_axisIDs[ HOOK_DELIVERY_DOWN ]         	= IDragonGamePad::LEFT_TRIGGER;

		/*m_controllerIndex[ CONTROL_PANEL_RAISE ] = ctrlNo;
		m_buttonIDs[ CONTROL_PANEL_RAISE] = IDragonGamePad::Y_BUTTON;

		m_controllerIndex[ CONTROL_PANEL_SPIN_WHEEL] = ctrlNo;
		m_buttonIDs[ CONTROL_PANEL_SPIN_WHEEL] = IDragonGamePad::B_BUTTON;*/

    }
    else
    {
        Logger::GetLogger()->LogError( string("TeleopControl::TeleopControl"), string("No controller plugged into port 0"));
    }

    ctrlNo = 1;
    if ( m_controllers[ctrlNo] != nullptr && ds->GetJoystickIsXbox(ctrlNo) )
    {
		m_controllerIndex[ SHOOTER_HOOD_MANUAL_AXIS] = ctrlNo;
		m_axisIDs[ SHOOTER_HOOD_MANUAL_AXIS ] = IDragonGamePad::RIGHT_JOYSTICK_Y;

		m_controllerIndex[ TURRET_MANUAL_AXIS] = ctrlNo;
		m_axisIDs[ TURRET_MANUAL_AXIS] = IDragonGamePad::LEFT_JOYSTICK_X;

		m_controllerIndex[ OFF ] = ctrlNo;
		m_buttonIDs[ OFF ] = IDragonGamePad::START_BUTTON;

		m_controllerIndex[ INTAKE ] = ctrlNo;
		m_buttonIDs[ INTAKE ] = IDragonGamePad::A_BUTTON;

		m_controllerIndex[ INTAKE_HUMAN_PLAYER] = ctrlNo;
		m_buttonIDs[ INTAKE_HUMAN_PLAYER ] = IDragonGamePad::B_BUTTON;

		m_controllerIndex[ SHOOT ] = ctrlNo;
		m_buttonIDs[ SHOOT ] = IDragonGamePad::X_BUTTON;
		
		m_controllerIndex[ TURRET_MANUAL_BUTTON] = ctrlNo;
		m_buttonIDs[ TURRET_MANUAL_BUTTON] = IDragonGamePad::Y_BUTTON;

		m_controllerIndex[ SHOOTER_HOOD_MANUAL_BUTTON] = ctrlNo;
		m_buttonIDs[ SHOOTER_HOOD_MANUAL_BUTTON] = IDragonGamePad::Y_BUTTON;

		m_controllerIndex[SHOOTER_MANUAL_SHOOT] = ctrlNo;
		m_buttonIDs[SHOOTER_MANUAL_SHOOT] = IDragonGamePad::POV_0;
		
		m_controllerIndex[SHOOTER_OFF] = ctrlNo;
		m_buttonIDs[SHOOTER_OFF] = IDragonGamePad::POV_180;

		m_controllerIndex[TURRET_LIMELIGHT_AIM] = ctrlNo;
		m_buttonIDs[TURRET_LIMELIGHT_AIM] = IDragonGamePad::POV_270;

		m_controllerIndex[ UNJAM_CLOCKWISE ] = ctrlNo;
		m_buttonIDs[ UNJAM_CLOCKWISE ] = IDragonGamePad::RIGHT_BUMPER;
		
		m_controllerIndex[ UNJAM_COUNTERCLOCKWISE ] = ctrlNo;
		m_buttonIDs[ UNJAM_COUNTERCLOCKWISE ] = IDragonGamePad::LEFT_BUMPER;

		m_controllerIndex[ TRANSFER_UP ] = ctrlNo;
		m_buttonIDs[ TRANSFER_UP ] = IDragonGamePad::LEFT_TRIGGER_PRESSED;

		m_controllerIndex[ TRANSFER_DOWN ] = ctrlNo;
		m_buttonIDs[ TRANSFER_DOWN ] = IDragonGamePad::RIGHT_TRIGGER_PRESSED;
		
		/*
		m_controllerIndex[ TURRET_LIMELIGHT_AIM] = ctrlNo;
		m_buttonIDs[ TURRET_LIMELIGHT_AIM] = IDragonGamePad::B_BUTTON;
		*/
	}
    else if ( m_controllers[ctrlNo] != nullptr )
    {
	}
	else
	{
        Logger::GetLogger()->LogError( string("TeleopControl::TeleopControl"), string("Controller 1 not handled"));
    }

	ctrlNo = 2;
    if ( m_controllers[ctrlNo] != nullptr && ds->GetJoystickIsXbox(ctrlNo) )
    {
	}
    else if ( m_controllers[ctrlNo] != nullptr )
    {
		m_controllerIndex[INTAKE_ON] = ctrlNo;
		m_buttonIDs[INTAKE_ON] = IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_1;
		m_controllerIndex[INTAKE_OFF] = ctrlNo;
		m_buttonIDs[INTAKE_OFF] = IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_2;

		m_controllerIndex[IMPELLER_OFF] = ctrlNo;
		m_buttonIDs[IMPELLER_OFF] = IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_3;
		m_controllerIndex[IMPELLER_HOLD] = ctrlNo;
		m_buttonIDs[IMPELLER_HOLD] = IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_4;
		/*m_controllerIndex[IMPELLER_AGITATE] = ctrlNo;
		m_buttonIDs[IMPELLER_AGITATE] = IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_5;
		*/
		m_controllerIndex[IMPELLER_TO_SHOOTER] = ctrlNo;
		m_buttonIDs[IMPELLER_TO_SHOOTER] = IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_5;
		

		//m_controllerIndex[CLIMBER_EXTEND] = ctrlNo;
		//m_buttonIDs[CLIMBER_EXTEND] = IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_14_UP;
		//m_controllerIndex[CLIMBER_LIFT] = ctrlNo;
		//m_buttonIDs[CLIMBER_LIFT] = IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_14_DOWN;
		//m_controllerIndex[CLIMBER_CRAWL] = ctrlNo;
		//m_buttonIDs[CLIMBER_CRAWL] = IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_DIAL_23;

		m_controllerIndex[BALL_TRANSFER_OFF] = ctrlNo;
		m_buttonIDs[BALL_TRANSFER_OFF] = IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_6;
		m_controllerIndex[BALL_TRANSFER_TO_IMPELLER] = ctrlNo;
		m_buttonIDs[BALL_TRANSFER_TO_IMPELLER] = IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_7;
		m_controllerIndex[BALL_TRANSFER_TO_SHOOTER] = ctrlNo;
		m_buttonIDs[BALL_TRANSFER_TO_SHOOTER] = IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_8;
		
		/*m_controllerIndex[CONTROL_PANEL_STOW] = ctrlNo;
		m_buttonIDs[CONTROL_PANEL_STOW] = IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_15_DOWN;
		m_controllerIndex[CONTROL_PANEL_RAISE] = ctrlNo;
		m_buttonIDs[CONTROL_PANEL_RAISE] = IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_15_UP;
		m_controllerIndex[CONTROL_PANEL_SPIN_WHEEL] = ctrlNo;
		m_buttonIDs[CONTROL_PANEL_SPIN_WHEEL] = IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_5;
		m_controllerIndex[CONTROL_PANEL_TURN_TO_COLOR] = ctrlNo;
		m_buttonIDs[CONTROL_PANEL_TURN_TO_COLOR] = IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_6;
*/
		

		/*m_controllerIndex[TURRET_MANUAL_BUTTON] = ctrlNo;
		m_buttonIDs[TURRET_MANUAL_BUTTON] = IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_11;*/
		
		/*m_buttonIDs[SHOOTER_MANUAL_AIM] = IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_9;
		m_controllerIndex[SHOOTER_MANUAL_ADJUST_DISTANCE] = ctrlNo;
		m_buttonIDs[SHOOTER_MANUAL_ADJUST_DISTANCE] = IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_10;
		*/
	}
	else
	{
        Logger::GetLogger()->LogError( string("TeleopControl::TeleopControl"), string("Controller 2 not handled"));
    }

    ctrlNo = 3;
    if ( m_controllers[ctrlNo] != nullptr && ds->GetJoystickIsXbox(ctrlNo) )
    {
	}
    else if ( m_controllers[ctrlNo] != nullptr )
    {
	}
	else
	{
		Logger::GetLogger()->LogError( string("TeleopControl::TeleopControl"), string("Controller 3 not handled"));

	}

    ctrlNo = 4;
    if ( m_controllers[ctrlNo] != nullptr && ds->GetJoystickIsXbox(ctrlNo) )
    {
	}
    else if ( m_controllers[ctrlNo] != nullptr )
    {
	}
	else
	{
        Logger::GetLogger()->LogError( string("TeleopControl::TeleopControl"), string("Controller 4 not handled"));
    }

    ctrlNo = 5;
    if ( m_controllers[ctrlNo] != nullptr && ds->GetJoystickIsXbox(ctrlNo) )
    {
	}
    else if ( m_controllers[ctrlNo] != nullptr )
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


