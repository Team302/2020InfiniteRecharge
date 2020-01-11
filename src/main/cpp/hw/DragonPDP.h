/*
 * DragonPDP.h
 */

#pragma once

#include <memory>
#include <frc/PowerDistributionPanel.h>

using namespace frc;

class DragonPDP
{
	public:
		static DragonPDP* GetInstance();

		//=======================================================================================
		// Method:  		CreatePDP
		// Description:		Create a PDP from inputs
		// Returns:         std::shared_ptr<PowerDistributionPanel>
		//=======================================================================================
		PowerDistributionPanel* CreatePDP
		(
			int			canID				// <I> - PDP CAN ID
		);

		frc::PowerDistributionPanel* GetPDP() const;

	private:
		DragonPDP();
		virtual ~DragonPDP() = default;

		static DragonPDP*						m_instance;
		mutable frc::PowerDistributionPanel*	m_pdp;

};


