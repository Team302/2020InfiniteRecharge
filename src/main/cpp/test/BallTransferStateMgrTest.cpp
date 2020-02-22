
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
#include <string>

// FRC includes

// Team 302 includes
#include <test/IStateTest.h>
#include <test/BallTransferStateMgrTest.h>
#include <states/balltransfer/BallTransferStateMgr.h>

#include <utils/Logger.h>
// Third Party Includes


using namespace std;

///	 @class BallTransferStateMgrTest
///  @brief Tests for BallTransferStateMgr.  There are three states: OFF, TO_IMPELLER, and TO_SHOOTER.  This will run each for 15 seconds.
///  		running TO_IMPELLER, then OFF and finally TO_SHOOTER.
BallTransferStateMgrTest::BallTransferStateMgrTest() : IStateTest(),
													   m_stateMgr( BallTransferStateMgr::GetInstance() ),
													   m_ranImpeller( false ),
													   m_ranOff( false ),
													   m_ranShooter( false ),
													   m_isDone( false ),
													   m_loopCnt( 0 )
{	

}
		
/// @brief Initialize the test setup.  This will be called from Robot::TestInit()
/// @return void
void BallTransferStateMgrTest::Init()
{
	m_loopCnt = 0;
	m_stateMgr->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::TO_IMPELLER, true );
	m_ranImpeller = true;
}

/// @brief Run the test.  This will be called from Robot::TestPeriodic()
/// @return void		
void BallTransferStateMgrTest::Periodic()
{
	m_loopCnt++;
	if ( m_loopCnt > m_nloops )
	{
		if ( !m_ranImpeller )
		{
			m_stateMgr->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::TO_IMPELLER, false );
			m_ranImpeller = true;
		}
		else if ( !m_ranOff )
		{
			m_stateMgr->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::OFF, false );
			m_ranOff = true;
		}
		else if ( !m_ranShooter )
		{
			m_stateMgr->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::TO_SHOOTER, false );
			m_ranShooter = true;
		}
		else
		{
			m_stateMgr->SetCurrentState( BallTransferStateMgr::BALL_TRANSFER_STATE::OFF, false );
			m_isDone = true;
		}
		m_loopCnt = 0;
	}
	m_stateMgr->RunCurrentState();
}

/// @brief Indicate whether the test has completed or not.
/// @return bool - true: test has completed, false: test is still running
bool BallTransferStateMgrTest::IsDone()
{
	return m_isDone;
}

		