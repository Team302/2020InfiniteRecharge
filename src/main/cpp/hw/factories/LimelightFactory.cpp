/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <map>

#include "hw/factories/LimelightFactory.h"
#include <hw/DragonLimelight.h>
#include <utils/Logger.h>


using namespace std;

LimelightFactory* LimelightFactory::m_limelightFactory = nullptr;

LimelightFactory* LimelightFactory::GetLimelightFactory()
{
    if(m_limelightFactory == nullptr)
    {
        m_limelightFactory = new LimelightFactory();
    }
    return m_limelightFactory;
}

shared_ptr<DragonLimelight> LimelightFactory::CreateLimelight
(
    IDragonSensor::SENSOR_USAGE     usage, 
    string                          tableName, 
    double                          mountingHeight, 
    double                          mountingHorizontalOffset, 
    double                          rotation, 
    double                          mountingAngle, 
    double                          targetHeight, 
    double                          targetHeight2,
    DragonLimelight::LED_MODE       ledMode,
    DragonLimelight::CAM_MODE       camMode,
    DragonLimelight::STREAM_MODE    streamMode,
    DragonLimelight::SNAPSHOT_MODE  snapMode,
    double                          defaultXHairX,
    double                          defaultXHairY,
    double                          secXHairX,
    double                          secXHairY
)
{
    if ( m_limelight == nullptr )
    {
        m_limelight.reset(new DragonLimelight(usage, tableName, mountingHeight, mountingHorizontalOffset, rotation, mountingAngle, targetHeight, targetHeight2));
        m_limelight.get()->SetLEDMode( ledMode );
        m_limelight.get()->SetCamMode( camMode );
        m_limelight.get()->SetStreamMode( streamMode );
        m_limelight.get()->ToggleSnapshot( snapMode );
        if ( defaultXHairX > -1.5 && defaultXHairY > -1.5 )
        {
            // m_limelight.get()->  todo add method
        }        
        if ( secXHairX > -1.5 && secXHairY > -1.5 )
        {
            // m_limelight.get()->  todo add method
        }

    }
    return m_limelight;
    /**
    auto it = m_limelightMap.find(usage);
    shared_ptr<DragonLimelight> limelight;
    if ( it != m_limelightMap.end() )
    {
        return GetLimelight(usage);
    }
    else
    {
        shared_ptr<DragonLimelight> limelight;
        limelight.reset(new DragonLimelight(usage, tableName, mountingHeight, mountingHorizontalOffset, rotation, mountingAngle, targetHeight, targetHeight2));
        m_limelightMap[usage] = limelight;
        return limelight;
        
    }
    **/
}

shared_ptr<DragonLimelight> LimelightFactory::GetLimelight(IDragonSensor::SENSOR_USAGE usage)
{
    return m_limelight;
    /**
    auto it = m_limelightMap.find(usage);
    if ( it != m_limelightMap.end() )
    {
        return m_limelightMap[usage];
    }
    else
    {
        std::string msg = "limelight not found; usage =";
        msg += to_string(usage);
        Logger::GetLogger()->LogError("LimelightFactory::GetLimilight", msg);
    }
    **/
}

