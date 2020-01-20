
#pragma once

#include <memory>
#include <map>

#include <hw/DragonSolenoid.h>
#include <hw/usages/SolenoidUsage.h>

typedef std::map <SolenoidUsage::SOLENOID_USAGE, std::shared_ptr<DragonSolenoid>> DragonSolenoidMap;
