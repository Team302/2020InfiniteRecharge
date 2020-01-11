
//====================================================================================================================================================
// Copyright 2019 Lake Orion Robotics FIRST Team 302
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

// C++ Includes
#include <memory>
#include <string>

// FRC includes
#include <frc/Timer.h>

// Team 302 includes
#include <auton/primitives/IPrimitive.h>
#include <auton/PrimitiveParams.h>
#include <auton/primitives/TurnAngle.h>
#include <auton/primitives/TurnToCube.h>

#include <hw/factories/LidarFactory.h>

#include <subsys/IMechanism.h>
#include <subsys/MechanismFactory.h> 
#include <controllers/ControlModes.h>

#include <utils/Logger.h>

// Third Party Includes


using namespace std;
using namespace frc;


TurnToCube::TurnToCube() : m_scanned( false ),
                           m_minAngle( 360.0 ),     // complete revolution
                           m_minDist( 648.0 ),      // 54 feet * 12 inches per foot
                           m_lidar( nullptr )
{
    /*
    LidarFactory* factory = LidarFactory::GetLidarFactory();
    if ( factory != nullptr )
    {
        m_lidar = factory->GetLidar( DragonLidar::FORWARD_GRABBER );
    }
    */
}


void TurnToCube::Init(PrimitiveParams* params)
{
    TurnAngle::Init( params );
    m_scanned  = false;
    m_minAngle = 360.0;
    /*
    if ( m_lidar != nullptr )
    {
        m_minDist = m_lidar->GetDistance();
    }
    */
}

void TurnToCube::Run()
{
    TurnAngle::Run();
    if ( m_lidar != nullptr )
    {
        /*
        double currDist = m_lidar->GetDistance();
        if ( currDist < m_minDist )
        {
            m_minDist = currDist;
            m_minAngle = ChassisFactory::GetChassisFactory()->GetIChassis()->GetHeading();
        }
        */
    }
}

bool TurnToCube::IsDone()
{
    bool done = TurnAngle::IsDone();
    if ( done && !m_scanned )
    {
        done = false;
        m_scanned = true;
    }
    return done;
}


