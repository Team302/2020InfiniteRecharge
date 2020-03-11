
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
#include <map>
#include <vector>

// FRC includes

// Team 302 includes
#include <states/IState.h>


// Third Party Includes

class HookDeliveryStateMgr 
{
    public:
        /// @enum the various states of the BallTransfer
        enum HOOK_DELIVERY_STATE
        {
            /*DOWN,
            RAISE,
            HIGH,
            LOWER,
            MANUAL,*/
            UP,
            DOWN,
            OFF,
            MAX_HOOK_DELIVERY_STATES
        };

        
		/// @brief  Find or create the state manmanager
		/// @return HookDeliveryStateMgr* pointer to the state manager
		static HookDeliveryStateMgr* GetInstance();

        /// @brief  run the current state
        /// @return void
        void RunCurrentState();

        /// @brief  set the current state, initialize it and run it
        /// @param [in]     HOOK_DELIVERY_STATE - state to set
        /// @param [in]     run - true means run, false just initialize it
        /// @return void
        void SetCurrentState
        (
            HOOK_DELIVERY_STATE     state,
            bool                    run
        );

        /// @brief  return the current state
        /// @return HOOK_DELIVERY_STATE - the current state
        inline HOOK_DELIVERY_STATE GetCurrentState() const { return m_currentStateEnum; };

    private:

        IState* m_currentState;
        std::vector<IState*> m_stateVector;
        HOOK_DELIVERY_STATE m_currentStateEnum;

        HookDeliveryStateMgr();
        ~HookDeliveryStateMgr() = default;

		static HookDeliveryStateMgr*	m_instance;


};


