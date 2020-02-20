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

        ///@brief Run the Climber as defined
        ///@param [in] ControlModes::CONTROL_TYPE   controlType
        ///@param [in] double   value
        ///@return void
        void SetOutput
        (
            ControlModes::CONTROL_TYPE controlType,
            double                                  value
        ) override;

        ///@brief Activate/deactivate the extender solenoid
        ///@param [in] bool - true == extended, false == retracted
        ///@return void
        void ActivateSolenoid
        (
            bool    activate
        ) override;

        ///@brief Check to see if the solenoid is activated
        ///@return bool - true == extended, false == retracted
        bool IsSolenoidActivated() override;

        ///@brief Return the current position of the climber in inches (positive is forward, negative is backward)
        ///@return  double position in inches
        double GetCurrentPosition() const override;

        ///@brief Return the current position of the climber in inches (positive is forward, negative is backward)
        ///@return double speed in inches
        double GetCurrentSpeed() const override;


        ///@brief Set the control constants (e.g. PIDF values)
        ///@param [in] ControlData*    pid - the control constants
        ///@return void
        void SetControlConstants
        (
            ControlData*    pid
        ) override;

    private:
        std::shared_ptr<IDragonMotorController>             m_motorMaster;
        std::shared_ptr<DragonSolenoid>                     m_solenoidMaster;
        double                                              m_winchDiameter;
        double                                              m_target;
};
