/*
 * DragonSolenoid.cpp
 */

#include <memory>
#include <frc/Solenoid.h>
#include <hw/DragonSolenoid.h>
#include <hw/usages/SolenoidUsage.h>
#include <utils/Logger.h>

using namespace frc;
using namespace std;

DragonSolenoid::DragonSolenoid
(
    SolenoidUsage::SOLENOID_USAGE usage,
    int  pcmID,
	int  channel,
    bool reversed
) : m_type( usage ),
    m_solenoid( make_shared<Solenoid>( pcmID, channel ) ),
    m_reversed( reversed )

{
}


void DragonSolenoid::Set
(
    bool on
)
{
    if ( m_solenoid.get() != nullptr )
    {
        bool val = ( m_reversed ) ? !on : on;
        m_solenoid.get()->Set( val );
    }
    else
    {
        Logger::GetLogger()->LogError( string("DragonSolenoid::Set"), string("solenoid ptr is nullptr"));
    }
}
bool DragonSolenoid::Get() const
{
    bool val = false;
    if ( m_solenoid != nullptr )
    {
        val = ( m_reversed ) ? !m_solenoid->Get() : m_solenoid->Get();
    }
    else
    {
        Logger::GetLogger()->LogError( string("DragonSolenoid::Get"), string("solenoid ptr is nullptr"));
    }
    return val;
}
bool DragonSolenoid::IsBlackListed() const
{
    bool val = false;
    if ( m_solenoid != nullptr )
    {
        val = m_solenoid->IsBlackListed();
    }
    else
    {
        Logger::GetLogger()->LogError( string("DragonSolenoid::IsBlackListed"), string("solenoid ptr is nullptr"));
    }
    return val;
}
void DragonSolenoid::SetPulseDuration
(
    double durationSeconds
)
{
    if ( m_solenoid != nullptr )
    {
        m_solenoid->SetPulseDuration( durationSeconds );
    }
    else
    {
        Logger::GetLogger()->LogError( string("DragonSolenoid::SetPulseDuration"), string("solenoid ptr is nullptr"));
    }
}
void DragonSolenoid::StartPulse()
{
    if ( m_solenoid != nullptr )
    {
        m_solenoid->StartPulse();
    }
    else
    {
        Logger::GetLogger()->LogError( string("DragonSolenoid::StartPulse"), string("solenoid ptr is nullptr"));
    }
}

SolenoidUsage::SOLENOID_USAGE DragonSolenoid::GetType() const
{
    return m_type;
}

