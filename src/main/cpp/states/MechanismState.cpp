
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
#include <memory>

// FRC includes

// Team 302 includes
#include <states/IState.h>
#include <states/MechanismState.h>
#include <controllers/ControlData.h>
#include <controllers/MechanismTargetData.h>
#include <subsys/IMechanism.h>
#include <utils/Logger.h>

#include <gamepad/TeleopControl.h>

// Third Party Includes

using namespace std;

/// @class MechanismState
/// @brief information about the control (open loop, closed loop position, closed loop velocity, etc.) for a mechanism state
MechanismState::MechanismState
(
    IMechanism*                     mechanism,
    ControlData*                    control,
    double                          target,
    MechanismTargetData::SOLENOID   solState
) : IState(),
    m_mechanism( mechanism ),
    m_control( control ),
    m_target( target ),
    m_solenoidState( solState ),
    m_positionBased( false ),
    m_speedBased( false )
{
    if ( mechanism == nullptr )
    {
        Logger::GetLogger()->LogError( string("MechanismState::MechanismState"), string("no mechanism"));
    }    
    
    if ( control == nullptr )
    {
        Logger::GetLogger()->LogError( string("MechanismState::MechanismState"), string("no control data"));
    }
    else
    {
        auto mode = control->GetMode();
        switch (mode)
        {
            case ControlModes::CONTROL_TYPE::PERCENT_OUTPUT:
                m_positionBased = false;
                m_speedBased = false;
                break;

            case ControlModes::CONTROL_TYPE::VOLTAGE:
                m_positionBased = false;
                m_speedBased = false;
                break;

            case ControlModes::CONTROL_TYPE::POSITION_DEGREES:
            case ControlModes::CONTROL_TYPE::POSITION_INCH:
                m_positionBased = true;
                m_speedBased = false;
                break;
            
            case ControlModes::CONTROL_TYPE::VELOCITY_DEGREES:
            case ControlModes::CONTROL_TYPE::VELOCITY_INCH:
            case ControlModes::CONTROL_TYPE::VELOCITY_RPS:
                m_positionBased = false;
                m_speedBased = true;
                break;

            case ControlModes::CONTROL_TYPE::CURRENT:
                m_positionBased = false;
                m_speedBased = false;
                break;

            case ControlModes::CONTROL_TYPE::MOTION_PROFILE:
                m_positionBased = false;
                m_speedBased = false;
                break;

            case ControlModes::CONTROL_TYPE::MOTION_PROFILE_ARC:
                m_positionBased = false;
                m_speedBased = false;
                break;

            case ControlModes::CONTROL_TYPE::TRAPEZOID:
                m_positionBased = false;
                m_speedBased = false;
                break;

            default:
                m_positionBased = false;
                m_speedBased = false;
                break;
        }
    }
    
}

void MechanismState::Init()
{
    if ( m_mechanism != nullptr && m_control != nullptr )
    {
        m_mechanism->SetControlConstants( m_control );
    }
}


void MechanismState::Run()           
{
    if ( m_mechanism != nullptr && m_control != nullptr )
    {
        m_mechanism->SetOutput( m_control->GetMode(), m_target );
        switch ( m_solenoidState )
        {
            case MechanismTargetData::SOLENOID::OFF:
                m_mechanism->ActivateSolenoid( false );
                break;
            
            case MechanismTargetData::SOLENOID::ON:
                m_mechanism->ActivateSolenoid( true );
                break;

            default:
                break;
        }
    }
}

bool MechanismState::AtTarget() const
{
    auto same = true;
    if ( m_mechanism != nullptr )
    {
        if ( m_positionBased && !m_speedBased )
        {
            same = ( abs( m_target - m_mechanism->GetCurrentPosition())  < 1.0 );
        }
        else if ( !m_positionBased && m_speedBased )
        {
            same = ( abs( m_target - m_mechanism->GetCurrentSpeed()) < 1.0 );
        }
        else if ( m_positionBased && m_speedBased )
        {
            same = ( ( abs( m_target - m_mechanism->GetCurrentPosition())  < 1.0 ) ||
                     ( abs( m_target - m_mechanism->GetCurrentSpeed())     < 1.0 ) );
        }
    }
    return same;
}

