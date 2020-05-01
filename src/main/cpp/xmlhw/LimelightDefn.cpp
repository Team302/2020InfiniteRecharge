/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include <string>
#include "xmlhw/LimelightDefn.h"
#include "hw/DragonLimelight.h"
#include "utils/HardwareIDValidation.h"
#include "utils/UsageValidation.h"
#include "utils/Logger.h"
#include <hw/factories/LimelightFactory.h>

#include <pugixml/pugixml.hpp>

using namespace std;

DragonLimelight* LimelightDefn::ParseXML(pugi::xml_node    limelightNode)
{
    // initialize the output
    DragonLimelight* limelight = nullptr;

    bool hasError = false;

    // initialize attributes to default values
    IDragonSensor::SENSOR_USAGE usage = IDragonSensor::SENSOR_USAGE::UNKNOWN_SENSOR;
    std::string tableName = "";
    double mountingHeight = 0.0;
    double horizontalOffset = 0.0;
    double mountingAngle = 0.0;
    double rotation = 0.0;
    double targetHeight = 0.0;
    double targetHeight2 = 0.0;

    DragonLimelight::LED_MODE ledMode = DragonLimelight::LED_MODE::LED_DEFAULT;
    DragonLimelight::CAM_MODE camMode = DragonLimelight::CAM_MODE::CAM_VISION;
    DragonLimelight::STREAM_MODE streamMode = DragonLimelight::STREAM_MODE::STREAM_DEFAULT;
    DragonLimelight::SNAPSHOT_MODE snapMode = DragonLimelight::SNAPSHOT_MODE::SNAP_OFF;
    double defaultXHairX = -2.0;
    double defaultXHairY = -2.0;
    double secXHairX = -2.0;
    double secXHairY = -2.0;

    for (pugi::xml_attribute attr = limelightNode.first_attribute(); attr && !hasError; attr = attr.next_attribute())
    {
        // validate/set the usage
        if ( strcmp( attr.name(), "usage" ) == 0 )
        {
            usage = UsageValidation::ValidateSensorUsage( attr.value(), "LimelightDefn::ParseXML");
            if ( usage == IDragonSensor::SENSOR_USAGE::UNKNOWN_SENSOR)
            {
                hasError = true;
            }
        }
        else if ( strcmp( attr.name(), "tablename" ) == 0 )
        {
            tableName = attr.value();
        }
        else if ( strcmp( attr.name(), "mountingheight" ) == 0 )
        {
            mountingHeight = attr.as_double();
        }
        else if ( strcmp( attr.name(), "horizontaloffset" ) == 0 )
        {
            horizontalOffset = attr.as_double();
        }
        else if ( strcmp( attr.name(), "mountingangle" ) == 0 )
        {
            mountingAngle = attr.as_double();
        }
        else if ( strcmp( attr.name(), "rotation" ) == 0 )
        {
            rotation = attr.as_double();
        }
		//todo: should this come from state XMLs
        else if ( strcmp( attr.name(), "targetheight" ) == 0 )
        {
            targetHeight = attr.as_double();
        }
        else if ( strcmp( attr.name(), "targetheight2" ) == 0 )
        {
            targetHeight2 = attr.as_double();
        }
        else if ( strcmp( attr.name(), "defaultledmode" ) == 0 )
        {
            if ( strcmp( attr.value(), "currentpipeline") == 0 )
            {
                ledMode = DragonLimelight::LED_MODE::LED_DEFAULT;
            }
            else if ( strcmp( attr.value(), "off") == 0 )
            {
                ledMode = DragonLimelight::LED_MODE::LED_OFF;
            }
            else if ( strcmp( attr.value(), "blink") == 0 )
            {
                ledMode = DragonLimelight::LED_MODE::LED_BLINK;
            }
            else if ( strcmp( attr.value(), "on") == 0 )
            {
                ledMode = DragonLimelight::LED_MODE::LED_ON;
            }
        }        
        else if ( strcmp( attr.name(), "defaultcammode" ) == 0 )
        {
            if ( strcmp( attr.value(), "drivercamera")==0)
            {
                camMode = DragonLimelight::CAM_MODE::CAM_DRIVER;
            }
        }        
        else if ( strcmp( attr.name(), "streammode" ) == 0 )
        {
            if ( strcmp( attr.value(), "pipmain") == 0 )
            {
                streamMode = DragonLimelight::STREAM_MODE::STREAM_MAIN_AND_SECOND;
            }
            else if ( strcmp( attr.value(), "pipsecondary" ) == 0 )
            {
                streamMode = DragonLimelight::STREAM_MODE::STREAM_SECOND_AND_MAIN;
            }
        }        
        else if ( strcmp( attr.name(), "snapshots" ) == 0 )
        {
            if ( strcmp( attr.value(), "twopersec") == 0 )
            {
                snapMode = DragonLimelight::SNAPSHOT_MODE::SNAP_ON;
            }
        }
        else if ( strcmp( attr.name(), "crosshairx" ) == 0 )
        {
            defaultXHairX = attr.as_double();
        }        
        else if ( strcmp( attr.name(), "crosshairy" ) == 0 )
        {
            defaultXHairY = attr.as_double();
        }        
        else if ( strcmp( attr.name(), "secondcrosshairx" ) == 0 )
        {
            secXHairX = attr.as_double();
        }        
        else if ( strcmp( attr.name(), "secondcrosshairy" ) == 0 )
        {
            secXHairY = attr.as_double();
        }


		//todo:  add cross hair stuff/streaming options -- everything after target heights
        else
        {
            string msg = "unknown attribute ";
            msg += attr.name();
            Logger::GetLogger()->LogError( "LimelightDefn::ParseXML", msg );
            hasError = true;
        }

        if(!hasError)
        {
            limelight = LimelightFactory::GetLimelightFactory()->CreateLimelight
            (
                usage,
                tableName,
                mountingHeight,
                horizontalOffset,
                rotation,
                mountingAngle,
                targetHeight,
                targetHeight2,
                ledMode,
                camMode,
                streamMode,
                snapMode,
                defaultXHairX,
                defaultXHairY,
                secXHairX,
                secXHairY
            );
        }
    }
    return limelight;
}