
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

// C++ Includes
#include <map>
#include <memory>

// FRC includes
#include <frc/SpeedController.h>

// Team 302 includes
#include <hw/usages/MotorControllerUsage.h>
#include <controllers/ControlModes.h>
#include <controllers/ControlData.h>

// Third Party Includes
#include <ctre/phoenix/motorcontrol/RemoteSensorSource.h>

/// @interface IDragonMotorController
/// @brief The general interface to motor controllers so that the specific mechanisms that use motors,
///        don't need to special case what motor controller is being used.
class IDragonMotorController
{
    public:
        // Getters
        /// @brief  Return the number of revolutions the output shaft has spun
        /// @return double number of revolutions
        virtual double GetRotations() const = 0;

        /// @brief  Return the angular velocity in revolutions per second
        /// @return double angular velocity in revolutions per second
        virtual double GetRPS() const = 0;

        /// @brief  Return the usage of the motor
        /// @return MotorControllerUsage::MOTOR_CONTROLLER_USAGE - what the motor is used for
        virtual MotorControllerUsage::MOTOR_CONTROLLER_USAGE GetType() const = 0;

        /// @brief  Return the current usage
        /// @return double - amperage usage for the controller
        virtual double GetCurrent() const = 0;

        /// @brief  Return the CAN ID
        /// @return int - CAN ID
        virtual int GetID() const = 0;

        /// @brief  Return the speedcontroller 
        /// @return std::shared_ptr<frc::SpeedControll> - pointer to the speed controller object
        virtual std::shared_ptr<frc::SpeedController> GetSpeedController() const = 0;

        // Setters
        virtual void SetControlMode(ControlModes::CONTROL_TYPE mode) = 0;
        virtual void Set(double value) = 0;
        virtual void SetRotationOffset(double rotations) = 0;
        virtual void SetVoltageRamping(double ramping, double closedLoopRamping = -1) = 0;
        virtual void EnableCurrentLimiting(bool enabled) = 0;
        virtual void EnableBrakeMode(bool enabled) = 0;
        virtual void Invert(bool inverted) = 0;
        virtual void SetSensorInverted(bool inverted) = 0;
		virtual void SetDiameter( double diameter ) = 0;


        /// @brief  Set the control constants (e.g. PIDF values).
        /// @param [in] ControlData*   pid - the control constants
        /// @return void
        virtual void SetControlConstants(ControlData* controlInfo) = 0;

        virtual void SetRemoteSensor
        (
            int                                             canID,
            ctre::phoenix::motorcontrol::RemoteSensorSource deviceType
        ) = 0;

    protected:
        IDragonMotorController() = default;
        virtual ~IDragonMotorController() = default;
};

