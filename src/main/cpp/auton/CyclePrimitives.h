
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

// Third Party Includes



#include <vector>
#include <states/IState.h>

class AutonSelector;
class AutoShoot;
class IPrimitive;
class PrimitiveFactory;
class PrimitiveParams;


class CyclePrimitives : public IState
{
	public:
		CyclePrimitives();
		virtual ~CyclePrimitives() = default;

		void Init() override;
		void Run() override;
	 	bool AtTarget() const override;


	protected:
		void GetNextPrim();
		void RunDoNothing();

	private:
		std::vector<PrimitiveParams*> 	m_primParams;
		int 							m_currentPrimSlot;
		IPrimitive*						m_currentPrim;
		PrimitiveFactory* 				m_primFactory;
		IPrimitive* 					m_doNothing;
		AutonSelector* 					m_autonSelector;
		std::unique_ptr<frc::Timer>     m_timer;
		double                          m_maxTime;
		AutoShoot*						m_powerCells;
		bool							m_isDone;
};

