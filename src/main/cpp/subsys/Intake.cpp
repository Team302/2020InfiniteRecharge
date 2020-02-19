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
#include <vector>
#include <memory>
#include <string>
// FRC includes

// Team 302 includes
#include <controllers/ControlModes.h>
#include <controllers/ControlData.h>
#include <subsys/Intake.h>
#include <hw/DragonSolenoid.h>
#include <hw/interfaces/IDragonMotorController.h>
#include <utils/Logger.h>
// Third Party Includes
using namespace std;

Intake::Intake

(
    std::shared_ptr<IDragonMotorController>     motorController,
    std::shared_ptr<DragonSolenoid>             solenoid
) : m_master( motorController ),
    m_crawlingLifter( solenoid )
{
    if (m_master.get() == nullptr )
    {
        Logger::GetLogger()->LogError( string( "Intake constructor" ), string( "motorController is nullptr" ) );
    }

    if (m_crawlingLifter.get() == nullptr )
    {
        Logger::GetLogger()->LogError( string( "Intake constructor" ), string( "solenoid is nullptr" ) );
    }

}

MechanismTypes::MECHANISM_TYPE Intake::GetType() const
{
    return MechanismTypes::MECHANISM_TYPE::INTAKE;
}

void Intake::SetOutput
(ControlModes::CONTROL_TYPE controlType,
   double                   value       )
{
    if ( m_master.get() != nullptr )
    {
        m_master.get()->SetControlMode(controlType);
        m_master.get()->Set( value );
    }
    else 
    {
        Logger::GetLogger()->LogError( string("Intake::SetOutput"), string("No master") );
    }
}

void Intake::ActivateSolenoid
(
    bool activate
)
{
    if ( m_crawlingLifter.get() != nullptr )
    {
        m_crawlingLifter.get()->Set( activate );
    }
    else
    {
        Logger::GetLogger()->LogError( string("Intake::ActivateSolenoid"), string("No crawlingLifter") );
    }
    
}

bool Intake::IsSolenoidActivated
(

)
{
    bool on = false;

    if ( m_crawlingLifter.get() != nullptr )
    {
       on = m_crawlingLifter.get() -> Get();
    }
    else
    {
        Logger::GetLogger()->LogError(string("Intake::IsSolenoid"), string("No crawlingLifter"));
    }
    
    return on;
    
}

double Intake::GetCurrentPosition 
(

)const
{
    Logger::GetLogger()->LogError(string("Intake::GetCurrentPosition"),string( "Called"));
    return 0.0;     //subj. to change

}



double Intake::GetCurrentSpeed
(

)const
{
    Logger::GetLogger()->LogError(string("Intake::GetCurrentSpeed"),string( "Called"));
    return 0.0;     //subj. to change
}


/// @brief  Set the control constants (e.g. PIDF values).
/// @param [in] ControlData*                                   pid:  the control constants
/// @return void
void Intake::SetControlConstants
(
    ControlData*                                pid                 
)
{
    m_master.get()->SetControlConstants( pid );
}





