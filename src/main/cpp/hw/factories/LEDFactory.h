//LEDFactory.h
//Christopher Castillo
//3/15/2019
#pragma once

#include <hw/LED.h>
#include <vector>


class LEDFactory
{
    public:

        static LEDFactory* GetInstance();

        enum LED_USAGE
        {
            UNDER_FRONT,
            UNDER_BACK,
            TOP
        };

        LED* GetLED
        (
            LEDFactory::LED_USAGE   usage
        );

        LED* CreateLED
        (
            LEDFactory::LED_USAGE       usage,
            int    CANId
        );

        private:
            LEDFactory();
            ~LEDFactory();
            LED*        m_ledUnderFront;
            LED*        m_ledUnderBack;
            LED*        m_ledTop;

            static LEDFactory* m_ledFactory;
            

    
};