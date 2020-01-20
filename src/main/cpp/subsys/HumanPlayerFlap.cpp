//====================================================================================================================================================
/// Copyright 2019 Lake Orion Robotics FIRST Team 302
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
/// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
/// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
/// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================

// C++ Includes
#include <vector>
#include <memory>
#include <string>
// FRC includes

// Team 302 includes
#include <controllers/ControlModes.h>
#include <controllers/ControlData.h>
#include <hw/DragonSolenoid.h>
#include <hw/interfaces/IDragonMotorController.h>
#include <utils/Logger.h>
#include <subsys/HumanPlayerFlap.h>
// Third Party Includes

using namespace std;

HumanPlayerFlap::HumanPlayerFlap
(
    std::shared_ptr<DragonSolenoid>     solenoid
) : m_openFlap( solenoid )
{

if (m_openFlap.get() == nullptr )
{
    Logger::GetLogger()->LogError( string( "Human Player Flap constructor" ), string( "solenoid is nullptr" ) );
}

}

MechanismTypes::MECHANISM_TYPE HumanPlayerFlap::GetType() const
{
    return MechanismTypes::MECHANISM_TYPE::HUMAN_PLAYER_FLAP;
}

void HumanPlayerFlap::SetOutput
(
     ControlModes::CONTROL_TYPE controlType,
     double                                   value    
)
{
    Logger::GetLogger()->LogError( string("HumanPlayerFlap::SetOutput"), string("No master") );
}

void HumanPlayerFlap::ActivateSolenoid
(
    bool activate 
)
{
    if ( m_openFlap != nullptr )
    {
        m_openFlap->Set( activate );
    }
    else
    {
    Logger::GetLogger()->LogError( string("HumanPlayerFlap::ActivateSolenoid"), string("No openFlap") );
    }
}

bool HumanPlayerFlap::IsSolenoidActivated
(

)
{
    bool on = false;

    if ( m_openFlap != nullptr )
    {
       on = m_openFlap -> Get();
    }
    else
    {
        Logger::GetLogger()->LogError(string("HumanPlayerFlap::IsSolenoid"), string("No openFlap"));
    }
    
    return on;
}

double HumanPlayerFlap::GetCurrentPosition
(

)const
{
    Logger::GetLogger()->LogError(string("HumanPlayerFlap::GetCurrentPosition"),string( "Called"));
    return 0.0;     //subj. to change
}

double HumanPlayerFlap::GetTargetPosition
(

)const
{
    Logger::GetLogger()->LogError(string("HumanPlayerFlap::GetCurrentPosition"),string( "Called"));
    return 0.0;     //subj. to change
}

double HumanPlayerFlap::GetCurrentSpeed
(

)const
{
    Logger::GetLogger()->LogError(string("HumanPlayerFlap::GetCurrentPosition"),string( "Called"));
    return 0.0;     //subj. to change
}

double HumanPlayerFlap::GetTargetSpeed
(

)const
{
    Logger::GetLogger()->LogError(string("HumanPlayerFlap::GetCurrentPosition"),string( "Called"));
    return 0.0;     //subj. to change
}

void HumanPlayerFlap::SetControlConstants
(
    ControlData*    pid
)
{
    Logger::GetLogger()->LogError(string("HumanPlayerFlap::SetControlConstants"), string("Called"));
}