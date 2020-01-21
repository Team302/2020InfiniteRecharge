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

#include <frc/Timer.h>
#include <controllers/ControlModes.h>
#include <controllers/ControlData.h>
#include <subsys/ControlPanel.h>

#include <frc/util/color.h>
#include <rev/ColorMatch.h>
#include <rev/ColorSensorV3.h>

#include <hw/interfaces/IDragonMotorController.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <utils/logger.h>

using namespace std;

static constexpr frc::Color kBlueTarget = frc::Color(0.143, 0.427, 0.429);
static constexpr frc::Color kGreenTarget = frc::Color(0.197, 0.561, 0.240);
static constexpr frc::Color kRedTarget = frc::Color(0.561, 0.232, 0.114);
static constexpr frc::Color kYellowTarget = frc::Color(0.361, 0.524, 0.113);

//todo: this needs to come in as a parameter to the constructor not a static item
static constexpr auto i2cPort = frc::I2C::Port::kOnboard;
rev::ColorSensorV3 m_colorSensor{i2cPort};
rev::ColorMatch m_colorMatcher;
frc::Timer m_timer = frc::Timer();

ControlPanel::ControlPanel
(
    std::shared_ptr<IDragonMotorController>     motorController,
    std::shared_ptr<DragonSolenoid>             solenoid
) : m_spinner ( motorController ),
    m_manipulatorExtender (solenoid)

{
    if (m_spinner.get() == nullptr )
    {
        Logger::GetLogger()->LogError( string( "Intake constructor" ), string( "motorController is nullptr" ) );
    }

    if (m_manipulatorExtender.get() == nullptr )
    {
        Logger::GetLogger()->LogError( string( "Intake constructor" ), string( "solenoid is nullptr" ) );
    }
    m_colorMatcher.AddColorMatch(kBlueTarget);
    m_colorMatcher.AddColorMatch(kGreenTarget);
    m_colorMatcher.AddColorMatch(kRedTarget);
    m_colorMatcher.AddColorMatch(kYellowTarget);
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
(ControlModes::CONTROL_TYPE controlType,
   double                   value       )
{
    if ( m_spinner != nullptr )
    {
        m_spinner->SetControlMode(controlType);
        m_spinner->Set( value );
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
    if ( m_manipulatorExtender != nullptr )
    {
        m_manipulatorExtender->Set( activate );
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

    if ( m_manipulatorExtender != nullptr )
    {
       on = m_manipulatorExtender -> Get();
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

double ControlPanel::GetTargetPosition 
(

)const
{
    Logger::GetLogger()->LogError(string("ControlPanel::GetTargetPosition"),string ("Called"));
    return 0.0;     //subj. to change
}


double ControlPanel::GetCurrentSpeed
(

)const
{
    Logger::GetLogger()->LogError(string("ControlPanel::GetCurrentSpeed"),string( "Called"));
    return 0.0;     //subj. to change
}


double ControlPanel::GetTargetSpeed
(

)const
{
    Logger::GetLogger()->LogError(string("ControlPanel::GetTargetSpeed"), string("Called"));
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
    Logger::GetLogger()->LogError(string("ControlPanel::SetControlConstants"), string("Called"));
}

ControlPanel::Colors ControlPanel::GetColorSeen()
{
    frc::Color detectedColor = m_colorSensor.GetColor();
    uint32_t detectedProximity = m_colorSensor.GetProximity();
    std::string colorString;
    double confidence = 0.0;
    frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);
    if(matchedColor == kGreenTarget && confidence >= 0.94 )
        return Colors::BLUE;
    else if(matchedColor == kBlueTarget && confidence >= 0.94 )
        return Colors::GREEN;
    else if(matchedColor == kYellowTarget && confidence >= 0.9 )
        return Colors::YELLOW;
    else if(matchedColor == kBlueTarget && confidence >= 0.9 )
        return Colors::RED;
    else 
        return Colors::UNKNOWN;
}