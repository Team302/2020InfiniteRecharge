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


#include <vector>
#include <memory>
#include <string>

#include <controllers/ControlModes.h>
#include <controllers/ControlData.h>
#include <subsys/ControlPanel.h>

#include <frc/util/color.h>
#include <rev/ColorMatch.h>
#include <rev/ColorSensorV3.h>

#include <hw/interfaces/IDragonMotorController.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <utils/logger.h>
#include <rev/ColorSensorV3.h>

using namespace std;
using namespace frc;
using namespace rev;

ControlPanel::ControlPanel
(
    std::shared_ptr<IDragonMotorController>     motorController,
    std::shared_ptr<DragonSolenoid>             solenoid,
    ColorSensorV3*                              colorSensor
) : IMechanism(), 
    m_spinner ( motorController ),
    m_manipulatorExtender (solenoid),
    m_color( colorSensor ),
    m_colorMatcher( new ColorMatch())
{
    if (m_spinner.get() == nullptr )
    {
        Logger::GetLogger()->LogError( string( "Intake constructor" ), string( "motorController is nullptr" ) );
    }

    if (m_manipulatorExtender.get() == nullptr )
    {
        Logger::GetLogger()->LogError( string( "Intake constructor" ), string( "solenoid is nullptr" ) );
    }
    m_colorMatcher->AddColorMatch(kBlueTarget);
    m_colorMatcher->AddColorMatch(kGreenTarget);
    m_colorMatcher->AddColorMatch(kRedTarget);
    m_colorMatcher->AddColorMatch(kYellowTarget);
}

//ControlPanel::~ControlPanel)()
//{
//    delete m_spinner;
//    delete m_manipulatorExtender;
//}
MechanismTypes::MECHANISM_TYPE ControlPanel::GetType() const 
{
    return MechanismTypes::MECHANISM_TYPE::CONTROL_TABLE_MANIPULATOR;
}

void ControlPanel::SetOutput
(
    ControlModes::CONTROL_TYPE controlType,
    double                     value       
)
{
    if ( m_spinner.get() != nullptr )
    {
        m_spinner.get()->SetControlMode(controlType);
        m_spinner.get()->Set( value );
    }
    else 
    {
        Logger::GetLogger()->LogError( string("ControlPanel::SetOutput"), string("No spiner") );
    }
}

void ControlPanel::ActivateSolenoid
(
    bool activate
)
{
    if ( m_manipulatorExtender.get() != nullptr )
    {
        m_manipulatorExtender.get()->Set( activate );
    }
    else
    {
        Logger::GetLogger()->LogError( string("ControlPanel::ActivateSolenoid"), string("No manipulatorExtender") );
    }
    
}

bool ControlPanel::IsSolenoidActivated
(

)
{
    bool on = false;

    if ( m_manipulatorExtender.get() != nullptr )
    {
       on = m_manipulatorExtender.get() -> Get();
    }
    else
    {
        Logger::GetLogger()->LogError(string("ControlPanel::IsSolenoid"), string("manipulatorExtender"));
    }
    
    return on;
    
}

double ControlPanel::GetCurrentPosition 
(

)const
{
    Logger::GetLogger()->LogError(string("ControlPanel::GetCurrentPosition"),string( "Called"));
    return 0.0;     //subj. to change

}



double ControlPanel::GetCurrentSpeed
(

)const
{
    Logger::GetLogger()->LogError(string("ControlPanel::GetCurrentSpeed"),string( "Called"));
    return 0.0;     //subj. to change
}



/// @brief  Set the control constants (e.g. PIDF values).
/// @param [in] ControlData*                                   pid:  the control constants
/// @return void
void ControlPanel::SetControlConstants
(
    ControlData*                                pid                 
)
{
    m_spinner.get()->SetControlConstants( pid );
}

ControlPanelColors::COLOR ControlPanel::GetColorSeen()
{
    frc::Color detectedColor = m_color->GetColor();
    //uint32_t detectedProximity = m_color->GetProximity();
    //std::string colorString;
    double confidence = 0.0;
    frc::Color matchedColor = m_colorMatcher->MatchClosestColor(detectedColor, confidence);
    if(matchedColor == kGreenTarget && confidence >= 0.94 )
    {
        return ControlPanelColors::COLOR::BLUE;
    }
    else if(matchedColor == kBlueTarget && confidence >= 0.94 )
    {
        return ControlPanelColors::COLOR::GREEN;
    }
    else if(matchedColor == kYellowTarget && confidence >= 0.9 )
    {
        return ControlPanelColors::COLOR::YELLOW;
    }
    else if(matchedColor == kBlueTarget && confidence >= 0.9 )
    {
        return ControlPanelColors::COLOR::RED;
    }
    return ControlPanelColors::COLOR::UNKNOWN;
}