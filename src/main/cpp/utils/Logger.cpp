
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
/// Logger.cpp
//========================================================================================================
///
/// File Description:
///     This logs error messages
///
//========================================================================================================


// C++ Includes
#include <algorithm>
#include <iostream>
#include <locale>
#include <string>

// FRC includes
#include <frc/SmartDashboard/SmartDashboard.h>

// Team 302 includes
#include <utils/Logger.h>


// Third Party Includes

using namespace frc;
using namespace std;


//=====================================================================================
/// Method:         GetLogger
/// Description:    Find or create the singleton logger
/// Returns:        Logger* pointer to the logger
//=====================================================================================
Logger* Logger::m_instance = nullptr;
Logger* Logger::GetLogger()
{
    if ( Logger::m_instance == nullptr )
    {
        Logger::m_instance = new Logger();
    }
    return Logger::m_instance;
}

void Logger::SetLoggingOption
(
    LOGGER_OPTION option    // <I> - Logging option
)
{

}


void Logger::LogError
(
    const string&   locationIdentifier,     // <I> - classname or object identifier
    const string&   message                 // <I> - error message
)
{
    switch ( m_level )
    {
        case LOGGER_OPTION::CONSOLE:
            cout << locationIdentifier << ": " << message << endl;
            break;

        case LOGGER_OPTION::DASHBOARD:
            SmartDashboard::PutString( locationIdentifier.c_str(), message.c_str());
            break;

        default:  // case LOGGER_OPTION::EAT_IT:
            break;

    }
}


Logger::Logger() : m_level( LOGGER_OPTION::CONSOLE )
{
}
