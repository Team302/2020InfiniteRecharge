
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

// C++ Includes
#include <memory>
#include <string>

// FRC includes
#include <frc/Timer.h>
#include <units/units.h>

// Team 302 includes
#include <auton/primitives/DoNothing.h>
#include <auton/PrimitiveParams.h>
#include <auton/primitives/IPrimitive.h>
#include <subsys/ChassisFactory.h>
#include <controllers/ControlModes.h>
#include <subsys/IMechanism.h>
#include <utils/Logger.h>

// Third Party Includes


using namespace std;
using namespace frc;

//========================================================================================================
/// @class  DoNothing
/// @brief  This is an auton primitive that causes the chassis to not drive 
//========================================================================================================


/// @brief constructor that creates/initializes the object
DoNothing::DoNothing() : m_maxTime(0.0),
						 m_currentTime(0.0),
						 m_chassis( ChassisFactory::GetChassisFactory()->GetIChassis()),
						 m_timer( make_unique<Timer>() )
{
}

/// @brief initialize this usage of the primitive
/// @param PrimitiveParms* params the drive parameters
/// @return void
void DoNothing::Init(PrimitiveParams* params) 
{
	m_maxTime = params->GetTime();
	m_timer->Reset();
	m_timer->Start();
}

/// @brief run the primitive (periodic routine)
/// @return void
void DoNothing::Run() 
{
	Logger::GetLogger() -> LogError(string("DoNothing::Run()"), string("Arrived!"));
	if ( m_chassis != nullptr )
	{
		m_chassis->SetOutput( ControlModes::CONTROL_TYPE::PERCENT_OUTPUT, 0.0, 0.0 );  
	}
	else
	{
		Logger::GetLogger()->LogError( string( "DoNothing::Run" ), string( "chassis not found") );
	}
}

/// @brief check if the end condition has been met
/// @return bool true means the end condition was reached, false means it hasn't
bool DoNothing::IsDone() 
{
	return m_timer->HasPeriodPassed( m_maxTime );
}
