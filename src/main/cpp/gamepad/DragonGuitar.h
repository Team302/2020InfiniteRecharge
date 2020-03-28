#pragma once

#include <frc/GenericHID.h>
#include <frc/Joystick.h>

#include <gamepad/IDragonGamePad.h>
#include <gamepad/axis/AnalogAxis.h>
#include <gamepad/button/AnalogButton.h>
#include <gamepad/button/IButton.h>

using namespace frc;
using namespace std;

class DragonGuitar : public IDragonGamePad
{
    public:
        DragonGuitar
        (
            int port
        );
        ~DragonGuitar();

        bool IsButtonPressed
        (
            BUTTON_IDENTIFIER button
        ) const override;

        void SetAxisDeadband
        (
            AXIS_IDENTIFIER axis,
            AXIS_DEADBAND type
        ) override;

        void SetAxisProfile
        (
            AXIS_IDENTIFIER axis,
            AXIS_PROFILE
        ) override;

        void SetAxisScale
        (
            AXIS_IDENTIFIER axis,
            float scaleFactor
        ) override;

        void SetButtonMode
        (
            BUTTON_IDENTIFIER button,
            BUTTON_MODE mode
        ) override;

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

        private:
            Joystick* m_gamepad;

            vector <AnalogAxis*> m_axis;
            vector <float> m_axisScale;
            vector <float> m_axisInversionFactor;
            vector <AXIS_PROFILE> m_axisProfile;
            vector <IButton*> m_button;

            const int GREEN_BUTTON_DIGITAL_ID = 0;
            const int RED_BUTTON_DIGITAL_ID = 1;
            const int YELLOW_BUTTON_DIGITAL_ID = 2;
            const int BLUE_BUTTON_DIGITAL_ID = 3;
            const int ORANGE_BUTTON_DIGITAL_ID = 4;
            
            const int STRUM_DOWN_DIGITAL_ID = 5;
            const int STRUM_UP_DIGITAL_ID = 6;
        DragonGuitar() = delete;
};