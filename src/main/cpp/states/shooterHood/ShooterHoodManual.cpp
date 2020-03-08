#include <memory>

#include <states/shooterHood/ShooterHoodManual.h>
#include <states/IState.h>
#include <subsys/IMechanism.h>
#include <subsys/MechanismFactory.h>
#include <gamepad/TeleopControl.h>
#include <controllers/ControlModes.h>

using namespace std;

ShooterHoodManual::ShooterHoodManual
(
    ControlData* control,
    double target
) : IState(),
    m_shooterHood( MechanismFactory::GetMechanismFactory()->GetIMechanism(MechanismTypes::MECHANISM_TYPE::SHOOTER_HOOD)),
    m_control( control ),
    m_target( target ),
    m_gamepad(TeleopControl::GetInstance())
{

}

void ShooterHoodManual::Init()
{
    m_gamepad ->SetAxisProfile( TeleopControl::FUNCTION_IDENTIFIER::SHOOTER_HOOD_MANUAL_AXIS, IDragonGamePad::AXIS_PROFILE::CUBED );
}

void ShooterHoodManual::Run()
{
    m_shooterHood ->SetOutput(m_control -> GetMode(), m_gamepad -> GetAxisValue(TeleopControl::FUNCTION_IDENTIFIER::SHOOTER_HOOD_MANUAL_AXIS) * .75);
}

bool ShooterHoodManual::AtTarget() const
{
    return true;
}