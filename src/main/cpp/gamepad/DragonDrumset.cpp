#include <gamepad/DragonDrumset.h>

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

DragonDrumset::DragonDrumset
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

    m_button[RED_PAD] = new DigitalButton(m_gamepad, RED_PAD_DIGITAL_ID);
    m_button[YELLOW_PAD] = new DigitalButton(m_gamepad, YELLOW_PAD_DIGITAL_ID);
    m_button[BLUE_PAD] = new DigitalButton(m_gamepad, BLUE_PAD_DIGITAL_ID);
    m_button[GREEN_PAD] = new DigitalButton(m_gamepad, GREEN_PAD_DIGITAL_ID);
}
/*DragonDrumset::~DragonDrumset()
{
    delete m_gamepad;
    m_gamepad = nullptr;
}*/

double DragonDrumset::GetAxisValue
(
    AXIS_IDENTIFIER axis
) const
{
    double value = 0.0;
}

bool DragonDrumset::IsButtonPressed
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

void DragonDrumset::SetAxisDeadband
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

void DragonDrumset::SetAxisProfile
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

void DragonDrumset::SetAxisScale
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

void DragonDrumset::SetButtonMode
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


bool DragonDrumset::WasButtonPressed
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

bool DragonDrumset::WasButtonReleased
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
    
    
    


