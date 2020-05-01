#include <test/ButtonBoxDisplay.h> 
#include <gamepad/DragonGamepad.h>
#include <frc/smartdashboard/SmartDashboard.h>
//#include <frc/GenericHID.h>
//#include <utils/Logger.h>
//#include <string>
#include <gamepad/IDragonGamePad.h>
//using namespace std;
ButtonBoxDisplay::ButtonBoxDisplay()
{
    m_GamePad = new DragonGamepad(0);


}

void ButtonBoxDisplay::periodic()
{
    bool ButtonOne = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_1);
    bool ButtonTwo = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_2);
    bool ButtonThree = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_3);
    bool ButtonFour = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_4);
    bool ButtonFive = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_5);
    bool ButtonSix = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_6);
    bool ButtonSeven = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_7);
    bool ButtonEight = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_8);
    bool ButtonNine = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_9);
    bool ButtonTen = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_10);
    bool ButtonEleven = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_11);
    bool ButtonTwelve = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_12);
    //bool ButtonThirteen = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_13);

    bool ButtonFourteenUp = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_14_UP);
    bool ButtonFourteenDown = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_14_DOWN);
    bool ButtonFifteenUp = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_15_UP);
    bool ButtonFifteenDown = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BUTTON_15_DOWN);

    double AxisSixteen = m_GamePad -> GetAxisValue( IDragonGamePad::AXIS_IDENTIFIER::GAMEPAD_AXIS_16);
    double AxisSeventeen = m_GamePad -> GetAxisValue( IDragonGamePad::AXIS_IDENTIFIER::GAMEPAD_AXIS_17);

    bool SwitchEighteen = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_SWITCH_18);
    bool SwitchNineteen = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_SWITCH_19); 
    bool SwitchTwenty = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_SWITCH_20);
    bool SwitchTwentyOne = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_SWITCH_21);

    bool DialTwentyTwo = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_DIAL_22);
    bool DialTwentyThree = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_DIAL_23);
    bool DialTwentyFour = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_DIAL_24);
    bool DialTwentyFive = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_DIAL_25);
    bool DialTwentySix = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_DIAL_26);
    bool DialTwentySeven = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_DIAL_27);
    
    double AxisOne = m_GamePad -> GetAxisValue( IDragonGamePad::AXIS_IDENTIFIER::LEFT_ANALOG_BUTTON_AXIS);
    double AxisTwo = m_GamePad -> GetAxisValue( IDragonGamePad::AXIS_IDENTIFIER::RIGHT_ANALOG_BUTTON_AXIS);
    double AxisThree = m_GamePad -> GetAxisValue( IDragonGamePad::AXIS_IDENTIFIER::DIAL_ANALOG_BUTTON_AXIS);
   // double AxisDummy1 = m_GamePad -> GetAxisValue( IDragonGamePad::AXIS_IDENTIFIER::DUMMY1);
   // double AxisDummy2 = m_GamePad -> GetAxisValue( IDragonGamePad::AXIS_IDENTIFIER::DUMMY2);
   // double AxisDummy3 = m_GamePad -> GetAxisValue( IDragonGamePad::AXIS_IDENTIFIER::DUMMY3);

//    bool RedButton = m_GamePad -> IsButtonPressed( IDragonGamePad::BUTTON_IDENTIFIER::GAMEPAD_BIG_RED_BUTTON);*/


    frc::SmartDashboard::PutBoolean("Button 1",ButtonOne);
    frc::SmartDashboard::PutBoolean("Button 2",ButtonTwo);
    frc::SmartDashboard::PutBoolean("Button 3",ButtonThree);
    frc::SmartDashboard::PutBoolean("Button 4",ButtonFour);
    frc::SmartDashboard::PutBoolean("Button 5",ButtonFive);
    frc::SmartDashboard::PutBoolean("Button 6",ButtonSix);
    frc::SmartDashboard::PutBoolean("Button 7",ButtonSeven);
    frc::SmartDashboard::PutBoolean("Button 8",ButtonEight);
    frc::SmartDashboard::PutBoolean("Button 9",ButtonNine);
    frc::SmartDashboard::PutBoolean("Button 10",ButtonTen);
    frc::SmartDashboard::PutBoolean("Button 11",ButtonEleven);
    frc::SmartDashboard::PutBoolean("Button 12",ButtonTwelve);
//    frc::SmartDashboard::PutBoolean("Button 13",ButtonThirteen);
    
    
    frc::SmartDashboard::PutBoolean("Switch 14 Up",ButtonFourteenUp);
    frc::SmartDashboard::PutBoolean("Switch 14 Down",ButtonFourteenDown);
    frc::SmartDashboard::PutBoolean("Switch 15 Up",ButtonFifteenUp);
    frc::SmartDashboard::PutBoolean("Switch 15 Down",ButtonFifteenDown);
    
    frc::SmartDashboard::PutNumber("Axis 16",AxisSixteen);
    frc::SmartDashboard::PutNumber("Axis 17",AxisSeventeen);

    frc::SmartDashboard::PutNumber("Axis Left Buttons",AxisOne);
    frc::SmartDashboard::PutNumber("Axis Right Buttons",AxisTwo);
    frc::SmartDashboard::PutNumber("Axis Dial Buttons",AxisThree);
    /**
    frc::SmartDashboard::PutNumber("Axis dummy1",AxisDummy1);
    frc::SmartDashboard::PutNumber("Axis dummy2",AxisDummy2);
    frc::SmartDashboard::PutNumber("Axis dummy3",AxisDummy3);
    **/
    

    frc::SmartDashboard::PutBoolean("Switch 18",SwitchEighteen);
    frc::SmartDashboard::PutBoolean("Switch 19",SwitchNineteen);
    frc::SmartDashboard::PutBoolean("Switch 20",SwitchTwenty);
    frc::SmartDashboard::PutBoolean("Switch 21",SwitchTwentyOne);
    
    frc::SmartDashboard::PutBoolean("Dial 22",DialTwentyTwo);
    frc::SmartDashboard::PutBoolean("Dial 23",DialTwentyThree);
    frc::SmartDashboard::PutBoolean("Dial 24",DialTwentyFour);
    frc::SmartDashboard::PutBoolean("Dial 25",DialTwentyFive);
    frc::SmartDashboard::PutBoolean("Dial 26",DialTwentySix);
    frc::SmartDashboard::PutBoolean("Dial 27",DialTwentySeven);
    /*
    frc::SmartDashboard::PutBoolean("Big Red Button", RedButton);
    */
}