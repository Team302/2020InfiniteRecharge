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

// Third Party Includes
#include <pugixml/pugixml.hpp>

using namespace std;
using namespace pugi;

//-----------------------------------------------------------------------
// Method:      ParseXML
// Description: Parse a pigeon XML element and create a DragonPigeon from
//              its definition.
//
//<!-- ====================================================
//     Pigeon IMU
//     ==================================================== -->
//<!ELEMENT pigeon EMPTY>
//<!ATTLIST pigeon
//          canId             (  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |
//                              10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 |
//                              20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 |
//                              30 | 31 | 32 | 33 | 34 | 35 | 36 | 37 | 38 | 39 |
//                              40 | 41 | 42 | 43 | 44 | 45 | 46 | 47 | 48 | 49 |
//                              50 | 51 | 52 | 53 | 54 | 55 | 56 | 57 | 58 | 59 |
//                              60 | 61 | 62 ) "0"
//>
//
// Returns:     DragonPigeon*       pigeon IMU (or nullptr if XML is ill-formed)
//-----------------------------------------------------------------------
shared_ptr<DragonPigeon> PigeonDefn::ParseXML
(
    xml_node      pigeonNode
)
{
    // initialize output
    shared_ptr<DragonPigeon> pigeon;

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
        pigeon = make_shared<DragonPigeon>( canID );
    }
    return pigeon;
}
