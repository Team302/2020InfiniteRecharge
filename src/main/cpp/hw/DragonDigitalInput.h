/*
 * DragonDigitalInput.h
 */

#ifndef SRC_SUBSYS_COMPONENTS_DRAGONDIGITALINPUT_H_
#define SRC_SUBSYS_COMPONENTS_DRAGONDIGITALINPUT_H_

#include <vector>

#include <frc/DigitalInput.h>

using namespace frc;

class DragonDigitalInput
{
	public:

        enum DIGITAL_INPUT_TYPE
        {
            UNKNOWN_DIGITAL_INPUT_TYPE = -1,
            ARM_MIN_POSITION,
            MAX_DIGITAL_INPPUT_TYPES
        };		

		//------------------------------------------------------------------------------
		// Method:		<<constructor>>
		// Description:
		//------------------------------------------------------------------------------
		DragonDigitalInput
		(
			DIGITAL_INPUT_TYPE		usage,	    	// <I> - Usage of the digital input
			int 					deviceID,		// <I> - digial io ID
			bool					reversed		// <I>
		);

		DragonDigitalInput() = delete;
		virtual ~DragonDigitalInput();

		bool Get() const;
		int  GetChannel() const;
		DIGITAL_INPUT_TYPE GetType() const;

	private:
		DigitalInput*		m_digital;
		bool				m_reversed;
		DIGITAL_INPUT_TYPE  m_type;
};
typedef std::vector<DragonDigitalInput*> DragonDigitalInputVector;

#endif /* SRC_SUBSYS_COMPONENTS_DRAGONDIGITALINPUT_H_ */
