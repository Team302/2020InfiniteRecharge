#include <memory>
#include <string>
#include <xmlhw/CanCoderDefn.h>
#include <pugixml/pugixml.hpp>
#include <utils/Logger.h>
#include <ctre/Phoenix.h>


using namespace std;
using namespace frc;
using namespace pugi;

std::shared_ptr<ctre::phoenix::sensors::CANCoder> CanCoderDefn::ParseXML
(
    pugi::xml_node CanCoderNode
)
{
    shared_ptr<ctre::phoenix::sensors::CANCoder> cancoder = nullptr;

    string usage;
    int canID = 0;
    
    bool hasError = false;

    for(pugi::xml_attribute attr = CanCoderNode.first_attribute(); attr &&!hasError; attr = attr.next_attribute() )
    {
        if ( strcmp( attr.name(), "usage") == 0)
        {
            usage = attr.value();
        }
        else if ( strcmp(attr.name(),"canID" ) == 0 )
        {
            int iVal = attr.as_int();
            if (iVal > -1 && iVal < 63)
            {
                canID = attr.as_int();
            }
            else
            {
                Logger::GetLogger()->LogError ("==>> CanCoderDefn::ParseXML invalid CAN Id \n", "iVal");
                hasError = true;
            }
        }
        else
        {
            Logger::GetLogger()->LogError ( "CanCoderDefn", "invalid attribute");
            hasError = true;
        }

    }   
    if(!hasError)
    {
        cancoder = new CanCoder(usage, canID);
    }
    return cancoder;
}