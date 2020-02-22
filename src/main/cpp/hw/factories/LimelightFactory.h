/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <memory>
#include <map>

#include <hw/DragonLimelight.h>
#include <hw/interfaces/IDragonSensor.h>


class LimelightFactory 
{
  public:
    static LimelightFactory* GetLimelightFactory();

    DragonLimelight* GetLimelight
    (
      IDragonSensor::SENSOR_USAGE usage
    );

    DragonLimelight* CreateLimelight
    (
      IDragonSensor::SENSOR_USAGE     usage,
      std::string                     tableName,                  /// <I> - network table name
      double                          mountingHeight,             /// <I> - mounting height of the limelight
      double                          mountingHorizontalOffset,   /// <I> - mounting horizontal offset from the middle of the robot
      double                          rotation,                   /// <I> - clockwise rotation of limelight
      double                          mountingAngle,              /// <I> - mounting angle of the camera
      double                          targetHeight,               /// <I> - height the target
      double                          targetHeight2,              /// <I> - height of second target
      DragonLimelight::LED_MODE       ledMode,
      DragonLimelight::CAM_MODE       camMode,
      DragonLimelight::STREAM_MODE    streamMode,
      DragonLimelight::SNAPSHOT_MODE  snapMode,
      double                          defaultXHairX,
      double                          defaultXHairY,
      double                          secXHairX,
      double                          secXHairY
    );

  private:
    LimelightFactory();
    ~LimelightFactory() = default;

    static LimelightFactory* m_limelightFactory;
    DragonLimelight* m_limelight;
    //std::map <IDragonSensor::SENSOR_USAGE, std::shared_ptr<DragonLimelight>> m_limelightMap;
};
