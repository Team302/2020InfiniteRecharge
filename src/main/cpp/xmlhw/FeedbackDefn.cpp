
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

/// @class FeedbackDefn. 
/// @brief Create a Feedback data from an XML definition 

// C++ includes
#include <map>
#include <memory>
#include <string>
#include <utility>


// FRC includes

// Team302 includes
#include <xmlhw/CameraDefn.h>
#include <xmlhw/FeedbackDefn.h>
#include <xmlhw/LEDDefn.h>
#include <utils/Logger.h>

// Third Party includes
#include <pugixml/pugixml.hpp>


using namespace pugi;
using namespace std;



/// @brief  Parse the Feedback element (and it children).  When this is done a Feedback object exists.
/// @param [in]  pugi::xml_node the Feedback element in the XML document
/// @return void
void FeedbackDefn::ParseXML
(
	xml_node      FeedbackNode
)
{
    // initialize the attributes to the default values
    double xloc	    = 0.0;
    double yloc     = 0.0;
    double heading  = 0.0;
    bool hasError   = false;

    // process attributes
    for (xml_attribute attr = FeedbackNode.first_attribute(); attr && !hasError; attr = attr.next_attribute())
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
            Logger::GetLogger()->LogError( string("FeedbackDefn::ParseXML"), msg );
            hasError = true;
        }
    }

    unique_ptr<CameraDefn> cameraXML = make_unique<CameraDefn>();
    unique_ptr<LEDDefn> ledXML = make_unique<LEDDefn>();

    // Process child element nodes
    for (xml_node child = FeedbackNode.first_child(); child; child = child.next_sibling())
    {
        if (strcmp(child.name(), "camera") == 0)
        {
            if ( cameraXML != nullptr )
            {
                cameraXML->ParseXML(child);
            }
            else
            {
                Logger::GetLogger()->LogError( string("OdometryDefn::ParseXML"), string("Unable to create CameeraDefn") );
            }
        }
        else if (strcmp(child.name(), "led") == 0)
        {
            if ( ledXML != nullptr )
            {
                ledXML->ParseXML(child);
            }
            else
            {
                Logger::GetLogger()->LogError( string("OdometryDefn::ParseXML"), string("Unable to create LDEDefn") );
            }
        }
    	else  // log errors
    	{
            string msg = "unknown child ";
            msg += child.name();
            Logger::GetLogger()->LogError( string("FeedbackDefn::ParseXML"), msg );
    	}
    }


    // create Feedback instance
    if ( !hasError )
    {
        // todo create the Feedback object
    }
}

