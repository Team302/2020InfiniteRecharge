
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

#pragma once

// C++ Includes
#include <vector>

// FRC includes

// Team 302 includes
#include <auton/PrimitiveEnums.h>
//#include <utils/DragonMath.h>

// Third Party Includes





class PrimitiveParams
{
    public:

        PrimitiveParams
        (
                PRIMITIVE_IDENTIFIER        id,
                float                       time,
                float                       distance,
                float                       xLoc,
                float                       yLoc,
                float                       heading,
                float                       startDriveSpeed,
                float                       endDriveSpeed
        );//Constructor. Takes in all parameters

        PrimitiveParams() = delete;
        virtual ~PrimitiveParams();//Destructor


        //Some getters
        PRIMITIVE_IDENTIFIER GetID() const;
        float GetTime() const;
        float GetDistance() const;
        float GetXLocation() const;
        float GetYLocation() const;
        float GetHeading() const;
        float GetDriveSpeed() const;
        float GetEndDriveSpeed() const;

        //Setters
        void SetDistance(float distance);

    private:
        //Primitive Parameters
        PRIMITIVE_IDENTIFIER        m_id; //Primitive ID
        float                       m_time;
        float                       m_distance;
        float                       m_xLoc;
        float                       m_yLoc;
        float                       m_heading;
        float                       m_startDriveSpeed;
        float                       m_endDriveSpeed;
};

typedef std::vector<PrimitiveParams*> PrimitiveParamsVector;



