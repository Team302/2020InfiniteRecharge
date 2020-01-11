
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

//========================================================================================================
/// HardwareIDValidation.h
//========================================================================================================
///
/// File Description:
///     This will validate the various hardware IDs against the valid values.
//========================================================================================================

#pragma once

// C++ Includes
#include <string>

// FRC Includes

// Team 302 Includes
#include <hw/interfaces/IDragonSensor.h>
#include <utils/Logger.h>

// Third Party Includes

class UsageValidation
{
    public:
        UsageValidation() = delete;
        ~UsageValidation() = delete;

        //======================================================================================
        /// Method:       ValidateSensorUsage
        /// Description:  Check the sensor usage string and convert it to the 
        ///               IDragonSensor::Sensor_Usage value.   If it is an invalid string, the
        ///               logger utility will be called.
        /// Returns:      IDragonSensor::Sensor_USAGE
        //=====================================================================================
        static IDragonSensor::SENSOR_USAGE ValidateSensorUsage
        (
            std::string  usageString,   // <I> - Usage String to validate and convert
            std::string  methodID       // <I> - class::method identifier for message
        );

};


