/*
LEDFactory.cpp
Christopher Castillo
3/16/2019
*/

#include <hw/factories/LEDFactory.h>
#include <hw/LED.h>

LEDFactory* LEDFactory::m_ledFactory = nullptr;

LEDFactory::LEDFactory() :
    m_ledUnderFront(nullptr),
    m_ledUnderBack(nullptr),
    m_ledTop(nullptr)
{
}

LEDFactory* LEDFactory::GetInstance
(
)
{
    if(LEDFactory::m_ledFactory == nullptr)
    {
        LEDFactory::m_ledFactory = new LEDFactory();
    }

    return LEDFactory::m_ledFactory;
}

LED* LEDFactory::GetLED
(
    LEDFactory::LED_USAGE  usage
)
{
     LED* led = nullptr;

    switch(usage)
    {
        case LEDFactory::UNDER_FRONT:
            led = m_ledUnderFront;
            break;
        case LEDFactory::UNDER_BACK:
            led = m_ledUnderBack;
            break;
        case LEDFactory::TOP:
            led = m_ledTop;
            break;
        default:
            printf("==>> Unknown LED usage %d \n", usage);
            break;
    }
    return led;
}

LED* LEDFactory::CreateLED
(
    LEDFactory::LED_USAGE       usage,
    int CANId
)
{
    LED* output = nullptr;
    switch(usage)
    {
        case LEDFactory::UNDER_FRONT:
            m_ledUnderFront = new LED(CANId);
            output = m_ledUnderFront;
            break;
        case LEDFactory::UNDER_BACK:
            m_ledUnderBack = new LED(CANId);
            output = m_ledUnderBack;
            break;
        case LEDFactory::TOP:
            m_ledTop = new LED(CANId);
            output = m_ledTop;
            break;
        default:
            printf("Unknown LED usage in CreateLED LEDFactory.cpp\n");
            break;
    }
    return output;
}