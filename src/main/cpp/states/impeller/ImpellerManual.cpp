#include <memory>

#include <states/impeller/ImpellerManual.h>
#include <states/IState.h>
#include <subsys/IMechanism.h>
#include <subsys/MechanismFactory.h>
#include <gamepad/TeleopControl.h>
#include <controllers/ControlModes.h>

using namespace std;

ImpellerManual::ImpellerManual
(
    ControlData* control,
    double target
) : IState(),
    m_impeller( MechanismFactory::GetMechanismFactory()->GetIMechanism(MechanismTypes::MECHANISM_TYPE::IMPELLER)),
    m_control( control ),
    m_target( target ),
    m_gamepad(TeleopControl::GetInstance())
{

}

void ImpellerManual::Init()
{
    m_gamepad->SetAxisProfile( TeleopControl::FUNCTION_IDENTIFIER::IMPELLER_MANUAL, IDragonGamePad::AXIS_PROFILE::CUBED);
}

void ImpellerManual::Run()
{
    m_impeller->SetOutput(m_control -> GetMode(), m_gamepad -> GetAxisValue(TeleopControl::FUNCTION_IDENTIFIER::IMPELLER_MANUAL) * .5);
}

bool ImpellerManual::AtTarget() const
{
    return true;
}