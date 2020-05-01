///@class Climber
///@brief The Climber subsystem. Includes pneumatic extender and winch.

//C++ Includes
#include <algorithm>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

//Team 302 Includes
#include <hw/interfaces/IDragonMotorController.h>
#include <subsys/IMechanism.h>
#include <subsys/Climber.h>
#include <controllers/ControlModes.h>
#include <subsys/MechanismTypes.h>
#include <utils/Logger.h>

//Third Party Includes

using namespace std;

///@brief Create and initialize the Climber sub-mechanism
///@param [in] std::shared_ptr<IDragonMotorController>  masterMotor - motor for Climber
///@param [in] std::shared_ptr<DragonSolenoid>  masterSolenoid - solenoid for Climber
///@param [in] double   winchDiameter - The diameter of winch in inches.
Climber::Climber
(
    shared_ptr<IDragonMotorController>             masterMotor,
    shared_ptr<DragonSolenoid>                     masterSolenoid,
    double                                         winchDiameter
) : m_motorMaster( masterMotor ),
    m_solenoidMaster( masterSolenoid ),
    m_winchDiameter( winchDiameter),
    m_target( 0.0 )
{
    if ( m_motorMaster.get() == nullptr )
    {
        Logger::GetLogger()->LogError( string( "Climber constructor" ), string( "motorMaster is nullptr" ) );
    }

    if ( m_solenoidMaster.get() == nullptr )
    {
        Logger::GetLogger()->LogError( string( "Climber constructor" ), string( "solenoidMaster is nullptr" ) );
    }

}

///@brief Indicates that this is Climber
///@return IMechanism::MECHANISM_TYPE::CLIMBER
MechanismTypes::MECHANISM_TYPE Climber::GetType() const
{
    return MechanismTypes::MECHANISM_TYPE::CLIMBER;
}

///@brief Run winch motor as defined
///@param [in] ControlModes::CONTROL_TYPE   controlType:    How the winch is being controlled
///@param [in] double   value:  Target (units are based on controlType)
///@return void
void Climber::SetOutput
(
    ControlModes::CONTROL_TYPE controlType,
    double                      value
)
{
    m_target = value;
    if ( m_motorMaster.get() != nullptr )
    {

        m_motorMaster.get()->SetControlMode( controlType );
        m_motorMaster.get()->Set( value );
        m_target = value;
    }
    else
    {
        Logger::GetLogger()->LogError( "Climber::SetOutput", "No motorMaster" );
    }
    
}

///@brief Activate/Deactivate the extender Solenoid
///@param [in] bool - true == extend, false == retract 
///@return void
void Climber::ActivateSolenoid
(
    bool activate
)
{
    if (m_solenoidMaster.get() != nullptr )
    {
        m_solenoidMaster.get()->Set(activate);
    }
    else
    {
        Logger::GetLogger()->LogError( "Climber::ActivateSolenoid", "No solenoidMaster");
    }
    
}

///@brief Check if the extender solenoid is activated
///@return  bool - true == extended, false == retracted
bool Climber::IsSolenoidActivated()
{
    bool solenoidStatus = false;
    if ( m_solenoidMaster.get() != nullptr )
    {
       solenoidStatus = m_solenoidMaster.get()->Get();
    }
    else
    {
        Logger::GetLogger()->LogError( "Climber::IsSolenoidActivated", "No solenoidMaster");
    }
    return solenoidStatus;
    
}

///@brief Return the current position of the climber in inches
///@return double   position in inches (positive is forward, negative is backward)
double Climber::GetCurrentPosition() const
{
    double distance = 0.0;
    if (m_motorMaster.get() != nullptr )
    {
        distance = ( m_winchDiameter * M_PI);
        auto nRotations = m_motorMaster.get()->GetRotations();
        distance *= nRotations;
    }
    else
    {
        Logger::GetLogger()->LogError( "Climber::SetOutput", "No master" ); 
    }
    return distance;
}

///@brief return the current speed of the climber in degrees per second.
///@return double   speed in degrees per second
double Climber::GetCurrentSpeed() const
{
    double speed = 0.0;
    if ( m_motorMaster.get() != nullptr )
    {
        speed = ( m_winchDiameter * M_PI ); // distance the wheel travels per revolution (inches)
        auto rps = m_motorMaster.get()->GetRPS(); // number of rotations per second
        speed *= rps;                       // distance per revolution * revolutions per second is inches per second
    }
    else
    {
        Logger::GetLogger()->LogError( "Climber::GetCurrentSpeed", "No motorMaster" );
    }
    return speed;

}

///@brief Set the control constants (e.g. PIDF values)
///@param [in] ControlData*     pid - the control constants
///@return void
void Climber::SetControlConstants
(
    ControlData*                    pid
)
{
    // todo:  need to account for voltage mode
    m_motorMaster.get()->SetControlConstants(pid);
}
