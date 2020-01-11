
/*========================================================================================================
 * DragonXBox.cpp
 *========================================================================================================
 *
 * File Description:  Wrapper for an XBOX controller used to control the robot in teleop mode.
 *
 *========================================================================================================*/


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

#include <gamepad/DragonXBox.h>

#include <gamepad/axis/IDeadband.h>
#include <gamepad/axis/IProfile.h>

#include <gamepad/button/AnalogButton.h>
#include <gamepad/button/DigitalButton.h>
#include <gamepad/button/ButtonDecorator.h>
#include <gamepad/button/POVButton.h>
#include <gamepad/button/ToggleButton.h>


#include <frc/GenericHID.h>
#include <frc/XboxController.h>
 
DragonXBox::DragonXBox
( 
    int port
) : m_xbox( new frc::XboxController( port ) )
{
    // Create Axis Objects
    m_axis[ LEFT_JOYSTICK_X ]  = new AnalogAxis( m_xbox, 0, false );
    m_axis[ LEFT_JOYSTICK_Y]  = new AnalogAxis( m_xbox, 1, true  );
    m_axis[ LEFT_TRIGGER]     = new AnalogAxis( m_xbox, 2, false );
    m_axis[ RIGHT_TRIGGER]    = new AnalogAxis( m_xbox, 3, false );
    m_axis[ RIGHT_JOYSTICK_X] = new AnalogAxis( m_xbox, 4, false );
    m_axis[ RIGHT_JOYSTICK_Y] = new AnalogAxis( m_xbox, 5, true  );

    /*
    m_axis[ LEFT_JOYSTICK_Y ] =  nullptr;
    m_axis[ RIGHT_JOYSTICK_X ] =  nullptr;
    m_axis[ RIGHT_JOYSTICK_Y ] =  nullptr;
    m_axis[ LEFT_TRIGGER ] =  nullptr;
    m_axis[ RIGHT_TRIGGER ] =  nullptr;    
    */

    // Create DigitalButton Objects for the physical buttons
    m_button[A_BUTTON]            = new DigitalButton( m_xbox, 1  );
    m_button[B_BUTTON]            = new DigitalButton( m_xbox, 2  );
    m_button[X_BUTTON]            = new DigitalButton( m_xbox, 3  );
    m_button[Y_BUTTON]            = new DigitalButton( m_xbox, 4  );
    m_button[LEFT_BUMPER]         = new DigitalButton( m_xbox, 5  );
    m_button[RIGHT_BUMPER]        = new DigitalButton( m_xbox, 6  );
    m_button[BACK_BUTTON]         = new DigitalButton( m_xbox, 7  );
    m_button[START_BUTTON]        = new DigitalButton( m_xbox, 8  );
    m_button[LEFT_STICK_PRESSED]  = new DigitalButton( m_xbox, 9  );
    m_button[RIGHT_STICK_PRESSED] = new DigitalButton( m_xbox, 10 );
    
    // Create AnalogButton Objects for the triggers
    m_button[LEFT_TRIGGER_PRESSED] = new AnalogButton( m_axis[LEFT_TRIGGER] );
    m_button[RIGHT_TRIGGER_PRESSED] = new AnalogButton( m_axis[RIGHT_TRIGGER] );

    // Create POVButton Objects for the POV

    m_button[POV_0]   = new POVButton( m_xbox, 0   );
    m_button[POV_45]  = new POVButton( m_xbox, 45  );
    m_button[POV_90]  = new POVButton( m_xbox, 90  );
    m_button[POV_135] = new POVButton( m_xbox, 135 );
    m_button[POV_180] = new POVButton( m_xbox, 180 );
    m_button[POV_225] = new POVButton( m_xbox, 225 );
    m_button[POV_270] = new POVButton( m_xbox, 270 );
    m_button[POV_315] = new POVButton( m_xbox, 315 );
}

DragonXBox::~DragonXBox()
{
    delete m_xbox;
    m_xbox = nullptr;
}

   
//getters
///-------------------------------------------------------------------------------------------------
/// Method:      GetAxisValue
/// Description: Return the current value (between -1.0 and 1.0) for the requested axis.
/// Returns:     double   - current axis value
///-------------------------------------------------------------------------------------------------
double DragonXBox::GetAxisValue
(
    AXIS_IDENTIFIER    axis// <I> - axis identifier to read
) const
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



///-------------------------------------------------------------------------------------------------
/// Method:      IsButtonPressed
/// Description: Return whether the requested button is selected (true) or not (false)
/// Returns:     bool    true  - button is pressed
///              false - button is not pressed
///-------------------------------------------------------------------------------------------------
bool DragonXBox::IsButtonPressed
(
    BUTTON_IDENTIFIER    button // <I> - button to check
) const
{
    bool isPressed = false;
    if ( m_button[button] != nullptr )
    {
        isPressed = m_button[button]->IsButtonPressed();
    }
    return isPressed;
}
        

    //==================================================================================
    /// <summary>
    /// Method:         WasButtonReleased
    /// Description:    Read whether the button was released since the last query.  This
    ///                 is only valid for digital buttons (normal buttons and bumpers).
    /// </summary>
    //==================================================================================
    bool DragonXBox::WasButtonReleased
    (
        BUTTON_IDENTIFIER    button // <I> - button to check
    ) const    
    {
        bool isPressed = false;
        if ( m_button[button] != nullptr )
        {
            isPressed = m_button[button]->WasButtonReleased();
        }
        return isPressed;
    }
    

    //==================================================================================
    /// <summary>
    /// Method:         WasButtonPressed
    /// Description:    Read whether the button was pressed since the last query.  This
    ///                 is only valid for digital buttons (normal buttons and bumpers).
    /// </summary>
    //==================================================================================
    bool DragonXBox::WasButtonPressed
    (
        BUTTON_IDENTIFIER    button // <I> - button to check
    ) const        
    {
        bool isPressed = false;
        if ( m_button[button] != nullptr )
        {
            isPressed = m_button[button]->WasButtonPressed();
        }
        return isPressed;
    }
 

//setters
///-------------------------------------------------------------------------------------------------
/// Method:      SetProfile
/// Description: Specify the profile curve used for setting the sensitivity of the axis.  By default,
///              this is linear, but a cubic curve would give more control when the axis is barely
///              pressed (e.g. if it were moved 50% forward, instead of returning 0.5, it would
///              return 0.5 * 0.5 * 0.5 or .125, but when the axis was moved all the way forward,
///              it would return the same value -- 1.0.  Since it is cubed, it retains the sign.
///
///              This affects values returned from GetAxis calls.
/// Returns:     void
///-------------------------------------------------------------------------------------------------
void DragonXBox::SetAxisProfile
(
    AXIS_IDENTIFIER                 axis,       // <I> - axis identifier to modify
    AXIS_PROFILE  	                curve       // <I> - the definition of the sensitivity
)
{
    if ( m_axis[axis] != nullptr )
    {
        m_axis[axis]->SetAxisProfile( curve );
    }        
}


///-------------------------------------------------------------------------------------------------
/// Method:      SetScale
/// Description: Scale the returned value to a range between the specified negative scale factor and
///              the scale factor.  This is used to reduce the maximum value returned.
///
///              This affects values returned from GetAxis calls.
/// Returns:     void
///-------------------------------------------------------------------------------------------------
void DragonXBox::SetAxisScale
(
    AXIS_IDENTIFIER    			        axis,       // <I> - axis identifier to modify
    float                               scaleFactor // <I> - value  (0 < scale <= 1.0) to scale the axis value
)
{
    if ( m_axis[axis] != nullptr )
    {
        m_axis[axis]->SetAxisScaleFactor( scaleFactor );
    }        
} 
 
//==================================================================================
/// <summary>
/// Method:         SetAxisDeadband
/// Description:    Specify what deadband behavior is desired such as none, standard,
///                 standard with scaling.
/// Returns:        void
/// </summary>
//==================================================================================
void DragonXBox::SetAxisDeadband
(
    AXIS_IDENTIFIER axis, /// <I> - axis to modify
    AXIS_DEADBAND type    /// <I> - deadband option
) 
{
    if ( m_axis[axis] != nullptr )
    {
        m_axis[axis]->SetDeadBand( type );
    }        
}



    //==================================================================================
    /// <summary>
    /// Method:         SetButtonMode
    /// Description:    Specify how the button should behave.  Examples include (but
    ///                 not limited to):
    ///                 - pressed / not pressed
    ///                 - toggle
    /// Returns:        void
    /// </summary>
    //==================================================================================
    void DragonXBox::SetButtonMode
    (
        BUTTON_IDENTIFIER button, /// <I> - button to check
        BUTTON_MODE mode          /// <I> - button behavior
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
    }



