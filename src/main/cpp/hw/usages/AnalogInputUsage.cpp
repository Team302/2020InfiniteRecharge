
//====================================================================================================================================================
// Copyright 2019 Lake Orion Robotics FIRST Team 302
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================

// C++ Includes
#include <map>
#include <memory>
#include <string>

// FRC includes

// Team 302 includes
#include <hw/usages/AnalogInputUsage.h>

// Third Party Includes

using namespace std;

AnalogInputUsage* AnalogInputUsage::m_instance = nullptr;
AnalogInputUsage* AnalogInputUsage::GetInstance()
{
    if ( m_instance == nullptr )
    {
        m_instance = new AnalogInputUsage();
    }
    return m_instance;
}

AnalogInputUsage::AnalogInputUsage()
{
    m_usageMap["EXTENDER_POTENTIOMETER"]  = AnalogInputUsage::ANALOG_SENSOR_USAGE::EXTENDER_POTENTIOMETER;
    m_usageMap["PRESSURE_GAUGE"] = AnalogInputUsage::ANALOG_SENSOR_USAGE::PRESSURE_GAUGE;
}

AnalogInputUsage::~AnalogInputUsage()
{
    m_usageMap.clear();
}

AnalogInputUsage::ANALOG_SENSOR_USAGE AnalogInputUsage::GetUsage
(
    string              usageString
)
{
    return m_usageMap.find(usageString)->second;
}

