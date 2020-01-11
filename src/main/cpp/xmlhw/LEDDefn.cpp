/*
* LEDDefn.cpp
*
* Created on: Feb 26, 2019
*   Author: Christopher Castillo
*/
   
#include <iostream>
#include <string.h>

#include <hw/LED.h>
#include <hw/factories/LEDFactory.h>
#include <xmlhw/LEDDefn.h>
#include <pugixml/pugixml.hpp>

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
LED* LEDDefn::ParseXML(
    pugi::xml_node LEDNode)
{
    //initialize output
    LED *led = nullptr;

    //initialize attributes to default values
    int canID = -1;
    int usage = -1;

    bool hasError = false;

    //parse/validate xml
    for (pugi::xml_attribute attr = LEDNode.first_attribute(); attr; attr = attr.next_attribute())
    {
        if (strcmp(attr.name(), "canId") == 0)
        {
            int iVal = attr.as_int();
            if (iVal > -1 && iVal < 63)
            {
                canID = iVal;
            }
            else
            {
                printf("==>> LEDDefn::ParseXML invalid canId %d \n", iVal);
                hasError = true;
            }
        }
        else if (strcmp(attr.name(), "usage") == 0)
        {
            int iVal = attr.as_int();
            if (iVal > -1 && iVal < 3)
            {
                usage = iVal;
            }
        }
    }
    //create object
    if (!hasError)
    {
        // led = new LED(canID);
        led = LEDFactory::GetInstance()->CreateLED((LEDFactory::LED_USAGE) usage, canID);
    }
    return led;
}
