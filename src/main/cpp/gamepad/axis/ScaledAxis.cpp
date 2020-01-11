
/*========================================================================================================
 * ScaledAxis.cpp
 *========================================================================================================
 *
 * File Description:  This scales an axis.
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

#include <gamepad/axis/ScaledAxis.h>

#include <cmath>
#include <iostream>

ScaledAxis::ScaledAxis() : m_scale( 1.0 )
{
}

        
//==================================================================================
/// <summary>
/// Method:         SetScaleFactor
/// Description:    Set a scalefactor
/// </summary>
//==================================================================================
void ScaledAxis::SetScaleFactor
(
    double      scaleFactor            // <I> - scale factor must be > 0.0 and <= 1.0
)
{
    if ( m_scale > 0.0 )
    {
        m_scale = scaleFactor;
    }
    else
    {
        m_scale = -1.0 * scaleFactor;
    }
}


//==================================================================================
/// <summary>
/// Method:         Scale
/// Description:    Multiply the output by the scale factor
/// </summary>
//==================================================================================
double ScaledAxis::Scale
(
    double      inputVal            // <I> - value to scale     
) const
{
    return (inputVal * m_scale);
}


