#pragma once 

#include <gamepad/DragonGamepad.h>

class ButtonBoxDisplay
{
    public:
    ButtonBoxDisplay();
    void periodic();

    private: 

    DragonGamepad* m_GamePad;

};