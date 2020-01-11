#pragma once


#include <memory>

#include <subsys/IChassis.h>
#include <hw/interfaces/IDragonMotorController.h>

class ChassisFactory
{

		public:
			enum CHASSIS_TYPE
			{
				UNKNOWN_CHASSIS = -1,
				TANK_CHASSIS,
				MECANUM_CHASSIS,
				MAX_CHASSIS_TYPES
			};
			static ChassisFactory* GetChassisFactory();

			std::shared_ptr<IChassis> GetIChassis();

			//=======================================================================================
			// Method:  		CreateChassis
			// Description:		Create a chassis from the inputs
			// Returns:         Void
			//=======================================================================================
			std::shared_ptr<IChassis> CreateChassis
			(
				CHASSIS_TYPE     			        type,				// <I> - Chassis Type
				double 						        wheelDiameter,		// <I> - Diameter of the wheel
			    double 						        wheelBase,			// <I> - Front-Back distance between wheel centers
				double 						        track,				// <I> - Left-Right distance between wheels (same axle)
				const IDragonMotorControllerMap&    motors 		        // <I> - Motor Controllers
			);



		private:
			ChassisFactory() = default;
			~ChassisFactory() = default;
			std::shared_ptr<IChassis>        m_chassis;

			static ChassisFactory*	m_chassisFactory;

};
