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
#include <subsys/IMechanism.h>

// Third Party Includes

class ImpellerStateMgr 
{
    public:
        /// @enum the various states of the impeller
        enum IMPELLER_STATE
        {
            OFF,
            HOLD,
            AGITATE,
            TO_SHOOTER,
            MAX_IMPELLER_STATES
        };
        
		/// @brief  Find or create the state manmanager
		/// @return ImpellerStateMgr* pointer to the state manager
		static ImpellerStateMgr* GetInstance();



        /// @brief  run the current state
        /// @return void
        void RunCurrentState();

        /// @brief  set the current state, initialize it and run it
        /// @param [in]     IMPELLER_STATE - state to set
        /// @param [in]     run - true means run, false just initialize it
        /// @return void
        void SetCurrentState
        (
            IMPELLER_STATE  state,
            bool            run
        );

        /// @brief  return the current state
        /// @return IMPELLER_STATE - the current state
        inline IMPELLER_STATE GetCurrentState() const { return m_currentStateEnum; };

    private:

        std::vector<IState*> m_stateVector;
        IState* m_currentState;
        IMPELLER_STATE m_currentStateEnum;
        IMechanism*     m_impeller;
        bool            m_reverse;
        int             m_numReverseLoops;
        int             m_consecZero;


		static ImpellerStateMgr*	m_instance;

        ImpellerStateMgr();
        ~ImpellerStateMgr() = default;

};

