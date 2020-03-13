#include <test/DrumsetTest.h>
#include <gamepad/DragonDrumset.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/GenericHID.h>
#include <utils/Logger.h>
#include <string>
using namespace std;

using namespace frc;

DrumsetTest::DrumsetTest()
{
    m_drumset = new DragonDrumset(0);
}

void DrumsetTest::periodic()
{
    bool RedPad = m_drumset -> IsButtonPressed(IDragonGamePad::BUTTON_IDENTIFIER::RED_PAD);
    frc::SmartDashboard::PutBoolean("Red Pad", RedPad);
    bool YellowPad = m_drumset -> IsButtonPressed(IDragonGamePad::BUTTON_IDENTIFIER::YELLOW_PAD);
    frc::SmartDashboard::PutBoolean("Yellow Pad", YellowPad);
    bool GreenPad = m_drumset -> IsButtonPressed(IDragonGamePad::BUTTON_IDENTIFIER::GREEN_PAD);
    frc::SmartDashboard::PutBoolean("Green Pad", GreenPad);
}