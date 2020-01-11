/*=============================================================================================
 * LimitValue.cpp
 *=============================================================================================
 *
 * File Description:
 *
 * This implements the IDrive interface to drive the robot using joysticks in a tank
 * drive mode.
 *=============================================================================================*/

// Team 302 includes
#include <utils/LimitValue.h>


//----------------------------------------------------------------------------------
// Method:      ForceInRange
// Description: This will compare a value to a range.  If the value is outside of the
//              range, the nearest bounding value will be returned.
// Returns:     float value to use which is in range
//----------------------------------------------------------------------------------
float LimitValue::ForceInRange
(
    const float value,      	// <I> - value to check
    const float lowerBound, 	// <I> - lower bound to check against
    const float upperBound  	// <I> - upper bound to check against
)
{
    float output  = value;			// initialize the return value
	
	if(value < lowerBound)
	{
		output = lowerBound;
	}
	else if(value > upperBound)
	{
		output = upperBound;
	}
    // If the value is less than the lower bound set the output value to the lower bound and update trimmedValue
    // If the output value is greater than the upper bound, set the output value to the upper bound and update trimmedValue


    // return the limited value to the caller
    return output;
}

//----------------------------------------------------------------------------------
// Method:      GetTrimmedValue
// Description: This will compare a value to a range and return the portion that is
//				out of range (e.g. if -1.5 is passed in and the range is -1.0 to 1.0,
//				it will return -0.5).
// Returns:     float 	if value is out of range, this is the value trimmed off to put
//       				it into range.
//----------------------------------------------------------------------------------
float LimitValue::GetTrimmedValue
(
    const float value,      	// <I> - value to check
    const float lowerBound, 	// <I> - lower bound to check against
    const float upperBound   	// <I> - upper bound to check against
)
{
    float output  = 0;
	
    if ( value < lowerBound )
	{
		output = output - lowerBound;
	}
	else if(value > upperBound)
	{
		output = output - upperBound;
	}

	// initialize the return value

    // If the value is less than the lower bound set the output to the value minus the lower bound.
    // If the value is greater than the upper bound, set the output to the value minus
    // the value.


    // return the trimmed value to the caller
    return output;
}



