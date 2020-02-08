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

//here are some includes
#include <memory>
#include <auton/PrimitiveParams.h>
#include <subsys/Intake.h>
#include <auton/primitives/IPrimitive.h>
#include <controllers/intake/IntakeStateMgr.h>

class IntakeBall : public IPrimitive 
{
	public:
		/// @brief constructor that creates/initializes the object
		IntakeBall();

		/// @brief destructor, clean  up the memory from this object
		virtual ~IntakeBall() = default;

		/// @brief initialize this usage of the primitive
		/// @param PrimitiveParms* params the drive parameters
		/// @return void
		void Init(PrimitiveParams* params) override;
		
		/// @brief run the primitive (periodic routine)
		/// @return void
		void Run() override;

		/// @brief check if the end condition has been met
		/// @return bool true means the end condition was reached, false means it hasn't
		bool IsDone() override;

        private:

        IntakeStateMgr*     m_stateManager;


};