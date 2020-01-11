
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

#pragma once

// C++ Includes

// FRC includes

// Team 302 includes

// Third Party Includes



#include <auton/FieldDefn.h>

class FieldMeasurement
{
public:
	static 	FieldMeasurement* GetFieldMeasurement();

	float distances[2] { 24, 34.5 }; // L Scale, R Scale, L Switch, R Switch

	enum Measurement
	{
		BLUE_SWITCH_RIGHT,
		BLUE_SWITCH_LEFT,
		BLUE_SCALE_RIGHT,
		BLUE_SCALE_LEFT,
		RED_SWITCH_RIGHT,
		RED_SWITCH_LEFT,
		RED_SCALE_RIGHT,
		RED_SCALE_LEFT,
		UNKNOWN_FIELD,
		MAX_POSITIONS
	};
	float GetXLoc(Measurement location);
	float GetYLoc(Measurement location);
	void AddLocation
	(
			Measurement location,
			float x,
			float y
	);
	float GetKeyPoint( Measurement keyPointLocation );
private:
	FieldMeasurement();
	virtual ~FieldMeasurement() =default;

	static FieldMeasurement* m_fieldMeasurement;

	float m_xLoc[9];
	float m_yLoc[9];
};

