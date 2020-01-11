
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
#include <string>

// FRC includes
#include <frc/SmartDashboard/SmartDashboard.h>

// Team 302 includes
#include <hw/factories/LidarFactory.h>
#include <hw/DragonLidar.h>
#include <xmlhw/LidarDefn.h>
#include <utils/HardwareIDValidation.h>
#include <utils/UsageValidation.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>

using namespace std;

///----------------------------------------------------------------------------------------------------
/// Method:      ParseXML
/// @brief       Parse a lidar XML element and create a DragonLidar object from its definition.
///
/// @param [in]  pugi::xml_node                input lidar node in the xml file
/// @return      
///              std::shared_ptr<DragonLidar>  pointer to the DragonLidar or nullptr if invalid inputs
///----------------------------------------------------------------------------------------------------
std::shared_ptr<DragonLidar> LidarDefn::ParseXML
(
    pugi::xml_node      lidarNode       
)
{
    // initialize the output
    shared_ptr<DragonLidar> lidar = nullptr;

    bool hasError = false;


    // initialize attributes to default values
    IDragonSensor::SENSOR_USAGE usage   = IDragonSensor::SENSOR_USAGE::UNKNOWN_SENSOR;
    int                      inputPin   = 0;
    int                      triggerPin = 0;

    // loop through the attributes, validating their values and updating the local variables,  if there
    // is an invalid attribute value, stop processing the attributes (set that there is an error)
    for (pugi::xml_attribute attr = lidarNode.first_attribute(); attr && !hasError; attr = attr.next_attribute())
    {
        // validate/set the usage
        if ( strcmp( attr.name(), "usage" ) == 0 )
        {
            usage = UsageValidation::ValidateSensorUsage( attr.value(), "LidarDefn::ParseXML");
            if ( usage == IDragonSensor::SENSOR_USAGE::UNKNOWN_SENSOR)
            {
                hasError = true;
            }
        }

        // validate/set the input pin
        else if ( strcmp( attr.name(), "inputpin" ) == 0 )
        {
            int iVal = attr.as_int();
            hasError = HardwareIDValidation::ValidateDIOID( iVal, string( "LidarDefn::ParseXML(input pin)" ) );
        }

        // validate/set the trigger pin
        else if ( strcmp( attr.name(), "triggerpin" ) == 0 )
        {
            int iVal = attr.as_int();
            hasError = HardwareIDValidation::ValidateDIOID( iVal, string( "LidarDefn::ParseXML(trigger pin)" ) );
        }

        // everything else is an unknown attribute; write an error
        else
        {
            string msg = "unknown attribute ";
            msg += attr.name();
            Logger::GetLogger()->LogError( "LidarDefn::ParseXML", msg );
            hasError = true;
        }
    }

    // if there aren't any errors create the lidar
    if ( !hasError )
    {
        lidar = LidarFactory::GetLidarFactory()->CreateLidar( usage, inputPin, triggerPin );
    }

    return lidar;
}
