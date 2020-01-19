// --------------------------------------------------------------------------------------------
// DigitalInputDefn.cpp
//
//  Created on: Jan 15, 2018
//      Author: casti
//
// --------------------------------------------------------------------------------------------
//
// Description: Create an DigitalInput from an XML definition
//
//
// --------------------------------------------------------------------------------------------

// C++ includes
#include <iostream>
#include <string>
#include <memory>

// FRC includes
#include <frc/SmartDashboard/SmartDashboard.h>

// Team302 includes
#include <hw/usages/DigitalInputUsage.h>
#include <xmlhw/DigitalInputDefn.h>
#include <hw/DragonDigitalInput.h>
#include <utils/HardwareIDValidation.h>

// Third Party includes
#include <pugixml/pugixml.hpp>


using namespace frc;
using namespace std;
using namespace pugi;

//-----------------------------------------------------------------------
// Method:      ParseXML
// Description: Parse a motor XML element and create a DragonTalon from
//              its definition.
//
// Returns:     DragonDigitalInput*
//-----------------------------------------------------------------------
shared_ptr<DragonDigitalInput> DigitalInputDefn::ParseXML
(
    xml_node DigitalNode
)
{
    // initialize the output
    shared_ptr<DragonDigitalInput> input;

    // initialize the attributes to default values
    DigitalInputUsage::DIGITAL_SENSOR_USAGE  usage = DigitalInputUsage::DIGITAL_SENSOR_USAGE::UNKNOWN_DIGITAL_TYPE;
    int                                     digitalID = 0;
    bool                                    reversed = false;

    bool hasError = false;

    // Parse/validate the XML
    for (pugi::xml_attribute attr = DigitalNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(), "usage" ) == 0 )
        {
            string usageString = string(attr.value());
            usage = DigitalInputUsage::GetInstance()->GetUsage(usageString );
        }
        else if ( strcmp( attr.name(), "digitalId" ) == 0 )
        {
            int iVal = attr.as_int();
            hasError = HardwareIDValidation::ValidateDIOID( iVal, string( "DigitalInputDefn::ParseXML(digital Input pin)" ) );
        }
        else if ( strcmp( attr.name(), "reversed" ) == 0 )
        {
            reversed = attr.as_bool();

        }
    }

    // Create the DragonDigitalInput
    if ( !hasError )
    {
        input = make_shared<DragonDigitalInput>( usage, digitalID, reversed );
    }
    return input;
}

