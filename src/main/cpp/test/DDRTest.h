#pragma once

#include <gamepad/DragonDDR.h>


class DDRTest
{
    public:
    DDRTest();
    void periodic();

    private:
    DragonDDR* m_DDR;
};