#pragma once

class ITeleopDrive
{
    public:
        ITeleopDrive() = default;
        ~ITeleopDrive() = default;

        virtual void Drive() =  0;

};
