/*
 * DragonSolenoid.h
 */

#pragma once

#include <memory>
#include <frc/Solenoid.h>
#include <hw/usages/SolenoidUsage.h>


class DragonSolenoid
{
    public:
        DragonSolenoid() = delete;
        DragonSolenoid
        (
            SolenoidUsage::SOLENOID_USAGE usage,
            int  pcmID,
			int  channel,
            bool reversed
        );
        virtual ~DragonSolenoid() = default;

        void Set
        (
            bool on
        );
        bool Get() const;
        bool IsBlackListed() const;
        void SetPulseDuration
        (
            double durationSeconds
        );
        void StartPulse();

        SolenoidUsage::SOLENOID_USAGE GetType() const;


    private:
        SolenoidUsage::SOLENOID_USAGE           m_type;
        std::shared_ptr<frc::Solenoid>          m_solenoid;
        bool                                    m_reversed;
};
