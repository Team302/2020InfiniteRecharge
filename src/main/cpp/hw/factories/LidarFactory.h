/*
 * LidarFactory.h
 *
 */

#pragma once

#include <memory>

#include <hw/interfaces/IDragonSensor.h>
#include <hw/DragonLidar.h>

class LidarFactory
{
    public:
        static LidarFactory* GetLidarFactory();

        static std::shared_ptr<DragonLidar> GetLidar
        (
            IDragonSensor::SENSOR_USAGE    usage
        );

        //=======================================================================================
        // Method:          CreateLidar
        // Description:     Create a lidar from the inputs
        // Returns:         Void
        //=======================================================================================
        std::shared_ptr<DragonLidar> CreateLidar
        (
            IDragonSensor::SENSOR_USAGE     usage,
            int                             inputPin,
            int                             triggerPin
        );

    private:
        LidarFactory() = default;
        ~LidarFactory() = default;

        static LidarFactory*        m_lidarFactory;
        static DragonLidar*         m_backwardLidar;
        static DragonLidar*         m_forwardLidar;


};

