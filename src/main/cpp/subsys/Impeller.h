
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

#pragma once

//========================================================================================================
/// @interface IMechanism
/// @brief     This is the interface for all subsystems
//========================================================================================================

// C++ Includes
#include <vector>

// FRC includes

// Team 302 includes
#include <controllers/ControlModes.h>
#include <subsys/MechanismTypes.h>
#include <controllers/ControlData.h>
#include <subsys/IMechanism.h>
#include <hw/DragonTalon.h>
#include <hw/interfaces/IDragonMotorController.h>
// Third Party Includes
#include <ctre/phoenix/sensors/CANCoder.h>

using namespace std;

///	 @interface IMechanism
///  @brief	    Interface for subsystems
class Impeller : public IMechanism
{
	public:

        /// @brief          Indicates the type of mechanism this is
        /// @return         MechanismTypes::MECHANISM_TYPE
        MechanismTypes::MECHANISM_TYPE GetType() const override;


        /// @brief      Run mechanism as defined 
        /// @param [in] ControlModes::CONTROL_TYPE   controlType:  How are the item(s) being controlled
        /// @param [in] double                                     value:        Target (units are based on the controlType)
        /// @return     void
        void SetOutput
        (
            ControlModes::CONTROL_TYPE controlType,
            double                                   value       
        ) override;

        /// @brief      Activate/deactivate pneumatic solenoid
        /// @param [in] bool - true == extend, false == retract
        /// @return     void 
        void ActivateSolenoid
        (
            bool     activate
        ) override;

        /// @brief      Check if the pneumatic solenoid is activated
        /// @return     bool - true == extended, false == retract
        bool IsSolenoidActivated() override;


        /// @brief  Return the current position of the mechanism.  The value is in inches or degrees.
        /// @return double	position in inches (translating mechanisms) or degrees (rotating mechanisms)
        double GetCurrentPosition() const override;

        /// @brief  Get the current speed of the mechanism.  The value is in inches per second or degrees per second.
        /// @return double	speed in inches/second (translating mechanisms) or degrees/second (rotating mechanisms)
        double GetCurrentSpeed() const override;


        /// @brief  Set the control constants (e.g. PIDF values).
        /// @param [in] ControlData*                                   pid:  the control constants
        /// @return void
        void SetControlConstants
        (
            ControlData*                                pid                 
        ) override;

        Impeller() = delete;
        Impeller
        (
            std::shared_ptr<IDragonMotorController> motor,
            std::shared_ptr<ctre::phoenix::sensors::CANCoder> encoder
        );

        private:
        std::shared_ptr<IDragonMotorController> m_motor;
        std::shared_ptr<ctre::phoenix::sensors::CANCoder> m_encoder;
        double m_target;
        mutable double m_lastTimeStamp;
        mutable double m_lastVelocity;
        
	
	//virtual ~Impeller() = default;
};
