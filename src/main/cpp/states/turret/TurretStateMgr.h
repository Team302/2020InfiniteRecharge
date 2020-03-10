/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <map>
#include <vector>

#include <states/IState.h>

class TurretStateMgr {
  public:
      enum TURRET_STATE
      {
        HOLD,
        LIMELIGHT_AIM,
        MANUAL_AIM,
        TURN_ANGLE,
        MAX_TURRET_STATES
      };


        /// @brief  Find or create the state manmanager
        /// @return TurretStateMgr* pointer to the state manager
        static TurretStateMgr* GetInstance();

        /// @brief  run the current state
        /// @return void
        void RunCurrentState();

        /// @brief  set the current state, initialize it and run it
        /// @param [in]     SHOOTER_HOOD_STATE - state to set
        /// @param [in]     run - true means run, false just initialize it
        /// @return void
        void SetCurrentState
        (
            TURRET_STATE  state,
            bool            run,
            double          turretAngle
        );

        /// @brief  return the current state
        /// @return SHOOTER_HOOD_STATE - the current state
        inline TURRET_STATE GetCurrentState() const { return m_currentStateEnum; };
        
        inline void SetApproxTargetAngle( double angle ) { m_approxTargetAngle = angle; }

    private:

        std::vector<IState*> m_stateVector;
        IState* m_currentState;
        TURRET_STATE m_currentStateEnum;
        double m_approxTargetAngle;

        TurretStateMgr();
        ~TurretStateMgr() = default;

        static TurretStateMgr*	m_instance;

};
