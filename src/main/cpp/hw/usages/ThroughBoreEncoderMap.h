#pragma once

#include <memory>
#include <map>
#include <hw/DragonThroughBoreEncoder.h>
#include <hw/usages/ThroughBoreEncoderUsage.h>

typedef std::map <ThroughBoreEncoderUsage::THROUGH_BORE_ENCODER_USAGE, std::shared_ptr<DragonThroughBoreEncoder>> ThroughBoreEncoderMap;