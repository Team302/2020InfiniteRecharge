/*
 * DragonServo.h
 */

#pragma once 

#include <string>
#include <vector>

#include <hw/usages/ServoUsage.h>

#include <frc/Servo.h>


class DragonServo
{
	public:

		DragonServo() = delete;

		//------------------------------------------------------------------------------
		// Method:		<<constructor>>
		// Description:	Create Servos for use in robot mechanisms
		//------------------------------------------------------------------------------
		DragonServo
		(
			ServoUsage::SERVO_USAGE 	deviceUsage,		// <I> - Usage of the servo
			int 						deviceID,			// <I> - PWM ID
			double 						minAngle,			// <I> - Minimun desired angle
			double						maxAngle			// <I> - Maximum desired angle
		);

		virtual ~DragonServo() = default;

		void Set(double value);
	    void SetOffline();
		double Get() const;
		void SetAngle(double angle);
		double GetAngle() const;

		ServoUsage::SERVO_USAGE GetUsage() const;
		void MoveToMaxAngle();
		void MoveToMinAngle();


	private:
		ServoUsage::SERVO_USAGE		m_usage;
		frc::Servo*                 m_servo;
		double 						m_minAngle;
		double						m_maxAngle;

};
