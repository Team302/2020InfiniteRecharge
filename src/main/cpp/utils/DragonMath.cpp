/*
 * DragonMath.cpp
 *
 *  Created on: Jan 19, 2018
 *      Author: jonah
 */

//Includes
#include <cmath>
//team302 includes
#include <utils/DragonMath.h>

float DragonMath::Distance(Point2D p1, Point2D p2) {
	double x = p1.x - p2.x;
	double y = p1.y - p2.y;
	return sqrt(pow(x, 2) + pow(y, 2));
}

float DragonMath::HeadingToStandardAngle(float headingInDegrees) {
	return -headingInDegrees + 90;
}

float DragonMath::DegreesToRadians(float degrees) {
	return (degrees / 180.0) * M_PI;
}

float DragonMath::ModWithSign(float a, float n) {
	return a - floor(a/n) * n;
}

float DragonMath::GetSmallestDeltaAngle(float aTarget, float aSource) {
	float a = aTarget - aSource;
	return ModWithSign(a + 180, 360) - 180;
}
