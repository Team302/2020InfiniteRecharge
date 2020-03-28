#include <test/DDRTest.h>
#include <gamepad/DragonDDR.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/GenericHID.h>
#include <utils/Logger.h>
#include <string>

using namespace std;
using namespace frc;

DDRTest::DDRTest()
{
    m_DDR = new DragonDDR(0);
}

void DDRTest::periodic()
{
    bool up = m_DDR -> IsButtonPressed(IDragonGamePad::BUTTON_IDENTIFIER::DDR_UP);
    frc::SmartDashboard::PutBoolean("Up Button", up);

    bool right = m_DDR -> IsButtonPressed(IDragonGamePad::BUTTON_IDENTIFIER::DDR_RIGHT);
    frc::SmartDashboard::PutBoolean("Right Button", right);

    bool down = m_DDR -> IsButtonPressed(IDragonGamePad::BUTTON_IDENTIFIER::DDR_DOWN);
    frc::SmartDashboard::PutBoolean("Down Button", down);

    bool left = m_DDR -> IsButtonPressed(IDragonGamePad::BUTTON_IDENTIFIER::DDR_LEFT);
    frc::SmartDashboard::PutBoolean("Left Button", left);
}