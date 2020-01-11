
/*========================================================================================================
 * DragonServoFactory.cpp
 *========================================================================================================
 *
 * File Description:  Create DragonServos and allow external clients to retrieve created DragonServos
 *
 *========================================================================================================*/


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

#include <map>
#include <memory>


#include <hw/factories/DragonServoFactory.h>
#include <hw/DragonServo.h>

#include <utils/Logger.h>

using namespace std;


DragonServoFactory* DragonServoFactory::m_instance = nullptr;



//=======================================================================================
/// Method: GetInstance
/// @brief  Get the factory singleton
/// @return DragonServoFactory*    pointer to the factory
//=======================================================================================
DragonServoFactory* DragonServoFactory::GetInstance()
{
    if ( DragonServoFactory::m_instance == nullptr )
    {
        DragonServoFactory::m_instance = new DragonServoFactory();
    }
    return DragonServoFactory::m_instance;
}



//=======================================================================================
/// Method: CreateDragonServo
/// @brief  Create a DragonServo from the inputs
/// @param [in] DragonServo::SERVO_USAGE   deviceUsage  Usage of the servo
/// @param [in] int                        deviceID     PWM ID of the  servo
/// @param [in] double                     minAngle     Minimum Angle for the servo
/// @param [in] double                     maxAngle     Maximum Angle for the servo
/// @return std::shared_ptr<DragonServo>    - could be nullptr if invalid inputs are supplied
//=======================================================================================
shared_ptr<DragonServo> DragonServoFactory::CreateDragonServo
(
    DragonServo::SERVO_USAGE    deviceUsage,        
    int                         deviceID,           
    double                      minAngle,           
    double                      maxAngle            
)
{
    shared_ptr<DragonServo> servo = nullptr;
    if ( deviceUsage > DragonServo::SERVO_USAGE::UNKNOWN_SERVO_USAGE && deviceUsage < DragonServo::SERVO_USAGE::MAX_SERVO_USAGES )
    {
        servo = m_servos.find(deviceUsage)->second;
        if ( servo != nullptr )
        {
            string msg = "servo with usage already exists " + to_string( deviceUsage );
            Logger::GetLogger()->LogError( "DragonServoFactory::CreateDragonServo", msg );
        }
        else
        {       
            switch ( deviceUsage )
            {
                case DragonServo::SERVO_USAGE::ROTATE_LIMELIGHT:
                    servo = make_shared<DragonServo>( deviceUsage, deviceID, minAngle, maxAngle );
                    m_servos[deviceUsage] = servo;
                    break;

                case DragonServo::SERVO_USAGE::TAIL_CONTROL:
                    servo = make_shared<DragonServo>( deviceUsage, deviceID, minAngle, maxAngle );
                    m_servos[deviceUsage] = servo;
                    break;

                default:
                    string msg = "Unknown Servo Usage " + to_string( deviceUsage );
                    Logger::GetLogger()->LogError( "DragonServoFactory::CreateDragonServo", msg );
                    break;
            }
        }
    }
    return servo;
}



//=======================================================================================
/// Method: GetDragonServo
/// @brief  Get a DragonServo from its usage
/// @param [in] DragonServo::SERVO_USAGE   deviceUsage  Usage of the servo
/// @return std::shared_ptr<DragonServo>    - could be nullptr if invalid inputs are supplied
//=======================================================================================
shared_ptr<DragonServo> DragonServoFactory::CreateDragonServo
(
    DragonServo::SERVO_USAGE    deviceUsage        
)
{
    return m_servos.find(deviceUsage)->second;
}


