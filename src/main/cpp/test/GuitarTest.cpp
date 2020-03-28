#include <test/GuitarTest.h>
#include <gamepad/DragonGuitar.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/GenericHID.h>
#include <utils/Logger.h>
#include <string>

using namespace std;
using namespace frc;

GuitarTest::GuitarTest()
{
    m_guitar = new DragonGuitar(0);
}

void GuitarTest::periodic()
{
    bool green = m_guitar -> IsButtonPressed(IDragonGamePad::BUTTON_IDENTIFIER::GUITAR_GREEN);
    frc::SmartDashboard::PutBoolean("Green Button", green);

    bool red = m_guitar -> IsButtonPressed(IDragonGamePad::BUTTON_IDENTIFIER::GUITAR_RED);
    frc::SmartDashboard::PutBoolean("Red Button", red);

    bool yellow = m_guitar -> IsButtonPressed(IDragonGamePad::BUTTON_IDENTIFIER::GUITAR_YELLOW);
    frc::SmartDashboard::PutBoolean("Yellow Button", yellow);

    bool blue = m_guitar -> IsButtonPressed(IDragonGamePad::BUTTON_IDENTIFIER::GUITAR_BLUE);
    frc::SmartDashboard::PutBoolean("Blue Button", blue);

    bool orange = m_guitar -> IsButtonPressed(IDragonGamePad::BUTTON_IDENTIFIER::GUITAR_ORANGE);
    frc::SmartDashboard::PutBoolean("Orange Button", orange);

    bool up = m_guitar -> IsButtonPressed(IDragonGamePad::BUTTON_IDENTIFIER::GUITAR_STRUM_UP);
    frc::SmartDashboard::PutBoolean("Strum Up", up);

    bool down = m_guitar -> IsButtonPressed(IDragonGamePad::BUTTON_IDENTIFIER::GUITAR_STRUM_DOWN);
    frc::SmartDashboard::PutBoolean("Strum Down", down);
}