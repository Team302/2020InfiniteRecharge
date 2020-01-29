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

// C++ includes
#include <string>

// Team 302 includes
#include <controllers/ControlData.h>
#include <controllers/ControlModes.h>

using namespace std;

ControlData::ControlData
(
    ControlModes::CONTROL_TYPE                  mode,
	ControlModes::CONTROL_RUN_LOCS				server,
    string                                      identifier,
    double                                      proportional,
    double                                      integral,
    double                                      derivative,
    double                                      feedforward,
    double                                      integralZone,
    double                                      maxAcceleration,
    double                                      cruiseVelocity,
    double                                      peakVal,
    double                                      nominalVal
) : m_mode( mode ),
    m_identifier( identifier ),
    m_proportional( proportional ),
    m_integral( integral ),
    m_derivative( derivative ),
    m_feedforward( feedforward ),
    m_iZone( integralZone ),
    m_maxAcceleration( maxAcceleration ),
    m_cruiseVelocity( cruiseVelocity ),
    m_peakValue( peakVal ),
    m_nominalValue( nominalVal )
{

}
