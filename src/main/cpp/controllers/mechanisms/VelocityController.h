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

        void Init() override;

        void Run() override;
        bool AtTarget() override;

    private:
        IMechanism*         m_mech;
        ControlData*        m_control;



};