/*
 * PrimitiveParams.cpp
 *
 *  Created on: Jan 17, 2017
 *      Author: Jonah Shader
 */

#include <auton/PrimitiveEnums.h>
#include <auton/PrimitiveParams.h>
#include <states/BallManipulator.h>

PrimitiveParams::PrimitiveParams
(
    PRIMITIVE_IDENTIFIER								id,
    float                       						time,
    float                       						distance,
    float                       						xLoc,
    float                       						yLoc,
    float                       						heading,
    float                       						startDriveSpeed,
    float                       						endDriveSpeed,
	BallManipulator::BALL_MANIPULATOR_STATE				ballState,
	float												turretAngle
):	//Pass over parameters to class variables
		m_id(id), //Primitive ID
		m_time(time),
		m_distance(distance),
		m_xLoc( xLoc ),
		m_yLoc( yLoc ),
		m_heading(heading),
		m_startDriveSpeed( startDriveSpeed ),
		m_endDriveSpeed( endDriveSpeed ),
		m_ballState( ballState ),
		m_turretAngle( turretAngle )
{
}

PRIMITIVE_IDENTIFIER PrimitiveParams::GetID() const
{
	return m_id;
}

float PrimitiveParams::GetTime() const
{
	return m_time;
}

float PrimitiveParams::GetDistance() const
{
	return m_distance;
}

float PrimitiveParams::GetXLocation() const
{
    return m_xLoc;
}

float PrimitiveParams::GetYLocation() const
{
    return m_yLoc;
}

float PrimitiveParams::GetHeading() const
{
	return m_heading;
}

float PrimitiveParams::GetDriveSpeed() const
{
    return m_startDriveSpeed;
}

float PrimitiveParams::GetEndDriveSpeed() const
{
    return m_endDriveSpeed;
}

BallManipulator::BALL_MANIPULATOR_STATE PrimitiveParams::GetBallState() const
{
	return m_ballState;
}

float PrimitiveParams::GetTurretAngle() const
{
	return m_turretAngle;
}

//Setters
void PrimitiveParams::SetDistance(float distance)
{
	m_distance = distance;
}

