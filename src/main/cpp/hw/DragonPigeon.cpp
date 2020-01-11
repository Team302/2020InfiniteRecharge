/*
 * DragonPigeon.cpp
 *
 *  Created on: Feb 3, 2018
 *      Author: team302
 */

#include <ctre/phoenix/Sensors/PigeonIMU.h>
#include <hw/DragonPigeon.h>
#include <iostream>
#include <frc/SmartDashboard/SmartDashboard.h>
#include <cmath>
#include <memory>

using namespace std;
using namespace frc;

using namespace ctre;
using namespace phoenix;
using namespace motorcontrol;
using namespace can;

DragonPigeon::DragonPigeon
(
    int  canID
)
{
    m_pigeon = make_unique<ctre::phoenix::sensors::PigeonIMU>( canID );
    m_initialRoll  = GetRawRoll( );
    m_initialPitch = GetRawPitch( );
    m_initialYaw   = GetRawYaw( );
}


double DragonPigeon::GetPitch()
{
    return -(GetRawPitch() - m_initialPitch); //TODO: add inversions into code
}

double DragonPigeon::GetRoll()
{
    return GetRawRoll() - m_initialRoll;
}

double DragonPigeon::GetYaw()
{
    return GetRawYaw() - m_initialYaw;
}

double DragonPigeon::GetRawPitch()
{
    double ypr[3];
    m_pigeon->GetYawPitchRoll(ypr);

    // return ypr[1]; // yaw = 0 pitch = 1 roll = 2 
    return ypr[2];
}

double DragonPigeon::GetRawRoll()
{
    double ypr[3];
    m_pigeon->GetYawPitchRoll(ypr);

    // return ypr[2]; // yaw = 0 pitch = 1 roll = 2 
    return ypr[1];
}

double DragonPigeon::GetRawYaw()
{
    double ypr[3];
    m_pigeon->GetYawPitchRoll(ypr);

    return ypr[0]; // yaw = 0 pitch = 1 roll = 2 
}

