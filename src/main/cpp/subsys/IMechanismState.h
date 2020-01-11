
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
/**
#pragma once

//========================================================================================================
/// IMechanismState.h
//========================================================================================================
///
/// File Description:
///     This is the interface for all subsystem states
///     - Percent Output
///     - Position Control
///     - Velocity Control
///
//========================================================================================================

// C++ Includes

// FRC includes

// Team 302 includes

// Third Party Includes


//========================================================================================================
///	 Class:			IMechanismState
///  Description:	Interface for subsystem states
//========================================================================================================
class IMechanismState
{
	public:

        //==================================================================================
        /// enum:           MECHANISM_TYPE
        /// description:    Indicates the type of mechanism
        //==================================================================================
        enum MECHANISM_STATE
        {
            PERCENT_OUTPUT,
            POSITION_CONTROL,
            VELOCITY_CONTROL,
            MAX_MECHANISM_STATES
        };



        //==================================================================================
        /// method:         GetCurrentSate
        /// description:    Return the current state
        /// returns:        MECHANISM_STATE state
        //==================================================================================
      //  virtual MECHANISM_STATE GetCurrentSate() = 0;


        //==================================================================================
        /// method:         SetTarget
        /// description:    Set the target value is
        ///                  - a unitless value between -1.0 and 1.0 for for Percent Output States
        ///                  - a value in inches for translating mechanisms in Position Control
        ///                  - a value in degrees for rotating mechanisms in Position Control
        ///                  - a value in inches per second for translating mechanisms in Velocity Control
        ///                  - a value in degrees per second for rotating mechanisms in Velocity Control
        /// returns:        void
        //==================================================================================
        virtual void SetTarget
        (
            double      value       /// <I> - target value for the mechanism
        ) = 0;


        //==================================================================================
        /// method:         GetCurrentValue
        /// description:    Return the current value for the mechanism.  
        /// returns:        double	current value
        ///                  - a unitless value between -1.0 and 1.0 for for Percent Output States
        ///                  - a value in inches for translating mechanisms in Position Control
        ///                  - a value in degrees for rotating mechanisms in Position Control
        ///                  - a value in inches per second for translating mechanisms in Velocity Control
        ///                  - a value in degrees per second for rotating mechanisms in Velocity Control
        //==================================================================================
        virtual double GetCurrentValue() const = 0;


        //==================================================================================
        /// method:         GetTargetValue
        /// description:    Return the target value for the mechanism.  
        /// returns:        double	target value
        ///                  - a unitless value between -1.0 and 1.0 for for Percent Output States
        ///                  - a value in inches for translating mechanisms in Position Control
        ///                  - a value in degrees for rotating mechanisms in Position Control
        ///                  - a value in inches per second for translating mechanisms in Velocity Control
        ///                  - a value in degrees per second for rotating mechanisms in Velocity Control
        //==================================================================================
        virtual double GetTargetValue() const = 0;


	IMechanismState() = default;
	virtual ~IMechanismState() = default;
};
**/



