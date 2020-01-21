/*
 * DragonAnalogInput.cpp
 */

#include <hw/DragonAnalogInput.h>

DragonAnalogInput::DragonAnalogInput
(
	AnalogInputUsage::ANALOG_SENSOR_USAGE	type,
	int 									analogID,
	float									voltageMin,
	float									voltageMax,
	float 									outputMin,
	float									outputMax
) : AnalogInput( analogID),
    m_type( type ),
	m_voltMin( voltageMin ),
	m_voltMax( voltageMax ),
	m_outMin( outputMin ),
	m_outMax( outputMax )
{
}

DragonAnalogInput::~DragonAnalogInput()
{
}

double DragonAnalogInput::GetInterpolatedValue() const
{
    return  (( GetVoltage() / (m_voltMax - m_voltMin) ) * (m_outMax - m_outMin) + m_outMin);
}

AnalogInputUsage::ANALOG_SENSOR_USAGE DragonAnalogInput::GetUsage() const
{
	return m_type;
}

