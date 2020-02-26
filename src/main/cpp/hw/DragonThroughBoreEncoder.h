#pragma once 

#include <hw/usages/ThroughBoreEncoderUsage.h>

using namespace frc;

class DragonThroughBoreEncoder 
{
    public:
        DragonThroughBoreEncoder(
            ThroughBoreEncoderUsage::THROUGH_BORE_ENCODER_USAGE usage,
            int                                                 DIOA,
            int                                                 DIOB,
            int                                                 PWMID
        );
        DragonThroughBoreEncoder() = delete;
        virtual ~DragonDigitalInput();

        bool Get() const;

        ThroughBoreEncoderUsage::THROUGH_BORE_ENCODER_USAGE GetType() const;
    private:
        ThroughBoreEncoder*         m_encoder;
        ThroughBoreEncoderUsage::THROUGH_BORE_ENCODER_USAGE m_type;
};