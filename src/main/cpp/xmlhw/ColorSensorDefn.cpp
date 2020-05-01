
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

// wpilib includes

// team 302 includes 
#include <xmlhw/ColorSensorDefn.h>
#include <utils/Logger.h>

// third party includes
#include <pugixml/pugixml.hpp>
#include <rev/ColorSensorV3.h>

using namespace std;
using namespace rev;
using namespace frc;
using namespace pugi;
 
/// @brief      parse the color sensor xml node and create a rev color sensor
/// @param [in] xml_node - the colorSensor node
/// @return     ColorSensorV3* the rev color sensor or nullptr if the node is invalid
ColorSensorV3* ColorSensorDefn::ParseXML
(
    xml_node ColorSensorNode
)
{
    ColorSensorV3* sensor = nullptr;
    I2C::Port port = I2C::Port::kOnboard; //ColorSensorV3 takes an I2C port and has kOnboard or kMXP

    bool hasError = false;
    
    for(xml_attribute attr = ColorSensorNode.first_attribute(); attr && !hasError; attr = attr.next_attribute() )
    {
        if (strcmp(attr.name(), "port") == 0 )
        {
            if ( strcmp ( attr.value(), "kOnboard" ) == 0) //strcmp string compare. It will compare the value of the string
            {
                port = I2C::Port::kOnboard;
            }
            else if (strcmp (attr.value(), "kMXP" ) == 0 )
            {
                port = I2C::Port::kMXP;
            }
            else 
            {
                string msg = "unknown port ";
                msg += attr.value();
                Logger::GetLogger()->LogError( string("ColorSensorDefn::ParseXML"), msg);
                hasError = true;
            }
        }
        else
        {
            string msg = "unknown attribute ";
            msg += attr.name();
            Logger::GetLogger()->LogError( string("ColorSensorDefn"), msg );

            hasError = true;
        }
        
        
    }

    if(!hasError)
    {
        sensor = new ColorSensorV3(port);
    }
    return sensor;
}