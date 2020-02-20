#pragma once

#include <memory>
#include <pugixml/pugixml.hpp>
#include <frc/Encoder.h>

class ThroughBoreEncoderDefn
{
    ThroughBoreEncoderDefn() = default;

    virtual ~ThroughBoreEncoderDefn() = default;
    std::shared_ptr<frc::Encoder> ParseXML
    (
        pugi::xml_node throughBoreEncoderNode
    );

};