#include <string.h>
#include <utils/Logger.h>
#include <pugixml/pugixml.hpp>
#include <utils/HardwareIDValidation.h>
#include <xmlhw/ThroughBoreEncoderDefn.h>
 
using namespace pugi;
using namespace std;

void ThroughBorerEncoderDefn::ParseXML
(
    pugi::xml_node throughBorerEncoderNode
)
{
    string usage;
    int DIOA;
    int DIOB;
    int PWM = 0;
    bool hasError = false;
    for ( xml_attribute attr = throughBorerEncoderNode.first_attribute(); attr && !hasError; attr = attr.next_attribute())
    {
        if ( strcmp (attr.name(), "usage") == 0 )
        {
            usage = attr.value();
        }
        else if (strcmp (attr.name(), "DIOA") == 0 )
        {
            DIOA = attr.as_int();
            hasError = HardwareIDValidation::ValidateDIOID( DIOA, string( "ThroughBorerEncoderDefn::ParseXML" ) );
        }
        else if ( strcmp( attr.name(), "DIOB ") == 0)
        {
            DIOB = attr.as_int();
            hasError = HardwareIDValidation::ValidateDIOID( DIOB, string( "ThroughBorerEncoderDefn::ParseXML" ) );
        }
        else if ( strcmp (attr.name(), "PWM") == 0)
        {
            int iVal = attr.as_int();
            if (iVal >= 0 && iVal <= 9) //filler values
            {
                PWM = attr.as_int();
            }
            else
            {
                Logger::GetLogger()->LogError ("==>> ThroughBorerEncoderDefn::ParseXML invalid PWN \n", "iVal");
                hasError = true;
            }
        }
    }
    /*if (!hasError)
    {
        throughborerencoder = new ( usage, DIOA, DIOB, PWN );
    }
    return throughborerencoder; */
}