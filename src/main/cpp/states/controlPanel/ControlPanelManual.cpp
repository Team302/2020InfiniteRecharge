//====================================================================================================================================================
// Copyright 2020 MILK PRIME
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

#include <memory>

#include <states/IState.h>
#include <subsys/IMechanism.h>
#include <subsys/MechanismFactory.h>
#include <subsys/ControlPanel.h>
#include <states/controlPanel/ControlPanelManual.h>
#include <controllers/ControlData.h>
#include <controllers/ControlModes.h>
#include <utils/Logger.h>

using namespace std;

ControlPanelManual::ControlPanelManual(ControlData* control_data, double target)  : IState(),
                                                                                    m_controller( TeleopControl::GetInstance() )
{
    auto factory = MechanismFactory::GetMechanismFactory();
    m_control_panel_manipulator = factory -> GetIMechanism(MechanismTypes::MECHANISM_TYPE::CONTROL_TABLE_MANIPULATOR);

    if ( m_controller == nullptr )
    {
        Logger::GetLogger()->LogError( string( "ControlPanelManual::ControlPanelManual"), string("teleopControl is a nullptr"));
    }

}

// Creates the desired target location for the spin to end at

void ControlPanelManual::Init()
{
    if ( m_controller != nullptr )
    {
        m_controller->SetAxisProfile( TeleopControl::FUNCTION_IDENTIFIER::CONTROL_PANEL_MANUAL, IDragonGamePad::AXIS_PROFILE::CUBED );
    }

}


void ControlPanelManual::Run()
{

auto manipulator = m_controller->GetAxisValue( TeleopControl::FUNCTION_IDENTIFIER::CONTROL_PANEL_MANUAL );

m_control.get()->SetOutput( ControlModes::PERCENT_OUTPUT, manipulator );

}


bool ControlPanelManual::AtTarget() const
{
    return true;
}
