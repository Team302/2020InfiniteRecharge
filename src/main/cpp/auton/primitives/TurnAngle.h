
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

// Team 302 includes
#include <auton/primitives/IPrimitive.h>
#include <subsys/IChassis.h>

// Third Party Includes


class TurnAngle : public IPrimitive 
{
    public:
        TurnAngle();
        virtual ~TurnAngle() = default;

        void Init(PrimitiveParams* params) override;
        void Run() override;
        bool IsDone() override;

    private:
        const float PROPORTIONAL_COEFF  = 3.0; //0.5
        const float INTREGRAL_COEFF     = 0.0;
        const float DERIVATIVE_COEFF    = 0.0;
        const float FEET_FORWARD_COEFF  = 0.0;

        std::shared_ptr<IChassis> m_chassis;
   		std::unique_ptr<frc::Timer> m_timer;

        float m_targetAngle;
        float m_maxTime;
        float m_leftPos;
        float m_rightPos;
        bool m_isDone;

        const float ANGLE_THRESH = 2; // +/- threshold for being at angle
        const float MAX_VELOCITY = 20; //inches per second
        const float MIN_VELOCITY = 4;
        const float ANGLE_DIFFERENCE_VELOCITY_MULTIPLIER = 0.7;
};

