#pragma once

#include <pugixml/pugixml.hpp>

class ThroughBorerEncoderDefn
{
    ThroughBorerEncoderDefn() = default;

    virtual ~ThroughBorerEncoderDefn() = default;
    void ThroughBorerEncoderDefn::ParseXML
    (
        pugi::xml_node throughBorerEncoderNode
    );

};