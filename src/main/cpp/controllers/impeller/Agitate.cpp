///Created by the one, the only, Big Chief, AJ Gdowski
///Nobody will ever be brave enough to steal my code, so don't even think about it

#include <controllers/IState.h>
#include <subsys/IMechanism.h>
#include <subsys/MechanismFactory.h>
#include <controllers/impeller/Agitate.h>


///This is used to contruct any elements I am going to use
Agitate::Agitate()
{
    auto factory = MechanismFactory::GetMechanismFactory();

    m_impeller = factory -> GetIMechanism(MechanismTypes::MECHANISM_TYPE::IMPELLER);
}


///This initializes any elements of the code I am going to use in Run
void Agitate::Init()
{
    is_moving_forward = true;
    m_target = m_impeller -> GetCurrentPosition() + addition_delta;
}


///This runs the code elements every 20ms on repeat
void Agitate::Run()
{
    double current_Position = m_impeller -> GetCurrentPosition();


    if (is_moving_forward == true)
    {
        if (current_Position <= m_target)
        {
            m_impeller -> SetOutput(ControlModes::CONTROL_TYPE::PERCENT_OUTPUT, 1); //Sets the motor to a output
        }
        else
        {
            is_moving_forward = false; //Changes to other side of if statement
            m_target = m_impeller -> GetCurrentPosition() - subtraction_delta; //Sets a new target position
        }
        
    }
    else
    {
        if (current_Position >= m_target)
        {
            m_impeller -> SetOutput(ControlModes::CONTROL_TYPE::PERCENT_OUTPUT, -1); //Makes the motor move backwards
        }
        else
        {
            is_moving_forward = true;
            m_target = m_impeller ->GetCurrentPosition() + addition_delta; //Resets the data to the moving forward
        }
        
    }
    
}

///This ends all the processes once a condition is reached
bool Agitate::AtTarget() const
{

}


