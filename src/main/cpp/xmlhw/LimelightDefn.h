/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma 

#include <iostream>

#include <hw/DragonLimelight.h>

#include <pugixml/pugixml.hpp>

class LimelightDefn {
 public:
  LimelightDefn() = default;
  virtual ~LimelightDefn() = default;

  std::shared_ptr<DragonLimelight> ParseXML
  (
    pugi::xml_node    limelightNode
  );
};
