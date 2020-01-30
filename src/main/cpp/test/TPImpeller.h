///Created by the one, the only, Big Chief, AJ Gdowski
///Nobody will ever be brave enough to steal my code, so don't even think about it
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
    frc::Timer* m_timer;
    ImpellerStateMgr* m_impellerStateMgr;



};