#pragma once 

#include <hw/usages/ThroughBoreEncoderUsage.h>
#include <frc/Encoder.h>

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
        virtual ~DragonThroughBoreEncoder();

        bool Get() const;

        ThroughBoreEncoderUsage::THROUGH_BORE_ENCODER_USAGE GetType() const;
    private:
        Encoder*         m_encoder; // can also try std::shared_ptr<frc::Encoder> at #include <frc/Encoder.h>
        int              m_pwmid;
        ThroughBoreEncoderUsage::THROUGH_BORE_ENCODER_USAGE m_type;
};