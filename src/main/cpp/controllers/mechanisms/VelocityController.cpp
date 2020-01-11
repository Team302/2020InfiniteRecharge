
#include <controllers/mechanisms/IMechController.h>
#include <controllers/mechanisms/VelocityController.h>
#include <controllers/ControlData.h>
#include <subsys/IMechanism.h>

VelocityController::VelocityController
(
    IMechanism*         mechanism,
    ControlData*        controlData
) : IMechController(),
    m_mech( mechanism ),
    m_control( controlData )
{
}

void VelocityController::Init
(
    IMechanism*         mechanism,
    ControlData*        controlData
) 
{
    m_mech = mechanism;
    m_control = controlData;
    if ( m_mech != nullptr )
    {
        m_mech->SetControlConstants( m_control );
    }
    Run();
}

void VelocityController::Run()
{
    if ( m_mech != nullptr )
    {
        // todo need to get target MechParamData here ...  profile could be different, though
        m_mech->SetOutput( m_control->GetMode(), 1.0 );
    }
}

bool VelocityController::ReachedTarget()
{
    return false;   // todo check current value vs. target value
}

VelocityController::~VelocityController()
{
    
}
