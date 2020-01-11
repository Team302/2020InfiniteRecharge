//====================================================================================================================================================
// IDragonDistanceSensor.h
//====================================================================================================================================================
// Copyright 2019 Lake Orion Robotics FIRST Team 302
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================

// C++ Includes
#include <memory>

// FRC includes

// Team 302 includes
#include <hw/interfaces/IDragonSensor.h>
#include <hw/interfaces/IDragonDistanceSensor.h>
#include <hw/factories/DistanceSensorFactory.h>
#include <hw/DragonLidar.h>
#include <hw/DragonLimeLight.h>
#include <hw/DragonUltrasonic.h>
#include <hw/DragonUltrasonicPWM.h>
#include <utils/Logger.h>

// Third Party Includes



using namespace std;


//====================================================================================================================================================
/// @class  DistanceSensorFactory
/// @brief  This factory constructs distance sensors
//====================================================================================================================================================


 
DistanceSensorFactory* DistanceSensorFactory::m_instance = nullptr;
DistanceSensorFactory* DistanceSensorFactory::GetFactory()
{
    if ( DistanceSensorFactory::m_instance == nullptr )
    {
        DistanceSensorFactory::m_instance = new DistanceSensorFactory();
    }
    return DistanceSensorFactory::m_instance;

}

DistanceSensorFactory::DistanceSensorFactory()
{

}

DistanceSensorFactory::~DistanceSensorFactory()
{
    
}

shared_ptr<IDragonDistanceSensor> GetSensor
(
    IDragonSensor::SENSOR_USAGE    usage
)
{
    shared_ptr<IDragonDistanceSensor> sensor = nullptr;
    return sensor;
}

/// @brief Create a distance sensor from the inputs
/// @param IDragonSensor::SENSOR_USAGE  usage       
/// @param int                          pwmInputPin (lidar or ultrasonic 3)
/// @param int                          pwmTriggerPin (lidar)
/// @param int                          analogPin (ultrasonic)
/// @param int                          i2cID (rev 2M)
/// @param int                          canID (playing with fusion time of flight)
/// @param std::string                  tableName (limelight) network table name
/// @param double                       mountingHeight in inches (limelight)
/// @param double                       mountingHorizontalOffset in inches (limelight)
/// @param double                       mountingAngle in degrees (limelight)
/// @param double                       targetHeight in inches (limelight)
/// @return std::shared_ptr<IDragonDistanceSensor>    sensor
shared_ptr<IDragonDistanceSensor> DistanceSensorFactory::CreateSensor
(
    IDragonSensor::SENSOR_USAGE     usage,
    int                             inputPin,
    int                             triggerPin,
    int                             analogInputPin,
    int                             i2cID,
    int                             canID,
    std::string                     tableName,                  
    double                          mountingHeight,             
    double                          mountingHorizontalOffset,   
    double                          mountingAngle,              
    double                          targetHeight                
)
{
    shared_ptr<IDragonDistanceSensor> sensor = nullptr;

    /**
    if ( inputPin > -1 && triggerPin > -1 )  // create lidar
    {
        // todo validate the pins/usage
        sensor = make_shared<IDragonDistanceSensor>( new DragonLidar( usage, inputPin, triggerPin ) );
    }
    else if ( analogInputPin > - 1 )  // create ultrasonic
    {
        // todo validate the channel
        sensor = make_shared<IDragonDistanceSensor>( new DragonUltrasonic( usage, analogInputPin ) );
    }
    else if ( inputPin > -1 )  // create ultrasonicPWM
    {
        // todo validate the pwm pin
        sensor = make_shared<IDragonDistanceSensor>( new DragonUltrasonicPWM( usage, inputPin ) );
    }
    else if ( i2cID > -1 )  // create Rev 2M 
    {
        // todo validate the i2c
        // todo create the sensor 

    }
    else if ( canID > -1 )  // create playing with fusion time of flight sensor
    {
        // todo validate the i2c
        // todo create the sensor 

    }
    else if ( !tableName.empty() )
    {
        // todo validate inputs
        sensor = make_shared<IDragonDistanceSensor>( new DragonLimelight( usage, tableName, mountingHeight, mountingHorizontalOffset, mountingAngle, targetHeight) );
    }
    else
    {
        Logger::GetLogger()->LogError( string( "DistanceSensorFactory::CreateSensor"), string("unknown sensor") );
    }
    **/

    return sensor;
}
