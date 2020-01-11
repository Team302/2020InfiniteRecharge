
//====================================================================================================================================================
// Copyright 2019 Lake Orion Robotics FIRST Team 302
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================


#pragma once

// C++ Includes

// FRC includes
#include <frc/GenericHID.h>
#include <frc/Joystick.h>

// Team 302 includes
#include <gamepad/IDragonGamePad.h>
#include <gamepad/axis/AnalogAxis.h>
#include <gamepad/button/AnalogButton.h>
#include <gamepad/button/IButton.h>


// Third Party Includes



class DragonGamepad : public IDragonGamePad
{
    public:
        DragonGamepad
        (
            int port
        );
        ~DragonGamepad();

        

        bool IsButtonPressed
        (
            BUTTON_IDENTIFIER button
        ) const override;

        void SetAxisDeadband
        (
            AXIS_IDENTIFIER axis,
            AXIS_DEADBAND type
        );

        void SetAxisProfile
        (
            AXIS_IDENTIFIER axis,
            AXIS_PROFILE curve
        );

        void SetAxisScale
        (
            AXIS_IDENTIFIER axis,
            float scaleFactor
        );

        void SetButtonMode
        (
            BUTTON_IDENTIFIER button,
            BUTTON_MODE mode
        );

        double GetRawAxis
        (
            AXIS_IDENTIFIER axis
        );

        bool IsRawButtonPressed
        (
            BUTTON_IDENTIFIER button
        );

        bool IsRawButtonPressed
        (
            ANALOG_BUTTON_IDENTIFIER button
        );

        double GetAxisValue
        (
            AXIS_IDENTIFIER axis
        ) const override;

        bool WasButtonPressed
        (
            BUTTON_IDENTIFIER button
        ) const override;

        bool WasButtonReleased
        (
            BUTTON_IDENTIFIER button
        ) const override;

        int GetPOVValue
        (

        );
    private:
        frc::Joystick* m_gamepad;
        
        std::vector<AnalogAxis*> m_axis;
        std::vector<float> m_axisScale;
        std::vector<float> m_axisInversionFactor;
        std::vector<AXIS_PROFILE> m_axisProfile;

        std::vector<IButton*> m_button;
        std::vector<AnalogButton*> m_analogButtons;


        int LEFT_BUTTON_AXIS_ID = 0;
        int RIGHT_BUTTON_AXIS_ID = 1;

        const double			BUTTON_1_LOWERBAND = 0.118;
        const double			BUTTON_1_UPPERBAND = 0.1182;
        const int               BUTTON_1_AXIS      = 0;

        const double			BUTTON_2_LOWERBAND = 0.10;
        const double			BUTTON_2_UPPERBAND = 0.1182;
        const int               BUTTON_2_AXIS      = 1;

        const double			BUTTON_3_LOWERBAND = 0.102;
        const double			BUTTON_3_UPPERBAND = 0.10236221;
        const int               BUTTON_3_AXIS      = 0;

        const double			BUTTON_4_LOWERBAND = 0.077;
        const double			BUTTON_4_UPPERBAND = 0.08;
        const int               BUTTON_4_AXIS      = 1;

        const double			BUTTON_5_LOWERBAND = 0.1023;
        const double			BUTTON_5_UPPERBAND = 0.1026223;
        const int               BUTTON_5_AXIS      = 1;

        const double			BUTTON_6_LOWERBAND = 0.077;
        const double			BUTTON_6_UPPERBAND = 0.079;
        const int               BUTTON_6_AXIS      = 0; 

        const double			BUTTON_7_LOWERBAND = 0.054;
        const double			BUTTON_7_UPPERBAND = 0.056;
        const int               BUTTON_7_AXIS      = 1;

        const double			BUTTON_8_LOWERBAND = 0.054;
        const double			BUTTON_8_UPPERBAND = 0.056;
        const int               BUTTON_8_AXIS      = 0;

        const double			BUTTON_9_LOWERBAND = 0.03;
        const double			BUTTON_9_UPPERBAND = 0.032;
        const int               BUTTON_9_AXIS      = 1;

        const double			BUTTON_10_LOWERBAND = 0.030;
        const double			BUTTON_10_UPPERBAND = 0.032;
        const int               BUTTON_10_AXIS      = 0;

        const double			BUTTON_11_LOWERBAND = 0.014;
        const double			BUTTON_11_UPPERBAND = 0.016;
        const int               BUTTON_11_AXIS      = 1;

        const double			BUTTON_12_LOWERBAND = 0.014;
        const double			BUTTON_12_UPPERBAND = 0.016;
        const int               BUTTON_12_AXIS      = 0;

        const double			BUTTON_13_LOWERBAND = 0.10;
        const double			BUTTON_13_UPPERBAND = 0.1182;
        const int               BUTTON_13_AXIS      = 1;

        DragonGamepad() = delete;
};

