#include <string>
#include <utils/Logger.h>
#include <pugixml/pugixml.hpp>
#include <utils/HardwareIDValidation.h>
#include <xmlhw/ThroughBoreEncoderDefn.h>
#include <frc/Encoder.h>

using namespace pugi;
using namespace std;
using namespace frc;

shared_ptr<frc::Encoder> ThroughBoreEncoderDefn::ParseXML
(
    pugi::xml_node throughBoreEncoderNode
)
{
    string usage;
    int DIOA;
    int DIOB;
    int PWMID = 0;
    bool hasError = false;
    shared_ptr<frc::Encoder> throughboreencoder = nullptr;
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
        else if ( strcmp (attr.name(), "PWMID") == 0)
        {
            int iVal = attr.as_int();
            if (iVal >= 0 && iVal <= 9) //filler values todo need to find actual values or have ID Validation
            {
                PWMID = attr.as_int();
            }
            else
            {
                Logger::GetLogger()->LogError ("==>> ThroughBoreEncoderDefn::ParseXML invalid PWN ID \n", "iVal");
                hasError = true;
            }
        }
    }
    if (!hasError)
    {
        throughboreencoder = make_shared<frc::Encoder> (/*usage,*/ DIOA, DIOB, PWMID ); //TODO add usage to dragon through bore encoder
    }
    return throughboreencoder;
}