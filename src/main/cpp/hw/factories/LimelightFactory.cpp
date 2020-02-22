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

LimelightFactory::LimelightFactory() : m_limelight( nullptr )
{
}
DragonLimelight* LimelightFactory::CreateLimelight
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
        m_limelight = new DragonLimelight(usage, tableName, mountingHeight, mountingHorizontalOffset, rotation, mountingAngle, targetHeight, targetHeight2);
        m_limelight->SetLEDMode( ledMode );
        m_limelight->SetCamMode( camMode );
        m_limelight->SetStreamMode( streamMode );
        m_limelight->ToggleSnapshot( snapMode );
        if ( defaultXHairX > -1.5 && defaultXHairY > -1.5 )
        {
            // m_limelight->  todo add method
        }        
        if ( secXHairX > -1.5 && secXHairY > -1.5 )
        {
            // m_limelight->  todo add method
        }

    }
    return m_limelight;
}

DragonLimelight* LimelightFactory::GetLimelight(IDragonSensor::SENSOR_USAGE usage)
{
    return m_limelight;
}

