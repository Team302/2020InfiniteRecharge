//========================================================================================================
/// ClimberHold.cpp
//========================================================================================================
///
/// File Description:
///     This controls the "hold" function of the climber
///
//========================================================================================================

//C++ Includes
#include <memory>

//Team 302 Includes
#include <controllers/climber/ClimberHold.h>
#include <controllers/IState.h>
#include <subsys/IMechanism.h>
#include <subsys/MechanismFactory.h>

using namespace std;



ClimberHold::ClimberHold
(
    ControlData* control,
    double target
) : MechanismState( MechanismFactory::GetMechanismFactory()->GetIMechanism(MechanismTypes::MECHANISM_TYPE::CLIMBER), control, target)
{

}

