
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
#include <test/ShooterStateMgrTest.h>

#include <controllers/shooter/ShooterStateMgr.h>

// Third Party Includes


using namespace std;
using namespace frc;

///	 @class ShooterStateMgrTest
///  @brief Tests for ShooterStateMgr.  There are three states: OFF, GET_READY, and SHOOT.  This will run each for 15 seconds each;
///  		running GET_READY, then SHOOT and finally OFF.
ShooterStateMgrTest::ShooterStateMgrTest() : IStateTest(),
											 m_timer( make_unique<Timer>() ),
											 m_stateMgr( make_unique<ShooterStateMgr>() ),
											 m_ranReady( false ),
											 m_ranShoot( false ),
											 m_ranOff( false ),
											 m_isDone( false )
{
}
		
/// @brief Initialize the test setup.  This will be called from Robot::TestInit()
/// @return void
void ShooterStateMgrTest::Init()
{
	m_timer->Reset();
	m_timer->Start();
	m_stateMgr->SetCurrentState( ShooterStateMgr::SHOOTER_STATE::GET_READY, true );
	m_ranReady = true;
}

/// @brief Run the test.  This will be called from Robot::TestPeriodic()
/// @return void		
void ShooterStateMgrTest::Periodic()
{
	if ( m_timer->HasPeriodPassed( m_stateTestPeriod ) )
	{
		if ( !m_ranReady )
		{
			m_stateMgr->SetCurrentState( ShooterStateMgr::SHOOTER_STATE::GET_READY, false );
			m_ranReady = true;
		}
		else if ( !m_ranShoot )
		{
			m_stateMgr->SetCurrentState( ShooterStateMgr::SHOOTER_STATE::SHOOT, false );
			m_ranShoot = true;
		}
		else if ( !m_ranOff )
		{
			m_stateMgr->SetCurrentState( ShooterStateMgr::SHOOTER_STATE::OFF, false );
			m_ranOff = true;
		}
		else
		{
			m_stateMgr->SetCurrentState( ShooterStateMgr::SHOOTER_STATE::OFF, false );
			m_isDone = true;
		}
		m_timer->Reset();
		m_timer->Start();
	}
	m_stateMgr->RunCurrentState();
}

/// @brief Indicate whether the test has completed or not.
/// @return bool - true: test has completed, false: test is still running
bool ShooterStateMgrTest::IsDone()
{
	return m_isDone;
}

		