
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

class DigitalInputUsage
{

    public:

        /// @enum DIGITAL_SENSOR_USAGE
        /// @brief Defines digital input sensor usages.  This should be modified for each robot.
        enum DIGITAL_SENSOR_USAGE
        {
            UNKNOWN_DIGITAL_TYPE = -1,
            TURRET_ANGLE_MIN,
            TURRET_ANGLE_MAX,
            MAX_DIGITAL_TYPES
        };

        static DigitalInputUsage* GetInstance();

        DIGITAL_SENSOR_USAGE GetUsage
        ( 
            std::string         usageString
        );

    private:
        static DigitalInputUsage*    m_instance;
        DigitalInputUsage();
        ~DigitalInputUsage();
        
		std::map <std::string, DIGITAL_SENSOR_USAGE> m_usageMap;

};
