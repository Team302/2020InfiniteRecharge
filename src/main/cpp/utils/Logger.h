
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
/// Logger.h
//========================================================================================================
///
/// File Description:
///     This logs error messages
///
//========================================================================================================

#pragma once

// C++ Includes
#include <string>

// FRC includes

// Team 302 includes


// Third Party Includes



class Logger
{
    public:

        enum LOGGER_OPTION
        {
            CONSOLE,
            DASHBOARD,
            EAT_IT
        };

        //=====================================================================================
        /// Method:         GetLogger
        /// Description:    Find or create the singleton logger
        /// Returns:        Logger* pointer to the logger
        //=====================================================================================
        static Logger* GetLogger();

        void SetLoggingOption
        (
            LOGGER_OPTION option    // <I> - Logging option
        );

       void LogError
       (
            const std::string&   locationIdentifier,     // <I> - classname or object identifier
            const std::string&   message                 // <I> - error message
       );

    protected:


    private:
        Logger();
        ~Logger() = default;

        LOGGER_OPTION m_level;
        static Logger* m_instance;


};


