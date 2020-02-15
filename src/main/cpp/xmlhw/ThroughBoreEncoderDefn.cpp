#include <string.h>
#include <utils/Logger.h>
#include <pugixml/pugixml.hpp>
#include <utils/HardwareIDValidation.h>
#include <xmlhw/ThroughBoreEncoderDefn.h>
#include <rev/CANEncoder.h>

using namespace pugi;
using namespace std;
using namespace rev;

shared_ptr<rev::CANEncoder> ThroughBoreEncoderDefn::ParseXML
(
    pugi::xml_node throughBoreEncoderNode
)
{
    string usage;
    int DIOA;
    int DIOB;
    int PWM = 0;
    bool hasError = false;
    shared_ptr<rev::CANEncoder> throughboreencoder = nullptr;
    for ( xml_attribute attr = throughBoreEncoderNode.first_attribute(); attr && !hasError; attr = attr.next_attribute())
    {
        if ( strcmp (attr.name(), "usage") == 0 )
        {
            usage = attr.value();
        }
        else if (strcmp (attr.name(), "DIOA") == 0 )
        {
            DIOA = attr.as_int();
            hasError = HardwareIDValidation::ValidateDIOID( DIOA, string( "ThroughBoreEncoderDefn::ParseXML" ) );
        }
        else if ( strcmp( attr.name(), "DIOB ") == 0)
        {
            DIOB = attr.as_int();
            hasError = HardwareIDValidation::ValidateDIOID( DIOB, string( "ThroughBoreEncoderDefn::ParseXML" ) );
        }
        else if ( strcmp (attr.name(), "PWM") == 0)
        {
            int iVal = attr.as_int();
            if (iVal >= 0 && iVal <= 9)
            {
                PWM = attr.as_int();
            }
            else
            {
                Logger::GetLogger()->LogError ("==>> ThroughBoreEncoderDefn::ParseXML invalid PWN id \n", "iVal");
                hasError = true;
            }
        }
    }
    /*if (!hasError)
    {
        throughboreencoder = make_shared<rev::CANEncoder> ( usage, DIOA, DIOB, PWM );
    }
    return throughboreencoder;*/
}