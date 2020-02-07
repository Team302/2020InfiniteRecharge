
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

// C++ includes
#include <string>
#include <cstring>

// wpilib includes

// team 302 includes
#include <xmlhw/CanCoderDefn.h>
#include <utils/HardwareIDValidation.h>
#include <utils/Logger.h>

// third party includes
#include <pugixml/pugixml.hpp>
#include <ctre/phoenix/sensors/CANCoder.h>

using namespace std;
using namespace pugi;
using namespace ctre::phoenix::sensors;

/// @brief parses the cancoder node in the robot.xml file and creates a cancoder
/// @param [in] xml_node - the cancoder element in the xml file
/// @return shared_ptr<CANCoder
shared_ptr<CANCoder> CanCoderDefn::ParseXML
(
    xml_node CanCoderNode
)
{
    shared_ptr<CANCoder> cancoder = nullptr;

    string usage;
    int canID = 0;
    
    bool hasError = false;

    for(xml_attribute attr = CanCoderNode.first_attribute(); attr &&!hasError; attr = attr.next_attribute() )
    {
        if ( strcmp( attr.name(), "usage") == 0)
        {
            usage = attr.value();
        }
        else if ( strcmp( attr.name(), "canId" ) == 0 )
        {
            canID = attr.as_int();
            hasError = HardwareIDValidation::ValidateCANID( canID, string( "CanCoderDefn::ParseXML" ) );
        }        
        else
        {
            Logger::GetLogger()->LogError ( "CanCoderDefn", "invalid attribute");
            hasError = true;
        }

    }   
    if(!hasError)
    {
        cancoder = make_shared<CANCoder>(canID); //need to add usage also can't use new CANCoder... because it hasn't been wrapped
    }
    return cancoder;
}