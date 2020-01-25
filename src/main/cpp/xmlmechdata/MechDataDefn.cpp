
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
/// MechDataDefn.cpp
//========================================================================================================
///
/// File Description:
///     Top-level XML parsing file for defining the key mechanism parameter values.  Examples include 
///     set points, min/max values, etc.  
///     This parsing leverages the 3rd party Open Source Pugixml library (https://pugixml.org/).
///
///     This parsing code will call the classes/methods to parse the lower-level objects.  When the parsing
///     has been completed, the mechanism parameters will be defined.
///
///     The robot definition XML file is:  /home/lvuser/config/mechdata/xxx.xml where xxx is the class name 
///     that will be reading the file.
//========================================================================================================

/**
// C++ Includes
#include <iostream>
#include <cstring>
#include <string>
#include <utility> 
#include <vector>

// FRC includes

// Team 302 includes
#include <xmlmechdata/MechDataDefn.h>
#include <xmlmechdata/MechanismTargetDefn.h>
#include <subsys/MechParamData.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>

//-----------------------------------------------------------------------
// Method:      ParseXML
// Description: Parse the mechanism parameter xml file
// Returns:     void
//-----------------------------------------------------------------------
void MechDataDefn::ParseXML
(
    std::string&            leaf,               /// <I> - the file name (without the path) to parse
    mechParameters&         params              /// <O> - the parameter data 
)
{
    params.clear();

    // set the file to parse
    std::string directory = "/home/lvuser/config/mechdata/";
    std::string filename = directory + leaf;

    // load the xml file into memory (parse it)
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file( filename.c_str() );

    // if it is good
    if ( result )
    {
        // get the root node <robot>
        pugi::xml_node parent = doc.root();
        for (pugi::xml_node node = parent.first_child(); node; node = node.next_sibling())
        {
            // loop through the direct children of <robot> and call the appropriate parser
            for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling())
            {
                if ( strcmp( child.name(), "mechanismData") == 0 )
                {
                    // Mechanism Data
                    params.emplace_back( MechanismTargetDefn::ParseXML( child ) );
                }
                else
                {
                    std::cout << "==>>MechDataDefn::ParseXML unknown robot child " << child.name() << std::endl;
                }
            }
        }
    }
    else
    {
        std::cout << "XML [" << filename.c_str() << "] parsed with errors, attr value: [" << doc.child("prototype").attribute("attr").value() << "]" << std::endl;
        std::cout << "Error description: " << result.description() << std::endl;
        std::cout << "Error offset: " << result.offset << " (error at [..." << (filename.c_str() + result.offset) << "]" << std::endl;
    }
}
**/
