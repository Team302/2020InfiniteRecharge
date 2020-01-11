/*
 * FieldMeasurement.cpp
 *
 *  Created on: Mar 8, 2018
 *      Author: team302
 */

#include <iostream>
#include <auton/FieldMeasurement.h>

FieldMeasurement* FieldMeasurement::m_fieldMeasurement = nullptr;

FieldMeasurement* FieldMeasurement::GetFieldMeasurement()
{
	if ( FieldMeasurement::m_fieldMeasurement == nullptr )
	{
		FieldMeasurement::m_fieldMeasurement = new FieldMeasurement();
	}
	return FieldMeasurement::m_fieldMeasurement;
}

FieldMeasurement::FieldMeasurement() : m_xLoc(),
									   m_yLoc()
{
	for ( int inx=0; inx<FieldMeasurement::MAX_POSITIONS; ++inx )
	{
		m_xLoc[inx] = 0.0;
		m_yLoc[inx] = 0.0;
	}

}

float FieldMeasurement::GetXLoc(Measurement location)
{
	float value = 0.0;
	if ( location > -1 && location < FieldMeasurement::MAX_POSITIONS )
	{
		value = m_xLoc[ location ];
	}
	else
	{
		printf( "==>> invalid XLoc requested \n");
	}
	return value;
}

float FieldMeasurement::GetYLoc(Measurement location)
{
	float value = 0.0;
	if ( location > -1 && location < FieldMeasurement::MAX_POSITIONS )
	{
		value = m_yLoc[ location ];
	}
	else
	{
		printf( "==>> invalid YLoc requested \n");
	}
	return value;
}

void FieldMeasurement::AddLocation
(
		Measurement location,
		float X,
		float Y
)
{
	if ( location > -1 && location < FieldMeasurement::MAX_POSITIONS )
	{
		m_xLoc[ location ] = X;
	}
	else
	{
		printf( "==>> invalid XLoc requested \n");
	}
}

float FieldMeasurement::GetKeyPoint( Measurement keyPointLocation )
{
	float keyPoint = 0.0;

	switch( keyPointLocation )
	{
		case BLUE_SCALE_LEFT:
			keyPoint = GetYLoc( keyPointLocation ) - distances[0];
			break;
		case BLUE_SCALE_RIGHT:
			keyPoint = GetYLoc( keyPointLocation ) - distances[1];
			break;
		case RED_SCALE_LEFT:
			keyPoint = GetYLoc( keyPointLocation ) - distances[0];
			break;
		case RED_SCALE_RIGHT:
			keyPoint = GetYLoc( keyPointLocation ) - distances[1];
			break;

		default:
			printf( "==>> FieldMeasurement::GetKeyPoint: unknown keypoint \n" );
			keyPoint = 0.0;
			break;
	}

	return keyPoint;
}
