/*
 * DragonServo.h
 */

#ifndef SRC_SUBSYS_COMPONENTS_DRAGONSERVO_H_
#define SRC_SUBSYS_COMPONENTS_DRAGONSERVO_H_

#include <string>
#include <vector>

#include <frc/Servo.h>

using namespace frc;

class DragonServo
{
	public:

		enum SERVO_USAGE
		{
			UNKNOWN_SERVO_USAGE = -1,
			ROTATE_LIMELIGHT,
			TAIL_CONTROL,
			MAX_SERVO_USAGES
		};
		DragonServo() = delete;

		//------------------------------------------------------------------------------
		// Method:		<<constructor>>
		// Description:	Create Servos for use in robot mechanisms
		//------------------------------------------------------------------------------
		DragonServo
		(
			DragonServo::SERVO_USAGE	deviceUsage,		// <I> - Usage of the servo
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

		DragonServo::SERVO_USAGE GetUsage() const;
		void MoveToMaxAngle();
		void MoveToMinAngle();


	private:
		DragonServo::SERVO_USAGE	m_usage;
		Servo*                      m_servo;
		double 						m_minAngle;
		double						m_maxAngle;

};
typedef std::vector<DragonServo*> DragonServoVector;

#endif /* SRC_SUBSYS_COMPONENTS_DRAGONSERVO_H_ */