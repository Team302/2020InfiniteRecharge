/*
 * DragonTalonTach.cpp
 */

#include <iostream>

#include <hw/DragonTalonTach.h>
#include <ctre/phoenix/CANifier.h>
#include <hw/factories/CanifierFactory.h>


DragonTalonTach::DragonTalonTach
(  
    TALON_TACH_USAGE                        usage,
    int                                     canID,
    ctre::phoenix::CANifier::GeneralPin     generalpin,
    bool                                    reversed
) : m_usage ( usage ),
    m_CAN (CanifierFactory::GetInstance()-> GetCanifier(0)),
    m_generalpin (generalpin),
    m_reversed (reversed)

{
}

bool DragonTalonTach::Get() const
{
	bool isSet = false;
	if ( m_CAN != nullptr )
	{
		isSet = (m_reversed) ? !m_CAN->GetGeneralInput(m_generalpin) : m_CAN->GetGeneralInput(m_generalpin);
	}
	else
	{
//		printf( "==>> Talon Tach not created \n" );
	}
	return isSet;
}
