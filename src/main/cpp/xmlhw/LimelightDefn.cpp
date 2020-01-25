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

#include <pugixml/pugixml.hpp>

using namespace std;

std::shared_ptr<DragonLimelight> LimelightDefn::ParseXML(pugi::xml_node    limelightNode)
{
    // initialize the output
    shared_ptr<DragonLimelight> limelight = nullptr;

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
        else if ( strcmp( attr.name(), "horizontal offset" ) == 0 )
        {
            horizontalOffset = attr.as_double();
        }
        else if ( strcmp( attr.name(), "mounting angle" ) == 0 )
        {
            mountingAngle = attr.as_double();
        }
        else if ( strcmp( attr.name(), "rotation" ) == 0 )
        {
            rotation = attr.as_double();
        }
        else if ( strcmp( attr.name(), "target height" ) == 0 )
        {
            targetHeight = attr.as_double();
        }
        else if ( strcmp( attr.name(), "target height 2" ) == 0 )
        {
            targetHeight2 = attr.as_double();
        }
        else
        {
            string msg = "unknown attribute ";
            msg += attr.name();
            Logger::GetLogger()->LogError( "LimelightDefn::ParseXML", msg );
            hasError = true;
        }

        if(!hasError)
        {
            limelight = make_shared<DragonLimelight>(usage, tableName, mountingHeight, horizontalOffset, mountingAngle, targetHeight);
            //need to add rotations and targetHeight2 
        }
    }
    return limelight;
}