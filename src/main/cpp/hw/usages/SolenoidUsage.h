
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
#include <map>
#include <memory>
#include <string>

// FRC includes

// Team 302 includes


// Third Party Includes



class SolenoidUsage
{

    public:

        /// @enum SOLENOID_USAGE
        /// @brief Defines solenoid usages.  This should be modified for each robot.
        enum SOLENOID_USAGE
        {
            UNKNOWN_SOLENOID_USAGE = -1,
            INTAKE,
            BALL_TRANSFER,
            SHOOTER_HOOD,
            CONTROL_TABLE_MANIPULATOR,
            CLIMBER,
            MAX_SOLENOID_USAGES
        };


        static SolenoidUsage* GetInstance();

        SOLENOID_USAGE GetUsage
        ( 
            const std::string         usageString
        );

    private:
        static SolenoidUsage*    m_instance;
        SolenoidUsage();
        ~SolenoidUsage();
        
		std::map <std::string, SOLENOID_USAGE> m_usageMap;

};



