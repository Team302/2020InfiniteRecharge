/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#pragma once

#include <memory>

// Third Party Includes
#include <pugixml/pugixml.hpp>

//CTRE Includes
#include <ctre/Phoenix.h>


class CANifierDefn
{
    public:

        CANifierDefn() = default;
        virtual ~CANifierDefn() = default;
    /*Method: ParseXML
     *Description: Parses a CANifier XML element
     * Returns: void
     *
     */
        std::shared_ptr<ctre::phoenix::CANifier> ParseXML( pugi::xml_node	canifierNode  );
private:

};

