#pragma once

#include <subsys/IMechanism.h>
#include <controllers/ControlData.h>

class IMechController
{
    public:
        IMechController() = default;
        virtual ~IMechController() = default;

        virtual void Init
        (
            IMechanism*         mechanism,
            ControlData*        controlData
        ) = 0;

        virtual void Run() = 0;
        virtual bool ReachedTarget() = 0;
};