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
// forward declares
class BallTransferStateMgr;
class ImpellerStateMgr;
class IntakeStateMgr;
class ShooterStateMgr;
class ShooterHoodStateMgr;
class TurretStateMgr;

// Third Party Includes

class BallManipulator 
{
    public:
        /// @enum the various states of ball manipulation
        enum BALL_MANIPULATOR_STATE
        {
            OFF,
            INTAKE,
            INTAKE_HUMAN_PLAYER,
            HOLD,
            GET_READY_TO_SHOOT,
            SHOOT,
            SHOOT_AUTON,
            AUTO_AIM,
            UNJAM_CLOCKWISE,
            UNJAM_COUNTERCLOCKWISE,
            TRANSFER_UP,
            TRANSFER_DOWN,
            TURRET_TURN_ANGLE,
            MAX_BALL_MANIPULATOR_STATES
        };

		/// @brief  Find or create the Ball Manipulator
		/// @return BallManipulator* pointer to the singleton
		static BallManipulator* GetInstance();


        /// @brief  run the current state
        /// @return void
        void RunCurrentState();

        /// @brief  set the current state, initialize it and run it
        /// @param [in]     INTAKE_STATE - state to set
        /// @return void
        void SetCurrentState
        (
            BALL_MANIPULATOR_STATE      state,
            double                      turretAngle
        );

        /// @brief  return the current state
        /// @return INTAKE_STATE - the current state
        inline BALL_MANIPULATOR_STATE GetCurrentState() const { return m_currentState; };

        void SetApproxAngle( double angle );

    private:

        BallManipulator();
        ~BallManipulator() = default;
		static BallManipulator*	m_instance;


        BALL_MANIPULATOR_STATE      m_currentState;
        IntakeStateMgr*             m_intake;
        ImpellerStateMgr*           m_impeller;
        BallTransferStateMgr*       m_transfer;
        TurretStateMgr*             m_turret;
        ShooterStateMgr*            m_shooter;
        ShooterHoodStateMgr*        m_hood;

};

