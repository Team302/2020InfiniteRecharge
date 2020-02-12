#include <utils/Logger.h>
#include <pugixml/pugixml.hpp>
#include <xmlhw/ThroughBorerEncoderDefn.h> //hong bing
 
using namespace pugi;
using namespace std;

void ThroughBorerEncoderDefn::ParseXML
(
    pugi::xml_node throughBorerEncoderNode
)
{
    string usage;
    bool DIOA;
    bool DIOB;
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
            DIOA = attr.as_bool();
        }
        else if ( strcmp( attr.name(), "DIOB ") == 0)
        {
            DIOB = attr.as_bool();
        }
        else if ( strcmp (attr.name(), "PWM") == 0)
        {
            int iVal = attr.as_int();
            if (iVal > -1 && iVal < 12) //filler values
            {
                PWN = attr.as_int();
            }
            else
            {
                Logger::GetLogger()->LogError ("==>> ThroughBorerEncoderDefn::ParseXML invalid PWN \n", "iVal");
                hasError = true;
            }
        }
    }
    if (!hasError)
    {
        throughborerencoder = new ( usage, DIOA, DIOB, PWN ); 
    }
    return throughborerencoder;
}
