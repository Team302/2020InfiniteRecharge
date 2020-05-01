
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
/// RobotDefn.cpp
//========================================================================================================
///
/// File Description:
///     Top-level XML parsing file for the robot.  This definition will construct the motor controllers,
///     sensors, chassis and mechanisms from an XML file.  This parsing leverages the 3rd party Open Source
///     Pugixml library (https://pugixml.org/).
///
///     This parsing code will call the classes/methods to parse the lower-level objects.  When the parsing
///     has been completed, the robot hardware will be defined.
///
///     The robot definition XML file is:  /home/lvuser/config/robot.xml
///
//========================================================================================================

// C++ Includes
#include <iostream>
#include <memory>

// FRC includes

// Team 302 includes
#include <xmlhw/CameraDefn.h>
#include <xmlhw/ChassisDefn.h>
#include <xmlhw/FeedbackDefn.h>
#include <xmlhw/RobotDefn.h>
#include <xmlhw/MechanismDefn.h>
#include <xmlhw/LimelightDefn.h>
#include <xmlhw/PDPDefn.h>
#include <xmlhw/PigeonDefn.h>
#include <hw/DragonPigeon.h>
#include <utils/Logger.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>

using namespace frc;
using namespace pugi;
using namespace std;


//-----------------------------------------------------------------------
// Method:      ParseXML
// Description: Parse a robot.xml file
// Returns:     void
//-----------------------------------------------------------------------
void RobotDefn::ParseXML()
{
    // set the file to parse
    const char *filename = "/home/lvuser/config/robot.xml";

    // load the xml file into memory (parse it)
    xml_document doc;
    xml_parse_result result = doc.load_file(filename);

    // if it is good
    if (result)
    {
        unique_ptr<CameraDefn> cameraXML = make_unique<CameraDefn>();
        unique_ptr<ChassisDefn> chassisXML = make_unique<ChassisDefn>();
        unique_ptr<MechanismDefn> mechanismXML = make_unique<MechanismDefn>();
        unique_ptr<PDPDefn> pdpXML = make_unique<PDPDefn>();
        unique_ptr<PigeonDefn> pigeonXML = make_unique<PigeonDefn>();
        unique_ptr<LimelightDefn> limelightXML = make_unique<LimelightDefn>();
        unique_ptr<FeedbackDefn> feedbackXML = make_unique<FeedbackDefn>();

        // get the root node <robot>
        xml_node parent = doc.root();
        for (xml_node node = parent.first_child(); node; node = node.next_sibling())
        {
            // loop through the direct children of <robot> and call the appropriate parser
            for (xml_node child = node.first_child(); child; child = child.next_sibling())
            {
                if (strcmp(child.name(), "chassis") == 0)
                {
                    chassisXML.get()->ParseXML(child);
                }
                else if (strcmp(child.name(), "mechanism") == 0)
                {
                    mechanismXML.get()->ParseXML(child);
                }
                else if (strcmp(child.name(), "camera") == 0)
                {
                    cameraXML.get()->ParseXML(child);
                }
                else if (strcmp(child.name(), "pdp") == 0)
                {
                    pdpXML.get()->ParseXML(child);
                }
                else if ( strcmp(child.name(), "odometry") == 0 )
                {

                }
                else if ( strcmp(child.name(), "feedback") == 0 )
                {
                }
                else if ( strcmp(child.name(), "pigeon") == 0 )
                {
                    pigeonXML.get()->ParseXML( child);
                }
                else if ( strcmp(child.name(), "limelight") == 0 )
                {
                    limelightXML.get()->ParseXML( child);
                }
                else
                {
                    string msg = "unknown child ";
                    msg += child.name();
                    Logger::GetLogger()->LogError( "RobotDefn::ParseXML", msg );
                }
            }
        }
    }
    else
    {
        string msg = "XML [";
        msg += filename;
        msg += "] parsed with errors, attr value: [";
        msg += doc.child( "prototype" ).attribute( "attr" ).value();
        msg += "]";
        Logger::GetLogger()->LogError( "RobotDefn::ParseXML (1) ", msg );

        msg = "Error description: ";
        msg += result.description();
        Logger::GetLogger()->LogError( "RobotDefn::ParseXML (2) ", msg );

        msg = "Error offset: ";
        msg += result.offset;
        msg += " error at ...";
        msg += filename;
        msg += result.offset;
        Logger::GetLogger()->LogError( "RobotDefn::ParseXML (3) ", msg );
    }
}
