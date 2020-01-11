/*
* LEDDefn.h
*
*   Created on: Feb 26, 2019
*       Author: Christopher Castillo
*/

#pragma once

// C++ Includes
#include <iostream>

// Team Includes
#include <hw/LED.h>

// Third Party Includes
#include <pugixml/pugixml.hpp>


class LEDDefn
{
public:
    LEDDefn() = default;
    virtual ~LEDDefn() = default;

/*----------------------------------------------------------------------------------------
Method:     ParseXML
Description: Parse a pcm XML element and create a LED* from its definition
<!-- ====================================================
	 LEDs
	 ==================================================== -->
<!ELEMENT led EMPTY>
<!ATTLIST led 
          canId             (  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 
                              10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 
                              20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 
                              30 | 31 | 32 | 33 | 34 | 35 | 36 | 37 | 38 | 39 | 
                              40 | 41 | 42 | 43 | 44 | 45 | 46 | 47 | 48 | 49 | 
                              50 | 51 | 52 | 53 | 54 | 55 | 56 | 57 | 58 | 59 | 
                              60 | 61 | 62 ) "0"
>
*/



    LED* ParseXML
    (
        pugi::xml_node      LEDNode
    );
};


