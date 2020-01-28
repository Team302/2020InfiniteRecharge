/*
 * FMS.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: Austin
 */

#include <auton/FMS.h>

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
	currentColor(FMS::COLOR::UNKNOWN)
{
}

FMS::COLOR FMS::GetColor()
{
	gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage(); //update when method is called
	switch ( gameData[0] )
	{
		case 'B' :
			return COLOR::BLUE;
		break;

		case 'G' :
			return FMS::COLOR::GREEN;
		break;

		case 'Y' :
			return FMS::COLOR::YELLOW;
		break;

		case 'R' :
			return FMS::COLOR::RED;
		break;

		default:
			return FMS::COLOR::UNKNOWN;
			break;
	}
}

