#pragma once
#include <subsys/Impeller.h>
#include <controllers/impeller/ImpellerAgitate.h>
#include <controllers/impeller/ImpellerOff.h>
#include <controllers/impeller/ImpellerOn.h>
#include <controllers/impeller/ImpellerStateMgr.h>
#include <frc/Timer.h>

class TPImpeller : ImpellerStateMgr
{
    public:
    TPImpeller();
    void periodic();
    

    private:
    Timer* m_timer;



};