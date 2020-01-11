
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
#include <string>
#include <vector>

// FRC includes
#include <networktables/NetworkTableInstance.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableEntry.h>
#include <frc/smartdashboard/SmartDashboard.h>

// Team 302 includes
#include <hw/DragonLimelight.h>
#include <utils/Logger.h>

// Third Party Includes

using namespace nt;
using namespace std;

///-----------------------------------------------------------------------------------
/// Method:         DragonLimelight (constructor)
/// Description:    Create the object
///-----------------------------------------------------------------------------------
DragonLimelight::DragonLimelight
(
    IDragonSensor::SENSOR_USAGE usage,
    string                      tableName,                  /// <I> - network table name
    double                      mountingHeight,             /// <I> - mounting height of the limelight
    double                      mountingHorizontalOffset,   /// <I> - mounting horizontal offset from the middle of the robot 
    double                      mountingAngle,              /// <I> - mounting angle of the camera
    double                      targetHeight                /// <I> - height the target
) : IDragonSensor(),
    IDragonDistanceSensor(),
    m_usage( usage ),
    m_networktable( NetworkTableInstance::GetDefault().GetTable( tableName.c_str() ) ),
    m_mountHeight( mountingHeight ),
    m_mountingHorizontalOffset( mountingHorizontalOffset ),
    m_mountingAngle( mountingAngle ),
    m_targetHeight( targetHeight )
{}

///-----------------------------------------------------------------------
/// Method:      GetDistance
/// Description: Return the measured distance in inches
/// Returns:     double     Measured Distance
///-----------------------------------------------------------------------
double DragonLimelight::GetDistance() const
{
    double distance = -1.0;
    if ( HasTarget() )
    {
        distance = (m_targetHeight - m_mountHeight) / tan( m_mountingAngle + GetTargetVerticalOffset() );
    }
    return distance;
}

///-----------------------------------------------------------------------
/// Method:      GetConfidence
/// Description: Indicates how accurate the returned value is
/// Returns:     double    0.0 == ignore (sensor has an error)
///                        1.0 == very confident 
///-----------------------------------------------------------------------
double DragonLimelight::GetConfidence() const
{
    double confidence = 0.0;
    if ( HasTarget() )
    {
        confidence = 1.0;
    }
    return confidence;
}

std::vector<double> DragonLimelight::Get3DSolve() const
{
    return m_networktable->GetNumberArray("camtran", 0);
}

bool DragonLimelight::HasTarget() const
{
    return ( m_networktable->GetNumber("tv", 0.0) > 0.1 );
}

double DragonLimelight::GetTargetHorizontalOffset() const
{
    return ( m_networktable->GetNumber("tx", 0.0) - m_mountingHorizontalOffset);
}

double DragonLimelight::GetTargetVerticalOffset() const
{
    return m_networktable->GetNumber("ty", 0.0);
}

double DragonLimelight::GetTargetArea() const
{
    return m_networktable->GetNumber("ta", 0.0);
}

double DragonLimelight::GetTargetSkew() const
{
    return m_networktable->GetNumber("ts", 0.0);
}

double DragonLimelight::GetPipelineLatency() const
{
    return m_networktable->GetNumber("tl", 0.0);
}

///-----------------------------------------------------------------------
/// Method:      GetUsage
/// Description: Indicate what the sensor is used for
/// Returns:     SENSOR_USAGE    sensor usage 
///-----------------------------------------------------------------------
IDragonSensor::SENSOR_USAGE DragonLimelight::GetUsage() const
{
    return m_usage;
}

void DragonLimelight::SetTargetHeight
(
    double targetHeight
)
{
    m_targetHeight = targetHeight;
}

void DragonLimelight::SetLEDMode(DragonLimelight::LED_MODE mode)
{
    m_networktable->PutNumber("ledMode", mode);
}

void DragonLimelight::SetCamMode(DragonLimelight::CAM_MODE mode)
{
    m_networktable->PutNumber("camMode", mode);
}

void DragonLimelight::SetPipeline(int pipeline)
{
    m_networktable->PutNumber("pipeline", pipeline);
}

void DragonLimelight::SetStreamMode(DragonLimelight::STREAM_MODE mode)
{
    m_networktable->PutNumber("stream", mode);
}

// MAX of 32 snapshots can be saved
void DragonLimelight::ToggleSnapshot(DragonLimelight::SNAPSHOT_MODE toggle)
{
    m_networktable->PutNumber("snapshot", toggle);
}

void DragonLimelight::PrintValues()
{
    Logger::GetLogger()->LogError( "DragonLimelight::PrintValues HasTarget", to_string( HasTarget() ) );    
    Logger::GetLogger()->LogError( "DragonLimelight::PrintValues XOffset", to_string( GetTargetHorizontalOffset() ) ); 
    Logger::GetLogger()->LogError( "DragonLimelight::PrintValues YOffset", to_string( GetTargetVerticalOffset() ) ); 
    Logger::GetLogger()->LogError( "DragonLimelight::PrintValues Area", to_string( GetTargetArea() ) ); 
    Logger::GetLogger()->LogError( "DragonLimelight::PrintValues Skew", to_string( GetTargetSkew() ) ); 
    Logger::GetLogger()->LogError( "DragonLimelight::PrintValues Latency", to_string( GetPipelineLatency() ) ); 
}

