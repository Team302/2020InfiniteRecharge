/*
 * DragonPigeon.h
 *
 *  Created on: Feb 3, 2018
 *      Author: team302
 */

#pragma once

#include <memory>
#include <ctre/phoenix/Sensors/PigeonIMU.h>


class DragonPigeon
{
    public:
        DragonPigeon
        (
            int  canID
        );
        DragonPigeon() = delete;
        virtual ~DragonPigeon() = default;

        double GetPitch();
        double GetRoll();
        double GetYaw();

    private:

        std::unique_ptr<ctre::phoenix::sensors::PigeonIMU> m_pigeon;

        double m_initialRoll;
        double m_initialPitch;
        double m_initialYaw;

        // these methods correct orientation, but do not apply the initial offsets
        double GetRawRoll();
        double GetRawPitch();
        double GetRawYaw();
};



