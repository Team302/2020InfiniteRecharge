#pragma once

#include <gamepad/DragonGuitar.h>


class GuitarTest
{
    public:
    GuitarTest();
    void periodic();

    private:
    DragonGuitar* m_guitar;
};