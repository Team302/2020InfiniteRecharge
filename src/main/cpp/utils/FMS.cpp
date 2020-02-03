
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

#include <utils/FMS.h>
#include <utils/ControlPanelColors.h>

FMS* FMS::m_instance = nullptr;


FMS* FMS::GetFMS()
{
	if ( FMS::m_instance == nullptr )
	{
		FMS::m_instance = new FMS();
	}
	return FMS::m_instance;
}


FMS::FMS() :
	gameData ( frc::DriverStation::GetInstance().GetGameSpecificMessage() ),
	currentColor(ControlPanelColors::COLOR::UNKNOWN)
{
}

ControlPanelColors::COLOR FMS::GetColor()
{
	gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage(); //update when method is called
	switch ( gameData[0] )
	{
		case 'B' :
			return ControlPanelColors::COLOR::BLUE;
		break;

		case 'G' :
			return ControlPanelColors::COLOR::GREEN;
		break;

		case 'Y' :
			return ControlPanelColors::COLOR::YELLOW;
		break;

		case 'R' :
			return ControlPanelColors::COLOR::RED;
		break;

		default:
			return ControlPanelColors::COLOR::UNKNOWN;
			break;
	}
}

