
#pragma once

// C++ Includes
#include <map>

// FRC includes

// Team 302 includes
#include <controllers/IState.h>

// Third Party Includes

class ShooterHoodStateMgr 
{
    public:
        /// @enum the various states of the shooter hood
        enum SHOOTER_HOOD_STATE
        {
            MOVE_UP,
            MOVE_DOWN,
            HOLD_POSITION,
            MAX_SHOOTER_HOOD_STATES
        };

        ShooterHoodStateMgr();
        ~ShooterHoodStateMgr() = default;


        /// @brief  run the current state
        /// @return void
        void RunCurrentState();

        /// @brief  set the current state, initialize it and run it
        /// @param [in]     SHOOTER_HOOD_STATE - state to set
        /// @param [in]     run - true means run, false just initialize it
        /// @return void
        void SetCurrentState
        (
            SHOOTER_HOOD_STATE  state,
            bool            run
        );

        /// @brief  return the current state
        /// @return SHOOTER_HOOD_STATE - the current state
        inline SHOOTER_HOOD_STATE GetCurrentState() const { return m_currentStateEnum; };

    private:

        std::map<SHOOTER_HOOD_STATE,IState*> m_stateMap;
        IState* m_currentState;
        SHOOTER_HOOD_STATE m_currentStateEnum;

};