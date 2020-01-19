
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

#include <xmlhw/AnalogInputDefn.h>
#include <xmlhw/DigitalInputDefn.h>
#include <xmlhw/MotorDefn.h>
#include <xmlhw/ServoDefn.h> 

#include <subsys/IMechanism.h>
#include <subsys/MechanismTypes.h>

#include <utils/Logger.h>

#include <xmlhw/MechanismDefn.h>
#include <hw/interfaces/IDragonMotorController.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>

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

    unique_ptr<MotorDefn> motorXML;
    unique_ptr<AnalogInputDefn> analogXML;
    unique_ptr<DigitalInputDefn> digitalXML;
    unique_ptr<ServoDefn> servoXML;

    // Parse/validate xml
    for (xml_attribute attr = mechanismNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(), "type" ) == 0 )
        {
            string typeStr = attr.as_string();
            for_each( typeStr.begin(), typeStr.end(), [](char & c){c = ::toupper(c);});

            if ( typeStr.compare( "CHASSIS") == 0 )
            {
                type = MechanismTypes::MECHANISM_TYPE::WRIST;
            }
            else if ( typeStr.compare( "SHOOTER") == 0 )
            {
                type = MechanismTypes::MECHANISM_TYPE::SHOOTER;
            }
            else if ( typeStr.compare( "ELEVATOR") == 0 )
            {
                type = MechanismTypes::MECHANISM_TYPE::ELEVATOR;
            }
            else if ( typeStr.compare( "WRIST") == 0 )
            {
                type = MechanismTypes::MECHANISM_TYPE::WRIST;
            }
            else if ( typeStr.compare( "INTAKE") == 0 )
            {
                type = MechanismTypes::MECHANISM_TYPE::INTAKE;
            }
            else if ( typeStr.compare( "ARM") == 0 )
            {
                type = MechanismTypes::MECHANISM_TYPE::ARM;
            }            
            else if ( typeStr.compare( "EXTENDER") == 0 )
            {
                type = MechanismTypes::MECHANISM_TYPE::EXTENDER;
            }
            else if ( typeStr.compare( "CLIMBER") == 0 )
            {
                type = MechanismTypes::MECHANISM_TYPE::CLIMBER;
            }
            else if ( typeStr.compare( "BEAK") == 0 )
            {
                type = MechanismTypes::MECHANISM_TYPE::BEAK;
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
    IDragonMotorControllerMap motors;
    for (xml_node child = mechanismNode.first_child(); child  && !hasError; child = child.next_sibling())
    {
        if ( strcmp( child.name(), "motor") == 0 )
        {
            if ( motorXML == nullptr )
            {
                motorXML = make_unique<MotorDefn>();
            }

            if ( motorXML != nullptr )
            {
                auto motor = motorXML->ParseXML(child);
                if ( motor.get() != nullptr )
                {
                    motors[ motor.get()->GetType() ] =  motor ;
                }
            }
            else
            {
                Logger::GetLogger()->LogError( "MechanismDefn", "unable to create MotorDefn" );
            }
        }
        else if ( strcmp( child.name(), "analogInput") == 0 )
        {
            if ( analogXML == nullptr )
            {
                analogXML = make_unique<AnalogInputDefn>();
            }

            if ( analogXML != nullptr )
            {
                auto analogIn = analogXML->ParseXML(child);
            }
            else
            {
                Logger::GetLogger()->LogError( "MechanismDefn", "unable to create AnalogInputDefn" );
            }
        }
        else if ( strcmp( child.name(), "digitalInput") == 0 )
        {
            if ( digitalXML == nullptr )
            {
                digitalXML = make_unique<DigitalInputDefn>();
            }

            if ( digitalXML != nullptr )
            {
                auto digitalIn = digitalXML->ParseXML(child);
            }
            else
            {
                Logger::GetLogger()->LogError( "MechanismDefn", "unable to create DigitalInputDefn" );
            }
        }
        else if ( strcmp( child.name(), "servo") == 0 )
        {
            if ( servoXML == nullptr )
            {
                servoXML = make_unique<ServoDefn>();
            }

            if ( servoXML != nullptr )
            {
                servoXML->ParseXML(child);
            }
            else
            {
                Logger::GetLogger()->LogError( "MechanismDefn", "unable to create ServoDefn" );
            }
        }
        else if ( strcmp( child.name(), "solenoid" ) == 0 )
        {
            // todo parse solenoids
        }
        else
        {
                Logger::GetLogger()->LogError( "MechanismDefn", "unknown child" );
        }
    }


    // create instance
    if ( !hasError )
    {
        MechanismFactory* factory =  MechanismFactory::GetMechanismFactory();
        mech = factory->GetIMechanism( type );
    }

    return mech;
}
