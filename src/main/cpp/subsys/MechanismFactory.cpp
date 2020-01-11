
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
#include <hw/usages/MotorControllerUsage.h>
#include <hw/DragonSolenoid.h>
#include <hw/DragonServo.h>
#include <hw/DragonAnalogInput.h>
#include <hw/DragonDigitalInput.h>
#include <subsys/MechanismFactory.h>
#include <subsys/IMechanism.h>
#include <subsys/MechanismTypes.h>
//#include <subsys/Intake.h>
#include <utils/Logger.h>

// Third Party Includes


using namespace std;


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

/// @brief      Find the requested mechanism
/// @param [in] MechanismTypes::MECHANISM_TYPE  type - the type of mechanism to retrieve
/// @return     IMechanism*  pointer to the mechanism or nullptr if mechanism doesn't exist.
IMechanism*  MechanismFactory::GetIMechanism
(
	MechanismTypes::MECHANISM_TYPE			type		
)
{
	IMechanism* subsys = nullptr;

    // See if the mechanism was created already, if it wasn't create it
    auto it = m_mechanisms.find( type );  
    if ( it != m_mechanisms.end() )      //  found
    {
        subsys = it->second;
    }
    else
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
    const DragonSolenoidVector&             solenoids,          // <I> - Solenoids
    const DragonDigitalInputVector&         digitalInputs,      // <I> - Digital Inputs
    const DragonAnalogInputVector&          analogInputs,       // <I> - Analog Inputs
    const DragonServoVector&                servos              // <I> - servos

)
{
	IMechanism* subsys = nullptr;

    // See if the mechanism was created already, if it wasn't create it
    auto it = m_mechanisms.find( type );  
    if ( it != m_mechanisms.end() )      //  found
    {
        subsys = it->second;
        string msg = "mechanism already exists";
        msg += to_string( type );
        Logger::GetLogger()->LogError( string("MechansimFactory::CreateIMechanism" ), msg );
    }
    else
    {
        // Create the mechanism
        switch ( type )
        {
            case MechanismTypes::MECHANISM_TYPE::DRIVETRAIN_SIDE:
            break;

            case MechanismTypes::MECHANISM_TYPE::SHOOTER:
            break;

            case MechanismTypes::MECHANISM_TYPE::ELEVATOR:
            break;

            case MechanismTypes::MECHANISM_TYPE::WRIST:
            break;

            case MechanismTypes::MECHANISM_TYPE::INTAKE:
            {
                /***
                auto it = motorControllers.find( MotorControllerUsage::MOTOR_CONTROLLER_USAGE::INTAKE );
                if ( it != motorControllers.end() )  // found it
                {
                    auto motor = it->second;
                    if ( motor.get() != nullptr )
                    {
                        subsys = new Intake( motor );
                    }
                    else
                    {
                        Logger::GetLogger()->LogError( string( "MechanismFactory::CreateIMechanism" ), string( "intake motor is nullptr" ) );
                    }
                }
                else
                {
                    Logger::GetLogger()->LogError( string( "MechanismFactory::CreateIMechanism" ), string( "intake motor not found" ) );
                }
                ***/
            }
            break;

            case MechanismTypes::MECHANISM_TYPE::EXTENDER:
            break;

            case MechanismTypes::MECHANISM_TYPE::CLIMBER:
            break;

            case MechanismTypes::MECHANISM_TYPE::BEAK:
            break;

            case MechanismTypes::MECHANISM_TYPE::TAIL:
            break;

            default:
            break;
        }
    }

	return subsys;
}




