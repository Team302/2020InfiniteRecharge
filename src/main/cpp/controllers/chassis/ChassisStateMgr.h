
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

#pragma once

// c++ includes
#include <memory>
#include <string> 

// frc includes
#include <frc/smartdashboard/SendableChooser.h>

// team 302 includes
#include <controllers/chassis/ArcadeDrive.h>
#include <controllers/chassis/GTADrive.h>
#include <controllers/chassis/TankDrive.h>

class ChassisStateMgr
{
    public:
        /// @enum   CHASSIS_STATE
        /// @brief  States the Chassis can be in
        enum CHASSIS_STATE
        {
            AUTON,
            TELEOP,
            DRIVER_ASSIST_DRIVE_TO_LOADING_STATION,
            MAX_CHASSIS_STATES
        };

        /// @brief create chassis states
        ChassisStateMgr();

        /// @brief initialize this object
        void Init();

        /// @brief  run the current state
        /// @return void
        void RunCurrentState();

        /// @brief      change the state of the chassis
        /// @param [in] CHASSIS_STATE the state to put the chassis in
        /// @return     void
        void SetState( CHASSIS_STATE state );

    private:

      std::shared_ptr<ArcadeDrive>    m_arcade;
      std::shared_ptr<GTADrive>       m_gta;
      std::shared_ptr<TankDrive>      m_tank;
      std::shared_ptr<IState>         m_currentDrive;

      CHASSIS_STATE                   m_currentState;

      frc::SendableChooser<std::string>   m_driveModeChooser;                    
      const std::string                   m_driveModeArcade = "Arcade";     
	  const std::string					  m_driveModeArcadeCurve = "Arcade Curvature";
      const std::string                   m_driveModeGTA = "GTA";       
      const std::string                   m_driveModeGTACurve = "GTA Curvature";       
      const std::string                   m_driveModeTank = "Tank";       
      std::string                         m_driveModeSelected;       


};