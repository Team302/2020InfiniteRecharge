
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

/// @class SolenoidDefn
/// @brief XML parsing for motor definitions.  This definition will construct the solenoids.
///     This parsing leverages the 3rd party Open Source Pugixml library (https://pugixml.org/).


// C++ Includes
#include <memory>
#include <string>

// FRC includes

// Team 302 includes
#include <xmlhw/SolenoidDefn.h>
#include <hw/DragonSolenoid.h>
#include <hw/usages/SolenoidUsage.h>
#include <utils/HardwareIDValidation.h>
#include <utils/Logger.h>


// Third Party Includes
#include <pugixml/pugixml.hpp>

using namespace frc;
using namespace pugi;
using namespace std;

/// @brief  Parse a solenoid XML element and create a DragonSolenoid from its definition.
/// @return std::shared_ptr<DragonSolenoid> solenoid pointer (or nullptr if XML is ill-formed)
shared_ptr<DragonSolenoid> SolenoidDefn::ParseXML
(
    xml_node      solenoidNode
)
{
    // initialize the output
    shared_ptr<DragonSolenoid> solenoid;

    // initialize attributes to default values
    SolenoidUsage::SOLENOID_USAGE usage = SolenoidUsage::SOLENOID_USAGE::UNKNOWN_SOLENOID_USAGE;
    int pcmID = 0;
    int channel = 0;
    bool reversed = false;

    bool hasError = false;

    for (xml_attribute attr = solenoidNode.first_attribute(); attr && !hasError; attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(), "usage" ) == 0 )
        {
             usage = SolenoidUsage::GetInstance()->GetUsage( string(attr.value()));
        }
        else if ( strcmp( attr.name(), "canId" ) == 0 )
        {
            pcmID = attr.as_int();
            hasError = HardwareIDValidation::ValidateCANID( pcmID, string( "SolenoidDefn::ParseXML" ) );
        }
        else if ( strcmp( attr.name(), "channel" ) == 0 )
        {
            channel = attr.as_int();
            hasError = HardwareIDValidation::ValidateSolenoidChannel( channel, string( "SolenoidDefn::ParseXML" ) );
        }
		// brake mode (or coast)
        else if ( strcmp( attr.name(), "reversed" ) == 0 )
        {
            reversed = attr.as_bool();
        }
        else
        {
            string msg = "Invalid attribute";
            msg += attr.name();
            Logger::GetLogger()->LogError( string("Solenoid::ParseXML "), msg );
            hasError = true;
        }
    }

    if ( !hasError )
    {
        solenoid = make_shared<DragonSolenoid>( usage, pcmID, channel, reversed );
    }
    return solenoid;
}


