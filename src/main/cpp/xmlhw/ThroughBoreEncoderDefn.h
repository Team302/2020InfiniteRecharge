#pragma once

#include <memory>
#include <pugixml/pugixml.hpp>
#include <rev/CANEncoder.h>
using namespace std;

class ThroughBoreEncoderDefn
{
    ThroughBoreEncoderDefn() = default;

    virtual ~ThroughBoreEncoderDefn() = default;
    std::shared_ptr<rev::CANEncoder> ParseXML
    (
        pugi::xml_node throughBoreEncoderNode
    );

};