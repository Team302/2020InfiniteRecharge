#pragma once

#include <gamepad/DragonXBox.h>

class XboxDisplay 
{
    public: 
    XboxDisplay();
    void periodic();



    private:

    DragonXBox* m_controller;



};

