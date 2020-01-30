#include <pugixml/pugixml.hpp>
#include <xmlhw/ColorSensorDefn.h>
#include <subsys/ControlPanel.h>
#include <rev/ColorSensorV3.h>
#include <utils/Logger.h>

 //standard libarys

using namespace std;
using namespace rev;
using namespace frc;
rev::ColorSensorV3* ParseXML
(
    pugi::xml_node ColorSensorNode
)
{
    rev::ColorSensorV3* sensor = nullptr;
    frc::I2C::Port port = frc::I2C::Port::kOnboard; //ColorSensorV3 takes an I2C port and has kOnboard or kMXP

    bool hasError = false;
    
        for(pugi::xml_attribute attr = ColorSensorNode.first_attribute(); attr && !hasError; attr = attr.next_attribute() )
        {
            if ( strcmp ( attr.name(), "kOnboard" ) == 0) //strcmp string compare. It will compare the value of the string
            {
                port = frc::I2C::Port::kOnboard;
            }
            else if (strcmp (attr.name(), "kMXP" ) == 0 )
            {
                port = frc::I2C::Port::kMXP;
            }
            else
            {
                Logger::GetLogger()->LogError( "ColorSensorDefn", "unknown child" );

                hasError = true;
            }
            
            
        }

    if(!hasError)
    {
        sensor = new ColorSensorV3(port);
    };
    return sensor;
    
}