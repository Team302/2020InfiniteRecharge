
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

#include <gamepad/DragonGamepad.h>

#include <gamepad/axis/IDeadband.h>
#include <gamepad/axis/IProfile.h>

#include <gamepad/button/DigitalButton.h>
#include <gamepad/axis/AnalogAxis.h>
#include <gamepad/button/AnalogButton.h>
#include <gamepad/button/ToggleButton.h>


#include <frc/GenericHID.h>
#include <frc/Joystick.h>
#include <utils/Logger.h>
#include <string>
using namespace std;
using namespace frc;

DragonGamepad::DragonGamepad
(
    int port
)  : m_gamepad( new Joystick(port)),
m_axis(),
m_axisScale(),
m_axisInversionFactor(),
m_axisProfile(),
//m_button(),
m_button()
{
// device type is 24
// 8 axis
// 11 buttons
    m_axis.resize( AXIS_IDENTIFIER::MAX_AXIS );
    m_axisScale.resize( AXIS_IDENTIFIER::MAX_AXIS );
    m_axisInversionFactor.resize( AXIS_IDENTIFIER::MAX_AXIS );
    m_axisProfile.resize( AXIS_IDENTIFIER::MAX_AXIS );

    for ( auto inx=0; inx<AXIS_IDENTIFIER::MAX_AXIS; ++inx )
    {
        m_axisScale[inx] = 1.0;
        m_axisInversionFactor[inx] = 1.0;
        m_axisProfile[inx] = LINEAR;
        m_axis[inx] = nullptr;
    }
    //Create Axis objects
    m_axis[GAMEPAD_AXIS_16] = new AnalogAxis(m_gamepad, LEFT_JOYSTICK,false);
    m_axis[GAMEPAD_AXIS_16]->SetDeadBand( AXIS_DEADBAND::NONE);
    m_axis[GAMEPAD_AXIS_16]->SetAxisScaleFactor(JOYSTICK_SCALE);

    m_axis[GAMEPAD_AXIS_17] = new AnalogAxis(m_gamepad, RIGHT_JOYSTICK,false);
    m_axis[GAMEPAD_AXIS_17]->SetDeadBand( AXIS_DEADBAND::NONE);
    m_axis[GAMEPAD_AXIS_17]->SetAxisScaleFactor(JOYSTICK_SCALE);

    //Create Button objects
    m_button.resize( BUTTON_IDENTIFIER::MAX_BUTTONS );
    for ( auto inx=0; inx<BUTTON_IDENTIFIER::MAX_BUTTONS; ++inx )
    {
        m_button[inx] = nullptr;
    }
 
    m_axis[LEFT_ANALOG_BUTTON_AXIS] = new AnalogAxis(m_gamepad, LEFT_BUTTON_AXIS_ID,false );
    m_axis[LEFT_ANALOG_BUTTON_AXIS]->SetDeadBand( AXIS_DEADBAND::NONE);


    m_button[GAMEPAD_BUTTON_1] = new AnalogButton(m_axis[LEFT_ANALOG_BUTTON_AXIS], BUTTON_1_LOWERBOUND,BUTTON_1_UPPERBOUND);
    m_button[GAMEPAD_BUTTON_3] = new AnalogButton(m_axis[LEFT_ANALOG_BUTTON_AXIS], BUTTON_3_LOWERBOUND,BUTTON_3_UPPERBOUND);
    m_button[GAMEPAD_BUTTON_6] = new AnalogButton(m_axis[LEFT_ANALOG_BUTTON_AXIS], BUTTON_6_LOWERBOUND,BUTTON_6_UPPERBOUND);
    m_button[GAMEPAD_BUTTON_8] = new AnalogButton(m_axis[LEFT_ANALOG_BUTTON_AXIS], BUTTON_8_LOWERBOUND,BUTTON_8_UPPERBOUND);
    m_button[GAMEPAD_BUTTON_10] = new AnalogButton(m_axis[LEFT_ANALOG_BUTTON_AXIS], BUTTON_10_LOWERBOUND,BUTTON_10_UPPERBOUND);
    m_button[GAMEPAD_BUTTON_12] = new AnalogButton(m_axis[LEFT_ANALOG_BUTTON_AXIS], BUTTON_12_LOWERBOUND,BUTTON_12_UPPERBOUND);

    m_axis[RIGHT_ANALOG_BUTTON_AXIS] = new AnalogAxis(m_gamepad, RIGHT_BUTTON_AXIS_ID,false);
    m_axis[RIGHT_ANALOG_BUTTON_AXIS]->SetDeadBand( AXIS_DEADBAND::NONE);

    m_button[GAMEPAD_BUTTON_2] = new AnalogButton( m_axis[RIGHT_ANALOG_BUTTON_AXIS], BUTTON_2_LOWERBOUND,BUTTON_2_UPPERBOUND);
    m_button[GAMEPAD_BUTTON_4] = new AnalogButton( m_axis[RIGHT_ANALOG_BUTTON_AXIS], BUTTON_4_LOWERBOUND,BUTTON_4_UPPERBOUND);
    m_button[GAMEPAD_BUTTON_5] = new AnalogButton( m_axis[RIGHT_ANALOG_BUTTON_AXIS], BUTTON_5_LOWERBOUND,BUTTON_5_UPPERBOUND);
    m_button[GAMEPAD_BUTTON_7] = new AnalogButton( m_axis[RIGHT_ANALOG_BUTTON_AXIS], BUTTON_7_LOWERBOUND,BUTTON_7_UPPERBOUND);
    m_button[GAMEPAD_BUTTON_9] = new AnalogButton( m_axis[RIGHT_ANALOG_BUTTON_AXIS], BUTTON_9_LOWERBOUND,BUTTON_9_UPPERBOUND);
    m_button[GAMEPAD_BUTTON_11] = new AnalogButton( m_axis[RIGHT_ANALOG_BUTTON_AXIS], BUTTON_11_LOWERBOUND,BUTTON_11_UPPERBOUND);
    m_button[GAMEPAD_BUTTON_13] = new AnalogButton( m_axis[RIGHT_ANALOG_BUTTON_AXIS], BUTTON_13_LOWERBOUND,BUTTON_13_UPPERBOUND);
    //m_button[GAMEPAD_BIG_RED_BUTTON] = new AnalogButton(m_gamepad, GAMEPAD_BIG_RED_BUTTON,);


    m_axis[DIAL_ANALOG_BUTTON_AXIS] = new AnalogAxis(m_gamepad, DIAL_BUTTON_AXIS_ID,false);
    m_axis[DIAL_ANALOG_BUTTON_AXIS]->SetDeadBand( AXIS_DEADBAND::NONE);

    m_button[GAMEPAD_DIAL_22] = new AnalogButton(m_axis[DIAL_ANALOG_BUTTON_AXIS], BUTTON_22_LOWERBOUND, BUTTON_22_UPPERBOUND );
    m_button[GAMEPAD_DIAL_23] = new AnalogButton(m_axis[DIAL_ANALOG_BUTTON_AXIS], BUTTON_23_LOWERBOUND, BUTTON_23_UPPERBOUND );
    m_button[GAMEPAD_DIAL_24] = new AnalogButton(m_axis[DIAL_ANALOG_BUTTON_AXIS], BUTTON_24_LOWERBOUND, BUTTON_24_UPPERBOUND );
    m_button[GAMEPAD_DIAL_25] = new AnalogButton(m_axis[DIAL_ANALOG_BUTTON_AXIS], BUTTON_25_LOWERBOUND, BUTTON_25_UPPERBOUND );
    m_button[GAMEPAD_DIAL_26] = new AnalogButton(m_axis[DIAL_ANALOG_BUTTON_AXIS], BUTTON_26_LOWERBOUND, BUTTON_26_UPPERBOUND );
    m_button[GAMEPAD_DIAL_27] = new AnalogButton(m_axis[DIAL_ANALOG_BUTTON_AXIS], BUTTON_27_LOWERBOUND, BUTTON_27_UPPERBOUND );

    m_button[GAMEPAD_SWITCH_18] = new DigitalButton(m_gamepad, SWITCH_18_DIGITAL_ID);
    m_button[GAMEPAD_SWITCH_19] = new DigitalButton(m_gamepad, SWITCH_19_DIGITAL_ID);
    m_button[GAMEPAD_SWITCH_20] = new DigitalButton(m_gamepad, SWITCH_20_DIGITAL_ID);
    m_button[GAMEPAD_SWITCH_21] = new DigitalButton(m_gamepad, SWITCH_21_DIGITAL_ID);
    m_button[GAMEPAD_BUTTON_14_UP] = new DigitalButton(m_gamepad, LEVER_14_UP_DIGITAL_ID);
    m_button[GAMEPAD_BUTTON_14_DOWN] = new DigitalButton(m_gamepad, LEVER_14_DOWN_DIGITAL_ID);
    m_button[GAMEPAD_BUTTON_15_UP] = new DigitalButton(m_gamepad, LEVER_15_UP_DIGITAL_ID);
    m_button[GAMEPAD_BUTTON_15_DOWN] = new DigitalButton(m_gamepad, LEVER_15_DOWN_DIGITAL_ID);

    /**
    m_axis[DUMMY1] = new AnalogAxis(m_gamepad, dummy1,false);
    m_axis[DUMMY1]->SetDeadBand( AXIS_DEADBAND::NONE);
    m_axis[DUMMY2] = new AnalogAxis(m_gamepad, dummy2,false);
    m_axis[DUMMY2]->SetDeadBand( AXIS_DEADBAND::NONE);
    m_axis[DUMMY3] = new AnalogAxis(m_gamepad, dummy3,false);
    m_axis[DUMMY3]->SetDeadBand( AXIS_DEADBAND::NONE);
    **/
}

DragonGamepad::~DragonGamepad()
{
    delete m_gamepad;
    m_gamepad = nullptr;
}

double DragonGamepad::GetAxisValue
(
    AXIS_IDENTIFIER axis
) const
{
    double value = 0.0;
    if ( m_axis[axis] != nullptr )
    {
        value = m_axis[axis]->GetAxisValue();
		if ( axis == AXIS_IDENTIFIER::GAMEPAD_AXIS_16 || axis == AXIS_IDENTIFIER::GAMEPAD_AXIS_17 )
		{
			value -= JOYSTICK_OFFSET;
		}
    }
    else
    {
        Logger::GetLogger()->LogError( string("DragonGamepad::GetAxisValue no axis"), to_string(axis) );
    }
    return value;
}

bool DragonGamepad::IsButtonPressed
(
    BUTTON_IDENTIFIER button
) const
{
    bool isPressed = false;
    if ( m_button[button] != nullptr )
    {
        isPressed = m_button[button]->IsButtonPressed();
    }
	else
	{
        Logger::GetLogger()->LogError( string("DragonGamepad::IsButtonPressed no button"), to_string(button) );
	}
    return isPressed;
}

void DragonGamepad::SetAxisDeadband
(
    AXIS_IDENTIFIER axis,
    AXIS_DEADBAND type
)
{
    if ( m_axis[axis] != nullptr )
    {
        m_axis[axis]->SetDeadBand( type );
    }        
    else
    {
        Logger::GetLogger()->LogError( string("DragonGamepad::SetAxisDeadband no axis"), to_string(axis) );
    }
}

void DragonGamepad::SetAxisProfile
(
    AXIS_IDENTIFIER axis,
    AXIS_PROFILE curve
)
{
    if ( m_axis[axis] != nullptr )
    {
        m_axis[axis]->SetAxisProfile( curve );
    }        
    else
    {
        Logger::GetLogger()->LogError( string("DragonGamepad::SetAxisProfile no axis"), to_string(axis) );
    }
}

void DragonGamepad::SetAxisScale
(
    AXIS_IDENTIFIER axis,
    float scaleFactor
)
{
    if ( m_axis[axis] != nullptr )
    {
        m_axis[axis]->SetAxisScaleFactor( scaleFactor );
    }        
    else
    {
        Logger::GetLogger()->LogError( string("DragonGamepad::SetAxisScale no axis"), to_string(axis) );
    }
}

void DragonGamepad::SetButtonMode
(
    BUTTON_IDENTIFIER button,
    BUTTON_MODE mode
) 
{
	if ( m_button[button] != nullptr )
	{
		if ( mode == BUTTON_MODE::TOGGLE)
		{
			auto btn = new ToggleButton( m_button[button] );
			m_button[button] = btn;
		}
		// TODO: should have else to re-create the button or remove the toggle decorator
	}
    else
    {
        Logger::GetLogger()->LogError( string("DragonGamepad::SetButtonMode no button"), to_string(button) );
    }

}


bool DragonGamepad::WasButtonPressed
(
    BUTTON_IDENTIFIER button
) const
{
	bool isPressed = false;
	if ( m_button[button] != nullptr )
	{
		isPressed = m_button[button]->WasButtonPressed();
	}
    else
    {
        Logger::GetLogger()->LogError( string("DragonGamepad::WasButtonPressed no button"), to_string(button) );
    }
	return isPressed;
}

bool DragonGamepad::WasButtonReleased
(
    BUTTON_IDENTIFIER button
) const
{
	bool isPressed = false;
	if ( m_button[button] != nullptr )
	{
		isPressed = m_button[button]->WasButtonReleased();
	}
    else
    {
        Logger::GetLogger()->LogError( string("DragonGamepad::WasButtonReleased no button"), to_string(button) );
    }
	return isPressed;
}