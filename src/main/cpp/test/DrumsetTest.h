#pragma once

#include <gamepad/DragonDrumset.h>


class DrumsetTest
{
    public:
    DrumsetTest();
    void periodic();

    private:
    DragonDrumset* m_drumset;

};