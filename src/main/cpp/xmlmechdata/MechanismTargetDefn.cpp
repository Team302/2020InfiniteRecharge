
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
#include <cstring>

// FRC includes

// Team 302 includes
#include <controllers/MechanismTargetData.h>
#include <xmlmechdata/MechanismTargetDefn.h>
#include <utils/Logger.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>

using namespace std;
using namespace pugi;


/// @brief      Parse MechanismTargetData XML element 
/// @param [in] pugi::xml_node  mechanism data node
/// @return     MechanismTargetData*       mechanism data
MechanismTargetData*  MechanismTargetDefn::ParseXML
(
    xml_node      MechanismDataNode
)
{
    // initialize output
    MechanismTargetData* mechData = nullptr;

    bool hasError = false;

    string stateName;
    string controllerIdentifier;
    double target = 0.0;
    MechanismTargetData::SOLENOID solenoid = MechanismTargetData::SOLENOID::NONE; 
    string failoverControllerIdentifier;
    double failoverTarget = 0.0;

    // parse/validate xml
    for (xml_attribute attr = MechanismDataNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(), "stateIdentifier" ) == 0 )
        {
            stateName = string( attr.value() );
        }
        else if ( strcmp( attr.name(), "controlDataIdentifier" ) == 0 )
        {
            controllerIdentifier = string( attr.value() );
        }
        else if ( strcmp( attr.name(), "value") == 0 )
        {
            target = attr.as_double();
        }
        else if( strcmp( attr.name(), "solenoid" ) == 0 )
        {
            auto val = attr.value();
            if(strcmp(val, "ON") == 0)
            {
                solenoid = MechanismTargetData::SOLENOID::ON;
            }
            else if ( strcmp(val, "OFF") == 0)
            {
                solenoid = MechanismTargetData::SOLENOID::OFF;
            }
            else if( strcmp(val, "NONE") == 0)
            {
                solenoid = MechanismTargetData::SOLENOID::NONE;
            }
            else
            {
                Logger::GetLogger()->LogError( string("MechanismTargetDefn::ParseXML"), string("solenoid enum"));
            }
        }
        else if ( strcmp( attr.name(), "failoverControlDataIdentifier") == 0 )
        {
            failoverControllerIdentifier = string( attr.value() );
        }
        else if ( strcmp( attr.name(), "failoverValue") == 0 )
        {
            failoverTarget = attr.as_double();
        }
        else
        {
            string msg = "unknown attribute ";
            msg += attr.name();
            Logger::GetLogger()->LogError( string("MechanismTargetDefn::ParseXML"), msg );
            hasError = true;
        }
    }

    if ( !hasError && !stateName.empty() && !controllerIdentifier.empty() )
    {
        mechData = new MechanismTargetData( stateName, controllerIdentifier, target, solenoid, failoverControllerIdentifier, failoverTarget );
    }
    else
    {
        Logger::GetLogger()->LogError( string("MechanismTargetDefn::ParseXML"), string("incomplete date"));
    }
    
    return mechData;
}


