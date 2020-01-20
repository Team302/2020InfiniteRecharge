
//====================================================================================================================================================
// Copyright 2010 Lake Orion Robotics FIRST Team 302
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
#include <map>
#include <memory>

// FRC includes

// Team 302 includes
#include <hw/usages/ServoUsage.h>
#include <hw/DragonServo.h>

// Third Party Includes




//========================================================================================================
/// @class DragonServoFactory
/// @brief Create DragonServos and allow external clients to retrieve created DragonServos
//========================================================================================================
class DragonServoFactory
{
    public:

        //=======================================================================================
        /// Method: GetInstance
        /// @brief  Get the factory singleton
        /// @return DragonServoFactory*    pointer to the factory
        //=======================================================================================
        static DragonServoFactory* GetInstance();

        //=======================================================================================
        /// Method: CreateDragonServo
        /// @brief  Create a DragonServo from the inputs
        /// @param [in] DragonServo::SERVO_USAGE   deviceUsage  Usage of the servo
        /// @param [in] int                        deviceID     PWM ID of the  servo
        /// @param [in] double                     minAngle     Minimum Angle for the servo
        /// @param [in] double                     maxAngle     Maximum Angle for the servo
        /// @return std::shared_ptr<DragonServo>    - could be nullptr if invalid inputs are supplied
        //=======================================================================================
        std::shared_ptr<DragonServo> CreateDragonServo
        (
            ServoUsage::SERVO_USAGE     deviceUsage,        
            int                         deviceID,           
            double                      minAngle,           
            double                      maxAngle            
        );

        //=======================================================================================
        /// Method: GetDragonServo
        /// @brief  Get a DragonServo from its usage
        /// @param [in] DragonServo::SERVO_USAGE   deviceUsage  Usage of the servo
        /// @return std::shared_ptr<DragonServo>    - could be nullptr if invalid inputs are supplied
        //=======================================================================================
        std::shared_ptr<DragonServo> CreateDragonServo
        (
            ServoUsage::SERVO_USAGE    deviceUsage        
        );



    private:
        DragonServoFactory() = default;
        ~DragonServoFactory() = default;

        static DragonServoFactory*        m_instance;

        std::map <ServoUsage::SERVO_USAGE, std::shared_ptr<DragonServo>> m_servos;

};
