//====================================================================================================================================================
/// Copyright 2019 Lake Orion Robotics FIRST Team 302
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
/// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
/// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
/// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================
#pragma once

//C++ Includes
#include <memory>

//Team 302 Includes
#include <hw/interfaces/IDragonMotorController.h>
#include <subsys/IMechanism.h>
#include <controllers/ControlModes.h>
#include <controllers/ControlData.h>
#include <subsys/MechanismTypes.h>

class Crawler : public IMechanism
{
    public:

        Crawler
        (
            std::shared_ptr<IDragonMotorController>     crawlerMotor
        );

        Crawler() = delete;

        virtual ~Crawler() = default;
        ///@brief Indicates what type this mechanism is
        ///@return MechanismTypes::MECHANISM_TYPE
        MechanismTypes::MECHANISM_TYPE GetType() const override;

        ///@brief Run the mechanism as defined
        ///@param [in] ControlModes::CONTROL_TYPE controlType: How mechanism is being controlled
        ///@param [in] double value: target (units based on control type)
        ///@return void
        void SetOutput
        (
            ControlModes::CONTROL_TYPE controlType,
            double                      value
        ) override;

        ///@brief Activate the solenoid as necessary
        ///@param [in] bool activate
        ///@return false
        void ActivateSolenoid
        (
            bool activate
        ) override;

        ///@brief Checks if solenoid is activate or inactive
        ///@return bool - true = activated, false = retracted
        bool IsSolenoidActivated() override;

        ///@brief get the current position of the mechanism
        ///@return void
        double GetCurrentPosition() const override;

        ///@brief Get the current speed of the mechanism.
        ///@return void
        double GetCurrentSpeed() const override;
        
        ///@brief Set the control constants (i.e the PIDF values)
        ///@param [in] ControlData* pid: The control constants
        ///@return void
        void SetControlConstants
        (
            ControlData*    pid
        ) override;

        private:
            std::shared_ptr<IDragonMotorController>  m_crawlerMotor;
            double                                   m_target;
};
