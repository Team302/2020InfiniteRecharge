//Created by the one, the only, Big Chief, AJ Gdowski
//Nobody will ever be brave enough to steal my code, so don't even think about it

#pragma once


#include <controllers/IState.h>
#include <subsys/IMechanism.h>
#include <subsys/MechanismFactory.h>

class Agitate : public IState
{
    public:

    Agitate();
    ~Agitate() = default;

    void Init() override;
    void Run() override;
    bool AtTarget() const override;

    private:

    IMechanism* m_impeller;

    const double addition_delta = 20;
    const double subtraction_delta = 10; //Used to move the motor either forwards or backwards
    double m_target;
    bool is_moving_forward;
};