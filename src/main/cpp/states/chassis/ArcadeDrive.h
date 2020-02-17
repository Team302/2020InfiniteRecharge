
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

// Standard C++ includes
#include <memory>

// Team 302 include
#include <subsys/IChassis.h>
#include <states/IState.h>
#include <gamepad/TeleopControl.h>

// CTRE includes 


class ArcadeDrive : public IState
{
    public:
    
        ArcadeDrive();
        ~ArcadeDrive() = default;
		
		/// @brief toggle between curvature and normal modes
		/// @param [in] true - use curvature-based driving, false use normal (default) drive mode
		/// @return void
		void SetCurvatureBased
		( 
			bool 	CurvatureBased
		);

		/// @brief initialize the profiles for the various gamepad inputs
		/// @return void        
		void Init() override;
		
		/// @brief calculate the output for the wheels on the chassis from the throttle and steer components
		/// @return void
        void Run() override;
		
		/// @brief indicates that we are not at our target
		/// @return bool
        bool AtTarget() const override;
               
    protected:
		/// @brief get the throttle component from the game controller
		/// @return double - throttle value between -1.0 and 1.0
        virtual double GetThrottle();

		/// @brief get the steer component from the game controller
		/// @return double - steer value between -1.0 and 1.0
        virtual double GetSteer();

		/// @brief calculate the normal output values for the wheels on the chassis from the throttle and steer components
		/// @param [in] thtottie - forward/backward value between -1.0 and 1.0
		/// @param [in] steer - turning value between -1.0 and 1.0
		/// @param [out] left - calculated value to set to the left wheels
		/// @param [out] right - calculated value to set to the right wheels
		/// @return void
		void NormalDrive
		(
			double 	throttle,
			double  steer,
			double* left,
			double* right
		);


		/// @brief calculate the curvature-based output values for the wheels on the chassis from the throttle and steer components as well as the quick turn input
		/// @param [in] thtottie - forward/backward value between -1.0 and 1.0
		/// @param [in] steer - turning value between -1.0 and 1.0
		/// @param [out] left - calculated value to set to the left wheels
		/// @param [out] right - calculated value to set to the right wheels
		/// @return void
		void CurvatureDrive
		(
			double 	throttle,
			double  steer,
			double* left,
			double* right
		);

		/// @brief return the teleop controller mapper
		/// @return TeleopControl* - controller mapper
        inline TeleopControl* GetController() const { return m_controller; }
		
		/// @brief return the chassis
		/// @return std::shared_ptr<IChassis>
		inline std::shared_ptr<IChassis> GetChassis() const { return m_chassis; }

    private:
        std::shared_ptr<IChassis> m_chassis;
        TeleopControl* m_controller;
		bool m_curvatureBased;
		const double m_quickStopThreshold = 0.2;
		double m_quickStopAccumulator;
		double m_quickStopAlpha;


};
