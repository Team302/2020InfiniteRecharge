
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

// C++ Includes
#include <memory>

// FRC includes
#include <frc/Timer.h>

// Team 302 includes
#include <test/IStateTest.h>
#include <test/ImpellerStateMgrTest.h>

#include <states/impeller/ImpellerStateMgr.h>

// Third Party Includes


using namespace std;
using namespace frc;

///	 @class ImpellerStateMgrTest
///  @brief	Tests for ImpellerStateMgr.  There are the following states: OFF, HOLD and AGITATE, TO_SHOOTER.  Each will run for 15 seconds in the following order:
///         HOLD, OFF, AGITATE, TO_SHOOTER.
ImpellerStateMgrTest::ImpellerStateMgrTest() : IStateTest(),
													   m_stateMgr( ImpellerStateMgr::GetInstance() ),
													   m_ranOff( false ),
													   m_ranHold( false ),
													   m_ranShoot( false ),
													   m_ranAgitate( false ),
													   m_isDone( false ),
													   m_loopCnt( 0 )
{
}
		
/// @brief Initialize the test setup.  This will be called from Robot::TestInit()
/// @return void
void ImpellerStateMgrTest::Init()
{
	m_loopCnt = 0;
	m_stateMgr->SetCurrentState( ImpellerStateMgr::IMPELLER_STATE::HOLD, true );
	m_ranHold = true;
}

/// @brief Run the test.  This will be called from Robot::TestPeriodic()
/// @return void		
void ImpellerStateMgrTest::Periodic()
{
	m_loopCnt++;
	if ( m_loopCnt > m_nloops )	
	{
		if ( !m_ranHold )
		{
			m_stateMgr->SetCurrentState( ImpellerStateMgr::IMPELLER_STATE::HOLD, false );
			m_ranHold = true;
		}
		else if ( !m_ranShoot )
		{
			m_stateMgr->SetCurrentState( ImpellerStateMgr::IMPELLER_STATE::TO_SHOOTER, false );
			m_ranShoot = true;
		}
		else if ( !m_ranOff )
		{
			m_stateMgr->SetCurrentState( ImpellerStateMgr::IMPELLER_STATE::OFF, false );
			m_ranOff = true;
		}
		else if ( !m_ranAgitate )
		{
			m_stateMgr->SetCurrentState( ImpellerStateMgr::IMPELLER_STATE::AGITATE, false );
			m_ranAgitate = true;
		}
		else
		{
			m_stateMgr->SetCurrentState( ImpellerStateMgr::IMPELLER_STATE::OFF, false );
			m_isDone = true;
		}
		m_loopCnt = 0;
	}
	m_stateMgr->RunCurrentState();
}

/// @brief Indicate whether the test has completed or not.
/// @return bool - true: test has completed, false: test is still running
bool ImpellerStateMgrTest::IsDone()
{
	return m_isDone;
}

		