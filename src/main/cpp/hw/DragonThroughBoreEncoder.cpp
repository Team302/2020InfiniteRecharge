#include <iostream>
#include <hw/DragonThroughBoreEncoder.h>
#include <hw/usages/ThroughBoreEncoderUsage.h>
#include <utils/Logger.h>
#include <frc/Encoder.h>

using namespace frc;
DragonThroughBoreEncoder::DragonThroughBoreEncoder(
    ThroughBoreEncoder::THROUGH_BORE_ENCODER_USAGE usage,
    int                                            DIOA,
    int                                            DIOB,
    int                                            PWMID
) : m_encoder(new Encoder( DIOA, DIOB )),
    m_pwmid( PWMID ),
    m_type( usage )
{
}

DragonThroughBoreEncoder::~DragonThroughBoreEncoder()
{
    delete m_encoder;
}
ThroughBoreEncoderUsage::THROUGH_BORE_ENCODER_USAGE::GetType() const
{
    return m_type;
}
int DragonThroughBoreEncoder::GetChannel() const
{
    in channel = 0;
    if (m_encoder != nullptr )
    {
        channel = m_encoder->GetChannel();
    }
    else
    {
        Logger::GetLogger()->LogError( string("DragonSolenoid::GetChannel"), string(" m_encoder ptr is nullptr"));
    }
    
}
bool DragonThroughBoreEncoder::Get() const
{
    double value = 0.0;
    if  ( m_encoder != nullptr)
    {
        value = m_encoder->Get();
    }
    else 
    {
        Logger::GetLogger()->LogError( string("DragonThroughBoreEncoder::Get"), string("m_encoder ptr is nullptr"));
    }
}