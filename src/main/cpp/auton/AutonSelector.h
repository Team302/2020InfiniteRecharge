
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
#include <auton/FMS.h>

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
			CROSS_LINE,
			SWITCH,
			SCALE_PLACE_FAR,
			SCALE_HALFWAY,
			END_SCALE_PLACE_FAR,
			END_SCALE_HALFWAY,
			SCALE_BACKUP_PLACE_FAR,
			SCALE_BACKUP_HALFWAY,
			SWITCH_SCALE,
			SMART
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

		enum FIELD_STATE
		{
            LEFTSWITCH_LEFTSCALE_LEFT = 0,
            RIGHTSWITCH_LEFTSCALE_LEFT = 1,
            LEFTSWITCH_RIGHTSCALE_LEFT = 10,
            RIGHTSWITCH_RIGHTSCALE_LEFT = 11,
            LEFTSWITCH_LEFTSCALE_CENTER = 100,
            RIGHTSWITCH_LEFTSCALE_CENTER = 101,
            LEFTSWITCH_RIGHTSCALE_CENTER = 110,
            RIGHTSWITCH_RIGHTSCALE_CENTER = 111,
            LEFTSWITCH_LEFTSCALE_RIGHT = 200,
            RIGHTSWITCH_LEFTSCALE_RIGHT = 201,
            LEFTSWITCH_RIGHTSCALE_RIGHT = 210,
            RIGHTSWITCH_RIGHTSCALE_RIGHT =211,
		};

		//---------------------------------------------------------------------
		// Method: 		GetCrossLineFile
		// Description: This determines which Cross line file to run based on starting
		//				position and FMS feedback
		// Returns:		std::string		filename to run
		//---------------------------------------------------------------------
        std::string GetCrossLineFile
        (
            int state		// <I> - FIELD_STATE enum value
        );

        //---------------------------------------------------------------------
        // Method: 		GetSwitchFile
        // Description: This determines which Switch file to run based on starting
        //				position and FMS feedback
        // Returns:		std::string		filename to run
        //---------------------------------------------------------------------
        std::string GetSwitchFile
        (
            int state		// <I> - FIELD_STATE enum value
        );

        //---------------------------------------------------------------------
        // Method: 		GetScaleFile
        // Description: This determines which Scale file to run based on starting
        //				position and FMS feedback
        // Returns:		std::string		filename to run
        //---------------------------------------------------------------------
        std::string GetScalePlaceFarFile
        (
            int state		// <I> - FIELD_STATE enum value
        );

        //---------------------------------------------------------------------
        // Method: 		GetScaleFile
        // Description: This determines which Scale file to run based on starting
        //				position and FMS feedback
        // Returns:		std::string		filename to run
        //---------------------------------------------------------------------
        std::string GetScaleHalfwayFile
        (
            int state		// <I> - FIELD_STATE enum value
        );

        //---------------------------------------------------------------------
        // Method: 		GetEndScalePlaceFarFile
        // Description: This determines which End Scale/Scale file to run based on starting
        // 				position and FMS feedback
        // Returns:		std::string		filename to run
        //---------------------------------------------------------------------
        std::string GetEndScalePlaceFarFile
		(
			int state		// <I> - FIELD_STATE enum value
		);

        //---------------------------------------------------------------------
        // Method: 		GetEndScaleHalfwayFile
        // Description: This determines which End Scale/Halfway file to run based on starting
        // 				position and FMS feedback
        // Returns:		std::string		filename to run
        //---------------------------------------------------------------------
        std::string GetEndScaleHalfwayFile
		(
			int state		// <I> - FIELD_STATE enum value
		);

        //---------------------------------------------------------------------
        // Method: 		GetSwitchScaleFile
        // Description: This determines which Switch/Scale file to run based on starting
        //				position and FMS feedback
        // Returns:		std::string		filename to run
        //---------------------------------------------------------------------
        std::string GetSwitchScaleFile
        (
            int state		// <I> - FIELD_STATE enum value
        );


        //does what the other ones do :)
        std::string GetScaleBackUpPlaceFarFile
		(
			int state		// <I> - FIELD_STATE enum value
		);

        //does what the other ones do :)
        std::string GetScaleBackUpHalfwayFile
		(
			int state		// <I> - FIELD_STATE enum value
		);

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


		bool ProcessSmartOptions
		(
			AUTON_POSITION		startPosition,				// <I> - robot starting position
			FMS::POS			fmsSwitch,					// <I> - FMS setting for our switch
			FMS::POS			fmsScale					// <I> - FMS setting for the scale
		);

		// Attributes
		std::vector<std::string> m_leftXMLFiles;
		std::vector<std::string> m_centerXMLFiles;
		std::vector<std::string> m_rightXMLFiles;


		// 16 character limits to avoid some smartdashboard issues
		// AUTOLINE Option
		const std::string CROSS_AUTON_LINE_STR = "Auto Line";
		// SWITCH Option
		const std::string PLACE_IN_SWITCH_STR = "Switch";
		// CORNER SCALE Option
		const std::string PLACE_ON_CORNER_SCALE_FAR_STR = "Corner SC Far";
		const std::string PLACE_ON_CORNER_SCALE_HALFWAY_STR = "Corner SC Half";
		// SAFE SCALE Option
		const std::string PLACE_ON_END_SCALE_FAR_STR = "End SC Far";
		const std::string PLACE_ON_END_SCALE_HALFWAY_STR = "End SC Half";
		// BACKUP SCALE Option
		const std::string PLACE_ON_CORNER_SCALE_BACKUP_FAR_STR = "Bkup SC Far";
		const std::string PLACE_ON_CORNER_SCALE_BACKUP_HALFWAY_STR = "Bkup SC Half";
		// SWITCH SCALE Option
		const std::string PLACE_ON_SWITCH_SCALE_STR = "Switch Scale";
		// SMART Option
		const std::string SMART_AUTON_STR = "Smart Auto";
		frc::SendableChooser<std::string> m_chooserOptions;

		// STARTING Positions
		const std::string LEFT_CORNER_STR = "LeftCorner";
		const std::string CENTER_STR = "Center";
		const std::string RIGHT_CORNER_STR = "RightCorner";
		frc::SendableChooser<std::string> m_chooserPosition;

		const std::string PARTNER_IN_MIDDLE_STR = "Partner in Middle can get switch";
		const std::string PARTNER_GET_THEIR_SIDE_SWITCH_STR = "Partner can get switch on their side";
		const std::string PARTNER_GET_THEIR_SIDE_SCALE_STR = "Partner can get scale on their side";
		const std::string PARTNERS_ONLY_MOVE = "Partners only cross auton line";
		const std::string PARTNERS_DO_NOT_MOVE = "Partners do not move";
		frc::SendableChooser<std::string> m_chooserPartners;

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

