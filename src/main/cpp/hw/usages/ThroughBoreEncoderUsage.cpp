#include <map>
#include <memory>
#include <string>
#include <hw/usages/ThroughBoreEncoderUsage.h>

using namespace std;

ThroughBoreEncoderUsage* ThroughBoreEncoderUsage::m_instance = nullptr;

ThroughBoreEncoderUsage* ThroughBoreEncoderUsage::GetInstance()
{
    if (m_instance == nullptr )
    {
        m_instance = new ThroughBoreEncoderUsage();
    }
    return m_instance;
}

ThroughBoreEncoderUsage::ThroughBoreEncoderUsage()
{
    m_usageMap["SHOOTER_HOOD"] = THROUGH_BORE_ENCODER_USAGE::SHOOTER_HOOD;
}

ThroughBoreEncoderUsage::~ThroughBoreEncoderUsage()
{
    m_usageMap.clear();
}

ThroughBoreEncoderUsage::THROUGH_BORE_ENCODER_USAGE ThroughBoreEncoderUsage::GetUsage(
    const string usageString
)
{
    return m_usageMap.find(usageString)->second;
}

