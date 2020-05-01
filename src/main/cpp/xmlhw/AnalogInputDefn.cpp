
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

/// --------------------------------------------------------------------------------------------
/// @class AnalogInputDefn
/// @brief 
///        Create an AnalogInput from an XML definition
/// --------------------------------------------------------------------------------------------

// C++ includes
#include <memory>
#include <string>

// FRC includes
#include <frc/AnalogInput.h>

// Team302 includes
#include <hw/factories/AnalogInputFactory.h>
#include <hw/DragonAnalogInput.h>
#include <utils/Logger.h>
#include <xmlhw/AnalogInputDefn.h>

// Third Party includes
#include <pugixml/pugixml.hpp>


using namespace frc;
using namespace std;
using namespace pugi;

///-----------------------------------------------------------------------------------------------------
/// Method:      ParseXML
/// @brief       Parse a analogSensor XML element and create a DragonAnalogInput from its definition.
/// @return      
///              shared_ptr<DragonAnalogInput> AnalogInput (or nullptr if XML is ill-formed)
///-----------------------------------------------------------------------------------------------------
shared_ptr<DragonAnalogInput> AnalogInputDefn::ParseXML
(
    xml_node      analogInputNode
)
{
    shared_ptr<DragonAnalogInput> sensor;
	string  type;
	int 	analogID = 0;
    float	voltageMin = 0.0;
    float	voltageMax = 5.0;
    float 	outputMin  = 0.0;
    float	outputMax  = 1.0;

    bool hasError = false;

    for (xml_attribute attr = analogInputNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(), "type" ) == 0 )
        {
            type = attr.as_string();
        }
        else if ( strcmp( attr.name(), "analogId" ) == 0 )
        {
        	analogID = attr.as_int();
        }
        else if ( strcmp( attr.name(), "voltageMin" ) == 0 )
        {
        	voltageMin = attr.as_float();
        }
        else if ( strcmp( attr.name(), "voltageMax" ) == 0 )
        {
        	voltageMax = attr.as_float();
        }
        else if ( strcmp( attr.name(), "outputMin" ) == 0 )
        {
        	outputMin = attr.as_float();
        }
        else if ( strcmp( attr.name(), "outputMax" ) == 0 )
        {
        	outputMax = attr.as_float();
        }
        else
        {
            string msg = "invalid attribute";
            msg += attr.name();
            Logger::GetLogger()->LogError( "AnalogInputDefn::ParseXML", msg );
            hasError = true;
        }
    }

    if ( !hasError )
    {
        auto factory  = AnalogInputFactory::GetFactory();
        sensor = factory->CreateInput( type, analogID, voltageMin, voltageMax, outputMin, outputMax );
    }

    return sensor;
}
