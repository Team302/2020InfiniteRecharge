/*
 * DragonMotorControllerFactory.cpp
 *
 */
#include <iostream>
#include <map>
#include <string>

#include <subsys/IMechanism.h>
#include <hw/factories/DragonMotorControllerFactory.h>        
#include <hw/usages/MotorControllerUsage.h>
#include <xmlhw/MotorDefn.h>
#include <hw/DragonTalon.h>
#include <hw/DragonFalcon.h>
#include <hw/DragonSparkMax.h>
#include <utils/Logger.h>

#include <ctre/phoenix/motorcontrol/can/TalonSRX.h>
#include <ctre/phoenix/motorcontrol/can/TalonFX.h>
#include <ctre/phoenix/motorcontrol/FeedbackDevice.h>
#include <rev/CANSparkMax.h>

using namespace std;
using namespace ctre::phoenix::motorcontrol;

DragonMotorControllerFactory* DragonMotorControllerFactory::m_instance = nullptr;


DragonMotorControllerFactory* DragonMotorControllerFactory::GetInstance()
{
    if ( DragonMotorControllerFactory::m_instance == nullptr )
    {
        DragonMotorControllerFactory::m_instance = new DragonMotorControllerFactory();
    }
    return DragonMotorControllerFactory::m_instance;
}

DragonMotorControllerFactory::DragonMotorControllerFactory() 
{
	for ( auto inx=0; inx<63; ++inx )
	{
		m_canControllers[inx] = nullptr;
	}
    MotorControllerUsage::GetInstance();
    CreateTypeMap();
}

//=======================================================================================
// Method:          CreateMotorController
// Description:     Create a motor controller from the inputs
// Returns:         Void
//=======================================================================================
shared_ptr<IDragonMotorController> DragonMotorControllerFactory::CreateMotorController
(
	string		                                    mtype,
    int 											canID,
	int 											pdpID,
    string                                          usage,
    bool 											inverted, 
    bool 											sensorInverted,
    FeedbackDevice  	                            feedbackDevice,
    int 											countsPerRev,
    float 											gearRatio,
    bool 											brakeMode,
    int 											slaveTo,
    int 											peakCurrentDuration,
    int 											continuousCurrentLimit,
    int 											peakCurrentLimit,
    bool 											enableCurrentLimit,
    bool											forwardLimitSwitch,
    bool											forwardLimitSwitchNormallyOpen,
    bool											reverseLimitSwitch,
    bool											reverseLimitSwitchNormallyOpen
)
{
    shared_ptr<IDragonMotorController> controller;

    auto hasError = false;

    auto type = m_typeMap.find(mtype)->second;
    if ( type == MOTOR_TYPE::TALONSRX )
    {
        auto talon = new DragonTalon( MotorControllerUsage::GetInstance()->GetUsage(usage), canID, pdpID, countsPerRev, gearRatio );
        talon->EnableBrakeMode( brakeMode );
        talon->Invert( inverted );
        talon->SetSensorInverted( sensorInverted );
        talon->ConfigSelectedFeedbackSensor( feedbackDevice, 0, 50 );
        talon->ConfigSelectedFeedbackSensor( feedbackDevice, 1, 50 );

        talon->ConfigPeakCurrentLimit( peakCurrentLimit, 50 );
        talon->ConfigPeakCurrentDuration( peakCurrentDuration, 50 );
        talon->ConfigContinuousCurrentLimit( continuousCurrentLimit, 50 );
        talon->EnableCurrentLimiting( enableCurrentLimit );
        if ( forwardLimitSwitch )
        {
            talon->SetForwardLimitSwitch(forwardLimitSwitchNormallyOpen);
        }        
        if ( reverseLimitSwitch )
        {
            talon->SetForwardLimitSwitch(reverseLimitSwitchNormallyOpen);
        }

        if ( slaveTo > -1 )
        {
            talon->SetAsSlave( slaveTo );
        }
        controller.reset( talon );
    }
    else if ( type == MOTOR_TYPE::FALCON )
    {
        auto talon = new DragonFalcon( MotorControllerUsage::GetInstance()->GetUsage(usage), canID, pdpID, countsPerRev, gearRatio );
        talon->EnableBrakeMode( brakeMode );
        talon->Invert( inverted );
        talon->SetSensorInverted( sensorInverted );
        talon->ConfigSelectedFeedbackSensor( feedbackDevice, 0, 50 );
        talon->ConfigSelectedFeedbackSensor( feedbackDevice, 1, 50 );

        /*talon->ConfigPeakCurrentLimit( 40, 50 );
        talon->ConfigPeakCurrentDuration( 1, 50 );
        talon->ConfigContinuousCurrentLimit( 30, 50 );
        talon->EnableCurrentLimiting( true );*/
        if ( forwardLimitSwitch )
        {
            talon->SetForwardLimitSwitch(forwardLimitSwitchNormallyOpen);
        }        
        if ( reverseLimitSwitch )
        {
            talon->SetForwardLimitSwitch(reverseLimitSwitchNormallyOpen);
        }
        
        if ( slaveTo > -1 )
        {
            talon->SetAsSlave( slaveTo );
        }
        controller.reset( talon );
    }
    else if ( type == MOTOR_TYPE::BRUSHED_SPARK_MAX || type == MOTOR_TYPE::BRUSHLESS_SPARK_MAX )
    {
        auto brushedBrushless = (type == MOTOR_TYPE::BRUSHED_SPARK_MAX) ? rev::CANSparkMax::MotorType::kBrushed : rev::CANSparkMax::MotorType::kBrushless;
        auto smax = new DragonSparkMax( canID, pdpID, MotorControllerUsage::GetInstance()->GetUsage(usage), brushedBrushless, gearRatio );
        smax->Invert( inverted );
        smax->EnableBrakeMode( brakeMode );
        smax->SetSensorInverted( sensorInverted );
        smax->EnableCurrentLimiting( enableCurrentLimit );
        smax->SetSmartCurrentLimiting( continuousCurrentLimit );
        if ( slaveTo > -1 )
        {
            DragonSparkMax* master = nullptr;
            if ( GetController( slaveTo ) != nullptr )
            {
                master = dynamic_cast<DragonSparkMax*>( GetController( slaveTo ).get() );
            }
            if ( master != nullptr )
            {
                smax->Follow( master );
            }
            else
            {
                string msg = "invalid Slave to ID ";
                msg += to_string( slaveTo );
                Logger::GetLogger()->LogError( "DragonMotorControllerFactory::CreateMotorController", msg );
            }
        }
        controller.reset( smax );
    }
    else
    {
        hasError = true;
    }

    if ( !hasError )
    {
        m_canControllers[ canID ] = controller;
    }
	return controller;
}



//=======================================================================================
// Method:          GetController
// Description:     return motor controller
// Returns:         IDragonMotorController* 	may be nullptr if there isn't a controller
//												with this CAN ID.
//=======================================================================================
shared_ptr<IDragonMotorController> DragonMotorControllerFactory::GetController
(
	int							canID		/// Motor controller CAN ID
) const
{
	shared_ptr<IDragonMotorController> controller;
	if ( canID > -1 && canID < 63 )
	{
		controller = m_canControllers[ canID ];
	}
	else
	{
	    string msg = "invalid CAN ID ";
	    msg += to_string( canID );
        Logger::GetLogger()->LogError( "DragonMotorControllerFactory::GetController", msg );
	}
	return controller;
}

void DragonMotorControllerFactory::CreateTypeMap()
{
    m_typeMap["TALONSRX"] = DragonMotorControllerFactory::MOTOR_TYPE::TALONSRX;
    m_typeMap["FALCON"] = DragonMotorControllerFactory::MOTOR_TYPE::FALCON;
    m_typeMap["BRUSHLESS_SPARK_MAX"] = DragonMotorControllerFactory::MOTOR_TYPE::BRUSHLESS_SPARK_MAX;
    m_typeMap["BRUSHED_SPARK_MAX"] = DragonMotorControllerFactory::MOTOR_TYPE::BRUSHED_SPARK_MAX;
}
