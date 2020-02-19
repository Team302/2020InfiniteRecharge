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
#include <subsys/BallTransfer.h>
#include <hw/interfaces/IDragonMotorController.h>
#include <utils/Logger.h>
// Third Party Includes
using namespace std;

BallTransfer::BallTransfer

(
    std::shared_ptr<IDragonMotorController>     motorController
) : m_master ( motorController )

{
    if (m_master.get() == nullptr )
    {
        Logger::GetLogger()->LogError( string("BallTransfer conductor"), string("motorController is nullptr"));
    }
}

MechanismTypes::MECHANISM_TYPE BallTransfer::GetType() const
{
    return MechanismTypes::MECHANISM_TYPE::BALL_TRANSFER;
}

void BallTransfer::SetOutput
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
        Logger::GetLogger()->LogError( string("BallTransfer::SetOutput"), string("No master") );
    }
}

void BallTransfer::ActivateSolenoid
(
    bool     activate
)
{
    Logger::GetLogger()->LogError(string("BallTransfer::ActivateSolenoid"), string("Called"));
}

bool BallTransfer::IsSolenoidActivated
(

)
{            
    Logger::GetLogger()->LogError(string("BallTransfer::IsSolenoidActivated"), string("Called"));
    return false;
}

double BallTransfer::GetCurrentPosition
(

)const
{
    Logger::GetLogger()->LogError(string("BallTransfer::GetCurrentPosition"), string("Called"));
    return 0.0;
}

double BallTransfer::GetCurrentSpeed
(

)const
{
    Logger::GetLogger()->LogError(string("BallTransfer::GetCurrentSpeed"), string("Called"));
    return 0.0;
}


void BallTransfer::SetControlConstants
(
    ControlData*    pid
)
{
    m_master.get()->SetControlConstants( pid );
}