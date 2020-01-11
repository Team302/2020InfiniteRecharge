/*
 * CanifierFactory.cpp
 */
#include <memory>
#include <string>

#include <ctre/phoenix/CANifier.h>

#include <hw/factories/CanifierFactory.h>
#include <utils/HardwareIDValidation.h>

using namespace std;
using namespace ctre::phoenix;

CanifierFactory* CanifierFactory::m_instance = nullptr;

CanifierFactory* CanifierFactory::GetInstance()
{
	if ( CanifierFactory::m_instance == nullptr )
	{
		CanifierFactory::m_instance = new CanifierFactory();
	}
	return CanifierFactory::m_instance;
}

CanifierFactory::CanifierFactory()
{
    for ( auto inx=0; inx<63; ++inx )
    {
        m_canifiers[inx] = nullptr;
    }
}


//=======================================================================================
// Method:  		GetCanifier
// Description:		Find or create a Canifier with a the particular CAN ID
// Returns:         CANifier*  
//=======================================================================================
shared_ptr<ctre::phoenix::CANifier> CanifierFactory::GetCanifier
(
	int			canID				// <I> - CAN ID
)
{
    auto hasError = HardwareIDValidation::ValidateCANID( canID, string( "CanifierFactory::GetCanifier" ) );
    if ( !hasError )
    {
        if ( m_canifiers[canID] != nullptr )
        {
            m_canifiers[canID] = make_shared<CANifier>( canID );
        }
    }
	return m_canifiers[canID];
}
