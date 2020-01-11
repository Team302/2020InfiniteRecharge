
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

// C++ Includes
#include <memory>
#include <string>
#include <vector>

// FRC includes
#include <frc/Counter.h>
#include <frc/DigitalInput.h>
#include <frc/DigitalOutput.h>

// Team 302 includes
#include <hw/DragonLidar.h>
#include <utils/Logger.h>

// Third Party Includes

using namespace nt;
using namespace std;
using namespace frc;


///-----------------------------------------------------------------------------------
/// Method:         DragonLidar (constructor)
/// Description:    Create the object
///-----------------------------------------------------------------------------------
DragonLidar::DragonLidar
(
    IDragonSensor::SENSOR_USAGE usage,
    int                         inputPin,
    int                         triggerPin
)  : IDragonSensor(),
     IDragonDistanceSensor(),
     m_usage( usage ),
     m_pulseWidthCounter( make_unique<Counter>(inputPin) ),	//Construct the counter with the desired digital input
     m_trigger( make_unique<DigitalOutput>(triggerPin) )
{
	m_pulseWidthCounter->SetSemiPeriodMode(true);
	m_trigger->Set(true);
}

///-----------------------------------------------------------------------
/// Method:      GetDistance
/// Description: Return the measured distance in inches
/// Returns:     double     Measured Distance
///-----------------------------------------------------------------------
double DragonLidar::GetDistance() const
{ 
	m_trigger->Set(false);
	return m_pulseWidthCounter->GetPeriod() * 100000.0 * 0.393701; //Converting from period to centimeters, and then to inches
}


///-----------------------------------------------------------------------
/// Method:      GetConfidence
/// Description: Indicates how accurate the returned value is
/// Returns:     double    0.0 == ignore (sensor has an error)
///                        1.0 == very confident 
///-----------------------------------------------------------------------
double DragonLidar::GetConfidence() const
{
    double confidence = 1.0;
    if ( m_pulseWidthCounter->GetError().GetCode() != 0 || m_trigger->GetError().GetCode() != 0 )
    {
        confidence = 1.0;
    }
    return confidence;
}


///-----------------------------------------------------------------------
/// Method:      GetUsage
/// Description: Indicate what the sensor is used for
/// Returns:     SENSOR_USAGE    sensor usage 
///-----------------------------------------------------------------------
IDragonSensor::SENSOR_USAGE DragonLidar::GetUsage() const
{
    return m_usage;
}

