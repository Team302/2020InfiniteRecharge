//====================================================================================================================================================
// ControlDataDefn.h
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
#include <map>

// FRC includes

// Team 302 includes
#include <controllers/ControlData.h>
#include <xmlmechdata/ControlDataDefn.h>
#include <controllers/ControlModes.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>

using namespace pugi;
using namespace std;

/// @brief Parse MechanismData XML element 
/// @param [in] pugi::xml_node mechanism data node
/// @return ControlData* mechanism control data
ControlData* ControlDataDefn::ParseXML
(
    xml_node      PIDNode
)
{
    // initialize output
    ControlData* data = nullptr;

    // initialize attributes to default values
    string identifier;
    ControlModes::CONTROL_TYPE mode = ControlModes::CONTROL_TYPE::PERCENT_OUTPUT;
	ControlModes::CONTROL_RUN_LOCS server = ControlModes::CONTROL_RUN_LOCS::MOTOR_CONTROLLER;

    double p = 0.0;
    double i = 0.0;
    double d = 0.0;
    double f = 0.0;
    double izone = 0.0;
    double maxAccel = 0.0;
    double cruiseVel = 0.0;
    double peak = 1.0;
    double nominal = 1.0;
	
	map<string, ControlModes::CONTROL_TYPE> modeMap;
	modeMap[string("PERCENT_OUTPUT")] = ControlModes::CONTROL_TYPE::PERCENT_OUTPUT;
	modeMap[string("VELOCITY_INCH")]  = ControlModes::CONTROL_TYPE::VELOCITY_INCH;
	modeMap[string("VELOCITY_DEGREES")] = ControlModes::CONTROL_TYPE::VELOCITY_DEGREES;
	modeMap[string("VELOCITY_RPS")]  = ControlModes::CONTROL_TYPE::VELOCITY_RPS;
	modeMap[string("VOLTAGE")] = ControlModes::CONTROL_TYPE::VOLTAGE;
    modeMap[string("CURRENT")] = ControlModes::CONTROL_TYPE::CURRENT;
	modeMap[string("TRAPEZOID")] = ControlModes::CONTROL_TYPE::TRAPEZOID;
	modeMap[string("MOTION_PROFILE")] = ControlModes::CONTROL_TYPE::MOTION_PROFILE;
    modeMap[string("MOTION_PROFILE_ARC")] = ControlModes::CONTROL_TYPE::MOTION_PROFILE_ARC;
	modeMap[string("PERCENT_OUTPUT")] = ControlModes::CONTROL_TYPE::PERCENT_OUTPUT;
    modeMap[string("POSITION_DEGREES")] = ControlModes::CONTROL_TYPE::POSITION_DEGREES;
	
	map<string, ControlModes::CONTROL_RUN_LOCS> serverMap;
	serverMap[string("MOTORCONTROLLER")] = ControlModes::CONTROL_RUN_LOCS::MOTOR_CONTROLLER;
	serverMap[string("ROBORIO")] = ControlModes::CONTROL_RUN_LOCS::ROBORIO;
    
	bool hasError = false;

    // parse/validate xml
    for (pugi::xml_attribute attr = PIDNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(), "identifier") == 0 )
        {
            identifier = string( attr.value() );
        }
        else if ( strcmp( attr.name(), "mode" ) == 0 )
        {
			auto it = modeMap.find( string(attr.value() ) );
			if ( it != modeMap.end() )
			{
				mode = it->second;
			}
        }
		else if ( strcmp( attr.name(), "constrolServer" ) == 0 )
		{
			auto itr = serverMap.find( string( attr.value() ) );
			if ( itr != serverMap.end() )
			{
				server = itr->second;
			}
		}				
        else if ( strcmp( attr.name(), "proportional") == 0 )
        {
            p = attr.as_double();
        }       
        else if ( strcmp( attr.name(), "integral") == 0 )
        {
            i = attr.as_double();
        }        
        else if ( strcmp( attr.name(), "derivative") == 0 )
        {
            d = attr.as_double();
        }        
        else if ( strcmp( attr.name(), "feedforward") == 0 )
        {
            f = attr.as_double();
        }        
        else if ( strcmp( attr.name(), "izone") == 0 )
        {
            izone = attr.as_double();
        }
        else if ( strcmp( attr.name(), "maxacceleration") == 0 )
        {
            maxAccel = attr.as_double();
        }
        else if ( strcmp( attr.name(), "cruisevelocity") == 0 )
        {
            cruiseVel = attr.as_double();
        }
        else if ( strcmp( attr.name(), "peak") == 0 )
        {
            peak = attr.as_double();
        }
        else if ( strcmp( attr.name(), "nominal") == 0 )
        {
            nominal = attr.as_double();
        }
        else
        {
            printf( "==>> ControlDataDefn::ParseXML invalid attribute %s \n", attr.name() );
            hasError = true;
        }
    }
    if ( !hasError )
    {
        data = new ControlData( mode, server, identifier, p, i, d, f, izone, maxAccel, cruiseVel, peak, nominal );
    }
    return data;
}


