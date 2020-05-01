
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
#include <string>
#include <memory>

// FRC includes
#include <frc/Timer.h>
#include <frc/DriverStation.h>

// Team 302 includes
#include <auton/CyclePrimitives.h>
#include <auton/PrimitiveFactory.h>
#include <auton/AutonSelector.h>
#include <auton/PrimitiveEnums.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include <auton/PrimitiveParser.h>
#include <auton/PrimitiveParams.h>
#include <states/BallManipulator.h>
#include <utils/Logger.h>
#include <auton/primitives/AutoShoot.h>

// Third Party Includes

using namespace frc;
using namespace std;

CyclePrimitives::CyclePrimitives() : m_primParams(), 
									 m_currentPrimSlot(0), 
								     m_currentPrim(nullptr), 
									 m_primFactory(
									 PrimitiveFactory::GetInstance()), 
									 m_doNothing(nullptr), 
									 m_autonSelector( new AutonSelector()) ,
									 m_timer( make_unique<Timer>()),
									 m_maxTime( 0.0 ),
									 m_powerCells( new AutoShoot() ),
									 m_isDone( false )
{
}

void CyclePrimitives::Init()
{
	m_currentPrimSlot = 0; //Reset current prim
	m_primParams.clear();
	m_primParams = PrimitiveParser::ParseXML( m_autonSelector->GetSelectedAutoFile() );
	if (!m_primParams.empty())
	{
		GetNextPrim();
	}
}

void CyclePrimitives::Run()
{
	if (m_currentPrim != nullptr)
	{
		Logger::GetLogger()->LogError( string("CyclePrimitive::RunCurrentPrimitive"), string("Primitive Detected!"));
		m_currentPrim->Run();
		m_powerCells->Run();
		if (m_currentPrim->IsDone() )
		{
			GetNextPrim();
		}
	}
	else
	{
		Logger::GetLogger()->LogError(string("CyclePrimitive"), string("Completed"));
		m_isDone = true;
		m_primParams.clear();	// clear the primitive params vector
		m_currentPrimSlot = 0;  //Reset current prim slot
		RunDoNothing();
	}
}

bool CyclePrimitives::AtTarget() const
{
	return m_isDone;
}

void CyclePrimitives::GetNextPrim()
{
	PrimitiveParams* currentPrimParam = (m_currentPrimSlot < (int) m_primParams.size()) ? m_primParams[m_currentPrimSlot] : nullptr;

	m_currentPrim = (currentPrimParam != nullptr) ? m_primFactory->GetIPrimitive(currentPrimParam) : nullptr;
	if (m_currentPrim != nullptr && currentPrimParam != nullptr)
	{
		m_currentPrim->Init(currentPrimParam);
		m_powerCells->Init(currentPrimParam);
		m_maxTime = currentPrimParam->GetTime();
		m_timer->Reset();
		m_timer->Start();
	}

	m_currentPrimSlot++;
}

void CyclePrimitives::RunDoNothing()
{
	if (m_doNothing == nullptr)
	{	
		BallManipulator::BALL_MANIPULATOR_STATE state = BallManipulator::BALL_MANIPULATOR_STATE::HOLD;
		auto time = DriverStation::GetInstance().GetMatchTime();
		auto params = new PrimitiveParams( DO_NOTHING,          // identifier
		                                   time,              	// time
		                                   0.0,                 // distance
		                                   0.0,                 // target x location
		                                   0.0,                 // target y location
		                                   0.0,                 // heading
		                                   0.0,                 // start drive speed
		                                   0.0,					// end drive speed
										   state,
										   0.0                  
										   );             
		m_doNothing = m_primFactory->GetIPrimitive(params);
		m_doNothing->Init(params);
		m_powerCells->Init(params);
	}
	m_doNothing->Run();
}
