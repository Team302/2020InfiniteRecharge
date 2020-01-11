/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include <memory>

#include <xmlhw/CANifierDefn.h>
#include <hw/factories/CanifierFactory.h>

//Third Party includes
#include <pugixml/pugixml.hpp>

//CTRE includes
#include <ctre/Phoenix.h>

using namespace frc;
using namespace std;


std::shared_ptr<ctre::phoenix::CANifier> CANifierDefn::ParseXML
(
    pugi::xml_node      canifierNode
)
{
	//initialize output
	shared_ptr<ctre::phoenix::CANifier> canifier = nullptr;
	// initialize attributes to default values
	int canID = 0;
	bool hasError = false;

//Parse/validate xml
	for(pugi::xml_attribute attr = canifierNode.first_attribute(); attr; attr = attr.next_attribute() )
	{
		if (strcmp(attr.name(), "canId" ) == 0)
		{
			int iVal = attr.as_int();
            if ( iVal > -1 && iVal < 63 )
            {
                canID = attr.as_int();
            }
            else
            {
                printf( "==>> CANifierDefn::ParseXML invalid CAN ID %d \n", iVal );
                hasError = true;
            }
		}		
		else
		{
		    hasError = true;
			printf( "==>CANifierDefn::ParseXML invalid attribute %s \n", attr.name() );
		}

	}

	if (!hasError)
	{
        //creates CANifier object if no error in XML
        canifier = CanifierFactory::GetInstance()->GetCanifier(canID);		
	}
    return canifier;
}

