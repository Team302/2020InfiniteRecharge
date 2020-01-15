/*
* DragonTalon.h
*
* Date Created: Jan 15, 2019
* Author: Jonah Shader
*/

#pragma once

#include <memory>
#include <vector>

#include <frc/SpeedController.h>


#include <hw/interfaces/IDragonMotorController.h>
#include <hw/usages/MotorControllerUsage.h>

#include <ctre/phoenix/ErrorCode.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>


class DragonTalon : public IDragonMotorController
{
  public:
    // Enums
    enum TALON_SENSOR_TYPE
    {
        NO_SENSOR = -1,
        QUAD_ENCODER,
        UNKNOWN_SENSOR,
        ANALOG_POT,
        ANALOG_ENCODER,
        ENCODER_RISING,
        ENCODER_FALLING,
        CTRE_MAG_ENCODER_RELATIVE,
        CTRE_MAG_ENCODER_ABSOLUTE,
        PULSE_WIDTH,
        MAX_SENSOR_TYPES
    };

    enum TALON_CONTROL_MODE
    {
        PERCENT,
        POSITION,
        VELOCITY,
        // RPS,
        FOLLOWER,
        MOTION_MAGIC,
        MAX_TALON_MODES
    };

    // Constructors
    DragonTalon() = delete;
    DragonTalon
    (
        MotorControllerUsage::MOTOR_CONTROLLER_USAGE deviceType, 
        int deviceID, 
        int pdpID, 
        int countsPerRev, 
        double gearRatio
    );
    virtual ~DragonTalon() = default;


    // Getters (override)
    double GetRotations() const override;
    double GetRPS() const override;
    MotorControllerUsage::MOTOR_CONTROLLER_USAGE GetType() const override;
    int GetID() const override;
    std::shared_ptr<frc::SpeedController> GetSpeedController() const override;
    double GetCurrent() const override;

    // Setters (override)
    void SetControlMode(IDragonMotorController::DRAGON_CONTROL_MODE mode) override; //:D
    void Set(double value) override;
    void SetRotationOffset(double rotations) override;
    void SetVoltageRamping(double ramping, double rampingClosedLoop = -1) override; // seconds 0 to full, set to 0 to disable
    void EnableCurrentLimiting(bool enabled) override; 
    void EnableBrakeMode(bool enabled) override; 
    void SetPIDF(double p, double i, double d, double f, int slot = 0) override; 
    void Invert(bool inverted) override; 

    // Setters (TalonSRX)
    // more complete SetControlMode method compared to the overrided one
    void SetControlMode(TALON_CONTROL_MODE mode); 
    void SetSensorInverted(bool inverted);

	// Method:		SelectClosedLoopProfile
	// Description:	Selects which profile slot to use for closed-loop control
	// Returns:		void
	void SelectClosedLoopProfile(int slot, int pidIndex);// <I> - 0 for primary closed loop, 1 for cascaded closed-loop

    int ConfigSelectedFeedbackSensor
    (
        ctre::phoenix::motorcontrol::FeedbackDevice feedbackDevice, 
        int pidIdx, 
        int timeoutMs
    ); 
    int ConfigSelectedFeedbackSensor
    (
        ctre::phoenix::motorcontrol::RemoteFeedbackDevice feedbackDevice, 
        int pidIdx, 
        int timeoutMs
    ); 
	int ConfigPeakCurrentLimit(int amps, int timeoutMs); 
	int ConfigPeakCurrentDuration(int milliseconds, int timeoutMs); 
	int ConfigContinuousCurrentLimit(int amps, int timeoutMs); 

    void SetAsSlave(int masterCANID); 

    //Methods for Motion Magic control mode
	void ConfigMotionAcceleration(float maxMotionAcceleration);      // in rotations per second per second
	void ConfigMotionCruiseVelocity(float maxMotionCruiseVelocity);  // in rotations per second
    void ConfigPeakOutput(double percentOutput);
    void ConfigNominalOutput(double nominalOutput);


  private:
    std::shared_ptr<ctre::phoenix::motorcontrol::can::WPI_TalonSRX>  m_talon;
    TALON_CONTROL_MODE m_controlMode;
    MotorControllerUsage::MOTOR_CONTROLLER_USAGE m_type;

    int m_id;
    int m_pdp;
    int m_countsPerRev;
    int m_tickOffset;
    double m_gearRatio;
};

typedef std::vector<DragonTalon*> DragonTalonVector;