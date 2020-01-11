
/*========================================================================================================
 * ButtonDecorator.cpp
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

#include <gamepad/button/ButtonDecorator.h>
#include <gamepad/button/IButton.h>

ButtonDecorator::ButtonDecorator
(
    IButton* button      // <I> - concrete button to decorate
) : IButton(),
    m_button( button )
{
}

bool ButtonDecorator::IsButtonPressed() const
{
    bool isPressed = false;
    if ( m_button != nullptr )
    {
        isPressed = m_button->IsButtonPressed();
    }
    return isPressed;
}

bool ButtonDecorator::WasButtonReleased() const 
{
    bool isPressed = false;
    if ( m_button != nullptr )
    {
        isPressed = m_button->WasButtonReleased();
    }
    return isPressed;
}

bool ButtonDecorator::WasButtonPressed() const 
{
    bool isPressed = false;
    if ( m_button != nullptr )
    {
        isPressed = m_button->WasButtonPressed();
    }
    return isPressed;
}
