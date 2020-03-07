
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



// C++ Includes
#include <iostream>
#include <memory>

// FRC includes


// Team 302 includes
#include <utils/HardwareIDValidation.h>
#include <utils/Logger.h>
#include <xmlhw/BlinknDefn.h>
#include <hw/LED.h>
#include <cstring>
#include <string>
#include <xmlhw/BLINKin.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>

using namespace pugi;
using namespace std;


BLINKin* BlinkinDefn::ParseXML
(
    pugi::xml_node      BlinkinNode    /// <I> - PDP node in the XML file
)
{
    // initialize output
    BLINKin* blinkin = nullptr;

    // initialize attributes to default values
    int pwmID = 0;

    bool hasError = false;

    // parse/validate the PDP XML node
    for (xml_attribute attr = BlinkinNode.first_attribute(); attr && !hasError; attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(), "pwmId" ) == 0 )
        {
            pwmID = attr.as_int();
            hasError = HardwareIDValidation::ValidateCANID( pwmID, string( "BlinkinDefn::ParseXML" ) ); //TODO be able to change this line to a PWM
        }
        else
        {
            string msg = "unknown attribute ";
            msg += attr.name();
            Logger::GetLogger()->LogError( "BlinkinDefn::ParseXML", msg );
            hasError = true;
        }
    }

    // If no errors, create the object
    if ( !hasError )
    {
        blinkin = new BLINKin( pwmID );
        return blinkin;
    }
    
}


