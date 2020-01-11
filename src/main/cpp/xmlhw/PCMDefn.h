
//====================================================================================================================================================
// Copyright 2019 Lake Orion Robotics FIRST Team 302
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================

#pragma once


// C++ Includes
#include <memory>

// FRC includes

// Team 302 includes
#include <frc/Compressor.h>
#include <frc/Solenoid.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>




/// @class PCMDefn
/// @brief XML parsing for the PCM node in the Robot definition xml file.  Upon successful parsing, it will
///        create a Compressor object and solenoid objects. The parsing leverages the 3rd party Open Source 
///        Pugixml library (https://pugixml.org/).
class PCMDefn
{
    public:

        PCMDefn() = default;
        virtual ~PCMDefn() = default;

        /// @brief      Parse a pcm XML element and create a PowerDistributionPanel* from its definition.
        /// @param [in] xml_node PDPNode the <PDP element in the xml document
        /// @return     PowerDistributionPanel*   PDP object
        frc::Compressor* ParseXML
        (
            pugi::xml_node      PDPNode
        );
};

