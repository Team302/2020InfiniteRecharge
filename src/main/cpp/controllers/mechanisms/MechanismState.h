#pragma once

#include <string>

#include <controllers/mechanisms/IMechController.h>

class MechanismState
{
    public:
        MechanismState();
        ~MechanismState() = default;
        
        virtual void Init() = 0;
        virtual void Run() = 0;
        virtual bool AtTarget() = 0;

    protected:
        virtual std::string GetMechControlDataFileName() = 0;
        virtual std::string GetMechTargetDataFilename() = 0;
        bool ReadMechControlData();
        bool ReadMechTargetData();

    private:
        ControlData*    m_controlData;
        

};