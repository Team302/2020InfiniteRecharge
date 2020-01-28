#include <test/TPImpeller.h>
#include <controllers/impeller/ImpellerStateMgr.h>
#include <controllers/impeller/ImpellerOn.h>
#include <controllers/impeller/ImpellerOff.h>
#include <controllers/impeller/ImpellerAgitate.h>
using namespace frc;

TPImpeller::TPImpeller()
{
    m_timer = new Timer;

}

void TPImpeller::periodic()
{
    auto time = m_timer -> Get();
    if (time < 15)
    {
        SetCurrentState(ImpellerStateMgr::IMPELLER_STATE::ON, true);
    }
    else if (time < 30)
    {
        SetCurrentState(ImpellerStateMgr::IMPELLER_STATE::OFF, true);
    }
    else if (time < 45)
    {
        SetCurrentState(ImpellerStateMgr::IMPELLER_STATE::AGITATE, true);
    }
    else
    {
        SetCurrentState(ImpellerStateMgr::IMPELLER_STATE::OFF, true);
    }
    
}