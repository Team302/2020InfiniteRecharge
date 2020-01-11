
//====================================================================================================================================================
/// Copyright 2019 Lake Orion Robotics FIRST Team 302
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
/// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
/// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
/// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================

#pragma once

//========================================================================================================
/// RobotDefn.h
//========================================================================================================
///
/// File Description:
///     Top-level XML parsing file for the robot.  This definition will construct the motor controllers,
///     sensors, chassis and mechanisms from an XML file.  This parsing leverages the 3rd party Open Source
///     Pugixml library (https://pugixml.org/).
///
///     This parsing code will call the classes/methods to parse the lower-level objects.  When the parsing
///     has been completed, the robot hardware will be defined.
///
///     The robot definition XML file is:  /home/lvuser/config/robot.xml
///
//========================================================================================================
class RobotDefn
{
    public:
        RobotDefn() = default;
        virtual ~RobotDefn() = default;

        //================================================================================================
        /// Method:      ParseXML
        /// Description: Parse a robot.xml file
        /// Returns:     void
        //================================================================================================
        void ParseXML();
};
