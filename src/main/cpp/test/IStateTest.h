
//====================================================================================================================================================
// Copyright 2020 Lake Orion Robotics FIRST Team 302
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

// Third Party Includes


///	 @interface IStateTest
///  @brief	    Interface for testing subsystem states
class IStateTest
{
	public:
		IStateTest() = default;
		virtual ~IStateTest() = default;
		
		/// @brief Initialize the test setup.  This will be called from Robot::TestInit()
		/// @return void
		virtual void Init() = 0;
		
		/// @brief Run the test.  This will be called from Robot::TestPeriodic()
		/// @return void		
		virtual void Periodic() = 0;
		
		/// @brief Indicate whether the test has completed or not.
		/// @return bool - true: test has completed, false: test is still running
		virtual bool IsDone() = 0;
};

		