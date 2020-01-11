
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
#include <memory>

// FRC includes
#include <frc/Timer.h>
// Team 302 includes
#include <subsys/IChassis.h>
#include <auton/primitives/IPrimitive.h>
#include <utils/DragonMath.h>

// Third Party Includes




class SuperDrive : public IPrimitive 
{
	public:
		void Init(PrimitiveParams* params) override;
		void Run() override;
		bool IsDone() override;
		void SlowDown();
		bool ReachedTargetSpeed();

		const float GYRO_CORRECTION_CONSTANT = 6; //2.3
		const float INCHES_PER_SECOND_SECOND = 120; //120
		const float MIN_SPEED_SLOWDOWN       = 13;

protected: 
		SuperDrive();
		virtual ~SuperDrive() = default;

	private:
		const float PROPORTIONAL_COEFF  = 12.0; //16
		const float INTREGRAL_COEFF     = 0;
		const float DERIVATIVE_COEFF    = 0.0; //.16
		const float FEET_FORWARD_COEFF  = 0.0;

        std::shared_ptr<IChassis> m_chassis;
   		std::unique_ptr<frc::Timer> m_timer;

		float m_targetSpeed;
		float m_currentSpeed;
		float m_speedOffset;

		float m_leftSpeed;
		float m_rightSpeed;

		float m_currentHeading;
		float m_startHeading;

		bool m_slowingDown;
		bool m_reachedTargetSpeed;
		float m_accelDecelTime;
		float m_currentTime;
		float m_minSpeedSlowdown;
};

