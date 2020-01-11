
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

//========================================================================================================
/// HardwareIDValidation.h
//========================================================================================================
///
/// File Description:
///     This will validate the various hardware IDs against the valid values.
//========================================================================================================

#pragma once

// C++ Includes
#include <string>

// FRC Includes

// Team 302 Includes
#include <utils/HardwareIDValidation.h>
#include <utils/Logger.h>

// Third Party Includes

class HardwareIDValidation
{
    public:
        //======================================================================================
        /// Method:       ValidateCANID
        /// Description:  Check the CAN ID against the valid range.  If it is invalid the logger
        ///               utility will be called.
        /// Returns:      bool          true  - valid
        ///                             false - invalid
        //=====================================================================================
        static bool ValidateCANID
        (
            int          canID,         // <I> - CAN ID to validate
            std::string  methodID       // <I> - class::method identifier for message
        );

        //======================================================================================
        /// Method:       ValidatePDPID
        /// Description:  Check the PDP ID against the valid range.  If it is invalid the logger
        ///               utility will be called.
        /// Returns:      bool          true  - valid
        ///                             false - invalid
        //=====================================================================================
        static bool ValidatePDPID
        (
            int          pdpID,         // <I> - PDP ID to validate
            std::string  methodID       // <I> - class::method identifier for message
        );
        
        //======================================================================================
        /// Method:       ValidateDIOID
        /// Description:  Check the Digitial IO ID against the valid range.  If it is invalid the logger
        ///               utility will be called.
        /// Returns:      bool          true  - valid
        ///                             false - invalid
        //=====================================================================================
        static bool ValidateDIOID
        (
            int          dioID,         // <I> - DIO ID to validate
            std::string  methodID       // <I> - class::method identifier for message
        );

        //======================================================================================
        /// Method:       ValidateID
        /// Description:  Check the ID against the valid range.  If it is invalid the logger
        ///               utility will be called.
        /// Returns:      bool          true  - valid
        ///                             false - invalid
        //=====================================================================================
        static bool ValidateID
        (
            int          id,            // <I> - ID to validate
            int          minID,         // <I> - minimum ID
            int          maxID,         // <I> - maximum ID
            std::string  methodID,      // <I> - class::method identifier for message
            std::string  errorMsg       // <I> - error message
        );

};


