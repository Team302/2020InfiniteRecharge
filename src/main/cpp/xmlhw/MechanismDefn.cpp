
//====================================================================================================================================================
/// Copyright 2019 Lake Orion Robotics FIRST Team 302
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
/// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
/// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
/// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================

//========================================================================================================
/// @class MechansimDefn
/// @brief Create a mechaism from an XML definition 
//========================================================================================================

// C++ Includes
#include <memory>
#include <string>
#include <utility>

// FRC includes
#include <frc/AnalogInput.h>
#include <frc/SmartDashboard/SmartDashboard.h>

// Team 302 includes
#include <subsys/MechanismFactory.h>
#include <subsys/IMechanism.h>

#include <hw/usages/IDragonMotorControllerMap.h>
#include <hw/usages/AnalogInputMap.h>
#include <hw/usages/DigitalInputMap.h>
#include <hw/usages/DragonSolenoidMap.h>
#include <hw/usages/ServoMap.h>

#include <xmlhw/AnalogInputDefn.h>
#include <xmlhw/CanCoderDefn.h>
#include <xmlhw/DigitalInputDefn.h>
#include <xmlhw/MotorDefn.h>
#include <xmlhw/ServoDefn.h> 
#include <xmlhw/SolenoidDefn.h>

#include <subsys/IMechanism.h>
#include <subsys/MechanismTypes.h>

#include <utils/Logger.h>

#include <xmlhw/MechanismDefn.h>
#include <xmlhw/ColorSensorDefn.h>
#include <hw/interfaces/IDragonMotorController.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>
#include <rev/ColorSensorV3.h>


using namespace frc;
using namespace pugi;
using namespace std;



/// @brief  Parse a Mechanism XML element and create an IMechanism from its definition.
/// @return IMechanism*   pointer to the mechanism
IMechanism* MechanismDefn::ParseXML
(
    xml_node      mechanismNode
)
{
    // initialize outputs
    IMechanism* mech = nullptr;

    // initialize attributes
    MechanismTypes::MECHANISM_TYPE type = MechanismTypes::UNKNOWN_MECHANISM;

    bool hasError       = false;

    // Parse/validate xml
    for (xml_attribute attr = mechanismNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(), "type" ) == 0 )
        {
            string typeStr = attr.as_string();
            for_each( typeStr.begin(), typeStr.end(), [](char & c){c = ::toupper(c);});

            if ( typeStr.compare( "INTAKE") == 0 )
            {
                type = MechanismTypes::MECHANISM_TYPE::INTAKE;
            }
            else if ( typeStr.compare( "IMPELLER") == 0 )
            {
                type = MechanismTypes::MECHANISM_TYPE::IMPELLER;
            }
            else if ( typeStr.compare( "BALL_TRANSFER") == 0 )
            {
                type = MechanismTypes::MECHANISM_TYPE::BALL_TRANSFER;
            }
            else if ( typeStr.compare( "SHOOTER") == 0 )
            {
                type = MechanismTypes::MECHANISM_TYPE::SHOOTER;
            }
            else if ( typeStr.compare( "SHOOTER_HOOD") == 0 )
            {
                type = MechanismTypes::MECHANISM_TYPE::SHOOTER_HOOD;
            }
            else if ( typeStr.compare( "TURRET") == 0 )
            {
                type = MechanismTypes::MECHANISM_TYPE::TURRET;
            }
            else if ( typeStr.compare( "CONTROL_TABLE_MANIPULATOR") == 0 )
            {
                type = MechanismTypes::MECHANISM_TYPE::CONTROL_TABLE_MANIPULATOR;
            }
            else if ( typeStr.compare( "CLIMBER") == 0 )
            {
                type = MechanismTypes::MECHANISM_TYPE::CLIMBER;
            }
            else if ( typeStr.compare( "CRAWLER") == 0 )
            {
                type = MechanismTypes::MECHANISM_TYPE::CRAWLER;
            }
            else if ( typeStr.compare( "HOOK_DELIVERY") == 0 )
            {
                type = MechanismTypes::MECHANISM_TYPE::HOOK_DELIVERY;
            }
            else
            {
                    string msg = "unknown Mechanism type ";
                    msg += attr.value();
                    Logger::GetLogger()->LogError( "MechanismDefn::ParseXML", msg );
                    hasError = true;
            }
        }
        else
        {
            string msg = "invalid attribute ";
            msg += attr.name();
            Logger::GetLogger()->LogError( "MechanismDefn::ParseXML", msg );
            hasError = true;
        }
    }

    // Parse/validate subobject xml
    unique_ptr<MotorDefn> motorXML = make_unique<MotorDefn>();
    unique_ptr<AnalogInputDefn> analogXML = make_unique<AnalogInputDefn>();
    unique_ptr<DigitalInputDefn> digitalXML = make_unique<DigitalInputDefn>();
    unique_ptr<ServoDefn> servoXML = make_unique<ServoDefn>();
    unique_ptr<SolenoidDefn> solenoidXML = make_unique<SolenoidDefn>();
    unique_ptr<ColorSensorDefn> colorXML = make_unique<ColorSensorDefn>();
    unique_ptr<CanCoderDefn> cancoderXML = make_unique<CanCoderDefn>();

    IDragonMotorControllerMap motors;
    ServoMap servos;
    DragonSolenoidMap solenoids;
    AnalogInputMap analogInputs;
    DigitalInputMap digitalInputs;
    rev::ColorSensorV3* colorSensor = nullptr;
    shared_ptr<ctre::phoenix::sensors::CANCoder> canCoder = nullptr;

    for (xml_node child = mechanismNode.first_child(); child  && !hasError; child = child.next_sibling())
    {
        if ( strcmp( child.name(), "motor") == 0 )
        {
            auto motor = motorXML.get()->ParseXML(child);
            if ( motor.get() != nullptr )
            {
                motors[ motor.get()->GetType() ] =  motor ;
            }
        }
        else if ( strcmp( child.name(), "analogInput") == 0 )
        {
            auto analogIn = analogXML->ParseXML(child);
            if ( analogIn.get() != nullptr )
            {
                analogInputs[analogIn.get()->GetUsage()] = analogIn;
            }
        }
        else if ( strcmp( child.name(), "digitalInput") == 0 )
        {
            auto digitalIn = digitalXML->ParseXML(child);
            if ( digitalIn.get() != nullptr )
            {
                digitalInputs[digitalIn.get()->GetType()] = digitalIn;
            }
        }
        else if ( strcmp( child.name(), "servo") == 0 )
        {
            auto servo = servoXML->ParseXML(child);
            if ( servo.get() != nullptr )
            {
                servos[servo.get()->GetUsage()] = servo;
            }
        }
        else if ( strcmp( child.name(), "solenoid" ) == 0 )
        {
            auto sol = solenoidXML->ParseXML(child);
            if ( sol.get() != nullptr )
            {
                solenoids[sol.get()->GetType()] = sol;
            }
        }
        else if ( strcmp( child.name(), "canCoder" ) == 0)
        {
            canCoder = cancoderXML.get()->ParseXML(child);
        }
        else if ( strcmp( child.name(), "colorsensor" ) == 0 )
        {
            colorSensor = colorXML.get()->ParseXML(child);
        }
        else
        {
            string msg = "unknown child ";
            msg += child.name();
            Logger::GetLogger()->LogError( string("MechanismDefn"), msg );
        }
    }


    // create instance
    if ( !hasError )
    {
        MechanismFactory* factory =  MechanismFactory::GetMechanismFactory();
        mech = factory->CreateIMechanism( type, motors, solenoids, servos, digitalInputs, analogInputs, colorSensor, canCoder );
    }

    return mech;
}
