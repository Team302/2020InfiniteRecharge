
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
#include <gamepad/IDragonGamePad.h>
#include <gamepad/TeleopControl.h>
#include <gamepad/FunctionMap.h>

// Third Party Includes

/// @class FunctionMap 
/// @brief This defines the mapping from a single function to its controller (index and mode) and button or axis 

/// @brief      The contructor initializes the object to default values
FunctionMap::FunctionMap() : m_function( TeleopControl::FUNCTION_IDENTIFIER::UNKNOW_FUNCTION ),
                             m_controllerIndex( 0 ),
                             m_axisID( IDragonGamePad::AXIS_IDENTIFIER::UNDEFINED_AXIS ),
                             m_axisDeadband( IDragonGamePad::AXIS_DEADBAND::APPLY_STANDARD_DEADBAND ),
                             m_axisProfile( IDragonGamePad::AXIS_PROFILE::CUBED ),
                             m_buttonID( IDragonGamePad::BUTTON_IDENTIFIER::UNDEFINED_BUTTON ),
                             m_buttonMode( IDragonGamePad::BUTTON_MODE::STANDARD )
{
}
/// @brief      The contructor initializes the object
/// @param [in] TeleopControl::FUNCTION_IDENTIFIER function - the function this maps to
/// @param [in] int controllerIndex - the controller number starting from 0 this applies to 
/// @param [in] IDragonGamePad::AXIS_IDENTIFIER axisID - the axis ID this maps to
/// @param [in] IDragonGamePad::AXIS_DEADBAND deadband - the deadband type this axis should have
/// @param [in] IDragonGamePad::AXIS_PROFILE profile - the profile type this axis should have
/// @param [in] IDragonGamePad::BUTTON_IDENTIFIER buttonID - the button ID this maps to
/// @param [in] IDragonGamePad::BUTTON_MODE buttonType - the type of button this should beS
FunctionMap::FunctionMap
(
    TeleopControl::FUNCTION_IDENTIFIER  function,
    int                                 controllerIndex,
    IDragonGamePad::AXIS_IDENTIFIER     axisID,
    IDragonGamePad::AXIS_DEADBAND       deadBand,
    IDragonGamePad::AXIS_PROFILE        profile,
    IDragonGamePad::BUTTON_IDENTIFIER   buttonID,
    IDragonGamePad::BUTTON_MODE         buttonType
) : m_function( function ),
    m_controllerIndex( controllerIndex ),
    m_axisID( axisID ),
    m_axisDeadband( deadBand ),
    m_axisProfile( profile ),
    m_buttonID( buttonID ),
    m_buttonMode( buttonType )
{
}


/// @brief  Returns the function
/// @return TeleopControl::FUNCTION_IDENTIFIER the function this object is defining
TeleopControl::FUNCTION_IDENTIFIER FunctionMap::GetFunction() const
{
    return m_function;
}


/// @brief  Returns the controller index
/// @return int the controller number starting from 0
int FunctionMap::GetControllerIndex() const
{
    return m_controllerIndex;
}


/// @brief  Returns the axis identifier
/// @return int the axis this is valid for (UNDEFINED_AXIS means this isn't using an axis) 
IDragonGamePad::AXIS_IDENTIFIER FunctionMap::GetAxisID() const
{
    return m_axisID;

}


/// @brief  Returns the axis deadband type
/// @return IDragonGamePad::AXIS_DEADBAND the axis deadband type 
IDragonGamePad::AXIS_DEADBAND FunctionMap::GetDeadband() const
{
    return m_axisDeadband;
}



/// @brief  Returns the axis profile type
/// @return IDragonGamePad::AXIS_PROFILE the axis profile type 
IDragonGamePad::AXIS_PROFILE FunctionMap::GetProfile() const
{
    return m_axisProfile;
}


/// @brief  Returns the button identifier
/// @return int the button this is valid for (UNDEFINED_BUTTON means this isn't using a button) 
IDragonGamePad::BUTTON_IDENTIFIER FunctionMap::GetButtonID() const
{
    return m_buttonID;
}



/// @brief  Returns the button mode
/// @return IDragonGamePad::BUTTON_MODE the button mode 
IDragonGamePad::BUTTON_MODE FunctionMap::GetMode() const
{
    return m_buttonMode;
}

