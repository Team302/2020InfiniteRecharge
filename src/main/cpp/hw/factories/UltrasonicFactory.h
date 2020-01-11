//====================================================================================================================================================
// IDragonAnglePositionSensor.h
//====================================================================================================================================================
// Copyright 2018 Lake Orion Robotics FIRST Team 302
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
#include <hw/interfaces/IDragonSensor.h>
#include <hw/interfaces/IDragonDistanceSensor.h>
#include <hw/DragonUltrasonic.h>

// Third Party Includes

class UltrasonicFactory
{
	public:

			static UltrasonicFactory* GetUltrasonicFactory();
			DragonUltrasonic* GetDragonUltrasonic
			(
			     IDragonSensor::SENSOR_USAGE  usage
			);

			//=======================================================================================
			// Method:  		CreateUltrasonic
			// Description:		Create an ultrasonic from the inputs
			// Returns:         Void
			//=======================================================================================
			DragonUltrasonic* CreateUltrasonic
			(
				IDragonSensor::SENSOR_USAGE				usage,
				int								        analogInChannel
			);



	private:
		UltrasonicFactory();
		~UltrasonicFactory() = default;

		DragonUltrasonic*            m_left;
		DragonUltrasonic*            m_right;



		static UltrasonicFactory*	        m_ultrasonicFactory;
		static DragonUltrasonic*			m_ultrasonic;



};

