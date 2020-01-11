//====================================================================================================================================================
// MechanismDataDefn.h
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

// C++ Includes
#include <iostream>
#include <utility>

// FRC includes
#include <frc/SmartDashboard/SmartDashboard.h>

// Team 302 includes
#include <subsys/IMechanism.h>
#include <subsys/MechanismParameters.h>
#include <subsys/MechParamData.h>
#include <xmlmechdata/MechanismDataDefn.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>



using namespace frc;


//-----------------------------------------------------------------------
// Method:      ParseXML
// Description: Parse MechanismData XML element 
//  <!ELEMENT mechanismData EMPTY>
//  <!ATTLIST mechanismData 
//            dataType
//            value CDATA "0.0"
//  >
//
// Returns:     mechParamData        mechanism data
//-----------------------------------------------------------------------
mechParamData  MechanismDataDefn::ParseXML
(
    pugi::xml_node      MechanismDataNode
)
{
    // initialize output
    mechParamData mechData;

    // initialize attributes to default values
    mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::MECHANISM_PARAM_UNKNOWN;
    mechData.second = 0.0;

    bool hasError = false;

    // parse/validate xml
    for (pugi::xml_attribute attr = MechanismDataNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(), "paramType" ) == 0 )
        {
            auto param = attr.value();
            if ( strcmp( param, "LEGAL_STARTING_ANGLE") == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::LEGAL_STARTING_ANGLE;               
            }
            else if ( strcmp( param, "TEST_STARTING_ANGLE" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::TEST_STARTING_ANGLE;               
            }
            else if ( strcmp( param, "EXTENDER_LEGAL_STARTING_INCHES" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::EXTENDER_LEGAL_STARTING_INCHES;               
            }
            else if ( strcmp( param, "EXTENDER_TEST_STARTING_INCHES" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::EXTENDER_TEST_STARTING_INCHES;               
            }
            else if ( strcmp( param, "HATCH_FLOOR_ANGLE" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::HATCH_FLOOR_ANGLE;               
            }
            else if ( strcmp( param, "HATCH_HP_SECOND_ANGLE" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::HATCH_HP_SECOND_ANGLE;               
            }
            else if ( strcmp( param, "HATCH_LOW_ANGLE" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::HATCH_LOW_ANGLE;               
            }
            else if ( strcmp( param, "HATCH_MID_ANGLE" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::HATCH_MID_ANGLE;               
            }
            else if ( strcmp( param, "HATCH_HIGH_ANGLE" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::HATCH_HIGH_ANGLE;               
            }
            else if ( strcmp( param, "HATCH_LOW_SECOND_ANGLE" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::HATCH_LOW_SECOND_ANGLE;               
            }
            else if ( strcmp( param, "HATCH_MID_SECOND_ANGLE" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::HATCH_MID_SECOND_ANGLE;               
            }
            else if ( strcmp( param, "HATCH_HIGH_SECOND_ANGLE" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::HATCH_HIGH_SECOND_ANGLE;               
            }
            else if ( strcmp( param, "CARGO_FLOOR_ANGLE" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::CARGO_FLOOR_ANGLE;               
            }
            else if ( strcmp( param, "CARGO_HP_ANGLE" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::CARGO_HP_ANGLE;               
            }
            else if ( strcmp( param, "CARGO_SHIP_ANGLE" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::CARGO_SHIP_ANGLE;               
            }
            else if ( strcmp( param, "CARGO_LOW_ANGLE" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::CARGO_LOW_ANGLE;               
            }
            else if ( strcmp( param, "CARGO_MID_ANGLE" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::CARGO_MID_ANGLE;               
            }
            else if ( strcmp( param, "CARGO_HIGH_ANGLE" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::CARGO_HIGH_ANGLE;               
            }
            else if ( strcmp( param, "CARGO_HP_EXTENSION" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::CARGO_HP_EXTENSION;               
            }
            else if ( strcmp( param, "HATCH_FLOOR_EXTENSION" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::HATCH_FLOOR_EXTENSION;               
            }
            else if ( strcmp( param, "HATCH_HP_SECOND_EXTENSION" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::HATCH_HP_SECOND_EXTENSION;               
            }
            else if ( strcmp( param, "HATCH_LOW_EXTENSION" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::HATCH_LOW_EXTENSION;               
            }
            else if ( strcmp( param, "HATCH_MID_EXTENSION" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::HATCH_MID_EXTENSION;               
            }
            else if ( strcmp( param, "HATCH_HIGH_EXTENSION" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::HATCH_HIGH_EXTENSION;               
            }
            else if ( strcmp( param, "HATCH_LOW_SECOND_EXTENSION" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::HATCH_LOW_SECOND_EXTENSION;               
            }
            else if ( strcmp( param, "HATCH_MID_SECOND_EXTENSION" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::HATCH_MID_SECOND_EXTENSION;               
            }
            else if ( strcmp( param, "HATCH_HIGH_SECOND_EXTENSION" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::HATCH_HIGH_SECOND_EXTENSION;               
            }
            else if ( strcmp( param, "CARGO_FLOOR_EXTENSION" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::CARGO_FLOOR_EXTENSION;               
            }
            else if ( strcmp( param, "CARGO_SHIP_EXTENSION" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::CARGO_SHIP_EXTENSION;               
            }
            else if ( strcmp( param, "CARGO_LOW_EXTENSION" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::CARGO_LOW_EXTENSION;               
            }
            else if ( strcmp( param, "CARGO_MID_EXTENSION" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::CARGO_MID_EXTENSION;               
            }
            else if ( strcmp( param, "CARGO_HIGH_EXTENSION" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::CARGO_HIGH_EXTENSION;               
            }
            else if ( strcmp( param, "CARGO_INTAKE_SPEED_PARAM" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::CARGO_INTAKE_SPEED_PARAM;               
            }
            else if ( strcmp( param, "CARGO_OUTTAKE_SPEED_PARAM" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::CARGO_OUTTAKE_SPEED_PARAM;               
            }
            else if ( strcmp( param, "HATCH_INTAKE_SPEED_PARAM" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::HATCH_INTAKE_SPEED_PARAM;               
            }
            else if ( strcmp( param, "HATCH_OUTTAKE_SPEED_PARAM" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::HATCH_OUTTAKE_SPEED_PARAM;               
            }
            else if ( strcmp( param, "SERVO_LOCKED_POSITION_PARAM" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::SERVO_LOCKED_POSITION_PARAM;               
            }
            else if ( strcmp( param, "SERVO_DROPPED_POSITION_PARAM" ) == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::SERVO_DROPPED_POSITION_PARAM;               
            }
            else if ( strcmp( param, "HATCH_MECH_OPEN_ROTATIONS") == 0 )
            {
                mechData.first = MechanismParameters::MECHANISM_PARAM_TYPE::HATCH_MECH_OPEN_ROTATIONS;               
            }
            else
            {
                printf( "==>> MechanismDataDefn::ParseXML invalid dataType %s \n", param );
                hasError = true;
            }            
        }
        else if ( strcmp( attr.name(), "value") == 0 )
        {
            mechData.second = attr.as_double();
        }
        else
        {
            printf( "==>> MechanismDataDefn::ParseXML invalid attribute %s \n", attr.name() );
            hasError = true;
        }
    }
    return mechData;
}


