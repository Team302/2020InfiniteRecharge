// c++ Includes 
#include <iostream>

//FRC includes
#include <frc/SmartDashboard/SmartDashboard.h>

//Team 302 includes
#include <xmlhw/TalonTach.h>
#include <hw/DragonTalonTach.h>

//Third Party Includes

#include <pugixml/pugixml.hpp>

//<!-- ====================================================
//	 TalonTach usage 
//	 ====================================================
//	 enum TALON_TACH_USAGE
///	 {
//	 	  UNKNOWN_TALON_TACH_USAGE = -1
//        MIN_WRIST_ANGLE,
//        MAX_WRIST_ANGLE,
//        TOP_HATCH_PRESENT,
//        BOTTOM_HATCH_PRESENT,
//        ARM_BOTTOM,
//        ARM_TOP
//        MAX_TALON_TACH_USAGE
//	 };
//	 ==================================================== -->
//<!ELEMENT talontach EMPTY>
//<!ATTLIST talontach 
//          canId             (  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 
//                              10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 
//                              20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 
//                              30 | 31 | 32 | 33 | 34 | 35 | 36 | 37 | 38 | 39 | 
//                              40 | 41 | 42 | 43 | 44 | 45 | 46 | 47 | 48 | 49 | 
//                              50 | 51 | 52 | 53 | 54 | 55 | 56 | 57 | 58 | 59 | 
//                              60 | 61 | 62 ) "0"
//          generalpin             (  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 
//                              10 | 11 )"0"
//
//  Returns:    DragonTachTalon        
//>

DragonTalonTach* TalonTachDefn::ParseXML// Node is where it takes the thing from robot.dtd talontach
(
    pugi::xml_node      talontachNode
)
{
    DragonTalonTach*         talontach = nullptr;

    DragonTalonTach::TALON_TACH_USAGE usage = DragonTalonTach::UNKNOWN_TALON_TACH_USAGE;
    int canID = 0;
    ctre::phoenix::CANifier::GeneralPin generalpin;
    
    bool reversed = false;

    bool hasError = false;
 
    //parse/validate xml
    for(pugi::xml_attribute attr = talontachNode.first_attribute(); attr; attr = attr.next_attribute()) //attributes for the talon tach
    {
        if (strcmp(attr.name(), "usage" ) == 0) // attribute usage.  Usage is for using things like a digital input and type is for differnt types like mechanisms.
        {
            int iVal = attr.as_int();
            switch (iVal) // enum for the things the talon tach is going to do 
            {
                case  DragonTalonTach::TALON_TACH_USAGE::MAX_WRIST_ANGLE:
                    usage = DragonTalonTach::TALON_TACH_USAGE::MAX_WRIST_ANGLE;
                    break;
                case DragonTalonTach::TALON_TACH_USAGE::MIN_WRIST_ANGLE:
                    usage = DragonTalonTach::TALON_TACH_USAGE::MIN_WRIST_ANGLE;
                    break;
                case DragonTalonTach::TALON_TACH_USAGE::TOP_HATCH_PRESENT:
                    usage = DragonTalonTach::TALON_TACH_USAGE::TOP_HATCH_PRESENT;
                    break;
                case DragonTalonTach::TALON_TACH_USAGE::BOTTOM_HATCH_PRESENT:
                    usage = DragonTalonTach::TALON_TACH_USAGE::BOTTOM_HATCH_PRESENT;
                    break;
                case DragonTalonTach::TALON_TACH_USAGE::ARM_BOTTOM:
                    usage = DragonTalonTach::TALON_TACH_USAGE::ARM_BOTTOM;
                    break;
                case DragonTalonTach::TALON_TACH_USAGE::ARM_TOP:
                    usage = DragonTalonTach::TALON_TACH_USAGE::ARM_TOP;
                    break;
            }
        }
        else if ( strcmp( attr.name(), "canId") == 0 ) // attribute canID
        {
           int iVal = attr.as_int(); //value of the ID
           if(iVal > -1 && iVal < 63 )  //Value between 0 and 62
           {
               canID  = attr.as_int();
           }
           else
           {
               printf("==>> TalonTachDefn::ParseXML invalid Can ID %d \n" , iVal); // if the value is not between 0 and 62 cause an error.
               hasError = true;
           }
        }    
        else if (strcmp( attr.name(), "generalpin")) // attribute for general pin.
        {    int iVal = attr.as_int(); // value of the ID
            if (iVal > -1 && iVal < 12) //Value between 0 and 11
            {
                generalpin = (ctre::phoenix::CANifier::GeneralPin)attr.as_int(); 
            }
            else
            {
                printf( "==>> TalonTachDefn::ParseXML invalid General Pin %d \n", iVal ); // if the value is not between 0 and 62 cause an error.
                hasError = true;
            }
        }   
        else if ( strcmp( attr.name(), "reversed" ) == 0 )
        {
            reversed = attr.as_bool();
        }
        else
        {
            printf("==>>TalonTachDefn::ParseXML invalid attribute %s |n" ,attr.name() );
            hasError = true;
        }
    }

    if ( !hasError )
    {
        talontach = new DragonTalonTach (usage, canID, generalpin, reversed );
    }
    return talontach;

}
