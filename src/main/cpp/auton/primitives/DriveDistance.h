
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

#include <auton/primitives/SuperDrive.h>

class PrimitiveParams;

class DriveDistance : public SuperDrive 
{
public:
	bool IsDone() override;
	void Init(PrimitiveParams* params) override;
	void Run() override;
	DriveDistance();
	virtual ~DriveDistance() = default;

protected:
    void SetDistance
    (
        double distance
    );
private:
	void CalculateSlowDownDistance();
	PrimitiveParams* m_params;

	float m_targetDistance;
	float m_initialDistance;
	float m_timeRemaining;

	float m_minSpeedCountTime;
	int m_underSpeedCounts;
	float m_startHeading;
	float m_endHeading;
	float m_minSpeed;
	bool m_arcing;

	const float SPEED_THRESHOLD = 1.5;
	const float MIN_SPEED_COUNT_TIME = 0.5; //seconds before we start checking for wall collisions
	const int UNDER_SPEED_COUNT_THRESHOLD = 4;
	const float DECEL_TIME_MULTIPLIER = 0.85; //0.75
};

