//====================================================================================================================================================
// IDragonAnglePositionSensor.h
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

//====================================================================================================================================================
/// Inteface:        IDragonSensor
/// Description:     This inteface provides a common set of methods for all sensors
//====================================================================================================================================================
class IDragonSensor
{
    public:

        enum SENSOR_USAGE
        {
            UNKNOWN_SENSOR = -1,
            MAIN_LIMELIGHT,
            FORWARD_SENSOR,
            REARWARD_SENSOR,
            MAX_SENSORS
        };

        ///-----------------------------------------------------------------------
        /// Method:      IDragonSensor
        /// Description: Constructor for the interface 
        ///-----------------------------------------------------------------------
        IDragonSensor() = default;
    
        ///-----------------------------------------------------------------------
        /// Method:      ~IDragonSensor
        /// Description: Destructor for the interface 
        ///-----------------------------------------------------------------------
        ~IDragonSensor() = default;


        ///-----------------------------------------------------------------------
        /// Method:      GetConfidence
        /// Description: Indicates how accurate the returned value is
        /// Returns:     double    0.0 == ignore (sensor has an error)
        ///                        1.0 == very confident 
        ///-----------------------------------------------------------------------
        virtual double GetConfidence() const = 0;

        ///-----------------------------------------------------------------------
        /// Method:      GetUsage
        /// Description: Indicate what the sensor is used for
        /// Returns:     SENSOR_USAGE    sensor usage 
        ///-----------------------------------------------------------------------
        virtual SENSOR_USAGE GetUsage() const = 0;

};
