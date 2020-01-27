#pragma once

#include <pugixml/pugixml.hpp>

#include <ctre/Phoenix.h>
#include <rev/ColorSensorV3.h>
using namespace std;


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