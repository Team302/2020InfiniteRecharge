/*
 * DragonMath.h
 *
 *  Created on: Nov 29, 2017
 *      Author: jonah
 */

#ifndef SRC_UTILS_DRAGONMATH_H_
#define SRC_UTILS_DRAGONMATH_H_

struct Vector2 {
	double direction;
	double magnitude;
};

struct Point2D {
	double x;
	double y;
};

class DragonMath {

public:
	static float Distance(Point2D p1, Point2D p2);
	static float HeadingToStandardAngle(float headingInDegrees); //also returns in degrees
	static float DegreesToRadians(float degrees);
	static float ModWithSign(float a, float n); //return a % n with the corrected sign (because regular modulus doesn't for some reason)
	//TODO: run some hand checks on this algorithm to see if it works as intended. it should return an angle that will move target towards source
	static float GetSmallestDeltaAngle(float aTarget, float aSource); //returns the smallest angle between a and b with the correct sign in degrees

};

#endif /* SRC_UTILS_DRAGONMATH_H_ */
