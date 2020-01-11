//====================================================================================================================================================
// DragonPositionSensor.h
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

#define _USE_MATH_DEFINES

// C++ Includes
#include <cmath>

// FRC includes

// Team 302 includes
#include <hw/DragonPositionSensor.h>
#include <hw/interfaces/IDragonAnglePositionSensor.h>

// Third Party Includes

//====================================================================================================================================================
/// Class:           IDragonPositionSensor
/// Description:     This provides a common set of methods for all sensors that measure the 
///                  distance/position a mechanism has moved.
//====================================================================================================================================================

///-----------------------------------------------------------------------
/// Method:      DragonPositionSensor
/// Description: Constructor  
///-----------------------------------------------------------------------
DragonPositionSensor::DragonPositionSensor
(
    IDragonAnglePositionSensor*     angleSensor,        /// <I> - angle sensor
    double                  diameter            /// <I> - diameter of the rotating item
) : m_angleSensor( angleSensor ),
    m_diameter( diameter ),
    m_startAngle( 0.0 ),
    m_startDist( 0.0 )
{
    if ( m_angleSensor != nullptr )
    {
        m_startAngle = m_angleSensor->GetRawAngle();
    }
}
    
///-----------------------------------------------------------------------
/// Method:      ~IDragonPositionSensor
/// Description: Destructor  
///-----------------------------------------------------------------------
DragonPositionSensor::~DragonPositionSensor() 
{
    /**
    if ( m_angleSensor != nullptr )
    {
        delete m_angleSensor;
        m_angleSensor = nullptr;
    }
    **/
}


///-----------------------------------------------------------------------
/// Method:      GetDistance
/// Description: Return the measured distance in inches
/// Returns:     double     Measured distance
///-----------------------------------------------------------------------
double DragonPositionSensor::GetDistance()
{
    double dist = 0.0;
    if ( m_angleSensor != nullptr )
    {
        auto currAngle = m_angleSensor->GetRawAngle();
        auto deltaAngle = currAngle - m_startAngle;
        auto deltaDist = deltaAngle * M_PI * m_diameter;
        dist = m_startDist + deltaDist;
    }
    return dist;
}

///-----------------------------------------------------------------------
/// Method:      ResetDistance
/// Description: Reset the current distance to 0 inches
/// Returns:     void
///-----------------------------------------------------------------------
void DragonPositionSensor::ResetDistance()
{
    ResetDistance( 0.0 );
}

///-----------------------------------------------------------------------
/// Method:      ResetDistance
/// Description: Reset the current distance to a known distance
/// Returns:     void
///-----------------------------------------------------------------------
void DragonPositionSensor::ResetDistance
( 
    double distance        /// <I> - value for the current distance in inches
)
{
    if ( m_angleSensor != nullptr )
    {
        m_startAngle = m_angleSensor->GetRawAngle();
        m_startDist  = distance;
    }
}


///-----------------------------------------------------------------------
/// Method:      GetDistanceConfidence
/// Description: Indicates how accurate the returned distance is
/// Returns:     double    0.0 == ignore (sensor has an error)
///                        1.0 == very confident 
///-----------------------------------------------------------------------
double DragonPositionSensor::GetDistanceConfidence()
{
    double confidence = 0.0;
    if ( m_angleSensor != nullptr )
    {
        confidence = m_angleSensor->GetAngleConfidence();
    }
    return confidence;
}
