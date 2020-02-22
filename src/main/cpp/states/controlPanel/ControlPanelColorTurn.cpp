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
#include <states/IState.h>
#include <subsys/IMechanism.h>
#include <subsys/MechanismFactory.h>
#include <states/controlPanel/ControlPanelColorTurn.h>
#include  <subsys/ControlPanel.h>
#include <utils/logger.h>
#include <utils/ControlPanelColors.h>
#include <utils/FMS.h>

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
    auto targetColor = FMS::GetFMS() -> GetColor();

    // Figure out the number of colors the wheel has to spin by.
    // In the event of something that isnt possible then move over by one and rescan.

    if (currentColor == ControlPanelColors::COLOR::BLUE)
    {
        if (targetColor == ControlPanelColors::COLOR::BLUE)
        {
            colorUnits = 2;
            rescan = false;
        }
        else if (targetColor == ControlPanelColors::COLOR::GREEN)
        {
            colorUnits = -1;
            rescan = false;
        }
        else if (targetColor == ControlPanelColors::COLOR::RED)
        {
            colorUnits = 1;
            rescan = true;
        }
        else if (targetColor == ControlPanelColors::COLOR::YELLOW)
        {
            colorUnits = 1;
            rescan = false;
        }
        else if (targetColor == ControlPanelColors::COLOR::UNKNOWN)
        {
            Logger::GetLogger()->LogError( string("ControlPanelColorTurn::Init"), string("No return from FMS") );
            rescan = false;
        }
    }
    else if (currentColor == ControlPanelColors::COLOR::GREEN)
    {
        if (targetColor == ControlPanelColors::COLOR::BLUE)
        {
            colorUnits = 1;
            rescan = false;
        }
        else if (targetColor == ControlPanelColors::COLOR::GREEN)
        {
            colorUnits = 2;
            rescan = false;
        }
        else if (targetColor == ControlPanelColors::COLOR::RED)
        {
            colorUnits = -1;
            rescan = false;
        }
        else if (targetColor == ControlPanelColors::COLOR::YELLOW)
        {
            colorUnits = 1;
            rescan = true;
        }
        else if (targetColor == ControlPanelColors::COLOR::UNKNOWN)
        {
            Logger::GetLogger()->LogError( string("ControlPanelColorTurn::Init"), string("No return from FMS") );
            rescan = false;
        }
    }
    else if (currentColor == ControlPanelColors::COLOR::RED)
    {
    if (targetColor == ControlPanelColors::COLOR::BLUE)
        {
            colorUnits = 1;
            rescan = true;
        }
        else if (targetColor == ControlPanelColors::COLOR::GREEN)
        {
            colorUnits = 1;
            rescan = false;
        }
        else if (targetColor == ControlPanelColors::COLOR::RED)
        {
            colorUnits = 2;
            rescan = false;
        }
        else if (targetColor == ControlPanelColors::COLOR::YELLOW)
        {
            colorUnits = -1;
            rescan = false;
        }
        else if (targetColor == ControlPanelColors::COLOR::UNKNOWN)
        {
            Logger::GetLogger()->LogError( string("ControlPanelColorTurn::Init"), string("No return from FMS") );
            rescan = false;
        }
    }
    else if (currentColor == ControlPanelColors::COLOR::YELLOW)
    {
        if (targetColor == ControlPanelColors::COLOR::BLUE)
        {
            colorUnits = -1;
            rescan = false;
        }
        else if (targetColor == ControlPanelColors::COLOR::GREEN)
        {
            colorUnits = 1;
            rescan = true;
        }
        else if (targetColor == ControlPanelColors::COLOR::RED)
        {
            colorUnits = -1;
            rescan = false;
        }
        else if (targetColor == ControlPanelColors::COLOR::YELLOW)
        {
            colorUnits = 1;
            rescan = false;
        }
        else if (targetColor == ControlPanelColors::COLOR::UNKNOWN)
        {
            Logger::GetLogger()->LogError( string("ControlPanelColorTurn::Init"), string("No return from FMS") );
            rescan = false;
        }
    }
    else if (currentColor == ControlPanelColors::COLOR::UNKNOWN)
    {
        colorUnits = 1;
        rescan = true;
    }

// convert colorunits into degrees
// the number is (the arc length of one color / our wheels circumfrence) * 360

rotations = (colorUnits * 358.0986);

}

void ControlPanelColorTurn::Run()           

//makes the motor turn the number of required degrees

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
