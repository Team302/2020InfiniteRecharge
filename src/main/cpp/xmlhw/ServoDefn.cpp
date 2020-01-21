/*
 * ServoDefn.cpp
 */

// C++ Includes
#include <memory>
#include <iostream>

// FRC includes

// Team 302 includes
#include <hw/DragonServo.h>
#include <hw/factories/DragonServoFactory.h>
#include <xmlhw/ServoDefn.h>
#include <hw/usages/ServoUsage.h>
#include <utils/HardwareIDValidation.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>

using namespace std;

    //-----------------------------------------------------------------------
    // Method:      ParseXML
    // Description: Parse a servo XML element and create a DragonServo from
    //              its definition.
    //
    //
    // Returns:     void        
    //-----------------------------------------------------------------------
    shared_ptr<DragonServo> ServoDefn::ParseXML
    (
        pugi::xml_node      ServoNode
    )
    {
        shared_ptr<DragonServo> servo = nullptr; 

        // initialize attributes to default values
        int pwmID = 0;
        ServoUsage::SERVO_USAGE usage = ServoUsage::UNKNOWN_SERVO_USAGE;
        double minAngle = 0.0;
        double maxAngle = 360.0;

        bool hasError = false;

        // parse/validate the xml
        for (pugi::xml_attribute attr = ServoNode.first_attribute(); attr && !hasError; attr = attr.next_attribute())
        {
            if ( strcmp( attr.name(), "usage" ) == 0 )
            {
                usage = ServoUsage::GetInstance()->GetUsage( string( attr.value()));
            }
            else if ( strcmp( attr.name(), "pwmId" ) == 0 )
            {
                pwmID = attr.as_int();
                hasError = HardwareIDValidation::ValidateDIOID( pwmID, string( "ServoDefn::ParseXML(PWM ID)" ) );
            }
            else if ( strcmp( attr.name(), "minAngle" ) == 0 )
            {
                minAngle = attr.as_int();
            }
            else if ( strcmp( attr.name(), "maxAngle" ) == 0 )
            {
                maxAngle = attr.as_int();
            }
            else
            {
                printf( "==>> ServoDefn::ParseXML invalid attribute %s \n", attr.name() );
                hasError = true;
            }
        }

        // create the object
        if ( !hasError )
        {
            servo = DragonServoFactory::GetInstance()->CreateDragonServo( usage, pwmID, minAngle, maxAngle );
        }
        return servo;
    }
