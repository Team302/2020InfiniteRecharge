
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

//========================================================================================================
///	 @class			MechanismParameters
///  @brief      	This contains the enum for the mechanism parameters
//========================================================================================================
class MechanismParameters
{
	public:
        //==================================================================================
        /// enum:           MECHANISM_PARAM_TYPE
        /// description:    Various parameters for mechanisms
        //==================================================================================
        enum MECHANISM_PARAM_TYPE
        {
            MECHANISM_PARAM_UNKNOWN = -1,
            LEGAL_STARTING_ANGLE,
            TEST_STARTING_ANGLE,
            EXTENDER_LEGAL_STARTING_INCHES,
            EXTENDER_TEST_STARTING_INCHES,
            HATCH_FLOOR_ANGLE,
            HATCH_HP_SECOND_ANGLE,
            HATCH_LOW_ANGLE,
            HATCH_MID_ANGLE,
            HATCH_HIGH_ANGLE,
            HATCH_LOW_SECOND_ANGLE,
            HATCH_MID_SECOND_ANGLE,
            HATCH_HIGH_SECOND_ANGLE,
            CARGO_FLOOR_ANGLE,
            CARGO_HP_ANGLE,
            CARGO_SHIP_ANGLE,
            CARGO_LOW_ANGLE,
            CARGO_MID_ANGLE,
            CARGO_HIGH_ANGLE,
            HATCH_FLOOR_EXTENSION,
            HATCH_HP_SECOND_EXTENSION,
            HATCH_LOW_EXTENSION,
            HATCH_MID_EXTENSION,
            HATCH_HIGH_EXTENSION,
            HATCH_LOW_SECOND_EXTENSION,
            HATCH_MID_SECOND_EXTENSION,
            HATCH_HIGH_SECOND_EXTENSION,
            CARGO_FLOOR_EXTENSION,
            CARGO_HP_EXTENSION,
            CARGO_HP_HOLE_EXTENSION,
            CARGO_SHIP_EXTENSION,
            CARGO_LOW_EXTENSION,
            CARGO_MID_EXTENSION,
            CARGO_HIGH_EXTENSION,
            CARGO_INTAKE_SPEED_PARAM,
            CARGO_OUTTAKE_SPEED_PARAM,
            HATCH_INTAKE_SPEED_PARAM,
            HATCH_OUTTAKE_SPEED_PARAM,
            SERVO_LOCKED_POSITION_PARAM,
            SERVO_DROPPED_POSITION_PARAM,
            HATCH_MECH_OPEN_ROTATIONS,
            MAX_MECHANISM_PARAM_TYPES
        };

};
