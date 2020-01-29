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

#include <string>

#include <controllers/ControlModes.h>

class ControlData
{
    public:
        /// @brief      Create the ControlData object that is used to control mechanisms
        /// @param [in] mode - control mode
        /// @param [in] server - where to run the controller on
        /// @param [in] indentifier - mapping identifier for this controller
        /// @param [in] proportional - p coefficient for a PID-based controller
        /// @param [in] integral - i coefficient for a PID-based controller
        /// @param [in] derivative - d coefficient for a PID-based controller
        /// @param [in] feedforward - f coefficient for a PID-based controller
        /// @param [in] integralZone - range of the integral for a PID-based controller
        /// @param [in] maxAcceleration - maximum acceleration 
        /// @param [in] cruiseVelocity - cruise velocity 
        /// @param [in] peakValue - peak value 
        /// @param [in] nominalValue - nominal value 
        ControlData
        (
            ControlModes::CONTROL_TYPE                  mode,
			ControlModes::CONTROL_RUN_LOCS				server,
            std::string                                 indentifier,
            double                                      proportional,
            double                                      integral,
            double                                      derivative,
            double                                      feedforward,
            double                                      integralZone,
            double                                      maxAcceleration,
            double                                      cruiseVelocity,
            double                                      peakValue,
            double                                      nominalValue
        );


        virtual ~ControlData() = default;

        /// @brief  Retrieve the Control Type
        /// @return ControlModes::CONTROL_TYPE
        inline ControlModes::CONTROL_TYPE GetMode() const { return m_mode; };

        /// @brief  Retrieve the identifier
        /// @return std::string the identifier
        inline std::string GetIdentifier() const { return m_identifier; };

        /// @brief  Retrieve the P coefficient for a PID-based control mode
        /// @return double - P coefficient
        inline double GetP() const { return m_proportional; };

        /// @brief  Retrieve the I coefficient for a PID-based control mode
        /// @return double - I coefficient
        inline double GetI() const { return m_integral; };

        /// @brief  Retrieve the D coefficient for a PID-based control mode
        /// @return double - D coefficient
        inline double GetD() const { return m_derivative; };

        /// @brief  Retrieve the Feed-forwared coefficient for a PID-based control mode
        /// @return double - F coefficient
        inline double GetF() const { return m_feedforward; };

        /// @brief  Retrieve the izone for a PID-based control mode (where the intregal is reset)
        /// @return double - izone value
        inline double GetIZone() const { return m_iZone; };

        /// @brief  Retrieve the max acceleration for a trapezoid control mode
        /// @return double - max acceleration
        inline double GetMaxAcceleration() const { return m_maxAcceleration; };

        /// @brief  Retrieve the cruise velocity for a trapezoid control mode
        /// @return double - cruise velocity
        inline double GetCruiseVelocity() const { return m_cruiseVelocity; };

        /// @brief  Retrieve the peak value 
        /// @return double - peak value
        inline double GetPeakValue() const { return m_peakValue; };

        /// @brief  Retrieve the nominal value 
        /// @return double - nominal value
        inline double GetNominalValue() const { return m_nominalValue; };

 
    private:
        ControlData() = delete;

        ControlModes::CONTROL_TYPE                  m_mode;
        std::string                                 m_identifier;
        double                                      m_proportional;
        double                                      m_integral;
        double                                      m_derivative;
        double                                      m_feedforward;
        double                                      m_iZone;
        double                                      m_maxAcceleration;
        double                                      m_cruiseVelocity;
        double                                      m_peakValue;
        double                                      m_nominalValue;

};

