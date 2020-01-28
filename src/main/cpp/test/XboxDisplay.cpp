#include <test/XboxDisplay.h>
#include <gamepad/DragonXBox.h> 
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/GenericHID.h>
#include <utils/Logger.h>
#include <string>
using namespace std;

XboxDisplay::XboxDisplay()
{
    m_controller = new DragonXBox(0);
}

void XboxDisplay::periodic()
{
   bool AButton = m_controller -> IsButtonPressed(IDragonGamePad::BUTTON_IDENTIFIER::A_BUTTON);
   //Logger::GetLogger() -> LogError(std::string("A Button"), string(to_string(AButton)));
   frc::SmartDashboard::PutBoolean("A Button", AButton);
   bool BButton = m_controller -> IsButtonPressed(IDragonGamePad::BUTTON_IDENTIFIER::B_BUTTON);
    frc::SmartDashboard::PutBoolean("B Button", BButton);
   bool XButton = m_controller -> IsButtonPressed(IDragonGamePad::BUTTON_IDENTIFIER::X_BUTTON);
   frc::SmartDashboard::PutBoolean("X Button", XButton);
   bool YButton = m_controller -> IsButtonPressed(IDragonGamePad::BUTTON_IDENTIFIER::Y_BUTTON);
   frc::SmartDashboard::PutBoolean("Y Button", YButton);
   bool StartButton = m_controller -> IsButtonPressed(IDragonGamePad::BUTTON_IDENTIFIER::START_BUTTON);
   frc::SmartDashboard::PutBoolean("Start Button", StartButton);
   //bool SelectButton = m_controller -> IsButtonPressed(IDragonGamePad::BUTTON_IDENTIFIER::SELECT_BUTTON);
   //frc::SmartDashboard::PutBoolean("Select Button", SelectButton);
   // TODO #1 Figure out why select button crashes code
   bool LeftStickPressed = m_controller -> IsButtonPressed(IDragonGamePad::BUTTON_IDENTIFIER::LEFT_STICK_PRESSED);
   frc::SmartDashboard::PutBoolean("Left Stick Pressed", LeftStickPressed);
   bool RightStickPressed = m_controller -> IsButtonPressed(IDragonGamePad::BUTTON_IDENTIFIER::RIGHT_STICK_PRESSED);
   frc::SmartDashboard::PutBoolean("Right Stick Pressed", RightStickPressed);
   double LeftXAxis = m_controller -> GetAxisValue(IDragonGamePad::AXIS_IDENTIFIER::LEFT_JOYSTICK_X);
   frc::SmartDashboard::PutNumber("Left Stick X", LeftXAxis);
   double LeftYAxis = m_controller -> GetAxisValue(IDragonGamePad::AXIS_IDENTIFIER::LEFT_JOYSTICK_Y);
   frc::SmartDashboard::PutNumber("Left Stick Y", LeftYAxis);
   double RightXAxis = m_controller -> GetAxisValue(IDragonGamePad::AXIS_IDENTIFIER::RIGHT_JOYSTICK_X);
   frc::SmartDashboard::PutNumber("Right Stick X", RightXAxis);
   double RightYAxis = m_controller -> GetAxisValue(IDragonGamePad::AXIS_IDENTIFIER::RIGHT_JOYSTICK_Y);
   frc::SmartDashboard::PutNumber("Right Stick Y", RightYAxis);
   double LeftTrigger = m_controller -> GetAxisValue(IDragonGamePad::AXIS_IDENTIFIER::LEFT_TRIGGER);
   frc::SmartDashboard::PutNumber("Left Trigger", LeftTrigger);
   double RightTrigger = m_controller -> GetAxisValue(IDragonGamePad::AXIS_IDENTIFIER::RIGHT_TRIGGER);
   frc::SmartDashboard::PutNumber("Right Trigger", RightTrigger);
   bool LeftBumper = m_controller -> IsButtonPressed(IDragonGamePad::BUTTON_IDENTIFIER::LEFT_BUMPER);
   frc::SmartDashboard::PutBoolean("Left Bumper", LeftBumper);
   bool RightBumper = m_controller -> IsButtonPressed(IDragonGamePad::BUTTON_IDENTIFIER::RIGHT_BUMPER);
   frc::SmartDashboard::PutBoolean("Right Bumper", RightBumper);
}