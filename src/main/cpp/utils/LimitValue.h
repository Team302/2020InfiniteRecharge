/*=============================================================================================
 * LimitValue.h
 *=============================================================================================
 *
 * File Description:
 *
 * This has a static function to limit the range of a value
 *=============================================================================================*/


#ifndef SRC_UTILS_LIMITVALUE_H_
#define SRC_UTILS_LIMITVALUE_H_

class LimitValue
{
public:

    //----------------------------------------------------------------------------------
    // Method:      ForceInRange
    // Description: This will compare a value to a range.  If the value is outside of the
    //              range, the nearest bounding value will be returned.
    // Returns:     float value to use which is in range
    //----------------------------------------------------------------------------------
    static float ForceInRange
    (
        const float value,          // <I> - value to check
        const float lowerBound, 	// <I> - lower bound to check against
        const float upperBound 	  	// <I> - upper bound to check against
    );

    //----------------------------------------------------------------------------------
    // Method:      GetTrimmedValue
    // Description: This will compare a value to a range and return the portion that is
    //				out of range (e.g. if -1.5 is passed in and the range is -1.0 to 1.0,
    //				it will return -0.5).
    // Returns:     float 	if value is out of range, this is the value trimmed off to put
	//       				it into range.
    //----------------------------------------------------------------------------------
    static float GetTrimmedValue
    (
        const float value,          // <I> - value to check
        const float lowerBound, 	// <I> - lower bound to check against
        const float upperBound 	  	// <I> - upper bound to check against
    );

    // Static functions, so no creator or destructor
    LimitValue() = delete;
    virtual ~LimitValue() = delete;
};

#endif /* SRC_UTILS_LIMITVALUE_H_ */
