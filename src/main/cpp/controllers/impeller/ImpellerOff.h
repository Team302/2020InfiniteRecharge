///Created by the one, the only, Big Chief, AJ Gdowski
///Nobody will ever be brave enough to steal my code, so don't even think about it
#include <subsys/IMechanism.h>
#include <controllers/MechanismState.h>
#include <controllers/IState.h>

class ImpellerOff : public MechanismState
{
    public:

        ImpellerOff
        (
            ControlData*    control,
            double          target
        );
        ImpellerOff() = delete;
        ~ImpellerOff() = default;
};