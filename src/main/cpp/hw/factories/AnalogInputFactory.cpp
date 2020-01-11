
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

//========================================================================================================
/// @class AnalogInputFactory
/// @brief This controls the creation of analog inputs
//========================================================================================================

// C++ Includes
#include <algorithm>
#include <locale>
#include <map>
#include <memory>
#include <string>

// FRC includes

// Team 302 includes
#include <hw/factories/AnalogInputFactory.h>
#include <hw/DragonAnalogInput.h>
#include <hw/usages/AnalogInputUsage.h>
//#include <hw/DragonAngleSensorFactory.h>
#include <utils/Logger.h>


// Third Party Includes


using namespace std;

//=====================================================================================
/// @brief  Find or create the analog input factory
/// @return AnalogInputFactory* pointer to the factory
//=====================================================================================
AnalogInputFactory* AnalogInputFactory::m_factory = nullptr;
AnalogInputFactory* AnalogInputFactory::GetFactory()
{
	if ( AnalogInputFactory::m_factory == nullptr )
	{
		AnalogInputFactory::m_factory = new AnalogInputFactory();
	}
	return AnalogInputFactory::m_factory;
}


//=====================================================================================
/// @brief  create the factory
//=====================================================================================
AnalogInputFactory::AnalogInputFactory( )
{
    CreateUsageMap();
}

//=====================================================================================
/// @brief  create the map of usage string to sensor usage map
/// @return void
//=====================================================================================
void AnalogInputFactory::CreateUsageMap()
{
    m_usageMap["EXTENDER_POTENTIOMETER"]  = AnalogInputUsage::ANALOG_SENSOR_USAGE::EXTENDER_POTENTIOMETER;
    m_usageMap["PRESSURE_GAUGE"] = AnalogInputUsage::ANALOG_SENSOR_USAGE::PRESSURE_GAUGE;
}
//=====================================================================================
/// @brief  Create the requested analog input
/// @return shared_ptr<DragonAnalogInput>   the mechanism or nullptr if mechanism doesn't 
///         exist and cannot be created.
//=====================================================================================
shared_ptr<DragonAnalogInput> AnalogInputFactory::CreateInput
(
    string  usage,
    int 	analogID,
    float	voltageMin,
    float	voltageMax,
    float 	outputMin,
    float	outputMax
)
{
    shared_ptr<DragonAnalogInput> sensor;

    auto type = m_usageMap.find(usage)->second;
    switch ( type )
    {
        case AnalogInputUsage::ANALOG_SENSOR_USAGE::EXTENDER_POTENTIOMETER:
            sensor = make_shared<DragonAnalogInput>( type,
                                                     analogID,
                                                     voltageMin,
                                                     voltageMax,
                                                     outputMin,
                                                     outputMax );
            // TODO: Create an angle sensor + decorate it as a position sensor
            break;

        case AnalogInputUsage::ANALOG_SENSOR_USAGE::PRESSURE_GAUGE:
            sensor = make_shared<DragonAnalogInput> ( type,
                                                      analogID,
                                                      voltageMin,
                                                      voltageMax,
                                                      outputMin,
                                                      outputMax );
            break;

        default:
            string msg = "unknown type " + type;
            Logger::GetLogger()->LogError( "AnalogInputFactory::CreateInput", msg );

    }
    return sensor;
}

