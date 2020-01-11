/*
 * PrimitiveParser.cpp
 *
 *  Created on: Jan 24, 2018
 *      Author: Chris
 */

#include <auton/PrimitiveParser.h>

#include <pugixml/pugixml.hpp>

#include <iostream>


#include <frc/SmartDashboard/SmartDashboard.h>

#include <auton/PrimitiveParams.h>
#include <auton/AutonSelector.h>
#include <auton/PrimitiveEnums.h>
#include <auton/primitives/IPrimitive.h>

PrimitiveParamsVector PrimitiveParser::ParseXML
(
    std::string     fileName
)
{

    PrimitiveParamsVector paramVector;

    PRIMITIVE_IDENTIFIER        primitiveType = UNKNOWN_PRIMITIVE;
    float                       time = 0.0;
    float                       distance = 0.0;
    float                       heading = 0.0;
    float                       startDriveSpeed = 0.0;
    float                       endDriveSpeed = 0.0;
    float                       xloc = 0.0;
    float                       yloc = 0.0;

    bool hasError = false;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file( fileName.c_str() );
    if ( result )
    {
//        printf( "XML file [ %s ] parsed without errors \n ", fileName.c_str() );

        pugi::xml_node auton = doc.root();
        for (pugi::xml_node node = auton.first_child(); node; node = node.next_sibling())
        {
            for (pugi::xml_node primitiveNode = node.first_child(); primitiveNode; primitiveNode = primitiveNode.next_sibling())
            {
                if ( strcmp( primitiveNode.name(), "primitive") == 0 )
                {

                    for (pugi::xml_attribute attr = primitiveNode.first_attribute(); attr; attr = attr.next_attribute())
                    {
                        if ( strcmp( attr.name(), "id" ) == 0 )
                        {
                            int iVal = attr.as_int();
                            switch ( iVal )
                            {
                                case DO_NOTHING:
                                    primitiveType = DO_NOTHING;
                                    break;

                                case HOLD_POSITION:
                                    primitiveType = HOLD_POSITION;
                                    break;

                                case DRIVE_DISTANCE:
                                    primitiveType = DRIVE_DISTANCE;
                                    break;

                                case DRIVE_TIME:
                                    primitiveType = DRIVE_TIME;
                                    break;

                                case DRIVE_TO_CUBE:
                                    primitiveType = DRIVE_TO_CUBE;
                                    break;

                                case TURN_ANGLE_ABS:
                                    primitiveType = TURN_ANGLE_ABS;
                                    break;

                                case TURN_ANGLE_REL:
                                    primitiveType = TURN_ANGLE_REL;
                                    break;

                                case DRIVE_TO_WALL:
                                    primitiveType = DRIVE_TO_WALL;
                                    break;

                                case TURN_TO_CUBE:
                                    primitiveType = TURN_TO_CUBE;
                                    break;

                                case DRIVE_LIDAR_DISTANCE:
                                    primitiveType = DRIVE_LIDAR_DISTANCE;
                                    break;

                                default:
                                    printf( "==>> PrimitiveParser::ParseXML:  Invalid Primitive Type %d \n", iVal );
                                    hasError = true;
                                    break;
                            }

                        }
                        else if ( strcmp( attr.name(), "time" ) == 0 )
                        {
                            time = attr.as_float();
                        }
                        else if ( strcmp( attr.name(), "distance" ) == 0 )
                        {
                            distance = attr.as_float();
                        }
                        else if ( strcmp( attr.name(), "heading" ) == 0 )
                        {
                            heading = attr.as_float();
                        }
                        else if ( strcmp( attr.name(), "drivespeed" ) == 0 )
                        {
                            startDriveSpeed = attr.as_float();
                        }
                        else if ( strcmp( attr.name(), "enddrivespeed" ) == 0 )
                        {
                            endDriveSpeed = attr.as_float();
                        }
                        else if ( strcmp( attr.name(), "xloc" ) == 0 )
                        {
                            xloc = attr.as_float();
                        }
                        else if ( strcmp( attr.name(), "yloc" ) == 0 )
                        {
                            yloc = attr.as_float();
                        }
                        else
                        {
                        	printf("You spelled something wrong \n");
                        }
                    }
                    if ( !hasError )
                    {
                        paramVector.emplace_back( new PrimitiveParams( primitiveType,
                                                                       time,
                                                                       distance,
                                                                       xloc,
                                                                       yloc,
                                                                       heading,
                                                                       startDriveSpeed,
                                                                       endDriveSpeed ) );
                    }
                }
            }
        }
    }
    else
    {
        printf("Errors parsing file %s\n", fileName.c_str() );
        printf("Error %s \n", result.description() );

    }

    return paramVector;
}
