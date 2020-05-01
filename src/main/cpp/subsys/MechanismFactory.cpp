
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

//========================================================================================================
/// MechanismFactory.cpp
//========================================================================================================
///
/// File Description:
///     This controls the creation of mechanisms/subsystems
///
//========================================================================================================

// C++ Includes
#include <map>
#include <memory>

// FRC includes

// Team 302 includes
#include <hw/interfaces/IDragonMotorController.h>
#include <hw/usages/IDragonMotorControllerMap.h>
#include <hw/usages/AnalogInputMap.h>
#include <hw/usages/DigitalInputMap.h>
#include <hw/usages/DragonSolenoidMap.h>
#include <hw/usages/ServoMap.h>
#include <hw/DragonSolenoid.h>
#include <hw/DragonServo.h>
#include <hw/DragonAnalogInput.h>
#include <hw/DragonDigitalInput.h>
#include <subsys/ControlPanel.h>
#include <subsys/MechanismFactory.h>
#include <subsys/HookDelivery.h>
#include <subsys/IMechanism.h>
#include <subsys/MechanismTypes.h>
#include <subsys/Intake.h>
#include <utils/Logger.h>
#include <subsys/Impeller.h>
#include <subsys/BallTransfer.h>
#include <subsys/Turret.h>
#include <subsys/Shooter.h>
#include <subsys/ShooterHood.h>

// Third Party Includes
#include <rev/ColorSensorV3.h>
#include <ctre/phoenix/sensors/CANCoder.h>


using namespace std;
using namespace rev;
using namespace ctre::phoenix::sensors;


//=====================================================================================
/// Method:         GetMechanismFactory
/// Description:    Find or create the mechanism factory
/// Returns:        MechanismFactory* pointer to the mechanism factory
//=====================================================================================
MechanismFactory* MechanismFactory::m_mechanismFactory = nullptr;
MechanismFactory* MechanismFactory::GetMechanismFactory()
{
	if ( MechanismFactory::m_mechanismFactory == nullptr )
	{
		MechanismFactory::m_mechanismFactory = new MechanismFactory();
	}
	return MechanismFactory::m_mechanismFactory;
}

MechanismFactory::MechanismFactory()
{
	m_mechanisms.resize( MechanismTypes::MECHANISM_TYPE::MAX_MECHANISM_TYPES );
	for ( auto inx=0; inx<MechanismTypes::MECHANISM_TYPE::MAX_MECHANISM_TYPES; ++inx )
	{
		m_mechanisms[inx] = nullptr;
	}
}

/// @brief      Find the requested mechanism
/// @param [in] MechanismTypes::MECHANISM_TYPE  type - the type of mechanism to retrieve
/// @return     IMechanism*  pointer to the mechanism or nullptr if mechanism doesn't exist.
IMechanism*  MechanismFactory::GetIMechanism
(
	MechanismTypes::MECHANISM_TYPE			type		
)
{
    // See if the mechanism was created already, if it wasn't create it
	IMechanism* subsys = m_mechanisms[type];
	if ( subsys == nullptr )
    {
        string msg = "mechanism doesn't exists";
        msg += to_string( type );
        Logger::GetLogger()->LogError( string("MechansimFactory::GetIMechanism" ), msg );
    }
	return subsys;
}



/// @brief      create the requested mechanism
/// @param [in] MechanismTypes::MECHANISM_TYPE  type - the type of mechanism to create
/// @param [in] const IDragonMotorControllerMap& map of the motor usage to the motor controller
/// @param [in] 
/// @param [in] 
/// @param [in] 
/// @param [in] 
/// @return  IMechanism*  pointer to the mechanism or nullptr if mechanism couldn't be created.
IMechanism*  MechanismFactory::CreateIMechanism
(
	MechanismTypes::MECHANISM_TYPE			type,
	const IDragonMotorControllerMap&        motorControllers,   // <I> - Motor Controllers
	const DragonSolenoidMap&                solenoids,
	const ServoMap&						    servos,
	const DigitalInputMap&					digitalInputs,
	const AnalogInputMap&                   analogInputs,
	ColorSensorV3*					        colorSensor,
	shared_ptr<CANCoder>					canCoder
)
{
    // See if the mechanism was created already, if it wasn't create it
	IMechanism* subsys = m_mechanisms[type];
	if ( subsys != nullptr )
    {
        string msg = "mechanism already exists";
        msg += to_string( type );
        Logger::GetLogger()->LogError( string("MechansimFactory::CreateIMechanism" ), msg );
    }
    else
    {
        // Create the mechanism
        switch ( type )
        {
            case MechanismTypes::MECHANISM_TYPE::INTAKE:
            {
				auto motor = GetMotorController( motorControllers, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::INTAKE );
				if ( motor.get() != nullptr )
				{
					auto solenoid = GetSolenoid( solenoids, SolenoidUsage::SOLENOID_USAGE::INTAKE );
					if ( solenoid.get() != nullptr )
					{
						auto intake = new Intake( motor, solenoid );
						subsys = dynamic_cast<IMechanism*>( intake );
					}
				}
            }
            break;

			case MechanismTypes::MECHANISM_TYPE::IMPELLER:
			{
				auto motor = GetMotorController( motorControllers, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::IMPELLER );
				if ( motor.get() != nullptr )
				{
					auto impeller = new Impeller(motor, canCoder);
					subsys = dynamic_cast<IMechanism*>(impeller);
				}
			}
			break;
			
			case MechanismTypes::MECHANISM_TYPE::BALL_TRANSFER:
			{
				auto motor = GetMotorController( motorControllers, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::BALL_TRANSFER );
				if ( motor.get() != nullptr )
				{
					auto ballTrans = new BallTransfer( motor );
					subsys = dynamic_cast<IMechanism*>( ballTrans );
				}
			}
			break;			
			
			case MechanismTypes::MECHANISM_TYPE::SHOOTER:
			{
				auto motor1 = GetMotorController( motorControllers, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::SHOOTER_1 );
				auto motor2 = GetMotorController( motorControllers, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::SHOOTER_2 );
				if ( motor1.get() != nullptr && motor2.get() != nullptr )
				{
					auto shooter = new Shooter(motor1, motor2);
					subsys = dynamic_cast<IMechanism*>(shooter);
				}
			}
			break;			
			
			case MechanismTypes::MECHANISM_TYPE::SHOOTER_HOOD:
			{
				auto shooterHoodMotor = GetMotorController ( motorControllers, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::SHOOTER_HOOD );
				if ( shooterHoodMotor.get() != nullptr )
				{
					auto shooterHood = new ShooterHood( shooterHoodMotor, canCoder);
					subsys = dynamic_cast<IMechanism*>(shooterHood);
				}
			}
			break;		
			
			case MechanismTypes::MECHANISM_TYPE::CONTROL_TABLE_MANIPULATOR:
			{
				auto motor = GetMotorController( motorControllers, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::CONTROL_TABLE_MANIPULATOR );
				if ( motor.get() != nullptr )
				{
					auto solenoid = GetSolenoid( solenoids, SolenoidUsage::SOLENOID_USAGE::CONTROL_TABLE_MANIPULATOR );
					if ( solenoid.get() != nullptr )
					{
						if ( colorSensor !=nullptr )
						{
							//todo color sensor pointer needs to be added to the constructor
							auto controlPanel = new ControlPanel( motor, solenoid, colorSensor );
							subsys = dynamic_cast<IMechanism*>(controlPanel);
						}
					}
				}
			}
			break;		
			
			case MechanismTypes::MECHANISM_TYPE::CLIMBER:
			{
			}
			break;		
			
			case MechanismTypes::MECHANISM_TYPE::CRAWLER:
			{
			}
			break;
			
			case MechanismTypes::MECHANISM_TYPE::TURRET:
			{
				auto motor = GetMotorController(motorControllers, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::TURRET);
				if(motor.get() != nullptr)
				{
					auto turret = new Turret(motor);
					subsys = dynamic_cast<IMechanism*>(turret);
				}
			}
			break;

			case MechanismTypes::MECHANISM_TYPE::HOOK_DELIVERY:
			{
				auto motor = GetMotorController(motorControllers, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::HOOK_DELIVERY);
				if(motor.get() != nullptr)
				{
					auto hook = new HookDelivery(motor);
					subsys = dynamic_cast<IMechanism*>(hook);
				}
			}
			break;

            default:
			{
				string msg = "unknown Mechanism type ";
				msg += to_string( type );
				Logger::GetLogger()->LogError( "MechanismFactory::CreateIMechanism", msg );
			}
            break;
        }
		m_mechanisms[type] = subsys;
    }

	return subsys;
}

shared_ptr<IDragonMotorController> MechanismFactory::GetMotorController
(
	const IDragonMotorControllerMap&				motorControllers,
	MotorControllerUsage::MOTOR_CONTROLLER_USAGE	usage
)
{
	shared_ptr<IDragonMotorController> motor;
	auto it = motorControllers.find( usage );
	if ( it != motorControllers.end() )  // found it
	{
		motor = it->second;
	}
	else
	{
		string msg = "motor not found; usage = ";
		msg += to_string( usage );
		Logger::GetLogger()->LogError( string( "MechanismFactory::GetMotorController" ), msg );
	}
	
	if ( motor.get() == nullptr )
	{
		string msg = "motor is nullptr; usage = ";
		msg += to_string( usage );
		Logger::GetLogger()->LogError( string( "MechanismFactory::GetMotorController" ), msg );
	}
	return motor;
}

shared_ptr<DragonSolenoid> MechanismFactory::GetSolenoid
(
	const DragonSolenoidMap&						solenoids,
	SolenoidUsage::SOLENOID_USAGE					usage
)
{
	shared_ptr<DragonSolenoid> solenoid;
	auto it = solenoids.find( usage );
	if ( it != solenoids.end() )  // found it
	{
		solenoid = it->second;
	}
	else
	{
		string msg = "solenoid not found; usage = ";
		msg += to_string( usage );
		Logger::GetLogger()->LogError( string( "MechanismFactory::GetSolenoid" ), msg );
	}
	
	if ( solenoid.get() == nullptr )
	{
		string msg = "solenoid is nullptr; usage = ";
		msg += to_string( usage );
		Logger::GetLogger()->LogError( string( "MechanismFactory::GetSolenoid" ), msg );
	}
	return solenoid;
}
shared_ptr<DragonServo> MechanismFactory::GetServo
(
	const ServoMap&									servos,
	ServoUsage::SERVO_USAGE							usage
)
{
	shared_ptr<DragonServo> servo;
	auto it = servos.find( usage );
	if ( it != servos.end() )  // found it
	{
		servo = it->second;
	}
	else
	{
		string msg = "servo not found; usage = ";
		msg += to_string( usage );
		Logger::GetLogger()->LogError( string( "MechanismFactory::GetServo" ), msg );
	}
	
	if ( servo.get() == nullptr )
	{
		string msg = "servo is nullptr; usage = ";
		msg += to_string( usage );
		Logger::GetLogger()->LogError( string( "MechanismFactory::GetServo" ), msg );
	}
	return servo;

}
shared_ptr<DragonDigitalInput> MechanismFactory::GetDigitalInput
(
	const DigitalInputMap&							digitaInputs,
	DigitalInputUsage::DIGITAL_SENSOR_USAGE			usage
)
{
	shared_ptr<DragonDigitalInput> dio;
	auto it = digitaInputs.find( usage );
	if ( it != digitaInputs.end() )  // found it
	{
		dio = it->second;
	}
	else
	{
		string msg = "digital input not found; usage = ";
		msg += to_string( usage );
		Logger::GetLogger()->LogError( string( "MechanismFactory::GetDigitalInput" ), msg );
	}
	
	if ( dio.get() == nullptr )
	{
		string msg = "digital input is nullptr; usage = ";
		msg += to_string( usage );
		Logger::GetLogger()->LogError( string( "MechanismFactory::GetDigitalInput" ), msg );
	}
	return dio;
}
shared_ptr<DragonAnalogInput> MechanismFactory::GetAnalogInput
(
	const AnalogInputMap&							analogInputs,
	AnalogInputUsage::ANALOG_SENSOR_USAGE			usage
)
{
	shared_ptr<DragonAnalogInput> anIn;
	auto it = analogInputs.find( usage );
	if ( it != analogInputs.end() )  // found it
	{
		anIn = it->second;
	}
	else
	{
		string msg = "analog input not found; usage = ";
		msg += to_string( usage );
		Logger::GetLogger()->LogError( string( "MechanismFactory::GetAnalogInput" ), msg );
	}
	
	if ( anIn.get() == nullptr )
	{
		string msg = "analog input is nullptr; usage = ";
		msg += to_string( usage );
		Logger::GetLogger()->LogError( string( "MechanismFactory::GetAnalogInput" ), msg );
	}
	return anIn;
}



