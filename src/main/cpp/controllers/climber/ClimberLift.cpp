#include <controllers/climber/ClimberLift.h>
#include <controllers/ControlData.h>
#include <controllers/MechanismState.h>
#include <subsys/IMechanism.h>
#include <subsys/MechanismFactory.h>

ClimberLift::ClimberLift
(
    ControlData* control,
    double target
) : MechanismState(MechanismFactory::GetMechanismFactory() -> GetIMechanism(MechanismTypes::MECHANISM_TYPE::CLIMBER), control, target)
{
}
