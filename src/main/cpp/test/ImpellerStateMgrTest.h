
//====================================================================================================================================================
// Copyright 2020 Lake Orion Robotics FIRST Team 302
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
#include <test/IStateTest.h>
#include <controllers/impeller/ImpellerStateMgr.h>

// Third Party Includes


///	 @class ImpellerStateMgrTest
///  @brief	Tests for ImpellerStateMgr.  There are the following states: OFF, HOLD and AGITATE, TO_SHOOTER.  Each will run for 15 seconds in the following order:
///         HOLD, OFF, AGITATE, TO_SHOOTER.
class ImpellerStateMgrTest : public IStateTest
{
	public:
		ImpellerStateMgrTest();
		~ImpellerStateMgrTest() = default;
		
		/// @brief Initialize the test setup.  This will be called from Robot::TestInit()
		/// @return void
		void Init() override;
		
		/// @brief Run the test.  This will be called from Robot::TestPeriodic()
		/// @return void		
		void Periodic() override;
		
		/// @brief Indicate whether the test has completed or not.
		/// @return bool - true: test has completed, false: test is still running
		bool IsDone() override;
		
	private:
		std::unique_ptr<frc::Timer>				m_timer;
		std::unique_ptr<ImpellerStateMgr>	    m_stateMgr;
		bool                                    m_ranOff;
		bool                                    m_ranHold;
		bool                                    m_ranShoot;
		bool                                    m_ranAgitate;
		bool 									m_isDone;
		const double m_stateTestPeriod = 15.0;
};

		