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

    m_button[]
}