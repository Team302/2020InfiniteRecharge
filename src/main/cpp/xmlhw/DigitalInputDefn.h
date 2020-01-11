/*
 * DigitalInputDfen.h
 *
 *  Created on: Jan 15, 2018
 *      Author: casti
 */

#ifndef SUBSYS_XMLPARSING_DIGITALINPUTDEFN_H_
#define SUBSYS_XMLPARSING_DIGITALINPUTDEFN_H_

// C++ Includes
#include <iostream>

// FRC includes

// Team 302 includes
#include <hw/DragonDigitalInput.h>

// Third Party includes
#include <pugixml/pugixml.hpp>


class DigitalInputDefn
{
    public:

        DigitalInputDefn() = default;
        virtual ~DigitalInputDefn() = default;

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
        //			      FRONT_LEFT_LINE_DETECT,
        //			      FRONT_RIGHT_LINE_DETECT,
        //			      BACK_LEFT_LINE_DETECT,
        //			      BACK_RIGHT_LINE_DETECT,
        //            MAX_DIGITAL_INPPUT_TYPES
        //        };
        //
        //     ==================================================== -->
        //<!ELEMENT digitalInput EMPTY>
        //<!ATTLIST digitalInput
        //          usage             (  0 |  1 |  2 |  3 |  4 | 5 | 6 | 7 | 8 ) "0"
        //          digitalId         (  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |
        //                              10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 |
        //                              20 | 21 | 22 | 23 | 24 | 25 ) "0"
        //          reversed          (true | false ) "false"
        //>
        //
        //
        // Returns:     DragonDigitalInput*
        //-----------------------------------------------------------------------
        DragonDigitalInput* ParseXML
        (
            pugi::xml_node      DigitalNode
        );

};

#endif /* SUBSYS_XMLPARSING_DIGITALINPUTDEFN_H_ */
