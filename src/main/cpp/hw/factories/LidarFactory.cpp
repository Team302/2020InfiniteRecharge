/*
 * LidarFactory.cpp
 *
 */

#include <hw/factories/LidarFactory.h>
#include <hw/DragonLidar.h>
#include <hw/interfaces/IDragonSensor.h>
#include <hw/interfaces/IDragonDistanceSensor.h>

using namespace std;

LidarFactory* LidarFactory::m_lidarFactory = nullptr;
DragonLidar*  LidarFactory::m_backwardLidar = nullptr;
DragonLidar*  LidarFactory::m_forwardLidar = nullptr;


LidarFactory* LidarFactory::GetLidarFactory()
{
    if ( LidarFactory::m_lidarFactory == nullptr )
    {
        LidarFactory::m_lidarFactory = new LidarFactory();
    }
    return LidarFactory::m_lidarFactory;
}

shared_ptr<DragonLidar> LidarFactory::GetLidar
(
    IDragonSensor::SENSOR_USAGE    usage
)
{
    shared_ptr<DragonLidar> lidar = nullptr;
    return lidar;
}

//=======================================================================================
// Method:          CreateLidar
// Description:     Create a lidar from the inputs
// Returns:         Void
//=======================================================================================
shared_ptr<DragonLidar> LidarFactory::CreateLidar
(
    IDragonSensor::SENSOR_USAGE     usage,
    int                             inputPin,
    int                             triggerPin
)
{
    shared_ptr<DragonLidar> lidar = nullptr;
    auto isValid = false;
    // todo: plug in validation

    if ( isValid )
    {
        lidar = make_shared<DragonLidar>( usage, inputPin, triggerPin );
    }

    return lidar;
}

