
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

// FRC includes

// Team 302 includes

// Third Party Includes



#include <string>
#include <vector>
#include <frc/SmartDashboard/SendableChooser.h>

class AutonSelector
{
	public:
		// TODO: Add boolean to show if Evan is dumb or not

		enum AUTON_POSITION
		{
			LEFT_CORNER,
			CENTER,
			RIGHT_CORNER
		};

		enum AUTON_OPTION
		{
			CROSS_LINE
		};
		//---------------------------------------------------------------------
		// Method: 		<<constructor>>
		// Description: This creates this object and reads the auto script (CSV)
		//  			files and displays a list on the dashboard.
		//---------------------------------------------------------------------
		AutonSelector();

		//---------------------------------------------------------------------
		// Method: 		<<destructor>>
		// Description: default cleanup
		//---------------------------------------------------------------------
		virtual ~AutonSelector() = default;

		//---------------------------------------------------------------------
		// Method: 		GetSelectedAutoFile
		// Description: This returns the selected auton file to run.  If it
		//  			returns "Do Nothing", it is indicating no auton should
		//				be run.
		// Returns:		std::string			auton file to run
		//---------------------------------------------------------------------
		std::string GetSelectedAutoFile();

	private:

		//---------------------------------------------------------------------
		// Method: 		GetCrossLineFile
		// Description: This determines which Cross line file to run based on starting
		//				position 
		// Returns:		std::string		filename to run
		//---------------------------------------------------------------------
        std::string GetCrossLineFile();

		//---------------------------------------------------------------------
		// Method: 		FindXMLFileNames
		// Description: This builds up a list of XML files in the directory and
		//				stores them in the attributes.
		// Returns:		void
			//---------------------------------------------------------------------
		void FindXMLFileNames();

		//---------------------------------------------------------------------
		// Method: 		PutChoicesOnDashboard
		// Description: This puts the list of files in the m_csvFiles attribute
		//				up on the dashboard for selection.
		// Returns:		void
		//---------------------------------------------------------------------
		void PutChoicesOnDashboard();

		//---------------------------------------------------------------------
		// Method: 		GetRobotStartPosition
		// Description: Read the starting position from the smart dashboard
		// Returns:		AutonSelector::AUTON_POSITION		starting position
		//---------------------------------------------------------------------
		AUTON_POSITION GetRobotStartPosition();

		//---------------------------------------------------------------------
		// Method: 		GetDesiredOption
		// Description: Read the desired behavior from the smart dashboard
		// Returns:		AutonSelector::AUTON_OPTION		desired behavior
		//---------------------------------------------------------------------
		AUTON_OPTION GetDesiredOption();

		// Attributes
		std::vector<std::string> m_leftXMLFiles;
		std::vector<std::string> m_centerXMLFiles;
		std::vector<std::string> m_rightXMLFiles;


		// 16 character limits to avoid some smartdashboard issues
		// AUTOLINE Option
		const std::string CROSS_AUTON_LINE_STR = "Auto Line";
		frc::SendableChooser<std::string> m_chooserOptions;

		// STARTING Positions
		const std::string LEFT_CORNER_STR = "LeftCorner";
		const std::string CENTER_STR = "Center";
		const std::string RIGHT_CORNER_STR = "RightCorner";
		frc::SendableChooser<std::string> m_chooserPosition;

		frc::SendableChooser<std::string> m_chooser;
		frc::SendableChooser<std::string> m_chooserLeft;
		frc::SendableChooser<std::string> m_chooserCenter;
		frc::SendableChooser<std::string> m_chooserRight;

		const std::string m_autonDir = "/home/lvuser/auton/";
		const std::string m_defaultFile = "CrossAutonLine.xml";
		std::string 	  m_autonPositionModifier;
		std::string 	  m_autonOption;


        const std::string XML = ".xml";
        const std::string DTD = ".dtd";

		const std::string CROSS_AUTON_LINE = "Cross Auton Line";
};

