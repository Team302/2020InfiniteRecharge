//========================================================================================================
/// ClimberHold.h
//========================================================================================================
///
/// File Description:
///     This controls the "hold" function of the climber
///
//========================================================================================================

#include <subsys/IMechanism.h>
#include <controllers/MechanismState.h>
#include <controllers/IState.h>

class ClimberHold : public MechanismState
{
    public:

        ClimberHold() = delete;
        ClimberHold
        (
            ControlData*    control,
            double          target
        );
        ~ClimberHold() =default;
};