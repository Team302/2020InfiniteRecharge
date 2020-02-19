
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

#pragma once


// C++ Includes

// FRC includes

// Team 302 includes
#include <hw/interfaces/IDragonMotorController.h>
#include <subsys/IChassis.h>
#include <subsys/IMechanism.h>
#include <controllers/ControlModes.h>
#include <subsys/MechanismTypes.h>
#include <controllers/ControlData.h>

// Third Party Includes


/// @class DragonChassis
/// @brief This is a differential chassis.  Each side of the robot will be treated as a separate mechanism
class DragonChassis : public IChassis
{
    public:


        /// @brief Create the subobjects and initialize the DragonChassis subsystem
        DragonChassis
        (
            double 						                            wheelDiameter,		
            double 					    	                        wheelBase,			
            double 						                            track,				
            std::shared_ptr<IDragonMotorController>                 leftMaster,
            std::shared_ptr<IDragonMotorController>                 rightMaster,
            std::shared_ptr<IDragonMotorController>                 leftFollower,
            std::shared_ptr<IDragonMotorController>                 rightFollower
        );
        DragonChassis() = delete;

        /// @brief clean up memory when this object gets deleted
        ~DragonChassis() override;

        /// @brief      Run chassis 
        /// @param [in] ControlModes::CONTROL_TYPE   controlType:  How are the item(s) being controlled
        /// @param [in] double                                     leftVvalue:   Left side target (units are based on the controlType)
        /// @param [in] double                                     rightValue:   Right side target (units are based on the controlType)
        /// @return     void
        void SetOutput
        (
            ControlModes::CONTROL_TYPE controlType,
            double                                   leftValue,
            double                                   rightValue     
        ) override;


        /// @brief  Return the current position of the center of the DragonChassis in inches.  
        /// @return double  position in inches of the center of the chassis
        double GetCurrentPosition() const override;

        /// @brief  Return the current position of the left side of the DragonChassis in inches.  
        /// @return double  position in inches of the left side of the chassis
        double GetCurrentLeftPosition() const override;

        /// @brief  Return the current position of the right side of the DragonChassis in inches.  
        /// @return double  position in inches of the right side of the chassis
        double GetCurrentRightPosition() const override;


        /// @brief  Return the current speed of the center of the DragonChassis in inches per second.  
        /// @return double  speed in inches per second of the center of the chassis
        double GetCurrentSpeed() const override;

        /// @brief  Return the current speed of the left side of the DragonChassis in inches per second.  
        /// @return double  speed in inches per second of the left side of the chassis
        double GetCurrentLeftSpeed() const override;

        /// @brief  Return the current speed of the right side of the DragonChassis in inches per second.  
        /// @return double  speed in inches per second of the right side of the chassis
        double GetCurrentRightSpeed() const override;


        /// @brief  Set the control constants (e.g. PIDF values).
        /// @param [in] ControlData*   pid - the control constants
        /// @return void
        void SetControlConstants
        (
            ControlData*                                 pid               
        ) override;

        double GetWheelDiameter() const override;
        
    private:
        IMechanism*                     m_leftSide;
        IMechanism*                     m_rightSide;

        double                          m_wheelBase;
        double                          m_wheelTrack;
        double                          m_wheelDiameter;
};




