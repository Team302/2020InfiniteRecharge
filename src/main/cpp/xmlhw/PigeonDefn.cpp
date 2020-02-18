/*
 * PideonDefn.cpp
 *
 *  Created on: Feb 2, 2018
 *      Author: team302
 */


// C++ Includes
#include <memory>

// FRC includes

// Team 302 includes
#include <xmlhw/PigeonDefn.h>
#include <hw/DragonPigeon.h>
#include <utils/HardwareIDValidation.h>
#include <utils/Logger.h>
#include <hw/factories/PigeonFactory.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>

using namespace std;
using namespace pugi;

//-----------------------------------------------------------------------
// Method:      ParseXML
// Description: Parse a pigeon XML element and create a DragonPigeon from
//              its definition.
// Returns:     DragonPigeon*       pigeon IMU (or nullptr if XML is ill-formed)
//-----------------------------------------------------------------------
DragonPigeon* PigeonDefn::ParseXML
(
    xml_node      pigeonNode
)
{
    // initialize output
    DragonPigeon* pigeon = nullptr;

    // initialize attributes to default values
    int canID = 0;

    bool hasError = false;

    // parse/validate xml
    for (xml_attribute attr = pigeonNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        canID = attr.as_int();
        hasError = HardwareIDValidation::ValidateCANID( canID, string( "Pigeon::ParseXML" ) );
    }

    if ( !hasError )
    {
        pigeon = PigeonFactory::GetFactory()->CreatePigeon( canID );
    }
    return pigeon;
}
