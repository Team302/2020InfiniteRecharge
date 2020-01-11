
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
/// UsageValidation.cpp
//========================================================================================================
///
/// File Description:
///     This will validate the various usages against the valid values.
//========================================================================================================

// C++ Includes
#include <algorithm>
#include <string>

// FRC Includes

// Team 302 Includes
#include <utils/UsageValidation.h>
#include <utils/Logger.h>

// Third Party Includes

using namespace std;


//======================================================================================
/// Method:       ValidateSensorUsage
/// Description:  Check the sensor usage string and convert it to the 
///               IDragonSensor::Sensor_Usage value.   If it is an invalid string, the
///               logger utility will be called.
/// Returns:      IDragonSensor::Sensor_USAGE
//=====================================================================================
IDragonSensor::SENSOR_USAGE UsageValidation::ValidateSensorUsage
(
    string  usageString,   // <I> - Usage String to validate and convert
    string  methodID       // <I> - class::method identifier for message
)
{
    IDragonSensor::SENSOR_USAGE usage = IDragonSensor::SENSOR_USAGE::UNKNOWN_SENSOR;

    // convert to upper case
    string compareString = usageString;
    for_each( compareString.begin(), compareString.end(), [](char & c){c = ::toupper(c);});

    // compare the string to known usage strings
    if ( compareString.compare( "TEST" ) )
    {
        usage = IDragonSensor::SENSOR_USAGE::MAX_SENSORS;
    }
    else
    {
    }
    
    // if it doesn't match any usage strings, log an error message
    if ( usage == IDragonSensor::SENSOR_USAGE::UNKNOWN_SENSOR )
    {
        string errorMsg = "Invalid usage " + usageString;
        Logger::GetLogger()->LogError( methodID, errorMsg );
    }

    return usage;
}




