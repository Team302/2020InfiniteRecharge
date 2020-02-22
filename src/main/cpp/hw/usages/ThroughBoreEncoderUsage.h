#pragma once
#include <map>
#include <memory>
#include <string>

class ThroughBoreEncoderUsage
{
    public:

        enum THROUGH_BORE_ENCODER_USAGE
        {
            UNKNOWN_THROUGH_BORE_ENCODER_USAGE = -1,
            SHOOTER_HOOD,
            IMPELLER
        };
        
        static ThroughBoreEncoderUsage* GetInstance();

        THROUGH_BORE_ENCODER_USAGE GetUsage(
            const std::string       usageString
        );

    private:
        static ThroughBoreEncoderUsage*     m_instance;
        ThroughBoreEncoderUsage();
        ~ThroughBoreEncoderUsage();
        
        std::map <std::string, THROUGH_BORE_ENCODER_USAGE> m_usageMap; //lookup type of thing.
};  