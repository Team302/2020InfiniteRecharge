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
#include <map>
#include <vector>

// FRC includes

// Team 302 includes
#include <states/IState.h>

// Third Party Includes

class IntakeStateMgr 
{
    public:
        /// @enum the various states of the intake
        enum INTAKE_STATE
        {
            OFF,
            ON,
            HUMANPLAYER,
            MAX_INTAKE_STATES
        };

		/// @brief  Find or create the state manmanager
		/// @return IntakeStateMgr* pointer to the state manager
		static IntakeStateMgr* GetInstance();

        /// @brief  run the current state
        /// @return void
        void RunCurrentState();

        /// @brief  set the current state, initialize it and run it
        /// @param [in]     INTAKE_STATE - state to set
        /// @param [in]     run - true means run, false just initialize it
        /// @return void
        void SetCurrentState
        (
            INTAKE_STATE    state,
            bool            run
        );

        /// @brief  return the current state
        /// @return INTAKE_STATE - the current state
        inline INTAKE_STATE GetCurrentState() const { return m_currentStateEnum; };

    private:

        std::vector<IState*> m_stateVector;
        IState* m_currentState;
        INTAKE_STATE m_currentStateEnum;

        IntakeStateMgr();
        ~IntakeStateMgr() = default;

		static IntakeStateMgr*	m_instance;

};

