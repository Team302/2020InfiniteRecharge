#pragma once

#include <memory>

#include <pugixml/pugixml.hpp>

#include <ctre/Phoenix.h>

class CanCoderDefn
{
    public:
        CanCoderDefn() = default;
        virtual ~CanCoderDefn() = default;

        std::shared_ptr<ctre::phoenix::sensors::CANCoder> ParseXML (pugi::xml_node  CanCoderNode);
};