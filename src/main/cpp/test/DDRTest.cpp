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
    
}