
#pragma once

// C++ Includes
#include <map>
#include <vector>

// FRC includes

// Team 302 includes
#include <states/IState.h>

// Third Party Includes

class ControlPanelStateMgr 
{
    public:
        /// @enum the various states of the control panel
        enum CONTROL_PANEL_STATE
        {
            RAISE,
            STOW,
            TURN,
            COLOR_TURN,
            MANUAL,
            MAX_CONTROL_PANEL_STATES
        };

		/// @brief  Find or create the state manmanager
		/// @return ControlPanelStateMgr* pointer to the state manager
		static ControlPanelStateMgr* GetInstance();

        /// @brief  run the current state
        /// @return void
        void RunCurrentState();

        /// @brief  set the current state, initialize it and run it
        /// @param [in]     CONTROL_PANEL_STATE - state to set
        /// @param [in]     run - true means run, false just initialize it
        /// @return void
        void SetCurrentState
        (
            CONTROL_PANEL_STATE  state,
            bool            run
        );

        /// @brief  return the current state
        /// @return CONTROL_PANEL_STATE - the current state
        inline CONTROL_PANEL_STATE GetCurrentState() const { return m_currentStateEnum; };

    private:

        std::vector<IState*> m_stateVector;
        IState* m_currentState;
        CONTROL_PANEL_STATE m_currentStateEnum;

        ControlPanelStateMgr();
        ~ControlPanelStateMgr() = default;

		static ControlPanelStateMgr*	m_instance;

};