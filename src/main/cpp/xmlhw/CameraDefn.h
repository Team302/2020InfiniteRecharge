

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

/// --------------------------------------------------------------------------------------------
/// @class CameraDefn
/// @brief 
///        Create a camera for streaming from an XML definition
/// --------------------------------------------------------------------------------------------
#pragma once

#include <cscore_oo.h>
// Third Party Includes
#include <pugixml/pugixml.hpp>


class CameraDefn
{
    public:

        // todo: eliminate this enum
        enum PIXEL_FORMAT
        {
                UNKNOWN_PIXEL_FORMAT = -1,
                KMJPEG,
                KYUYV,
                KRGB565,
                KBGR,
                KGRAY
        };

        CameraDefn() = default;
        virtual ~CameraDefn() = default;

        ///-----------------------------------------------------------------------
        /// Method:      ParseXML
        /// @brief       Parse a Camera XML element....
        /// @param		 pugi::xml_node cameraNode   XML <camera node
        /// @return     
        ///				 cs::UsbCamera USB camera reference
        ///-----------------------------------------------------------------------
        cs::UsbCamera ParseXML( pugi::xml_node	cameraNode  );

    private:

};

