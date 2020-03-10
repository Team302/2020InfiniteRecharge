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



#include <states/shooter/ShooterDifferentSpeeds.h>
#include <controllers/ControlData.h>
#include <subsys/MechanismFactory.h>
#include <subsys/IMechanism.h>
#include <subsys/MechanismTypes.h>
#include <states/MechanismState.h>
#include <controllers/MechanismTargetData.h>
#include <states/IState.h>

ShooterDifferentSpeeds::ShooterDifferentSpeeds
(
    ControlData*                    controlData, 
    double                          target
    
) : m_positionBased( false ),
    m_speedBased( false )
{
    m_mechanism = dynamic_cast <Shooter*> (MechanismFactory::GetMechanismFactory()->GetIMechanism(MechanismTypes::SHOOTER));
}

void ShooterDifferentSpeeds::Init()
{
    if ( m_mechanism != nullptr && m_control != nullptr )
    {
        m_mechanism->SetControlConstants( m_control );
    }


}

void ShooterDifferentSpeeds::Run()
{

    if ( m_mechanism != nullptr && m_control != nullptr )
    {
        auto lower = 0.9 * m_target;
        m_mechanism->SetOutput( m_control->GetMode(), m_target, lower );
    }

    
}

bool ShooterDifferentSpeeds::AtTarget() const
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

