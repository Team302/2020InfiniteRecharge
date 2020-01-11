/*
 * DragonServo.cpp
 */

#include <hw/DragonServo.h>

#include <frc/Servo.h>

using namespace frc;

DragonServo::DragonServo
(
	DragonServo::SERVO_USAGE	deviceUsage,		// <I> - Usage of the servo
	int 						deviceID,			// <I> - PWM ID
	double 						minAngle,			// <I> - Minimun desired angle
	double						maxAngle			// <I> - Maximum desired angle

) : m_usage( deviceUsage ),
    m_servo(),
	m_minAngle( minAngle ),
	m_maxAngle( maxAngle )
{
    switch ( deviceUsage )
    {
        case DragonServo::SERVO_USAGE::ROTATE_LIMELIGHT:
            m_servo =new Servo(deviceID);
            break;

        case DragonServo::SERVO_USAGE::TAIL_CONTROL:
            m_servo = new Servo(deviceID);
            break;

        default:
         break;
    }
}



void DragonServo::Set(double value)
{
    if ( m_servo != nullptr )
    {
        m_servo->Set( value );
    }
    else
    {
//        printf( "==>> servo not initialize \n ");
    }

}
void DragonServo::SetOffline()
{
    if ( m_servo != nullptr )
    {
        m_servo->SetOffline();
    }
    else
    {
//        printf( "==>> servo not initialize \n ");
    }

}
double DragonServo::Get() const
{
    double value = 0.0;
    if ( m_servo != nullptr )
    {
        value = m_servo->Get();
    }
    else
    {
 //       printf( "==>> servo not initialize \n ");
    }
    return value;
}
void DragonServo::SetAngle(double angle)
{
    printf( "==>> moving to angle %g \n", angle );
    if ( m_servo != nullptr )
    {
        m_servo->SetAngle( angle );
    }
    else
    {
//        printf( "==>> servo not initialize \n ");
    }
}
double DragonServo::GetAngle() const
{
    double angle = 0.0;
    if ( m_servo != nullptr )
    {
        angle = m_servo->GetAngle();
    }
    else
    {
//        printf( "==>> servo not initialize \n ");
    }
    return angle;
}

void DragonServo::MoveToMaxAngle()
{
	SetAngle( m_maxAngle );
}

void DragonServo::MoveToMinAngle()
{
	SetAngle( m_minAngle );
}

DragonServo::SERVO_USAGE DragonServo::GetUsage() const
{
    return m_usage;
}