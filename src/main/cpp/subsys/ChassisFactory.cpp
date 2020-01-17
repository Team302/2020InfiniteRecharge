
#include <memory>

#include <subsys/IChassis.h>
#include <subsys/ChassisFactory.h>
#include <subsys/DragonChassis.h>
#include <hw/interfaces/IDragonMotorController.h>

#include <utils/Logger.h>

using namespace std;

ChassisFactory* ChassisFactory::m_chassisFactory = nullptr;
ChassisFactory* ChassisFactory::GetChassisFactory()
{
    if ( ChassisFactory::m_chassisFactory == nullptr )
    {
        ChassisFactory::m_chassisFactory = new ChassisFactory();
    }
    return ChassisFactory::m_chassisFactory;
}

shared_ptr<IChassis> ChassisFactory::GetIChassis()
{
    shared_ptr<IChassis> chassis = nullptr;
    return chassis;
}

//=======================================================================================
// Method:  		CreateChassis
// Description:		Create a chassis from the inputs
// Returns:         Void
//=======================================================================================
shared_ptr<IChassis> ChassisFactory::CreateChassis
(
    ChassisFactory::CHASSIS_TYPE   	    type,				// <I> - Chassis Type
    double 						        wheelDiameter,		// <I> - Diameter of the wheel
    double 					    	    wheelBase,			// <I> - Front-Back distance between wheel centers
    double 						        track,				// <I> - Left-Right distance between wheels (same axle)
 	const IDragonMotorControllerMap&    motors 		        // <I> - Motor Controllers
)
{
    shared_ptr<IChassis> chassis = nullptr;

    switch ( type )
    {
        case ChassisFactory::CHASSIS_TYPE::TANK_CHASSIS:
        {
            shared_ptr<IDragonMotorController>  leftMaster;
            shared_ptr<IDragonMotorController>  rightMaster;
            
            vector<shared_ptr<IDragonMotorController>> leftSlaves;
            vector<shared_ptr<IDragonMotorController>> rightSlaves;

            leftMaster = GetMotorController( motors, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::BACK_LEFT_DRIVE);
            auto slave = GetMotorController( motors, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::FRONT_LEFT_DRIVE);
            leftSlaves.push_back( slave );
            
            rightMaster = GetMotorController( motors, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::BACK_RIGHT_DRIVE);
            slave = GetMotorController( motors, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::FRONT_RIGHT_DRIVE);
            rightSlaves.push_back( slave );
            
            chassis = make_shared<DragonChassis>(  wheelDiameter, wheelBase, track, leftMaster, rightMaster, leftSlaves, rightSlaves );
        }
        break;

        case ChassisFactory::CHASSIS_TYPE::MECANUM_CHASSIS:
        {
            // todo plug in mecanum drive
        }
        break;

        default:
        break;

    }

    return chassis;
}
shared_ptr<IDragonMotorController> ChassisFactory::GetMotorController
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
		Logger::GetLogger()->LogError( string( "ChassisFactory::GetMotorController" ), msg );
	}
	
	if ( motor.get() == nullptr )
	{
		string msg = "motor is nullptr; usage = ";
		msg += to_string( usage );
		Logger::GetLogger()->LogError( string( "ChassisFactory::GetMotorController" ), msg );
	}
	return motor;
}


