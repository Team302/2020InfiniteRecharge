//Created by the one, the only, Big Chief, AJ Gdowski
//Nobody will ever be brave enough to steal my code, so don't even think about it

#pragma once


#include <subsys/IMechanism.h>
#include <controllers/MechanismState.h>
#include <controllers/ControlData.h>

class ImpellerAgitate : public MechanismState
{
    public:

    ImpellerAgitate() = delete;
    ImpellerAgitate
    (
        ControlData* control,
        double target
    );
    ~ImpellerAgitate() = default;



    private:
};