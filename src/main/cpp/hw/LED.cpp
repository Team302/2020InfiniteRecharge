#include <hw/LED.h>

#include <hw/factories/CanifierFactory.h>

using namespace ctre::phoenix;

//#include <ctre/phoenix/>

LED::LED(int CANId)
{
    m_CAN = CanifierFactory::GetInstance()->GetCanifier(CANId);
    m_ledEnabled = true;
}

void LED::SetColor(Colors color)
{
    double r = 0;
    double g = 0;
    double b = 0;

    switch (color)
    {
    case RED:
        r = 255;
        g = 0;
        b = 0;
        break;

    case YELLOW:
        r = 255;
        g = 255;
        b = 0;
        break;

    case PURPLE:
        r = 255;
        g = 100;
        b = 10;
        break;

    case GREEN:
        r = 0;
        g = 255;
        b = 0;
        break;

    case BLUE:
        r = 0;
        g = 0;
        b = 255;
        break;

    case MAGENTA:
        r = 255;
        g = 0;
        b = 255;
        break;

    default:

        break;
    }
    if (m_ledEnabled)
    {
        m_CAN->SetLEDOutput(r, m_CAN->LEDChannelB);
        m_CAN->SetLEDOutput(g, m_CAN->LEDChannelA);
        m_CAN->SetLEDOutput(b, m_CAN->LEDChannelC);
    }
}

void LED::SetRGB(double r, double g, double b)
{
    if (m_ledEnabled)
    {
        m_CAN->SetLEDOutput(r * 255, m_CAN->LEDChannelB);
        m_CAN->SetLEDOutput(g * 255, m_CAN->LEDChannelA);
        m_CAN->SetLEDOutput(b * 255, m_CAN->LEDChannelC);
    }
}

void LED::EnableLED()
{
    m_ledEnabled = true;
}

void LED::DisableLED()
{
    m_ledEnabled = false;
    m_CAN->SetLEDOutput(0, m_CAN->LEDChannelB);
    m_CAN->SetLEDOutput(0, m_CAN->LEDChannelA);
    m_CAN->SetLEDOutput(0, m_CAN->LEDChannelC);
}