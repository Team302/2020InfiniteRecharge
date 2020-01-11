

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

// C++ includes
#include <memory>
#include <string>

// FRC includes
#include <cameraserver/CameraServer.h>
#include <cscore_cpp.h>

// Team302 includes
#include <utils/Logger.h>
#include <xmlhw/CameraDefn.h>

// Third Party includes
#include <pugixml/pugixml.hpp>



using namespace frc;
using namespace std;

///-----------------------------------------------------------------------
/// Method:      ParseXML
/// @brief       Parse a Camera XML element....
/// @param		 pugi::xml_node cameraNode   XML <camera node
/// @return     
///				 cs::UsbCamera USB camera reference
///-----------------------------------------------------------------------
cs::UsbCamera CameraDefn::ParseXML
(
    pugi::xml_node      cameraNode
)
{
	cs::UsbCamera camera;  // todo: create a pointer that can be initialized

	bool hasError = false;

	// initialize attributes to default values
	cs::VideoMode::PixelFormat type = cs::VideoMode::kUnknown;
	int 					     id = 0;
	int 					  width = 640;
	int 				     height = 480;
	int 				        fps = 30;

	// todo: integrate the DragonCamera + separate thread logic from Destination Deep Space

	//Parse/validate xml
	for(pugi::xml_attribute attr = cameraNode.first_attribute(); attr && !hasError; attr = attr.next_attribute() )
	{
		if ( strcmp( attr.name(), "ID") == 0 )
		{
			id = attr.as_int();
		}
		else if (strcmp(attr.name(), "format" ) == 0)
		{
			// todo: parse strings and map to the cs::VideoMode enum
			int iVal = attr.as_int();
			switch(iVal)
			{
				case CameraDefn::KMJPEG:
					type = cs::VideoMode::kMJPEG;
					break;

				case CameraDefn::KYUYV:
					type = cs::VideoMode::kYUYV;
					break;

				case CameraDefn::KRGB565:
					type = cs::VideoMode::kRGB565;
					break;

				case CameraDefn::KBGR:
					type = cs::VideoMode::kBGR;
					break;

				case CameraDefn::KGRAY:
					type = cs::VideoMode::kGray;
					break;

				default:
					type = cs::VideoMode::kUnknown;
					string msg = "unknown camera format ";
					msg += to_string( iVal );
					Logger::GetLogger()->LogError( "CameraDefn::ParseXML", msg );
					hasError = true;
					break;
			}
		}
		else if (strcmp(attr.name(), "width") == 0)
		{
			width = attr.as_int();
		}

		else if (strcmp(attr.name(), "height") == 0)
		{
			height = attr.as_int();
		}
		else if (strcmp(attr.name(), "fps") == 0)
		{
			fps = attr.as_int();
		}
		else
		{
            string msg = "unknown attribute ";
            msg += attr.name();
            Logger::GetLogger()->LogError( "CameraDefn::ParseXML", msg );
            hasError = true;
		}

	}

	if (!hasError)
	{
		CameraServer* server = CameraServer::GetInstance();
		if ( server != nullptr )
		{
		    camera = server->StartAutomaticCapture( id );
            camera.SetVideoMode(type, width, height, fps );
		}
		else
		{
            string msg = "camera server not found ";
            Logger::GetLogger()->LogError( "CameraDefn::ParseXML", msg );
            hasError = true;
		}
	}
	return camera;
}

