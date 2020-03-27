#include <gamepad/DragonDDR.h>

#include <gamepad/axis/IDeadband.h>
#include <gamepad/axis/IProfile.h>

#include <gamepad/button/DigitalButton.h>
#include <gamepad/axis/AnalogAxis.h>
#include <gamepad/button/AnalogButton.h>
#include <gamepad/button/ToggleButton.h>

#include <frc/GenericHID.h>
#include <utils/Logger.h>
#include <string>
using namespace std;
using namespace frc;

DragonDDR::DragonDDR
(
    int port
) : m_gamepad(new Joystick(port)),
m_axis(),
m_axisScale(),
m_axisInversionFactor(),
m_axisProfile(),
m_button()
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

    m_button[DDR_UP] = new DigitalButton(m_gamepad, DDR_UP_DIGITAL_ID);
    m_button[DDR_RIGHT] = new DigitalButton(m_gamepad, DDR_RIGHT_DIGITAL_ID);
    m_button[DDR_DOWN] = new DigitalButton(m_gamepad, DDR_DOWN_DIGITAL_ID);
    m_button[DDR_LEFT] = new DigitalButton(m_gamepad, DDR_LEFT_DIGITAL_ID);

}

/*DragonDDR::~DragonDDR()
{
    delete m_gamepad;
    m_gamepad = nullptr;
}*/

double DragonDDR::GetAxisValue
(
    AXIS_IDENTIFIER axis
) const
{
    double value = 0.0;
}

bool DragonDDR::IsButtonPressed
(
    BUTTON_IDENTIFIER button
) const
{
    bool isPressed = false;
    if ( m_button[button] != nullptr )
    {
        isPressed = m_button[button] -> IsButtonPressed();
    }
    else
    {
        Logger::GetLogger() -> LogError( string("DragonGamepad::IsButtonPressed no button"), to_string(button) );
    }
    return isPressed;
}

void DragonDDR::SetAxisDeadband
(
    AXIS_IDENTIFIER axis,
    AXIS_DEADBAND type
)
{
    if ( m_axis[axis] != nullptr )
    {
        m_axis[axis] -> SetDeadBand( type );
    }
    else
    {
        Logger::GetLogger() -> LogError( string("DragonGamepad::SetAxisDeadband no axis"), to_string(axis) );
    }
}

void DragonDDR::SetAxisProfile
(
    AXIS_IDENTIFIER axis,
    AXIS_PROFILE curve
)
{
    if( m_axis[axis] != nullptr )
    {
        m_axis[axis] -> SetAxisProfile( curve );
    }
    else
    {
        Logger::GetLogger() -> LogError( string("DragonGamepad::SetAxisProfile no axis"), to_string(axis) );
    }
}

void DragonDDR::SetAxisScale
(
    AXIS_IDENTIFIER axis,
    float scaleFactor
)
{
    if ( m_axis[axis] != nullptr )
    {
        m_axis[axis] -> SetAxisScaleFactor( scaleFactor );
    }
    else
    {
        Logger::GetLogger() -> LogError( string("DragonGamepad::SetAxisScale no axis"), to_string(axis) );
    }
}

void DragonDDR::SetButtonMode
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
    }
    else
    {
        Logger::GetLogger() -> LogError( string("DragonGamepad::SetButtonMode no button"), to_string(button) );
    }
}

bool DragonDDR::WasButtonPressed
(
    BUTTON_IDENTIFIER button
) const
{
    bool isPressed = false;
}