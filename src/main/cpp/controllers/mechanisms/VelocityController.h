#pragma once

#include <controllers/ControlData.h>
#include <subsys/IMechanism.h>
#include <controllers/mechanisms/IMechController.h>

class VelocityController : public IMechController
{
    public:
        VelocityController() = delete;
        VelocityController
        (
            IMechanism*         mechanism,
            ControlData*        controlData
        );

        ~VelocityController() override;

        void Init
        (
            IMechanism*         mechanism,
            ControlData*        controlData
        ) override;

        void Run() override;
        bool ReachedTarget() override;

    private:
        IMechanism*         m_mech;
        ControlData*        m_control;



};