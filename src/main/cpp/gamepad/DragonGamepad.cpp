/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <gamepad/DragonGamepad.h>

#include <gamepad/axis/IDeadband.h>
#include <gamepad/axis/IProfile.h>

#include <gamepad/button/DigitalButton.h>
#include <gamepad/axis/AnalogAxis.h>
#include <gamepad/button/AnalogButton.h>

#include <frc/GenericHID.h>
#include <frc/Joystick.h>

DragonGamepad::DragonGamepad
(
    int port
)  : m_gamepad( new frc::Joystick(port)),
m_axis(),
m_axisScale(),
m_axisInversionFactor(),
m_axisProfile(),
m_button(),
m_analogButtons()
{
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
    m_axis[GAMEPAD_AXIS_16] = new AnalogAxis(m_gamepad, 0,false);
    m_axis[GAMEPAD_AXIS_17] = new AnalogAxis(m_gamepad, 0,false);
    m_axis[GAMEPAD_DIAL_22] = new AnalogAxis(m_gamepad, GAMEPAD_DIAL_22,false);
    m_axis[GAMEPAD_DIAL_23] = new AnalogAxis(m_gamepad, GAMEPAD_DIAL_23,false);
    m_axis[GAMEPAD_DIAL_24] = new AnalogAxis(m_gamepad, GAMEPAD_DIAL_24,false);
    m_axis[GAMEPAD_DIAL_25] = new AnalogAxis(m_gamepad, GAMEPAD_DIAL_25,false);
    m_axis[GAMEPAD_DIAL_26] = new AnalogAxis(m_gamepad, GAMEPAD_DIAL_26,false);
    m_axis[GAMEPAD_DIAL_27] = new AnalogAxis(m_gamepad, GAMEPAD_DIAL_27,false);
    m_axis[LEFT_ANALOG_BUTTON_AXIS] = new AnalogAxis(m_gamepad, LEFT_BUTTON_AXIS_ID,false );
    m_axis[RIGHT_ANALOG_BUTTON_AXIS] = new AnalogAxis(m_gamepad, RIGHT_BUTTON_AXIS_ID,false);

    //Create Button objects
    m_analogButtons.resize( BUTTON_IDENTIFIER::MAX_BUTTONS );
    for ( auto inx=0; inx<BUTTON_IDENTIFIER::MAX_BUTTONS; ++inx )
    {
        m_analogButtons[inx] = nullptr;
    }
    m_analogButtons[GAMEPAD_BUTTON_1] = new AnalogButton(m_axis[LEFT_ANALOG_BUTTON_AXIS], BUTTON_1_LOWERBAND,BUTTON_1_UPPERBAND);
    m_analogButtons[GAMEPAD_BUTTON_2] = new AnalogButton( m_axis[RIGHT_ANALOG_BUTTON_AXIS], BUTTON_2_LOWERBAND,BUTTON_2_UPPERBAND);
    m_analogButtons[GAMEPAD_BUTTON_3] = new AnalogButton(m_axis[LEFT_ANALOG_BUTTON_AXIS], BUTTON_3_LOWERBAND,BUTTON_3_UPPERBAND);
    m_analogButtons[GAMEPAD_BUTTON_4] = new AnalogButton( m_axis[RIGHT_ANALOG_BUTTON_AXIS], BUTTON_4_LOWERBAND,BUTTON_4_UPPERBAND);
    m_analogButtons[GAMEPAD_BUTTON_5] = new AnalogButton( m_axis[RIGHT_ANALOG_BUTTON_AXIS], BUTTON_5_LOWERBAND,BUTTON_5_UPPERBAND);
    m_analogButtons[GAMEPAD_BUTTON_6] = new AnalogButton(m_axis[LEFT_ANALOG_BUTTON_AXIS], BUTTON_6_LOWERBAND,BUTTON_6_UPPERBAND);
    m_analogButtons[GAMEPAD_BUTTON_7] = new AnalogButton( m_axis[RIGHT_ANALOG_BUTTON_AXIS], BUTTON_7_LOWERBAND,BUTTON_7_UPPERBAND);
    m_analogButtons[GAMEPAD_BUTTON_8] = new AnalogButton(m_axis[LEFT_ANALOG_BUTTON_AXIS], BUTTON_8_LOWERBAND,BUTTON_8_UPPERBAND);
    m_analogButtons[GAMEPAD_BUTTON_9] = new AnalogButton( m_axis[RIGHT_ANALOG_BUTTON_AXIS], BUTTON_9_LOWERBAND,BUTTON_9_UPPERBAND);
    m_analogButtons[GAMEPAD_BUTTON_10] = new AnalogButton(m_axis[LEFT_ANALOG_BUTTON_AXIS], BUTTON_10_LOWERBAND,BUTTON_10_UPPERBAND);
    m_analogButtons[GAMEPAD_BUTTON_11] = new AnalogButton( m_axis[RIGHT_ANALOG_BUTTON_AXIS], BUTTON_11_LOWERBAND,BUTTON_11_UPPERBAND);
    m_analogButtons[GAMEPAD_BUTTON_12] = new AnalogButton(m_axis[LEFT_ANALOG_BUTTON_AXIS], BUTTON_12_LOWERBAND,BUTTON_12_UPPERBAND);
    m_analogButtons[GAMEPAD_BUTTON_13] = new AnalogButton( m_axis[RIGHT_ANALOG_BUTTON_AXIS], BUTTON_13_LOWERBAND,BUTTON_13_UPPERBAND);
    //m_analogButtons[GAMEPAD_BIG_RED_BUTTON] = new AnalogButton(m_gamepad, GAMEPAD_BIG_RED_BUTTON,);

    m_button.resize( BUTTON_IDENTIFIER::MAX_BUTTONS );
    for ( auto inx=0; inx<BUTTON_IDENTIFIER::MAX_BUTTONS; ++inx )
    {
        m_button[inx] = nullptr;
    }
    m_button[GAMEPAD_SWITCH_18] = new DigitalButton(m_gamepad, 1);
    m_button[GAMEPAD_SWITCH_19] = new DigitalButton(m_gamepad, 2);
    m_button[GAMEPAD_SWITCH_20] = new DigitalButton(m_gamepad, 3);
    m_button[GAMEPAD_SWITCH_21] = new DigitalButton(m_gamepad, 4);
    m_button[GAMEPAD_BUTTON_14_UP] = new DigitalButton(m_gamepad, 7);
    m_button[GAMEPAD_BUTTON_14_DOWN] = new DigitalButton(m_gamepad, 6);
    m_button[GAMEPAD_BUTTON_15_UP] = new DigitalButton(m_gamepad, 9);
    m_button[GAMEPAD_BUTTON_15_DOWN] = new DigitalButton(m_gamepad, 8);
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
    double output = 0.0;
	if ( axis < MAX_GAMEPAD_AXIS )
	{
		switch ( axis )//switch method to find out the axes for each gamepad buttons that use axis.
		{
		case GAMEPAD_AXIS_16:
			output = m_gamepad->GetY( frc::GenericHID::kLeftHand ) * m_axisInversionFactor[ axis ];
			break;

		case GAMEPAD_AXIS_17:
			output = m_gamepad->GetY( frc::GenericHID::kRightHand ) * m_axisInversionFactor[ axis ];
			break;

		// jw - changed 2 to axis
		case GAMEPAD_DIAL_22: //Dial has six settings, 22-27.
			output = m_gamepad->GetY( frc::GenericHID::kLeftHand ) * m_axisInversionFactor[ axis ];
			break;

		case GAMEPAD_DIAL_23:
			output = m_gamepad->GetY( frc::GenericHID::kLeftHand ) * m_axisInversionFactor[ axis ];
			break;

		case GAMEPAD_DIAL_24:
			output = m_gamepad->GetY( frc::GenericHID::kLeftHand ) * m_axisInversionFactor[ axis ];
			break;

		case GAMEPAD_DIAL_25:
			output = m_gamepad->GetY( frc::GenericHID::kLeftHand ) * m_axisInversionFactor[ axis ];
			break;

		case GAMEPAD_DIAL_26:
			output = m_gamepad->GetY( frc::GenericHID::kLeftHand ) * m_axisInversionFactor[ axis ];
			break;

		case GAMEPAD_DIAL_27:
			output = m_gamepad->GetY( frc::GenericHID::kLeftHand ) * m_axisInversionFactor[ axis ];
			break;

		default:
			break;

		}
		if (std::abs(output) < APPLY_STANDARD_DEADBAND)
		{
			output = 0.0;
		}
		else if (std::abs(output)> APPLY_STANDARD_DEADBAND)
		{
			if ( m_axisProfile[axis] == CUBED )
			{
				output = pow( output, 3.0 );
			}
			output = output * m_axisScale[axis];
		}
	}
	return output;
}

bool DragonGamepad::IsButtonPressed
(
    BUTTON_IDENTIFIER button
) const
{
    bool isPressed = false;
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
}

void DragonGamepad::SetButtonMode
(
    BUTTON_IDENTIFIER button,
    BUTTON_MODE mode
) 
{

}

double DragonGamepad::GetRawAxis
(
    AXIS_IDENTIFIER axis
)
{
    double value = 0.0;
    if ( m_axis[axis] != nullptr )
    {
        value = m_axis[axis]->GetAxisValue();
    }
    else
    {
        printf( "==>> no axis %d \n", axis );
    }
    return value;
}

bool DragonGamepad::IsRawButtonPressed
(
    BUTTON_IDENTIFIER button
) 
{
    bool pressed = false;
    if(m_button[button] != nullptr)
    {
        pressed = m_button[button]->IsButtonPressed();
    }
    return pressed;
}

bool DragonGamepad::IsRawButtonPressed
(
    ANALOG_BUTTON_IDENTIFIER button
) 
{
    bool pressed = false;
    if(m_analogButtons[button] != nullptr)
    {
        pressed = m_analogButtons[button]->IsButtonPressed();
    }
    return pressed;
}
int DragonGamepad::GetPOVValue
(
)
{
    return 0;
}

bool DragonGamepad::WasButtonPressed
(
    BUTTON_IDENTIFIER button
) const
{
    return false;
}

bool DragonGamepad::WasButtonReleased
(
    BUTTON_IDENTIFIER button
) const
{
    return false;
}