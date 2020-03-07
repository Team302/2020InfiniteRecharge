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
#include <vector>
#include <memory>
#include <string>
// FRC includes

// Team 302 includes
#include <controllers/ControlModes.h>
#include <controllers/ControlData.h>
#include <subsys/HookDelivery.h>
#include <hw/interfaces/IDragonMotorController.h>
#include <utils/Logger.h>
// Third Party Includes
using namespace std;

HookDelivery::HookDelivery

(
    std::shared_ptr<IDragonMotorController>     motorController
) : m_master ( motorController )

{
    if (m_master.get() == nullptr )
    {
        Logger::GetLogger()->LogError( string("HookDelivery constructor"), string("motorController is nullptr"));
    }
}

MechanismTypes::MECHANISM_TYPE HookDelivery::GetType() const
{
    return MechanismTypes::MECHANISM_TYPE::HOOK_DELIVERY;
}

void HookDelivery::SetOutput
(
    ControlModes::CONTROL_TYPE controlType,
    double        value 
)
{        
    if ( m_master.get() != nullptr )
    {
        m_master.get()->SetControlMode(controlType);
        m_master.get()->Set( value );
    }
    else 
    {
        Logger::GetLogger()->LogError( string("HookDelivery::SetOutput"), string("No master") );
    }
}

void HookDelivery::ActivateSolenoid
(
    bool     activate
)
{
    Logger::GetLogger()->LogError(string("HookDelivery::ActivateSolenoid"), string("Called"));
}

bool HookDelivery::IsSolenoidActivated
(

)
{            
    Logger::GetLogger()->LogError(string("HookDelivery::IsSolenoidActivated"), string("Called"));
    return false;
}

double HookDelivery::GetCurrentPosition
(

)const
{
    Logger::GetLogger()->LogError(string("HookDelivery::GetCurrentPosition"), string("Called"));
    return 0.0;
}

double HookDelivery::GetCurrentSpeed
(

)const
{
    Logger::GetLogger()->LogError(string("HookDelivery::GetCurrentSpeed"), string("Called"));
    return 0.0;
}


void HookDelivery::SetControlConstants
(
    ControlData*    pid
)
{
    m_master.get()->SetControlConstants( pid );
}