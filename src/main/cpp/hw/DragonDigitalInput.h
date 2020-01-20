/*
 * DragonDigitalInput.h
 */

#pragma once

#include <frc/DigitalInput.h>
#include <hw/usages/DigitalInputUsage.h>

using namespace frc;

class DragonDigitalInput
{
	public:

		//------------------------------------------------------------------------------
		// Method:		<<constructor>>
		// Description:
		//------------------------------------------------------------------------------
		DragonDigitalInput
		(
    		DigitalInputUsage::DIGITAL_SENSOR_USAGE			type,
			int 											deviceID,		// <I> - digial io ID
			bool											reversed		// <I>
		);

		DragonDigitalInput() = delete;
		virtual ~DragonDigitalInput();

		bool Get() const;
		int  GetChannel() const;
		DigitalInputUsage::DIGITAL_SENSOR_USAGE GetType() const;

	private:
		DigitalInput*		m_digital;
		bool				m_reversed;
		DigitalInputUsage::DIGITAL_SENSOR_USAGE  m_type;
};
