
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

/// @class OdometryDefn. 
/// @brief Create a Odometry data from an XML definition 

// C++ includes
#include <map>
#include <memory>
#include <string>
#include <utility>


// FRC includes

// Team302 includes
#include <xmlhw/OdometryDefn.h>
#include <xmlhw/LidarDefn.h>
#include <xmlhw/PigeonDefn.h>
#include <utils/Logger.h>

// Third Party includes
#include <pugixml/pugixml.hpp>


using namespace pugi;
using namespace std;



/// @brief  Parse the odometry element (and it children).  When this is done a Odometry object exists.
/// @param [in]  pugi::xml_node the odometry element in the XML document
/// @return void
void OdometryDefn::ParseXML
(
	xml_node      OdometryNode
)
{
    // initialize the attributes to the default values
    double xloc	    = 0.0;
    double yloc     = 0.0;
    double heading  = 0.0;
    bool hasError   = false;

    // process attributes
    for (xml_attribute attr = OdometryNode.first_attribute(); attr && !hasError; attr = attr.next_attribute())
    {
        if ( strcmp( attr.name(), "xloc" ) == 0 )
        {
        	xloc = attr.as_double();
        }
        else if ( strcmp( attr.name(), "yloc" ) == 0 )
        {
        	yloc = attr.as_double();
        }
        else if ( strcmp( attr.name(), "heading" ) == 0 )
        {
        	heading = attr.as_double();
        }
        else   // log errors
        {
            string msg = "unknown attribute ";
            msg += attr.name();
            Logger::GetLogger()->LogError( string("OdometryDefn::ParseXML"), msg );
            hasError = true;
        }
    }

    unique_ptr<PigeonDefn> pigeonXML = make_unique<PigeonDefn>();
    unique_ptr<LidarDefn> lidarXML = make_unique<LidarDefn>();

    // Process child element nodes
    for (xml_node child = OdometryNode.first_child(); child; child = child.next_sibling())
    {
        if (strcmp(child.name(), "pigeon") == 0)
        {
            if ( pigeonXML != nullptr )
            {
                pigeonXML->ParseXML(child);
            }
            else
            {
                Logger::GetLogger()->LogError( string("OdometryDefn::ParseXML"), string("Unable to create PigeonDefn") );
            }
        }
        else if ( strcmp( child.name(), "lidar") == 0 )
        {
            if ( lidarXML != nullptr )
            {
                lidarXML->ParseXML(child);
            }
            else
            {
                Logger::GetLogger()->LogError( string("OdometryDefn::ParseXML"), string("Unable to create LidarDefn") );
            }
        }
        else if ( strcmp( child.name(), "ultrasonic") == 0 )
        {
            // todo add ultrasonic processing
        }
    	else  // log errors
    	{
            string msg = "unknown child ";
            msg += child.name();
            Logger::GetLogger()->LogError( string("OdometryDefn::ParseXML"), msg );
    	}
    }


    // create Odometry instance
    if ( !hasError )
    {
        // todo create the odometry object
    }
}

