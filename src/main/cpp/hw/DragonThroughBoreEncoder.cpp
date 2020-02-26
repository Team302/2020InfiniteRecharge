#include <iostream>
#include <hw/DragonThroughBoreEncoder.h>
#include <hw/usages/ThroughBoreEncoderUsage.h>
#include <utils/Logger.h>

using namespace frc;
DragonThroughBoreEncoder::DragonThroughBoreEncoder(
    ThroughBoreEncoder::THROUGH_BORE_ENCODER_USAGE usage,
    int                                            DIOA,
    int                                            DIOB,
    int                                            PWMID
) : m_encoder(new ThroughBoreEncoder(PWMID)),
    m_dioa( DIOA ),
    m_diob( DIOB ),
    m_type( usage )
{
}

DragonThroughBoreEncoder::~DragonThroughBoreEncoder()\
{
    delete m_encoder;
}
ThroughBoreEncoderUsage::THROUGH_BORE_ENCODER_USAGE::GetType() const
{
    return m_type;
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