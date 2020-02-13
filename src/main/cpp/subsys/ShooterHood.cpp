///==================================================================================================================================================== 
/// Copyright 2020 Lake Orion Robotics FIRST Team 302 
/// 
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
/// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
/// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions: 
/// 
/// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software. 
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
/// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
/// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
/// OR OTHER DEALINGS IN THE SOFTWARE. 
//==================================================================================================================================================== 
 
 
// C++ Includes 
 
#include <memory> 
  
// FRC includes 
            
 
// Team 302 includes 
#include <subsys/ShooterHood.h> 
#include <utils/logger.h> 
#include <hw/DragonSolenoid.h> 
#include <hw/interfaces/IDragonMotorController.h> 
#include <hw/DragonServo.h> 
#include <subsys/MechanismTypes.h> 

// Third Party includes
#include <ctre/phoenix/sensors/CANCoder.h>

using namespace std; 
using namespace ctre::phoenix::sensors;
using namespace ctre::phoenix::motorcontrol;
 
ShooterHood::ShooterHood 
( 
   shared_ptr<IDragonMotorController>        shmotor,
	shared_ptr<CANCoder>					         canCoder

) : m_shmotor(shmotor),
    m_encoder( canCoder )
{ 
      m_shmotor.get()->SetRemoteSensor( canCoder.get()->GetDeviceNumber(), RemoteSensorSource::RemoteSensorSource_CANCoder );
} 
/// @brief          Indicates the type of mechanism this is 
/// @return         MechanismTypes::MECHANISM_TYPE 
MechanismTypes::MECHANISM_TYPE ShooterHood :: GetType() const  
{ 
   return MechanismTypes::MECHANISM_TYPE::SHOOTER_HOOD; 
} 
/// @brief      Run mechanism as defined  
/// @param [in] ControlModes::CONTROL_TYPE   controlType:  How are the item(s) being controlled 
/// @param [in] double                                     value:        Target (units are based on the controlType) 
/// @return     void 
void ShooterHood::SetOutput
( 
ControlModes::CONTROL_TYPE controlType, 
double                                   value        
)  
{ 
  m_shmotor.get()->SetControlMode(controlType);
  m_shmotor.get()->Set( value );
} 
/// @brief      Activate/deactivate pneumatic solenoid 
/// @param [in] bool - true == extend, false == retract 
/// @return     void  
void ShooterHood ::ActivateSolenoid 
( 
bool     activate 
) 
{ 
} 
/// @brief      Check if the pneumatic solenoid is activated 
/// @return     bool - true == extended, false == retract 
bool ShooterHood :: IsSolenoidActivated()  
{ 
return false; 
} 
/// @brief  Return the current position of the mechanism.  The value is in inches or degrees. 
/// @return double  position in inches (translating mechanisms) or degrees (rotating mechanisms) 
double ShooterHood :: GetCurrentPosition() const  
{ 
    return m_encoder.get() != nullptr ? m_encoder.get()->GetAbsolutePosition() : 0.0;
} 

/// @brief  Get the current speed of the mechanism.  The value is in inches per second or degrees per second. 
/// @return double  speed in inches/second (translating mechanisms) or degrees/second (rotating mechanisms) 
double ShooterHood ::GetCurrentSpeed() const  
{ 
    return m_encoder.get() != nullptr ? m_encoder.get()->GetVelocity()*10.0 : 0.0;
} 

/// @brief  Set the control constants (e.g. PIDF values). 
/// @param [in] ControlData*                                   pid:  the control constants 
/// @return void 
void ShooterHood :: SetControlConstants 
( 
ControlData*                                pid                  
)  
{ 
    m_shmotor.get()->SetControlConstants( pid );
} 