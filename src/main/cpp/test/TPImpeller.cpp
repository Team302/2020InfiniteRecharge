///Created by the one, the only, Big Chief, AJ Gdowski
///Nobody will ever be brave enough to steal my code, so don't even think about it
#include <test/TPImpeller.h>
#include <controllers/impeller/ImpellerStateMgr.h>
using namespace frc;

TPImpeller::TPImpeller()
{
    m_timer = new Timer;
    m_impellerStateMgr = new ImpellerStateMgr();
}

void TPImpeller::periodic()
{
    auto time = m_timer -> Get();
    if (time < 15)
    {
        m_impellerStateMgr -> SetCurrentState(ImpellerStateMgr::IMPELLER_STATE::ON, true);
    }
    else if (time < 30)
    {
        m_impellerStateMgr -> SetCurrentState(ImpellerStateMgr::IMPELLER_STATE::OFF, true);
    }
    else if (time < 45)
    {
        m_impellerStateMgr -> SetCurrentState(ImpellerStateMgr::IMPELLER_STATE::AGITATE, true);
    }
    else
    {
        m_impellerStateMgr -> SetCurrentState(ImpellerStateMgr::IMPELLER_STATE::OFF, true);
    }
    
}