
#pragma once

#include <memory>
#include <map>

#include <hw/DragonDigitalInput.h>
#include <hw/usages/DigitalInputUsage.h>

typedef std::map <DigitalInputUsage::DIGITAL_SENSOR_USAGE, std::shared_ptr<DragonDigitalInput>> DigitalInputMap;
