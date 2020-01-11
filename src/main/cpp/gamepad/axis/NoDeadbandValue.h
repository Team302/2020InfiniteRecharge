
/*========================================================================================================
 * NoDeadbandValue.h
 *========================================================================================================
 *
 * File Description: Returns raw value without a deadband
 *
 *========================================================================================================*/

//====================================================================================================================================================
// Copyright 2019 Lake Orion Robotics FIRST Team 302
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================

#pragma once

// C++ Includes

// FRC includes

// Team 302 includes
#include <gamepad/axis/IDeadband.h>


// Third Party Includes



//==================================================================================
/// <summary>
/// Class:          NoDeadbandValue
/// Description:    This class doesn't apply a deadband to axis values
/// </summary>
//==================================================================================
class NoDeadbandValue : public IDeadband
{
    public:

        //==================================================================================
        /// <summary>
        /// Method:         GetInstance
        /// Description:    Static singleton method to create the object
        /// Returns:        DeadbandValue*  Singleton deadband object
        /// </summary>
        //==================================================================================
        static NoDeadbandValue* GetInstance();


        //==================================================================================
        /// <summary>
        /// Method:         ApplyDeadband
        /// Description:    Apply the standard deadband
        /// </summary>
        //==================================================================================
        double ApplyDeadband
        (
            double      inputVal            // <I> - value to apply profile to
        ) const override;

        
    private:
        NoDeadbandValue() = default;

        static NoDeadbandValue*     m_instance;
};

