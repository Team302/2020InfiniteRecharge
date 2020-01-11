
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

/// @class PDPDefn
/// @brief XML parsing for the PDP node in the Robot definition xml file.  Upon successful parsing, it will
///     create a PDP singleton object. The parsing leverages the 3rd party Open Source Pugixml library (https://pugixml.org/).

// C++ Includes
#include <iostream>
#include <memory>

// FRC includes
#include <frc/PowerDistributionPanel.h>

// Team 302 includes
#include <hw/DragonPDP.h>
#include <utils/HardwareIDValidation.h>
#include <utils/Logger.h>
#include <xmlhw/PDPDefn.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>

using namespace frc;
using namespace pugi;
using namespace std;



/// @brief      Parse a pcm XML element and create a PowerDistributionPanel* from its definition.
/// @param [in] xml_node PDPNode the <PDP element in the xml document
/// @return     PowerDistributionPanel*   PDP object
PowerDistributionPanel* PDPDefn::ParseXML
(
    xml_node      PDPNode           /// <I> - PDP node in the XML file
)
{
    // initialize output
    PowerDistributionPanel* pdp = nullptr;

    // initialize attributes to default values
    int canID = 0;

    bool hasError = false;

    // parse/validate the PDP XML node
    for (xml_attribute attr = PDPNode.first_attribute(); attr && !hasError; attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(), "canId" ) == 0 )
        {
            canID = attr.as_int();
            hasError = HardwareIDValidation::ValidateCANID( canID, string( "PDPDefn::ParseXML" ) );
        }
        else
        {
            string msg = "unknown attribute ";
            msg += attr.name();
            Logger::GetLogger()->LogError( "PDPDefn::ParseXML", msg );
            hasError = true;
        }
    }

    // If no errors, create the object
    if ( !hasError )
    {
        pdp = DragonPDP::GetInstance()->CreatePDP( canID );
    }
    return pdp;
}


