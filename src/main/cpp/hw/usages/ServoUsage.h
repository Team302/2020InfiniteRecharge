
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



class ServoUsage
{

    public:

        /// @enum SERVO_USAGE
        /// @brief Defines Servo usages.  This should be modified for each robot.
        enum SERVO_USAGE
        {
            UNKNOWN_SERVO_USAGE = -1,
            SHOOTER_HOOD,
            MAX_SERVO_USAGES
        };


        static ServoUsage* GetInstance();

        SERVO_USAGE GetUsage
        ( 
            const std::string         usageString
        );

    private:
        static ServoUsage*    m_instance;
        ServoUsage();
        ~ServoUsage();
        
		std::map <std::string, SERVO_USAGE> m_usageMap;

};



