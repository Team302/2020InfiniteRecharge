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


//C++ Includes
#include <algorithm>
#include <iostream>
#include <string>

// Team 302 Includes
#include <hw/interfaces/IDragonMotorController.h>
#include <subsys/IMechanism.h>
#include <subsys/Crawler.h>
#include <controllers/ControlModes.h>
#include <subsys/MechanismTypes.h>
#include <utils/Logger.h>

using namespace std;

Crawler::Crawler
(
    std::shared_ptr<IDragonMotorController>      crawlerMotor
) : m_crawlerMotor( crawlerMotor ),
    m_target( 0.0 )
{
    if( m_crawlerMotor.get() == nullptr )
    {
        Logger::GetLogger()->LogError( string( "Crawler constructor" ), string( "motorMaster is nullptr" ) );
    }
}

///@brief Gets the type of the mechanism type
///@return MechanismTypes::MECHANISM_TYPE::CRAWLER
MechanismTypes::MECHANISM_TYPE Crawler::GetType() const
{
    return MechanismTypes::MECHANISM_TYPE::CRAWLER;
}

///@brief Run the mechanism as defined
///@param [in] ControlModes::CONTROL_TYPE controlType
///@param [in] double value
void Crawler::SetOutput
(
    ControlModes::CONTROL_TYPE controlType,
    double  value
)
{
    m_target = value;
    if( m_crawlerMotor != nullptr)
    {
        m_crawlerMotor->SetControlMode( controlType );
        m_crawlerMotor->Set( value );
        m_target = value;
    }
    else
    {
        Logger::GetLogger()->LogError( string("Crawler::SetOutput"), string("No motorMaster") );
    }
}

///@brief extends or retracts the solenoid
///@param [in] bool activate: true = extend, false = retract
///@return void
void Crawler::ActivateSolenoid
(
    bool activate
)
{
    //No Solenoid in Crawler; Nothing to do.
    Logger::GetLogger()->LogError( string("Crawler::ActivateSolenoid"), string( "Called" ) );
}

///@brief checks to see if the solenoid is extended or retracted
///@return false
bool Crawler::IsSolenoidActivated()
{
    Logger::GetLogger()->LogError( string( "Crawler::IsSolenoidActivated" ), string( "Called" ) );
    return false; //No Solenoid on Crawler
}

///@brief Retrieves the current position of the mechanism
///@return double 0.0
double Crawler::GetCurrentPosition() const
{
    Logger::GetLogger()->LogError( string( "Crawler::GetCurrentPosition" ), string( "Called" ) );
    return 0.0; //no encoder
}

///@brief Retrieves the target position of the mechanism
///@return double 0.0

///@brief Retrieves the current speed of the mechanism.
///@return double 0.0
double Crawler::GetCurrentSpeed() const
{
    Logger::GetLogger()->LogError( string( "Crawler::GetCurrentSpeed" ), string( "Called" ) );
    return 0.0; //no encoder
}

///@brief Sets the control constants (i.e PIDF values)
///@return void
void Crawler::SetControlConstants
(
    ControlData*    pid
)
{
    Logger::GetLogger()->LogError( string( "Crawler::SetControlConstants" ), string("Called") ); 
}
