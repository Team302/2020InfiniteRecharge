/*
 * DragonDigitalInput.cpp
 */

#include <iostream>

#include <hw/DragonDigitalInput.h>
#include <hw/usages/DigitalInputUsage.h>
#include <frc/DigitalInput.h>

using namespace frc;

DragonDigitalInput::DragonDigitalInput
(
	DigitalInputUsage::DIGITAL_SENSOR_USAGE		usage,	    	// <I> - Usage of the digital input
	int 										deviceID,		// <I> - digial io ID
	bool										reversed		// <I>
) : m_digital( new DigitalInput( deviceID ) ),
	m_reversed( reversed ),
	m_type( usage )
{
}

DragonDigitalInput::~DragonDigitalInput()
{
	delete m_digital;
}

DigitalInputUsage::DIGITAL_SENSOR_USAGE DragonDigitalInput::GetType() const
{
    return m_type;
}

bool DragonDigitalInput::Get() const
{
	bool isSet = false;
	if ( m_digital != nullptr )
	{
		isSet = (m_reversed) ? !m_digital->Get() : m_digital->Get();
	}
	else
	{
		printf( "==>> Digital Input not created \n" );
	}
	return isSet;
}
int  DragonDigitalInput::GetChannel() const
{
	int channel = 0;
	if ( m_digital != nullptr )
	{
		channel = m_digital->GetChannel();
	}
	else
	{
//		printf( "==>> Digital Input not created \n" );
	}
	return channel;
}

