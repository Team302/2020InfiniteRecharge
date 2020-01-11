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

#pragma once

// C++ Includes

// FRC includes

// Team 302 includes
#include <hw/interfaces/IDragonAnglePositionSensor.h>

// Third Party Includes

//====================================================================================================================================================
/// Class:           IDragonPositionSensor
/// Description:     This provides a common set of methods for all sensors that measure the 
///                  distance/position a mechanism has moved.
//====================================================================================================================================================
class DragonPositionSensor
{
    public:

        ///-----------------------------------------------------------------------
        /// Method:      DragonPositionSensor
        /// Description: Constructor  
        ///-----------------------------------------------------------------------
        DragonPositionSensor() = delete;
        DragonPositionSensor
        (
            IDragonAnglePositionSensor*     angleSensor,        /// <I> - angle sensor
            double                  diameter            /// <I> - diameter of the rotating item
        );
    
        ///-----------------------------------------------------------------------
        /// Method:      ~IDragonPositionSensor
        /// Description: Destructor  
        ///-----------------------------------------------------------------------
        ~DragonPositionSensor();

    
        ///-----------------------------------------------------------------------
        /// Method:      GetDistance
        /// Description: Return the measured distance in inches
        /// Returns:     double     Measured distance
        ///-----------------------------------------------------------------------
        double GetDistance();
    
        ///-----------------------------------------------------------------------
        /// Method:      ResetDistance
        /// Description: Reset the current distance to 0 inches
        /// Returns:     void
        ///-----------------------------------------------------------------------
        void ResetDistance();
    
        ///-----------------------------------------------------------------------
        /// Method:      ResetDistance
        /// Description: Reset the current distance to a known distance
        /// Returns:     void
        ///-----------------------------------------------------------------------
        void ResetDistance
        ( 
            double distance        /// <I> - value for the current distance in inches
        );

    
        ///-----------------------------------------------------------------------
        /// Method:      GetDistanceConfidence
        /// Description: Indicates how accurate the returned distance is
        /// Returns:     double    0.0 == ignore (sensor has an error)
        ///                        1.0 == very confident 
        ///-----------------------------------------------------------------------
        double GetDistanceConfidence();

    private:
        IDragonAnglePositionSensor*     m_angleSensor;      // sensor measuring angles
        double                  m_diameter;         // used to calculate rotational distance
        double                  m_startAngle;       // angle value to measure from
        double                  m_startDist;        // distance the starting angle corresponds to
};
