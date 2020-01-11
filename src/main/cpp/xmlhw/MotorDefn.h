
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

//========================================================================================================
/// MotorDefn.h
//========================================================================================================
///
/// File Description:
///     This will parse the motor (controller) definition XML and create a motor controller object.
//========================================================================================================

#pragma once


// C++ Includes
#include <memory>
#include <vector>

// FRC includes

// Team 302 includes
#include <hw/interfaces/IDragonMotorController.h>
#include <hw/DragonSparkMax.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>



class MotorDefn
{
    public:

        MotorDefn() = default;
        virtual ~MotorDefn() = default;


        ///-----------------------------------------------------------------------
        /// Method:      ParseXML
        /// Description: Parse a motor XML element and create a DragonTalon from
        ///              its definition.
        /// Returns:     DragonTalon*        motor controller (or nullptr if XML
        ///                                  is ill-formed)
        ///-----------------------------------------------------------------------
        std::shared_ptr<IDragonMotorController> ParseXML
        (
            pugi::xml_node      motorNode   /// <I> - xml motor node
        );

    private:
};


