#pragma once

//C++ Includes
#include <memory>

//Team 302 includes
#include <hw/interfaces/IDragonMotorController.h>
#include <hw/DragonSolenoid.h>
#include <subsys/IMechanism.h>
#include <controllers/ControlModes.h>
#include <controllers/ControlData.h>
#include <subsys/MechanismTypes.h>

///@class Climber
///@brief This is the climber sub-system
class Climber : public IMechanism
{
    public:

        ///@brief   Create and initialize the Climber sub-mechanism
        ///@param [in] std::shared_ptr<IDragonMotorController>   masterMotor - master motor for the Climber
        ///@param [in] std::shared_ptr<DragonSolenoid>  masterSolenoid - master solenoid for the Climber
        ///@param [in] double   **
        Climber
        (
            std::shared_ptr<IDragonMotorController>          masterMotor,
            std::shared_ptr<DragonSolenoid>                  masterSolenoid,
            double                                           winchDiameter
        );
        Climber() = delete;
        ///@brief Clean up memory when this object gets deleted
        virtual ~Climber() = default;

        ///@brief Indicates that this is Climber
        ///@return IMechanism::MECHANISM_TYPE::CLIMBER
        MechanismTypes::MECHANISM_TYPE GetType() const override;

        ///@brief 
        void SetOutput
        (
            ControlModes::CONTROL_TYPE controlType,
            double                                  value
        ) override;

        void ActivateSolenoid
        (
            bool    activate
        ) override;

        bool IsSolenoidActivated() override;

        double GetCurrentPosition() const override;

        double GetTargetPosition() const override;

        double GetCurrentSpeed() const override;

        double GetTargetSpeed() const override;

        void SetControlConstants
        (
            ControlData*
        ) override;

    private:
        std::shared_ptr<IDragonMotorController>             m_motorMaster;
        std::shared_ptr<DragonSolenoid>                     m_solenoidMaster;
        double                                              m_winchDiameter;
        double                                              m_target;
};