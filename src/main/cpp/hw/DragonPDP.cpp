/*
 * DragonPDP.cpp
 */

#include <memory>

#include <hw/DragonPDP.h>
#include <frc/PowerDistributionPanel.h>

using namespace frc;
using namespace std;

DragonPDP* DragonPDP::m_instance = nullptr;

DragonPDP* DragonPDP::GetInstance()
{
	if ( DragonPDP::m_instance == nullptr )
	{
		DragonPDP::m_instance = new DragonPDP();
	}
	return DragonPDP::m_instance;
}

DragonPDP::DragonPDP()
{
	if ( DragonPDP::m_pdp == nullptr )
	{
		CreatePDP( 0 );
	}
}

PowerDistributionPanel* DragonPDP::GetPDP() const
{
	return DragonPDP::m_pdp;
}

//=======================================================================================
// Method:  		CreatePDP
// Description:		Create a PDP from the inputs
// Returns:         std::shared_ptr<PowerDistributionPanel>
//=======================================================================================
PowerDistributionPanel* DragonPDP::CreatePDP
(
	int			canID				// <I> - CANLight CAN ID
)
{
	DragonPDP::m_pdp = new PowerDistributionPanel( canID );

	return DragonPDP::m_pdp;
}
