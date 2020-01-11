
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

//========================================================================================================
/// @class MotorDefn
/// @brief XML parsing for motor definitions.  This definition will construct the motor controllers.
///     This parsing leverages the 3rd party Open Source Pugixml library (https://pugixml.org/).
//========================================================================================================

// C++ Includes
#include <iostream>
#include <memory>
#include <string>

// FRC includes

// Team 302 includes
#include <hw/DragonTalon.h>
#include <hw/DragonSparkMax.h>
#include <hw/factories/DragonMotorControllerFactory.h>
#include <utils/HardwareIDValidation.h>
#include <utils/Logger.h>


// Third Party Includes
#include <pugixml/pugixml.hpp>

using namespace frc;
using namespace pugi;
using namespace std;

//-----------------------------------------------------------------------
// Method:      ParseXML
// Description: Parse a motor XML element and create a DragonTalon from
//              its definition.
//
//        <!-- ====================================================
//             motor usage options
//             ====================================================
//
//		enum MOTOR_CONTROLLER_USAGE
//		{
//			UNKNOWN_MOTOR_CONTROLLER_USAGE = -1,
//			FRONT_LEFT_DRIVE,
//			MIDDLE_LEFT_DRIVE,
//			BACK_LEFT_DRIVE,
//			FRONT_RIGHT_DRIVE,
//			MIDDLE_RIGHT_DRIVE,
//			BACK_RIGHT_DRIVE,
//			ARM_MASTER,
//			ARM_SLAVE,
//			ARM_EXTENSION,
//			WRIST,
//			INTAKE,
//			ELEVATOR_WINCH,
//			ELEVATOR_DRIVE,
//			MAX_MOTOR_CONTROLLER_USAGES
//		};
//
//
//
//    ====================================================
//    motor sensor types
//    ====================================================
//        enum TALON_SENSOR_TYPE
//        {
//            NO_SENSOR = -1,
//            QUAD_ENCODER,
//            UNKNOWN_SENSOR,
//            ANALOG_POT,
//            ANALOG_ENCODER,
//            ENCODER_RISING,
//            ENCODER_FALLING,
//            CTRE_MAG_ENCODER_RELATIVE,
//            CTRE_MAG_ENCODER_ABSOLUTE,
//            PULSE_WIDTH,
//            MAX_SENSOR_TYPES
//        };
//    ==================================================== -->
//<!ELEMENT motor EMPTY>
//<!ATTLIST motor
//          usage             CDATA #REQUIRED
//          canId             (  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |
//                              10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 |
//                              20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 |
//                              30 | 31 | 32 | 33 | 34 | 35 | 36 | 37 | 38 | 39 |
//                              40 | 41 | 42 | 43 | 44 | 45 | 46 | 47 | 48 | 49 |
//                              50 | 51 | 52 | 53 | 54 | 55 | 56 | 57 | 58 | 59 |
//                              60 | 61 | 62 ) "0"
//          pdpID			  CDATA #IMPLIED
//          type              CDATA #REQUIRED
//          inverted          ( true | false ) "false"
//          sensorInverted    ( true | false ) "false"
//          feedbackDevice    ( -1 | 0  |  2 |  3 |  4 |  5 |  6 |  7 |  8 ) "-1"
//          countsPerRev      CDATA "0"
//          gearRatio         CDATA "1"
//          brakeMode         ( true | false ) "false"
//          slaveTo           CDATA "-1"
//          currentLimiting   CDATA "0"
//>
//
// Returns:     DragonTalon*        motor controller (or nullptr if XML
//                                  is ill-formed
//-----------------------------------------------------------------------
shared_ptr<IDragonMotorController> MotorDefn::ParseXML
(
    xml_node      motorNode
)
{
    // initialize the output
    shared_ptr<IDragonMotorController> controller;

    // initialize attributes to default values
    int canID = 0;
	int pdpID = -1;
	string usage;
    bool inverted = false;
    bool sensorInverted = false;
    ctre::phoenix::motorcontrol::FeedbackDevice  feedbackDevice = ctre::phoenix::motorcontrol::FeedbackDevice::QuadEncoder;
    //TODO:: make sure enum matches defines in dtd
    int countsPerRev = 0;
    float gearRatio = 1;
    bool brakeMode = false;
    int slaveTo = -1;
    int peakCurrentDuration = 0;
    int continuousCurrentLimit = 0;
    int peakCurrentLimit = 0;
    bool enableCurrentLimit = false;

    string mtype;


    bool hasError = false;

    for (xml_attribute attr = motorNode.first_attribute(); attr && !hasError; attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(), "usage" ) == 0 )
        {
             usage = attr.value();
             transform(usage.begin(), usage.end(), usage.begin(), ::toupper);
        }
		// CAN ID 0 thru 62 are valid
        else if ( strcmp( attr.name(), "canId" ) == 0 )
        {
            canID = attr.as_int();
            hasError = HardwareIDValidation::ValidateCANID( canID, string( "MotorDefn::ParseXML" ) );
        }
		// PDP ID 0 thru 15 are valid
        else if ( strcmp( attr.name(), "pdpID" ) == 0 )
        {
            pdpID = attr.as_int();
            hasError = HardwareIDValidation::ValidatePDPID( pdpID, string( "MotorDefn::ParseXML" ) );
        }
		// type:  cantalon, sparkmax_brushless and sparkmax_brushed are valid
        else if ( strcmp( attr.name(), "type" ) == 0 )
        {
            mtype = attr.value();
            transform(mtype.begin(), mtype.end(), mtype.begin(), ::toupper);
        }
		// inverted
        else if ( strcmp( attr.name(), "inverted" ) == 0 )
        {
            inverted = attr.as_bool();
        }
		// sensor inverted
        else if ( strcmp( attr.name(), "sensorInverted" ) == 0 )
        {
            sensorInverted = attr.as_bool();
        }
		else if ( strcmp( attr.name(), "feedbackDevice" ) == 0 )
        {
            auto val = string( attr.value() );
            if ( val.compare( "QUADENCODER") == 0 )
            {
                feedbackDevice = ctre::phoenix::motorcontrol::FeedbackDevice::QuadEncoder;
            }
            else if ( val.compare( "ANALOG") == 0 )
            {
                feedbackDevice = ctre::phoenix::motorcontrol::FeedbackDevice::Analog;
            }
            else if ( val.compare( "TACHOMETER") == 0 )
            {
                feedbackDevice = ctre::phoenix::motorcontrol::FeedbackDevice::Tachometer;
            }
            else if ( val.compare( "PULSEWIDTHENCODERPOSITION") == 0 )
            {
                feedbackDevice = ctre::phoenix::motorcontrol::FeedbackDevice::PulseWidthEncodedPosition;
            }
            else if ( val.compare( "SENSORSUM") == 0 )
            {
                feedbackDevice = ctre::phoenix::motorcontrol::FeedbackDevice::SensorSum;
            }
            else if ( val.compare( "SENSORDIFFERENCE") == 0 )
            {
                feedbackDevice = ctre::phoenix::motorcontrol::FeedbackDevice::SensorDifference;
            }
            else if ( val.compare( "REMOTESENSOR0") == 0 )
            {
                feedbackDevice = ctre::phoenix::motorcontrol::FeedbackDevice::RemoteSensor0;
            }
            else if ( val.compare( "REMOTESENSOR1") == 0 )
            {
                feedbackDevice = ctre::phoenix::motorcontrol::FeedbackDevice::RemoteSensor1;
            }
            else if ( val.compare( "SOFTWAREEMULATEDSENSOR") == 0 )
            {
                feedbackDevice = ctre::phoenix::motorcontrol::FeedbackDevice::SoftwareEmulatedSensor;
            }
            else if ( val.compare( "CTRE_MAGENCODER_ABSOLUTE") == 0 )
            {
                feedbackDevice = ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Absolute;
            }
            else if ( val.compare( "CTRE_MAGENCODER_RELATIVE") == 0 )
            {
                feedbackDevice = ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative;
            }
            else 
            {
                Logger::GetLogger()->LogError( string("MotorDefn::ParseXML "), string("Invalid feedback device"));
            }
        }
		// counts per revolution
        else if ( strcmp( attr.name(), "countsPerRev" ) == 0 )
        {
            countsPerRev = attr.as_int();
        }
		// gear ratio
        else if ( strcmp( attr.name(), "gearRatio" ) == 0 )
        {
            gearRatio = attr.as_float();
        }

		// brake mode (or coast)
        else if ( strcmp( attr.name(), "brakeMode" ) == 0 )
        {
            brakeMode = attr.as_bool();
        }
		// slaveto (existing CAN id of the master motor)
        else if ( strcmp( attr.name(), "slaveTo") == 0 )
        {
            slaveTo = attr.as_int();
        }
		// peak current duration (cantalon)
        else if ( strcmp( attr.name(), "peakCurrentDuration") == 0 )
        {
            peakCurrentDuration = attr.as_int();
        }
		// continuous current duration (cantalon)
        else if ( strcmp( attr.name(), "continuousCurrentLimit") == 0 )
        {
            continuousCurrentLimit = attr.as_int();
        }
		// peak current limit (cantalon)
        else if ( strcmp( attr.name(), "peakCurrentLimit") == 0 )
        {
            peakCurrentLimit = attr.as_int();
        }
		// enable current limiting
        else if ( strcmp( attr.name(), "currentLimiting") == 0 )
        {
            enableCurrentLimit = attr.as_bool();
        }
        else
        {
            printf( "==>>MotorDefn::ParseXML invalid attribute %s \n", attr.name() );
            hasError = true;
        }
    }

    if ( !hasError )
    {
		pdpID = ( pdpID < 0 ) ? canID : pdpID;
        controller = DragonMotorControllerFactory::GetInstance()->CreateMotorController( mtype,
                                                                                         canID,
                                                                                         pdpID,
                                                                                         usage,
                                                                                         inverted,
                                                                                         sensorInverted,
                                                                                         feedbackDevice,
                                                                                         countsPerRev,
                                                                                         gearRatio,
                                                                                         brakeMode,
                                                                                         slaveTo,
                                                                                         peakCurrentLimit,
                                                                                         peakCurrentDuration,
                                                                                         peakCurrentLimit,
                                                                                         enableCurrentLimit );
    }
    return controller;
}


