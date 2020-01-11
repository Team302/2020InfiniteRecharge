/*
 * DragonSolenoid.h
 */

#ifndef SRC_SUBSYS_COMPONENTS_DRAGONSOLENOID_H_
#define SRC_SUBSYS_COMPONENTS_DRAGONSOLENOID_H_

#include <vector>
#include <frc/Solenoid.h>

using namespace frc;

class DragonSolenoid
{
    public:
        enum DRAGON_SOLENOID_USAGE
        {
            CONTROL_4BAR,
            GRABBER_CLUTCH,
            GRABBER_POSITION,
            SIDEHANGER_LATCH,
            SIDEHANGER_LATCH2
        };
        DragonSolenoid() = delete;
        DragonSolenoid
        (
            DRAGON_SOLENOID_USAGE usage,
            int  pcmID,
			int  channel,
            bool reversed
        );
        virtual ~DragonSolenoid();

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

        DRAGON_SOLENOID_USAGE GetType() const;


    private:
        DRAGON_SOLENOID_USAGE                   m_type;
        Solenoid*                               m_solenoid;
        bool                                    m_reversed;
};
typedef std::vector<DragonSolenoid*> DragonSolenoidVector;

#endif /* SRC_SUBSYS_COMPONENTS_DRAGONSOLENOID_H_ */
