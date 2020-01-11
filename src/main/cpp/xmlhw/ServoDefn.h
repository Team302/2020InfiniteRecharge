/*
 * ServoDefn.h
 */

#pragma once 

// C++ Includes
#include <memory>
#include <iostream>

// FRC includes

// Team 302 includes
#include <hw/DragonServo.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>

class ServoDefn
{
    public:
        ServoDefn() = default;
        virtual ~ServoDefn() = default;

        //-----------------------------------------------------------------------
        // Method:      ParseXML
        // Description: Parse a servo XML element and create a DragonServo from
        //              its definition.
        // Returns:     void
        //-----------------------------------------------------------------------
        std::shared_ptr<DragonServo> ParseXML
        (
            pugi::xml_node      ServoNode
        );
};
