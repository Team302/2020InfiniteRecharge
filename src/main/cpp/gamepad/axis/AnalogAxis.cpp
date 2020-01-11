
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
//==================================================================================
/// @class  AnalogAxis
/// @brief  This class handles the analog inputs on a gamepad
//==================================================================================

// C++ Includes
#include <cmath>
#include <string>


// FRC includes
#include <frc/GenericHID.h>

// Team 302 includes

#include <gamepad/axis/AnalogAxis.h>

#include <gamepad/axis/LinearProfile.h>
#include <gamepad/axis/CubedProfile.h>
#include <gamepad/axis/DeadbandValue.h>
#include <gamepad/axis/FlippedAxis.h>
#include <gamepad/axis/NoDeadbandValue.h>
#include <gamepad/axis/ScaledDeadbandValue.h>
#include <gamepad/axis/SquaredProfile.h>

#include <utils/Logger.h>

// Third Party Includes


using namespace std;
using namespace frc;

//=========================================================================================
/// @brief  construct the AnalogAxis object
/// @param [in] frc::GenericHID* gamepad - gamepad to query
/// @param [in] int axisID - id this axis maps to
/// @param [in] bool flipped - true the axis is reversed from what is expected, false the axis 
///         has the expected direction.
//=========================================================================================
AnalogAxis::AnalogAxis
(
    GenericHID*                         gamepad,            
    int                                 axisID,             
    bool                                flipAxis            
) : m_gamepad( gamepad ),                                   
    m_axis( axisID ),
    m_profile( LinearProfile::GetInstance() ),  
    m_deadband( NoDeadbandValue::GetInstance() ), 
    m_scale( new ScaledAxis()  )
{
    if ( flipAxis )
    {
        m_scale->SetScaleFactor( -1.0 );
    }
}

//================================================================================================
/// @brief  Read the analog (axis) value and return it.  If the gamepad has an issue, return 0.0.
/// @return double axis value after applying the deadband, profile and scaling operations
//================================================================================================
double AnalogAxis::GetAxisValue()
{
    double value = 0.0;

    if ( m_gamepad != nullptr )
    {
        value = GetRawValue();
        value = m_deadband->ApplyDeadband( value );
        value = m_profile->ApplyProfile( value );
        value = m_scale->Scale( value );
    }
    else
    {
            string msg = "missing gamepad ";
            Logger::GetLogger()->LogError( "AnalogAxis::GetAxisValue", msg );
    }
    return value;
}

//================================================================================================
/// @brief  Set the deadband type
/// @param  IDragonGamePad::AXIS_DEADBAND type - deadband option
/// @return void
//================================================================================================
void AnalogAxis::SetDeadBand
(
    IDragonGamePad::AXIS_DEADBAND   type            /// <I> - deadband option
)
{
    switch ( type )
    {
        case IDragonGamePad::AXIS_DEADBAND::NONE:
            m_deadband = NoDeadbandValue::GetInstance();
            break;

        case IDragonGamePad::AXIS_DEADBAND::APPLY_STANDARD_DEADBAND:
            m_deadband = DeadbandValue::GetInstance();
            break;

        case IDragonGamePad::AXIS_DEADBAND::APPLY_SCALED_DEADBAND:
            m_deadband = ScaledDeadbandValue::GetInstance();
            break;

        default:
            string msg = "invalid deadband specified ";
            Logger::GetLogger()->LogError( "AnalogAxis::SetDeadBand", msg );
            break;
    }

}


//================================================================================================
/// @brief  Set the axis profile (cubed, linear, etc.)
/// @param  IDragonGamePad::AXIS_PROFILE profile - profile option
/// @return void
//================================================================================================
void AnalogAxis::SetAxisProfile
(
     IDragonGamePad::AXIS_PROFILE    profile         /// <I> - axis profile
)
{
    switch ( profile )
    {
        case IDragonGamePad::AXIS_PROFILE::CUBED:
            m_profile = CubedProfile::GetInstance();
            break;

        case IDragonGamePad::AXIS_PROFILE::SQUARED:
            m_profile = SquaredProfile::GetInstance();
            break;

        case IDragonGamePad::AXIS_PROFILE::LINEAR:
            m_profile = LinearProfile::GetInstance();
            break;

        default:
            string msg = "invalid profile specified ";
            Logger::GetLogger()->LogError( "AnalogAxis::SetAxisProfile", msg );
            break;
    }
}

//================================================================================================
/// @brief  Set the axis scale factor (default is 1.0) 
/// @param  double scale - value greater than 0.0
/// @return void
//================================================================================================        
void AnalogAxis::SetAxisScaleFactor
(
    double scale                     /// <I> - scale factor - must be positive number
)
{
    m_scale->SetScaleFactor( scale );
}
       
//==================================================================================
/// @brief  Returns the analog input's raw value. If there is a connection problem, 
///         0.0 will be returned and a debug message will be written.
/// @return double - raw axis value 
//==================================================================================
double AnalogAxis::GetRawValue()
{
    double value = 0.0;
    if ( m_gamepad != nullptr )
    {
        value = m_gamepad->GetRawAxis( m_axis );
    }
    else
    {
        string msg = "gamepad missing ";
        Logger::GetLogger()->LogError( "AnalogAxis::GetRawValue", msg );
    }
    return value;
}

