
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

// Team 302 includes

// Third Party Includes
#include <memory>
#include <map>

#include <gamepad/IDragonGamePad.h>
#include <gamepad/DragonXbox.h>
#include <gamepad/DragonGamePad.h>
#include <frc/driverstation.h>

using namespace frc;

class TeleopControl
{
    public:

        enum FUNCTION_IDENTIFIER
        {
            UNKNOW_FUNCTION,
            TANK_DRIVE_LEFT_CONTROL,
            TANK_DRIVE_RIGHT_CONTROL,
            ARCADE_DRIVE_THROTTLE,
            ARCADE_DRIVE_STEER,
            GTA_DRIVE_FORWARD,
            GTA_DRIVE_BACKWARD,
            GTA_DRIVE_STEER,
            SWITCH_DRIVE_MODE,
            MAX_FUNCTIONS
        };


        //----------------------------------------------------------------------------------
        // Method:      GetInstance
        // Description: If there isn't an instance of this class, it will create one.  The
        //              single class instance will be returned.
        // Returns:     OperatorInterface*  instance of this class
        //----------------------------------------------------------------------------------
        static TeleopControl* GetInstance();


        //------------------------------------------------------------------
        // Method:      SetScaleFactor
        // Description: Allow the range of values to be set smaller than
        //              -1.0 to 1.0.  By providing a scale factor between 0.0
        //              and 1.0, the range can be made smaller.  If a value
        //              outside the range is provided, then the value will
        //              be set to the closest bounding value (e.g. 1.5 will
        //              become 1.0)
        // Returns:     void
        //------------------------------------------------------------------
        void SetAxisScaleFactor
        (
            TeleopControl::FUNCTION_IDENTIFIER  axis,          // <I> - axis number to update
            float                               scaleFactor    // <I> - scale factor used to limit the range
        );

        //------------------------------------------------------------------
        // Method:      SetAxisProfile
        // Description: Sets the axis profile for the specifed axis
        // Returns:     void
        //------------------------------------------------------------------
        void SetAxisProfile
        (
            TeleopControl::FUNCTION_IDENTIFIER      axis,       // <I> - axis number to update
			IDragonGamePad::AXIS_PROFILE			profile     // <I> - profile to use
        );

        //------------------------------------------------------------------
        // Method:      GetAxisValue
        // Description: Reads the joystick axis, removes any deadband (small
        //              value) and then scales as requested.
        // Returns:     float   -  scaled axis value
        //------------------------------------------------------------------
        float GetAxisValue
        (
            TeleopControl::FUNCTION_IDENTIFIER     axis // <I> - axis number to update
        ) const;

        //------------------------------------------------------------------
        // Method:      GetRawButton
        // Description: Reads the button value.  Also allows POV, bumpers,
        //              and triggers to be treated as buttons.
        // Returns:     bool   -  scaled axis value
        //------------------------------------------------------------------
        bool IsButtonPressed
        (
            TeleopControl::FUNCTION_IDENTIFIER button   // <I> - button number to query
        ) const;


    private:
        //----------------------------------------------------------------------------------
        // Method:      OperatorInterface <<constructor>>
        // Description: This will construct and initialize the object
        //----------------------------------------------------------------------------------
        TeleopControl();

        //----------------------------------------------------------------------------------
        // Method:      ~OperatorInterface <<destructor>>
        // Description: This will clean up the object
        //----------------------------------------------------------------------------------
        virtual ~TeleopControl() = default;

        //----------------------------------------------------------------------------------
        // Attributes
        //----------------------------------------------------------------------------------
        static TeleopControl*               m_instance; // Singleton instance of this class
        const int                           m_maxFunctions = 35;

        std::map<FUNCTION_IDENTIFIER, IDragonGamePad::AXIS_IDENTIFIER> m_axisMap;
        std::map<FUNCTION_IDENTIFIER, IDragonGamePad::BUTTON_IDENTIFIER> m_buttonMap;
        std::map<FUNCTION_IDENTIFIER, int> m_controllerMap;

        IDragonGamePad::AXIS_IDENTIFIER     m_axisIDs[35];
        IDragonGamePad::BUTTON_IDENTIFIER   m_buttonIDs[35];
        int							        m_controllerIndex[35];
        IDragonGamePad*			            m_controllers[DriverStation::kJoystickPorts];

        mutable int                         m_count;
};

