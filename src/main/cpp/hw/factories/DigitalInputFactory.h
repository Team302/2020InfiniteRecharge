
//====================================================================================================================================================
/// Copyright 2019 Lake Orion Robotics FIRST Team 302
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
/// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
/// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
/// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================

//========================================================================================================
/// DigitalInputFactory.h
//========================================================================================================
///
/// File Description:
///     This controls the creation of Digital inputs
///
//========================================================================================================

#pragma once

// C++ Includes


// FRC includes

// Team 302 includes
#include <hw/DragonDigitalInput.h>


// Third Party Includes


class DigitalInputFactory
{
	public:

		static DigitalInputFactory* GetFactory();


		//=====================================================================================
		/// Method:         CreateInput
		/// Description:    Create the requested Digital input
		/// Returns:        IMechanism*     pointer to the mechanism or nullptr if mechanism 
		///                                 doesn't exist and cannot be created.
		//=====================================================================================
        DragonDigitalInput* CreateInput
        (
            DragonDigitalInput::DIGITAL_INPUT_TYPE			type,
            int 						                    digitalID,
            bool						                    reversed
        );

		//=====================================================================================
		/// Method:         GetInput
		/// Description:    Get the requested Digital input
		/// Returns:        IMechanism*     pointer to the mechanism or nullptr if mechanism 
		///                                 doesn't exist.
		//=====================================================================================
        DragonDigitalInput* GetInput
        (
            DragonDigitalInput::DIGITAL_INPUT_TYPE			type
        );


	private:
		DigitalInputFactory();
		~DigitalInputFactory();

		static DigitalInputFactory*	m_factory;

        DragonDigitalInput* m_armExtendMin;
			
};