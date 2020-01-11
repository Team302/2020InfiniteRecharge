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
	switchPos ( POS::UNKNOWN ),
	oppSwitchPos ( POS::UNKNOWN ),
	scalePos ( POS::UNKNOWN )
{
}

FMS::POS FMS::GetSwitchPos()
{
	switch ( gameData[0] )
	{
	case 'L':
		switchPos = FMS::LEFT;
		break;
	case 'R':
		switchPos = FMS::RIGHT;
		break;
	default:
		switchPos = FMS::UNKNOWN;
		break;
	}

	return switchPos;
}

FMS::POS FMS::GetOppSwitchPos()
{
	switch ( gameData[2] )
	{
	case 'L':
		oppSwitchPos = FMS::LEFT;
		break;
	case 'R':
		oppSwitchPos = FMS::RIGHT;
		break;
	default:
		switchPos = FMS::UNKNOWN;
		break;
	}

	return oppSwitchPos;
}

FMS::POS FMS::GetScalePos()
{
	switch ( gameData[1] )
	{
	case 'L':
		scalePos = FMS::LEFT;
		break;
	case 'R':
		scalePos = FMS::RIGHT;
		break;
	default:
		scalePos = FMS::UNKNOWN;
		break;
	}

	return scalePos;
}
