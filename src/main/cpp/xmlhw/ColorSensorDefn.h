#pragma once

#include <pugixml/pugixml.hpp>


class ColorSensorDefn
{
    public:
    ColorSensorDefn() = default;
    virtual ~ColorSensorDefn() = default;
    ColorSensorDefn* ParseXML
    (
    
    pugi::xml_node  ColorSensorNode

    );
};