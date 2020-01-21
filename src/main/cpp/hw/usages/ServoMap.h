
#pragma once

#include <memory>
#include <map>

#include <hw/DragonServo.h>
#include <hw/usages/ServoUsage.h>

typedef std::map <ServoUsage::SERVO_USAGE, std::shared_ptr<DragonServo>> ServoMap;
