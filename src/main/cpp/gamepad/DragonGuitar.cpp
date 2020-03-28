#include <gamepad/DragonGuitar.h>

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

DragonGuitar::DragonGuitar
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
    m_axisInversionFactor.resize( AXIS_IDENTIFIER::MAX_AXIS);
    m_axisProfile.resize( AXIS_IDENTIFIER::MAX_AXIS );

    for ( auto inx=0; inx<AXIS_IDENTIFIER::MAX_AXIS; ++inx )
    {
        m_axisScale[inx] = 1.0;
        m_axisInversionFactor[inx] = 1.0;
        m_axisProfile[inx] = LINEAR;
        m_axis[inx] = nullptr;
    }

    m_button[GUITAR_GREEN] = new DigitalButton(m_gamepad, GREEN_BUTTON_DIGITAL_ID);
    m_button[GUITAR_RED] = new DigitalButton(m_gamepad, RED_BUTTON_DIGITAL_ID);
    m_button[GUITAR_YELLOW] = new DigitalButton(m_gamepad, YELLOW_BUTTON_DIGITAL_ID);
    m_button[GUITAR_BLUE] = new DigitalButton(m_gamepad, BLUE_BUTTON_DIGITAL_ID);
    m_button[GUITAR_ORANGE] = new DigitalButton(m_gamepad, ORANGE_BUTTON_DIGITAL_ID);

    m_button[GUITAR_STRUM_UP] = new DigitalButton(m_gamepad, STRUM_UP_DIGITAL_ID);
    m_button[GUITAR_STRUM_DOWN] = new DigitalButton(m_gamepad, STRUM_DOWN_DIGITAL_ID);
}

/*DragonGuitar::~DragonGuitar()
{
    delete m_gamepad;
    m_gamepad = nullptr;
}*/

double DragonGuitar::GetAxisValue
(
    AXIS_IDENTIFIER axis
) const
{
    double value = 0.0;
}

bool DragonGuitar::IsButtonPressed
(
    BUTTON_IDENTIFIER button
) const
{
    bool isPressed = false;
    if ( m_button[button] != nullptr)
    {
        isPressed = m_button[button] -> IsButtonPressed();
    }
    else
    {
        Logger::GetLogger() -> LogError( string("DragonGuitar::IsButtonPressed no button"), to_string(button) );
    }
    return isPressed;
}

void DragonGuitar::SetAxisDeadband
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
        Logger::GetLogger() -> LogError( string("DragonGuitar::SetAxisDeadband no axis"), to_string(axis) );
    }
}

void DragonGuitar::SetAxisProfile
(
    AXIS_IDENTIFIER axis,
    AXIS_PROFILE curve
)
{
    if ( m_axis[axis] != nullptr )
    {
        m_axis[axis] -> SetAxisProfile( curve );
    }
    else
    {
        Logger::GetLogger() -> LogError( string("DragonGuitar::SetAxisScale no axis"), to_string(axis) );
    }
}

void DragonGuitar::SetButtonMode
(
    BUTTON_IDENTIFIER button,
    BUTTON_MODE mode
)
{
    if ( m_button[button] != nullptr )
    {
        if ( mode == BUTTON_MODE::TOGGLE )
        {
            auto btn = new ToggleButton( m_button[button] );
            m_button[button] = btn;
        }
    }
    else
    {
        Logger::GetLogger() -> LogError( string("DragonGuitar::SetButtonMode no button"), to_string(button) );
    }
}

bool DragonGuitar::WasButtonPressed
(
    BUTTON_IDENTIFIER button
) const
{
    bool isPressed = false;
    if ( m_button[button] != nullptr )
    {
        isPressed = m_button[button] -> WasButtonPressed();
    }
    else
    {
        Logger::GetLogger() -> LogError( string("DragonGuitar::WasButtonPressed no button"), to_string(button) );
    }
    return isPressed;
}

bool DragonGuitar::WasButtonReleased
(
    BUTTON_IDENTIFIER button
) const
{
    bool isPressed = false;
    if ( m_button[button] != nullptr )
    {
        isPressed = m_button[button] -> WasButtonReleased();
    }
    else
    {
        Logger::GetLogger() -> LogError( string("DragonGuitar::WasButtonReleased no button"), to_string(button) );
    }
    return isPressed;
}