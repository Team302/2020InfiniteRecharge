#pragma once

#include <pugixml/pugixml.hpp>

class ThroughBorerEncoderDefn
{
    ThroughBorerEncoderDefn() = default;

    virtual ~ThroughBorerEncoderDefn() = default;
    void ParseXML
    (
        pugi::xml_node throughBorerEncoderNode
    );

};