
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
/// StateDataDefn.cpp
//========================================================================================================
///
/// File Description:
///     Top-level XML parsing file for the state data.  This definition will construct objects to help
///     set the state targets and control modes.
///
///     This parsing leverages the 3rd party Open Source Pugixml library (https://pugixml.org/).
///
///     The state definition XML files are in:  /home/lvuser/config/states/XXX.xml where the XXX
///     is the mechanism name.
///
//========================================================================================================

// C++ Includes
#include <memory>
#include <string>
#include <cstring>

// FRC includes

// Team 302 includes
#include <xmlmechdata/StateDataDefn.h>
#include <utils/Logger.h>
#include <subsys/MechanismTypes.h>
#include <controllers/ControlData.h>
#include <xmlmechdata/ControlDataDefn.h>
#include <xmlmechdata/MechanismTargetDefn.h>
#include <controllers/MechanismTargetData.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>

using namespace pugi;
using namespace std;


/// @brief      Parse a mechanismState.xml file
/// @param [in] MechanismTypes::MECHANISM_TYPE  - mechanism that the states are for
/// @return     state data
vector<MechanismTargetData*> StateDataDefn::ParseXML
(
    MechanismTypes::MECHANISM_TYPE mechanism
)
{
    bool hasError = false;

    vector<MechanismTargetData*> targetDataVector;

    // set the file to parse
    string filename = "/home/lvuser/config/states/";
    switch ( mechanism )
    {
        case MechanismTypes::DRIVETRAIN_SIDE:
            filename += string( "drivetrainside.xml");
            break;

        case MechanismTypes::INTAKE:
            filename += string( "intake.xml");
            break;

        case MechanismTypes::IMPELLER:
            filename += string( "impeller.xml");
            break;

        case MechanismTypes::BALL_TRANSFER:
            filename += string( "balltransfer.xml");
            break;

        case MechanismTypes::TURRET:
            filename += string( "turret.xml");
            break;

        case MechanismTypes::SHOOTER:
            filename += string( "shooter.xml");
            break;

        case MechanismTypes::SHOOTER_HOOD:
            filename += string( "shooterhood.xml");
            break;

        case MechanismTypes::CONTROL_TABLE_MANIPULATOR:
            filename += string( "controltablemanipulator.xml");
            break;

        case MechanismTypes::CLIMBER:
            filename += string( "climber.xml");
            break;

        case MechanismTypes::CRAWLER:
            filename += string( "crawler.xml");
            break;

        case MechanismTypes::HOOK_DELIVERY:
            filename += string( "hookdelivery.xml");
            break;

        default:
            Logger::GetLogger()->LogError( "StateDataDefn::ParseXML", "invalid mechanism" );
            hasError = true;
            break;
    }

    if ( !hasError )
    {
        // load the xml file into memory (parse it)
        xml_document doc;
        xml_parse_result result = doc.load_file(filename.c_str());

        // if it is good
        if (result)
        {
            unique_ptr<ControlDataDefn> controlDataXML = make_unique<ControlDataDefn>();
            unique_ptr<MechanismTargetDefn> mechanismTargetXML = make_unique<MechanismTargetDefn>();

            vector<ControlData*> controlDataVector;

            // get the root node <robot>
            xml_node parent = doc.root();
            for (xml_node node = parent.first_child(); node; node = node.next_sibling())
            {   
                // loop through the direct children of <robot> and call the appropriate parser
                for (xml_node child = node.first_child(); child; child = child.next_sibling())
                {
                    if (strcmp(child.name(), "controlData") == 0)
                    {
                        controlDataVector.push_back( controlDataXML->ParseXML( child ) );
                    }
                    else if (strcmp(child.name(), "mechanismTarget") == 0)
                    {
                        targetDataVector.push_back( mechanismTargetXML->ParseXML( child ) );
                    }
                    else
                    {
                        string msg = "unknown child ";
                        msg += child.name();
                        Logger::GetLogger()->LogError( "StateDataDefn::ParseXML", msg );
                    }
                }
            }

            for ( auto td : targetDataVector )
            {
                td->Update( controlDataVector );
            }
        }
        else
        {
            string msg = "XML [";
            msg += filename;
            msg += "] parsed with errors, attr value: [";
            msg += doc.child( "prototype" ).attribute( "attr" ).value();
            msg += "]";
            Logger::GetLogger()->LogError( "StateDataDefn::ParseXML (1) ", msg );

            msg = "Error description: ";
            msg += result.description();
            Logger::GetLogger()->LogError( "StateDataDefn::ParseXML (2) ", msg );

            msg = "Error offset: ";
            msg += result.offset;
            msg += " error at ...";
            msg += filename;
            msg += result.offset;
            Logger::GetLogger()->LogError( "StateDataDefn::ParseXML (3) ", msg );
        }
    }
    return targetDataVector;
}
