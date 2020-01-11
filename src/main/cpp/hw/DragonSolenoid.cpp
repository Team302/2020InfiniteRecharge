/*
 * DragonSolenoid.cpp
 */

#include <iostream>
#include <frc/Solenoid.h>
#include <hw/DragonSolenoid.h>

using namespace frc;

DragonSolenoid::DragonSolenoid
(
    DragonSolenoid::DRAGON_SOLENOID_USAGE usage,
    int  pcmID,
	int  channel,
    bool reversed
) : m_type( usage ),
    m_solenoid( new Solenoid( pcmID, channel ) ),
    m_reversed( reversed )

{
}

DragonSolenoid::~DragonSolenoid()
{
    delete m_solenoid;
}


void DragonSolenoid::Set
(
    bool on
)
{
    if ( m_solenoid != nullptr )
    {
        bool val = ( m_reversed ) ? !on : on;
        m_solenoid->Set( val );
    }
    else
    {
//        printf( "==> solenoid not set \n" );
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
//        printf( "==> solenoid not set \n" );
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
//        printf( "==> solenoid not set \n" );
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
//        printf( "==> solenoid not set \n" );
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
 //       printf( "==> solenoid not set \n" );
    }
}

DragonSolenoid::DRAGON_SOLENOID_USAGE DragonSolenoid::GetType() const
{
    return m_type;
}

