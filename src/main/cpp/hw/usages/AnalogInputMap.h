
#pragma once

#include <memory>
#include <map>

#include <hw/DragonAnalogInput.h>
#include <hw/usages/AnalogInputUsage.h>

typedef std::map <AnalogInputUsage::ANALOG_SENSOR_USAGE, std::shared_ptr<DragonAnalogInput>> AnalogInputMap;
