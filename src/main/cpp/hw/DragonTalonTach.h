/*
 *DragonTalonTach.h
 */

#pragma once

#include <memory>
#include <vector>

#include <iostream>

#include <ctre/phoenix/CANifier.h> 



class DragonTalonTach
{
    public:
        enum TALON_TACH_USAGE
	    {
	        UNKNOWN_TALON_TACH_USAGE = -1,
            MIN_WRIST_ANGLE,
            MAX_WRIST_ANGLE,
            TOP_HATCH_PRESENT,
            BOTTOM_HATCH_PRESENT,
            ARM_BOTTOM,
            ARM_TOP,
            MAX_TALON_TACH_USAGE
	    };

        //------------------------------------------------------------------------------
        // Method:		<<constructor>>
        // Description:
        //------------------------------------------------------------------------------
	    DragonTalonTach	
            (
                TALON_TACH_USAGE                        usage,	    // <I> - Usage of the talon tach
			    int	                                    canID,		// <I> - CAN io ID
			    ctre::phoenix::CANifier::GeneralPin	    generalpin,	// <I> - general pin
                bool                                    reversed
            );

        DragonTalonTach() = delete;
	    virtual ~DragonTalonTach() = default;

        bool Get() const;

    private:
	    TALON_TACH_USAGE                                    m_usage;
        std::shared_ptr<ctre::phoenix::CANifier>            m_CAN;
        ctre::phoenix::CANifier::GeneralPin                 m_generalpin;
        bool                                                m_reversed;
};

