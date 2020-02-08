/*
 * PrimitiveParams.cpp
 *
 *  Created on: Jan 17, 2017
 *      Author: Jonah Shader
 */

#include <auton/PrimitiveEnums.h>
#include <auton/PrimitiveParams.h>

PrimitiveParams::PrimitiveParams
(
    PRIMITIVE_IDENTIFIER        id,
    float                       time,
    float                       distance,
    float                       xLoc,
    float                       yLoc,
    float                       heading,
    float                       startDriveSpeed,
    float                       endDriveSpeed
):	//Pass over parameters to class variables
		m_id(id), //Primitive ID
		m_time(time),
		m_distance(distance),
		m_xLoc( xLoc ),
		m_yLoc( yLoc ),
		m_heading(heading),
		m_startDriveSpeed( startDriveSpeed ),
		m_endDriveSpeed( endDriveSpeed ),
		m_intakeOn(true)	//todo pass a param
{
}

PrimitiveParams::~PrimitiveParams()
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
bool PrimitiveParams::IsIntakeOn() const
{
	return m_intakeOn;
}
bool PrimitiveParams::IsShooterOn() const
{
	return m_shooterOn;
}



//Setters
void PrimitiveParams::SetDistance(float distance)
{
	m_distance = distance;
}

