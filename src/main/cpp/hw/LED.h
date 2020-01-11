#pragma once

#include <memory>
#include <ctre/phoenix/CANifier.h>


class LED
{
    public:

    enum Colors
    { 
        RED,
        PURPLE,
        YELLOW,
        GREEN,
        BLUE,
        MAGENTA
        

    };

    LED(int CANId);
    LED() = delete;
   void SetColor( Colors color );
   void SetRGB(double r, double g, double b); //0 - black, 1 - full brightness
   void EnableLED();
   void DisableLED();

   private:
    std::shared_ptr<ctre::phoenix::CANifier> m_CAN;
    bool m_ledEnabled;
};