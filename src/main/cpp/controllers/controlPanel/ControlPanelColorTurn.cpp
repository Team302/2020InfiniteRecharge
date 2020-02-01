/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// C++ Includes
#include <memory>

// FRC includes

// Team 302 includes
#include <controllers/IState.h>
#include <subsys/IMechanism.h>
#include <subsys/MechanismFactory.h>
#include <controllers/controlPanel/ControlPanelColorTurn.h>
#include  <subsys/ControlPanel.h>
#include <utils/logger.h>

// Third Party Includes

using namespace std;

ControlPanelColorTurn::ControlPanelColorTurn
(
    ControlData*    control,
    double          target
) : IState(),
    m_control( control ),
    m_target( target )

{
    auto factory = MechanismFactory::GetMechanismFactory();

    m_controlPanel = dynamic_cast < ControlPanel* >( factory -> GetIMechanism(MechanismTypes::MECHANISM_TYPE::CONTROL_TABLE_MANIPULATOR));

    

}

void ControlPanelColorTurn::Init()
{
    auto currentColor = m_controlPanel -> GetColorSeen();
    auto targetColor = m_controlPanel -> GetColorSeen();
    if (currentColor == ControlPanel::COLORS::BLUE)
    {
        if (targetColor == ControlPanel::COLORS::BLUE)
        {
            colorUnits = 2;
            rescan = false;
        }
        else if (targetColor == ControlPanel::COLORS::GREEN)
        {
            colorUnits = -1;
            rescan = false;
        }
        else if (targetColor == ControlPanel::COLORS::RED)
        {
            colorUnits = 1;
            rescan = true;
        }
        else if (targetColor == ControlPanel::COLORS::YELLOW)
        {
            colorUnits = 1;
            rescan = false;
        }
        else if (targetColor == ControlPanel::COLORS::UNKNOWN)
        {
            Logger::GetLogger()->LogError( string("ControlPanelColorTurn::Init"), string("No return from FMS") );
            rescan = false;
        }
    }
    else if (currentColor == ControlPanel::COLORS::GREEN)
    {
        if (targetColor == ControlPanel::COLORS::BLUE)
        {
            colorUnits = 1;
            rescan = false;
        }
        else if (targetColor == ControlPanel::COLORS::GREEN)
        {
            colorUnits = 2;
            rescan = false;
        }
        else if (targetColor == ControlPanel::COLORS::RED)
        {
            colorUnits = -1;
            rescan = false;
        }
        else if (targetColor == ControlPanel::COLORS::YELLOW)
        {
            colorUnits = 1;
            rescan = true;
        }
        else if (targetColor == ControlPanel::COLORS::UNKNOWN)
        {
            Logger::GetLogger()->LogError( string("ControlPanelColorTurn::Init"), string("No return from FMS") );
            rescan = false;
        }
    }
    else if (currentColor == ControlPanel::COLORS::RED)
    {
    if (targetColor == ControlPanel::COLORS::BLUE)
        {
            colorUnits = 1;
            rescan = true;
        }
        else if (targetColor == ControlPanel::COLORS::GREEN)
        {
            colorUnits = 1;
            rescan = false;
        }
        else if (targetColor == ControlPanel::COLORS::RED)
        {
            colorUnits = 2;
            rescan = false;
        }
        else if (targetColor == ControlPanel::COLORS::YELLOW)
        {
            colorUnits = -1;
            rescan = false;
        }
        else if (targetColor == ControlPanel::COLORS::UNKNOWN)
        {
            Logger::GetLogger()->LogError( string("ControlPanelColorTurn::Init"), string("No return from FMS") );
            rescan = false;
        }
    }
    else if (currentColor == ControlPanel::COLORS::YELLOW)
    {
        if (targetColor == ControlPanel::COLORS::BLUE)
        {
            colorUnits = -1;
            rescan = false;
        }
        else if (targetColor == ControlPanel::COLORS::GREEN)
        {
            colorUnits = 1;
            rescan = true;
        }
        else if (targetColor == ControlPanel::COLORS::RED)
        {
            colorUnits = -1;
            rescan = false;
        }
        else if (targetColor == ControlPanel::COLORS::YELLOW)
        {
            colorUnits = 1;
            rescan = false;
        }
        else if (targetColor == ControlPanel::COLORS::UNKNOWN)
        {
            Logger::GetLogger()->LogError( string("ControlPanelColorTurn::Init"), string("No return from FMS") );
            rescan = false;
        }
    }
    else if (currentColor == ControlPanel::COLORS::UNKNOWN)
    {
        colorUnits = 1;
        rescan = true;
    }

rotations = (colorUnits / 358.0986);

}

void ControlPanelColorTurn::Run()           
{
    m_controlPanel -> SetOutput(m_control -> GetMode(), rotations);
}

bool ControlPanelColorTurn::AtTarget() const                                 //confirms that it worked
{
    if (m_controlPanel -> GetCurrentPosition() >= (rotations - 5) &&  m_controlPanel -> GetCurrentPosition() <= (rotations + 5) )
    { 
        return true;
    }
    else
    {
        return false;
    }
}
