///Created by the one, the only, Big Chief, AJ Gdowski
///Nobody will ever be brave enough to steal my code, so don't even think about it
#include <subsys/IMechanism.h>
#include <controllers/MechanismState.h>
#include <controllers/IState.h>

class ShooterHoodHoldPosition : public MechanismState
{
    public:

        ShooterHoodHoldPosition() = delete;
        ShooterHoodHoldPosition
        (
            ControlData*    control,
            double          target
        );
        ~ShooterHoodHoldPosition() =default;
};