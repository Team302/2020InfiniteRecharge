
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

#pragma once

//========================================================================================================
/// DragonMotorControllerFactory.h
//========================================================================================================
///
/// File Description:
///     This is the factory for creating Motor Controllers
///
//========================================================================================================

// C++ Includes


// FRC includes
#include <map>
#include <memory>
#include <string>

// Team 302 includes
#include <subsys/IMechanism.h>
#include <xmlhw/MotorDefn.h>
#include <hw/DragonTalon.h>
#include <hw/DragonSparkMax.h>

// Third Party Includes
#include <ctre/phoenix/MotorControl/CAN/TalonSRX.h>
#include <ctre/phoenix/MotorControl/FeedbackDevice.h>
#include <rev/CANSparkMax.h>


//========================================================================================================
///	 Class:			DragonMotorControllerFactory
///  Description:	This is a singleton that creates motor controllers (IDragonMotorController).  This 
///				 	allows us to interact with motor controllers such as TalonSRX, Rev Spark Max without
///					actually knowing what type is actually being used.
//========================================================================================================
class DragonMotorControllerFactory
{
    public:
		///---------------------------------------------------------------------------------
		///  enum:			MOTOR_TYPE
		///  description:	This indicates the type of motor controller.  Most of our 
		///					code doesn't need/care about this, however since this is the
		///					factory, it is needed when constructing the object.
		///---------------------------------------------------------------------------------
	    enum MOTOR_TYPE
    	{
        	TALONSRX,				/// Controller is a Cross the Road Electronics (CTRE) Talon SRX on the CAN network
        	BRUSHLESS_SPARK_MAX,	/// Controller is a Rev Robotics Spark Max controlling a brushless motor
        	BRUSHED_SPARK_MAX		/// Controller is a Rev Robotics Spark Max conrolling a brushed motor
    	};


        static DragonMotorControllerFactory* GetInstance();

		//=======================================================================================
		/// Method:          CreateMotorController
		/// Description:     Create a motor controller from the inputs
		/// Returns:         Void
		//=======================================================================================
		std::shared_ptr<IDragonMotorController> CreateMotorController
		(
			std::string                             		mtype,					/// Controller Type
			int 											canID,					/// CAN ID for the controller
			int 											pdpID,					/// PDP slot the motor is on
			std::string                                     usage,					/// Motor usage (e.g. Front Left Drive Motor)
			bool 											inverted, 				/// Motor is inverted (positive values make the motor turn in reverse)or not
			bool 											sensorInverted,			/// Sensor direction matches motor direction or not 
			ctre::phoenix::motorcontrol::FeedbackDevice  	feedbackDevice,			/// Sensor type
			int 											countsPerRev,			/// Number of pulses per revolution for the sensor
			float 											gearRatio,				/// Gear ratio (output to input ... see https://www.wikihow.com/Determine-Gear-Ratio)
			bool 											brakeMode,				/// brake mode using back emf to resist motion when power is not applied
			int 											slaveTo,				/// CAN ID of the "master" motor controller if this is a follower motor controller (-1 indicates it is a master)
			int 											peakCurrentDuration,	/// peak current limit
			int 											continuousCurrentLimit,	/// continuous current limit
			int 											peakCurrentLimit,		/// amount of time the peak current can be achieved before limiting to the continuous current limit
			bool 											enableCurrentLimit		/// enable current limiting or not
		);

	private:

		//=======================================================================================
		/// Method:          GetController
		/// Description:     return motor controller
		/// Returns:         IDragonMotorController* 	may be nullptr if there isn't a controller
		///												with this usage.
		//=======================================================================================
		std::shared_ptr<IDragonMotorController> GetController
		(
			int													canID		/// Motor Controller CAN ID
		) const;

		void CreateTypeMap();

        DragonMotorControllerFactory();
        ~DragonMotorControllerFactory() = default;

        static DragonMotorControllerFactory*                                    m_instance;

		std::array<std::shared_ptr<IDragonMotorController>,63>				    m_canControllers;
        std::map<std::string, DragonMotorControllerFactory::MOTOR_TYPE>         m_typeMap;


};

