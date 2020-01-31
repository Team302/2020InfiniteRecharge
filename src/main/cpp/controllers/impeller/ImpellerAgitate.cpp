///Created by the one, the only, Big Chief, AJ Gdowski
///Nobody will ever be brave enough to steal my code, so don't even think about it
#include <controllers/impeller/ImpellerAgitate.h>
#include <controllers/ControlData.h>
#include <controllers/MechanismState.h>
#include <subsys/IMechanism.h>
#include <subsys/MechanismFactory.h>

///This is used to contruct any elements I am going to use
ImpellerAgitate::ImpellerAgitate
(
    ControlData* control,
    double target
) : MechanismState(MechanismFactory::GetMechanismFactory() -> GetIMechanism(MechanismTypes::MECHANISM_TYPE::IMPELLER), control, target)
{

}





