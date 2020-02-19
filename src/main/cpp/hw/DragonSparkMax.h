/*
* DragonSparkMax.h
*
* Date Created: Jan 15, 2019
* Author: Jonah Shader
*/

#pragma once

#include <memory>

#include <frc/SpeedController.h>

#include <controllers/ControlModes.h>
#include <hw/interfaces/IDragonMotorController.h>
#include <hw/usages/MotorControllerUsage.h>

// Third Party Includes
#include <ctre/phoenix/motorcontrol/RemoteSensorSource.h>
#include <rev/CANSparkMax.h>

// namespaces
//using namespace rev;

class DragonSparkMax : public IDragonMotorController
{
    public:
        //note: two PIDs: 0 is position, 1 is velocity
        // Constructors
        DragonSparkMax() = delete;
        DragonSparkMax
        (
            int id, 
            int pdpID,
            MotorControllerUsage::MOTOR_CONTROLLER_USAGE deviceType, 
            rev::CANSparkMax::MotorType motorType, 
            double gearRatio
        );

        virtual ~DragonSparkMax() = default;

        // Getters
        double GetRotations() const override;
        double GetRPS() const override;
        MotorControllerUsage::MOTOR_CONTROLLER_USAGE GetType() const override;
        int GetID() const override;
        std::shared_ptr<frc::SpeedController> GetSpeedController() const override;
        double GetCurrent() const override;

        std::shared_ptr<rev::CANSparkMax> GetSparkMax() const;
        

        // Setters
        void SetControlMode(ControlModes::CONTROL_TYPE mode) override;
        void Set(double value) override;
        void SetRotationOffset(double rotations) override;
        void SetVoltageRamping(double ramping, double rampingClosedLoop = -1) override; // seconds 0 to full, set to 0 to disable
        void EnableCurrentLimiting(bool enabled) override;
        void EnableBrakeMode(bool enabled) override;
        void Invert(bool inverted) override;
        void SetSensorInverted( bool inverted) override;

        /// @brief  Set the control constants (e.g. PIDF values).
        /// @param [in] ControlData*   pid - the control constants
        /// @return void
        void SetControlConstants(ControlData* controlInfo) override;

        void SetSmartCurrentLimiting(int limit);
        rev::CANError Follow(DragonSparkMax* leader, bool invert = false);

        void SetRemoteSensor
        (
            int                                             canID,
            ctre::phoenix::motorcontrol::RemoteSensorSource deviceType
        ) override;
        void SetDiameter( double diameter ) override;
    private:
        double GetRotationsWithGearNoOffset() const;
        int m_id;
        int m_pdp;
        std::shared_ptr<rev::CANSparkMax> m_spark;
        ControlModes::CONTROL_TYPE m_controlMode;
        double m_outputRotationOffset;
        double m_gearRatio;
		double m_diameter;
        MotorControllerUsage::MOTOR_CONTROLLER_USAGE m_deviceType;    
        const int m_countsPerRev = 40;
};