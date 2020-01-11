//====================================================================================================================================================
// IDragonDistanceSensor.h
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

// FRC includes

// Team 302 includes
#include <hw/interfaces/IDragonSensor.h>
#include <hw/interfaces/IDragonDistanceSensor.h>
#include <hw/DragonLidar.h>
#include <hw/DragonUltrasonic.h>
#include <hw/DragonUltrasonicPWM.h>

// Third Party Includes



//====================================================================================================================================================
/// @class  DistanceSensorFactory
/// @brief  This factory constructs distance sensors
//====================================================================================================================================================
class DistanceSensorFactory
{
    public:
        static DistanceSensorFactory* GetFactory();

        std::shared_ptr<IDragonDistanceSensor> GetSensor
        (
            IDragonSensor::SENSOR_USAGE    usage
        );

        /// @brief Create a distance sensor from the inputs
        /// @param IDragonSensor::SENSOR_USAGE  usage       
        /// @param int                          pwmInputPin (lidar or ultrasonic 3)
        /// @param int                          pwmTriggerPin (lidar)
        /// @param int                          analogPin (ultrasonic)
        /// @param int                          i2cID (rev 2M)
        /// @param int                          canID (playing with fusion time of flight)
        /// @param std::string                  tableName (limelight) network table name
        /// @param double                       mountingHeight in inches (limelight)
        /// @param double                       mountingHorizontalOffset in inches (limelight)
        /// @param double                       mountingAngle in degrees (limelight)
        /// @param double                       targetHeight in inches (limelight)
        /// @return std::shared_ptr<IDragonDistanceSensor>    sensor
        std::shared_ptr<IDragonDistanceSensor> CreateSensor
        (
            IDragonSensor::SENSOR_USAGE     usage,
            int                             inputPin,
            int                             triggerPin,
            int                             analogInputPin,
            int                             i2cID,
            int                             canID,
            std::string                     tableName,                  
            double                          mountingHeight,             
            double                          mountingHorizontalOffset,   
            double                          mountingAngle,              
            double                          targetHeight                
        );

    private:
        DistanceSensorFactory();
        ~DistanceSensorFactory();

        static DistanceSensorFactory*        m_instance;


};
