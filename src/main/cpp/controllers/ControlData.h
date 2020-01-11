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

#include <controllers/ControlModes.h>

class ControlData
{
    public:
        /**
        enum CONTROL_MODE
        {
            VELOCITY,
            POSITION,
            MOTION_MAGIC,
            VOLTAGE,
            CURRENT,
            MOTION_PROFILE,
            MOTION_PROFILE_ARC
        };
        **/

        ControlData
        (
            ControlModes::CONTROL_TYPE    mode,
            double                                      proportional,
            double                                      integral,
            double                                      derivative,
            double                                      feedforward,
            double                                      integralZone,
            double                                      maxAcceleration,
            double                                      cruiseVelocity
        );


        virtual ~ControlData() = default;

        inline ControlModes::CONTROL_TYPE GetMode() { return m_mode; };
        inline double GetP() { return m_proportional; };
        inline double GetI() { return m_integral; };
        inline double GetD() { return m_derivative; };
        inline double GetF() { return m_feedforward; };
        inline double GetIZone() { return m_iZone; };
        inline double GetMaxAcceleration() { return m_maxAcceleration; };
        inline double GetCruiseVelocity() { return m_cruiseVelocity; };

 
    private:
        ControlData() = delete;

        ControlModes::CONTROL_TYPE    m_mode;
        double                                      m_proportional;
        double                                      m_integral;
        double                                      m_derivative;
        double                                      m_feedforward;
        double                                      m_iZone;
        double                                      m_maxAcceleration;
        double                                      m_cruiseVelocity;

};

