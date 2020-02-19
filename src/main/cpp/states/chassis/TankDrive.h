
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

// Standard C++ includes
#include <memory>

// FRC includes

// Team 302 include
#include <subsys/IChassis.h>
#include <gamepad/TeleopControl.h>
#include <states/IState.h>


// Third Party includes 

/// @class TankDrive
/// @brief Drive differential chassis with one joystick controlling each side of the robot
class TankDrive : public IState
{
    public:
    
        /// @brief initialize the object
        TankDrive();

        /// @brief clean up memory
        ~TankDrive() = default;

        void Init() override;

        /// @brief  Read two joysticks and drive a differential chassis (each joystick drives a separate side)
        /// @return void
        void Run() override;
        bool AtTarget() const override;

    private:
        std::shared_ptr<IChassis> m_chassis;
        TeleopControl* m_controller;
               
};
