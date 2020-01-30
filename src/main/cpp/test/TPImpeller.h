#pragma once
#include <subsys/Impeller.h>
#include <controllers/impeller/ImpellerStateMgr.h>
#include <frc/Timer.h>

class TPImpeller 
{
    public:
    TPImpeller();
    void periodic();
    

    private:
    Timer* m_timer;
    ImpellerStateMgr* m_impellerStateMgr;



};