/*
 *TalonTachDefn.h
 *
 */

#ifndef SRC_MAIN_CPP_XMLHW_TALONTACH_H_
#define SRC_MAIN_CPP_XMLHW_TALONTACH_H_

// C++ Includes
#include <iostream>
// FRC includes

// Team 302 includes
#include <hw/DragonTalonTach.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>



class TalonTachDefn
{
    public:

        TalonTachDefn() = default;
        virtual ~TalonTachDefn() = default;

        //-----------------------------------------------------------------------
        // Method:      ParseXML
        // Description: Parse a TalonTach XML element 
        // Returns:     DragonTalonTach
        //-----------------------------------------------------------------------
        DragonTalonTach* ParseXML
        (
            pugi::xml_node      talontachNode
        );
};

#endif /* SRC_MAIN_CPP_XMLHW_TALONTACH_H_ */