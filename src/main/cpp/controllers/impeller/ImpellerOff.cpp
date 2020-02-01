///Created by the one, the only, Big Chief, AJ Gdowski
///Nobody will ever be brave enough to steal my code, so don't even think about it
//C++ Includes
#include <memory>

//Team 302 Includes
#include <controllers/impeller/ImpellerOff.h>
#include <controllers/IState.h>
#include <subsys/IMechanism.h>
#include <subsys/MechanismFactory.h>

using namespace std;



ImpellerOff::ImpellerOff
(
    ControlData* control,
    double target
) : MechanismState( MechanismFactory::GetMechanismFactory()->GetIMechanism(MechanismTypes::MECHANISM_TYPE::IMPELLER), control, target)
{

}
