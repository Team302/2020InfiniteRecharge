/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "xmlhw/LimelightDefn.h"
#include "hw/DragonLimelight.h"
#include "utils/HardwareIDValidation.h"
#include "utils/UsageValidation.h"

#include <pugixml/pugixml.hpp>

using namespace std;

std::shared_ptr<DragonLimelight> LimelightDefn::ParseXML(pugi::xml_node    limelightNode)
{
    shared_ptr<DragonLimelight> limelight = nullptr;

    bool hasError = false;

    
}