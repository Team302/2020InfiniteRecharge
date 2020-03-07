#include <iostream>
#include <utils/Logger.h>

#include <frc/Encoder.h>

#include <hw/DragonThroughBoreEncoder.h>
#include <hw/usages/ThroughBoreEncoderUsage.h>

using namespace frc;
using namespace std;
DragonThroughBoreEncoder::DragonThroughBoreEncoder
(
    ThroughBoreEncoderUsage::THROUGH_BORE_ENCODER_USAGE usage,
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
ThroughBoreEncoderUsage::THROUGH_BORE_ENCODER_USAGE DragonThroughBoreEncoder::GetType() const
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