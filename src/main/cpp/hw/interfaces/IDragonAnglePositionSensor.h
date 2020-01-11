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
/// Inteface:        IDragonAnglePositionSensor
/// Description:     This inteface provides a common set of methods for all sensors that measure angles
//====================================================================================================================================================
class IDragonAnglePositionSensor
{
    public:

        ///-----------------------------------------------------------------------
        /// Method:      IDragonAnglePositionSensor
        /// Description: Constructor for the interface 
        ///-----------------------------------------------------------------------
        IDragonAnglePositionSensor() = default;
    
        ///-----------------------------------------------------------------------
        /// Method:      ~IDragonAnglePositionSensor
        /// Description: Destructor for the interface 
        ///-----------------------------------------------------------------------
        ~IDragonAnglePositionSensor() = default;

    
        ///-----------------------------------------------------------------------
        /// Method:      GetRawAngle
        /// Description: Return the measured angle in degrees
        /// Returns:     double     Measured Angle
        ///-----------------------------------------------------------------------
        virtual double GetRawAngle() = 0;
    
        ///-----------------------------------------------------------------------
        /// Method:      GetNormalizedAngle
        /// Description: Return the measured angle and adjust the value to be 
        ///              between 0 and 360 degrees
        /// Returns:     double     Measured Angle
        ///-----------------------------------------------------------------------
        virtual double GetNormalizedAngle() = 0;
    
        ///-----------------------------------------------------------------------
        /// Method:      ResetAngle
        /// Description: Reset the current angle to 0 degrees
        /// Returns:     void
        ///-----------------------------------------------------------------------
        virtual void ResetAngle() = 0;
    
        ///-----------------------------------------------------------------------
        /// Method:      ResetAngle
        /// Description: Reset the current angle to a known angle
        /// Returns:     void
        ///-----------------------------------------------------------------------
        virtual void ResetAngle
        ( 
            double angle        /// <I> - set the current angle to measure this value (degrees)
        ) = 0;

    
        ///-----------------------------------------------------------------------
        /// Method:      GetAngleConfidence
        /// Description: Indicates how accurate the returned angle is
        /// Returns:     double    0.0 == ignore (sensor has an error)
        ///                        1.0 == very confident 
        ///-----------------------------------------------------------------------
        virtual double GetAngleConfidence() = 0;

};
