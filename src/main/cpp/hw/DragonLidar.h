
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
#include <memory>
#include <string>
#include <vector>

// FRC includes
#include <networktables/NetworkTableInstance.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableEntry.h>
#include <frc/Counter.h>
#include <frc/DigitalOutput.h>

// Team 302 includes
#include <hw/interfaces/IDragonSensor.h>
#include <hw/interfaces/IDragonDistanceSensor.h>

// Third Party Includes

//========================================================================================================
/// @class DragonLidar
/// @brief This class takes a LIDAR that is connected to a digital input on the roborio using PWM.  The
///        high pulse length is measured and converted to distance in GetDistance().  The trigger pin is
///        just used to initialize the lidar. It shouldn't have to be called periodically.
//========================================================================================================
class DragonLidar : public IDragonSensor,  public IDragonDistanceSensor
{
    public:
        //-----------------------------------------------------------------------------------
        /// Method: DragonLidar (constructor)
        /// @param  IDragonSensor::SENSOR_USAGE usage - what is the lidar being used for
        /// @param  int inputPin - PWM ID for the reading the distance
        /// @param  int triggerPin - PWM ID used to initialize the lidar
        /// @brief  Create the object
        //-----------------------------------------------------------------------------------
        DragonLidar() = delete;
        DragonLidar
        (
            IDragonSensor::SENSOR_USAGE usage,
            int                         inputPin,
            int                         triggerPin
        );

        //-----------------------------------------------------------------------------------
        /// Method:  ~DragonLidar (destructor)
        /// @brief   Delete the object
        //-----------------------------------------------------------------------------------
        virtual ~DragonLidar() = default;

        //-----------------------------------------------------------------------
        /// Method: GetDistance
        /// @brief  Return the measured distance in inches
        /// @return double     Measured Distance in inches
        //-----------------------------------------------------------------------
        double GetDistance() const override;   // IDragonDistanceSensor


        //-----------------------------------------------------------------------
        /// Method: GetConfidence
        /// @brief  Indicates how accurate the returned value is
        /// @return double    0.0 == ignore (sensor has an error), 1.0 == very confident 
        //-----------------------------------------------------------------------
        double GetConfidence() const override; // IDragonSensor

        //-----------------------------------------------------------------------
        /// Method: GetUsage
        /// @brief  Indicate what the sensor is used for
        /// @return SENSOR_USAGE    sensor usage 
        //-----------------------------------------------------------------------
        IDragonSensor::SENSOR_USAGE GetUsage() const override;

    private:
        IDragonSensor::SENSOR_USAGE                 m_usage;
        std::unique_ptr<frc::Counter>               m_pulseWidthCounter;
        std::unique_ptr<frc::DigitalOutput>         m_trigger;
};

