/*
 * PigeonDefn.h
 *
 *  Created on: Feb 2, 2018
 *      Author: team302
 */

#pragma once


// C++ Includes
#include <memory>

// FRC includes
#include <frc/SmartDashboard/SmartDashboard.h>

// Team 302 includes
#include <hw/DragonPigeon.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>


class PigeonDefn
{
    public:

        PigeonDefn() = default;
        virtual ~PigeonDefn() = default;


        //-----------------------------------------------------------------------
        // Method:      ParseXML
        // Description: Parse a pigeon XML element and create a DragonPigeon from
        //              its definition.
        // Returns:     DragonPigeon*       pigeon IMU (or nullptr if XML is ill-formed)
        //-----------------------------------------------------------------------
        std::shared_ptr<DragonPigeon> ParseXML
        (
            pugi::xml_node      pigeonNode
        );
};

