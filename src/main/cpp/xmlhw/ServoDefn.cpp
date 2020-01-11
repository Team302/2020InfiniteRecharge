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


// Third Party Includes
#include <pugixml/pugixml.hpp>

using namespace std;

    //-----------------------------------------------------------------------
    // Method:      ParseXML
    // Description: Parse a servo XML element and create a DragonServo from
    //              its definition.
    //
    //
    //<!-- ====================================================
    //     servo usage options
    //     ====================================================
    //        enum SERVO_USAGE
    //        {
    //            UNKNOWN_SERVO_USAGE = -1,
    //            SERVO_SIDEBAR_RELEASE_1,
    //            SERVO_SIDEBAR_RELEASE_2,
    //            MAX_SERVO_USAGES
    //        };
    //
    //
    //     ==================================================== -->
    //<!ELEMENT servo EMPTY>
    //<!ATTLIST servo
    //          usage             (  0 |  1 | 2 ) "0"
    //          pwmId             (  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |
    //                              10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 ) "0"
    //          minAngle          CDATA "0.0"
    //          maxAngle          CDATA "180.0"
    //>
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
        DragonServo::SERVO_USAGE usage = DragonServo::UNKNOWN_SERVO_USAGE;
        double minAngle = 0.0;
        double maxAngle = 360.0;

        bool hasError = false;

        // parse/validate the xml
        for (pugi::xml_attribute attr = ServoNode.first_attribute(); attr && !hasError; attr = attr.next_attribute())
        {
            if ( strcmp( attr.name(), "usage" ) == 0 )
            {
                int iVal = attr.as_int();
                switch ( iVal )
                {
                    case DragonServo::ROTATE_LIMELIGHT:
                        usage = DragonServo::ROTATE_LIMELIGHT;
                        break;

                    case DragonServo::TAIL_CONTROL:
                        usage = DragonServo::TAIL_CONTROL;
                        break;

                    default:
                        printf( "==>> Invalid servo usage %d \n", iVal );
                        hasError = true;
                        break;
                }
            }
            else if ( strcmp( attr.name(), "pwmId" ) == 0 )
            {
                pwmID = attr.as_int();
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
