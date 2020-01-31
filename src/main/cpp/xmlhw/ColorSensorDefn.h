#pragma once

namespace rev
{
    class ColorSensorV3;
}

namespace pugi
{
    class xml_node;
}

class ColorSensorDefn
{
    public:
        ColorSensorDefn() = default;
        virtual ~ColorSensorDefn() = default;
        rev::ColorSensorV3* ParseXML
        (
            pugi::xml_node  ColorSensorNode
        );
};