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

// FRC includes
#include <xmlhw/DigitalInputDefn.h>
#include <frc/SmartDashboard/SmartDashboard.h>

// Team302 includes
#include <xmlhw/DigitalInputDefn.h>
#include <hw/DragonDigitalInput.h>

// Third Party includes
#include <pugixml/pugixml.hpp>


using namespace frc;

//-----------------------------------------------------------------------
// Method:      ParseXML
// Description: Parse a motor XML element and create a DragonTalon from
//              its definition.
//
//<!-- ====================================================
//     digitalInput
//     ====================================================
//        enum DIGITAL_INPUT_TYPE
//        {
//            UNKNOWN_DIGITAL_INPUT_TYPE = -1,
//            CARGO_PRESENT,
//            HATCH_PRESENT_SIDE1,
//            HATCH_PRESENT_SIDE2,
//            ARM_MIN_POSITION,
//            ARM_MAX_POSITION,
//	      FRONT_LEFT_LINE_DETECT,
//	      FRONT_RIGHT_LINE_DETECT,
//	      BACK_LEFT_LINE_DETECT,
//	      BACK_RIGHT_LINE_DETECT,
//            MAX_DIGITAL_INPPUT_TYPES
//        };
//
//     ==================================================== -->
//<!ELEMENT digitalInput EMPTY>
//<!ATTLIST digitalInput
//          usage             (  0 |  1 |  2 |  3 |  4 | 5 | 6 | 8 ) "0"
//          digitalId         (  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |
//                              10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 |
//                              20 | 21 | 22 | 23 | 24 | 25 ) "0"
//          reversed          (true | false ) "false"
//>
//
//
// Returns:     DragonDigitalInput*
//-----------------------------------------------------------------------
DragonDigitalInput* DigitalInputDefn::ParseXML
(
    pugi::xml_node DigitalNode
)
{
    // initialize the output
    DragonDigitalInput*         input = nullptr;

    // initialize the attributes to default values
    DragonDigitalInput::DIGITAL_INPUT_TYPE  usage = DragonDigitalInput::UNKNOWN_DIGITAL_INPUT_TYPE;
    int                                     digitalID = 0;
    bool                                    reversed = false;

    bool hasError = false;

    // Parse/validate the XML
    for (pugi::xml_attribute attr = DigitalNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(), "usage" ) == 0 )
        {
            int iVal = attr.as_int();
            switch (iVal )
            {
                case DragonDigitalInput::DIGITAL_INPUT_TYPE::ARM_MIN_POSITION:
                    usage = DragonDigitalInput::DIGITAL_INPUT_TYPE::ARM_MIN_POSITION;
                    break;

                default:
                	hasError = true;
                    printf( "==>> unknown DragonDigitalInput type %d \n", iVal );
                    break;
            }
        }
        else if ( strcmp( attr.name(), "digitalId" ) == 0 )
        {
            int iVal = attr.as_int();
            if ( iVal >=0 && iVal <= 25 )
            {
                digitalID = iVal;
            }
            else
            {
                printf( "==>> DigitalInputDefn::ParseXML  invalid digitalId %d \n", iVal );
                hasError = true;
            }
        }
        else if ( strcmp( attr.name(), "reversed" ) == 0 )
        {
            reversed = attr.as_bool();

        }
    }

    // Create the DragonDigitalInput
    if ( !hasError )
    {
        input = new DragonDigitalInput( usage, digitalID, reversed );
    }
    return input;
}

