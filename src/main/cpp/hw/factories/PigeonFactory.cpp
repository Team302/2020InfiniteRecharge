
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

//========================================================================================================
/// @class PigeonFactory
/// @brief This creates the pigeon
//========================================================================================================

// C++ Includes
#include <algorithm>
#include <locale>
#include <map>
#include <memory>
#include <string>

// FRC includes

// Team 302 includes
#include <hw/factories/PigeonFactory.h>
#include <hw/DragonPigeon.h>
#include <hw/usages/AnalogInputUsage.h>
#include <utils/Logger.h>


// Third Party Includes


using namespace std;

/// @brief  Find or create the analog input factory
/// @return PigeonFactory* pointer to the factory
PigeonFactory* PigeonFactory::m_factory = nullptr;
PigeonFactory* PigeonFactory::GetFactory()
{
	if ( PigeonFactory::m_factory == nullptr )
	{
		PigeonFactory::m_factory = new PigeonFactory();
	}
	return PigeonFactory::m_factory;
}

PigeonFactory::PigeonFactory()
{
    m_pigeon = nullptr;
}


/// @brief  Create the requested analog input
/// @return shared_ptr<DragonPigeon>   the mechanism or nullptr if mechanism doesn't 
///         exist and cannot be created.
DragonPigeon* PigeonFactory::CreatePigeon
(
    int 	canID
)
{
    if ( m_pigeon == nullptr )
    {
        m_pigeon = new DragonPigeon( canID );
    }
    return m_pigeon;
}

DragonPigeon* PigeonFactory::GetPigeon() const
{
    return m_pigeon;
}
