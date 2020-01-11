/*
 * AutonSelector.cpp
 *
 *  Created on: Jan 20, 2018
 *      Author: jonah
 */
//Includes
#include <string>
#include <vector>
#include <dirent.h>

#include <frc/SmartDashboard/SendableChooser.h>
#include <frc/SmartDashboard/SmartDashboard.h>

//Team302 includes
#include <auton/AutonSelector.h>
#include <auton/FMS.h>

//---------------------------------------------------------------------
// Method: 		<<constructor>>
// Description: This creates this object and reads the auto script (CSV)
//  			files and displays a list on the dashboard.
//---------------------------------------------------------------------
AutonSelector::AutonSelector() : m_leftXMLFiles(),
								 m_centerXMLFiles(),
								 m_rightXMLFiles(),
								 m_chooserOptions(),
								 m_chooserPosition(),
								 m_chooserLeft(),
								 m_chooserCenter(),
								 m_chooserRight(),
								 m_autonPositionModifier( "" ),
								 m_autonOption( "CrossAutonLine.xml")
//									 m_autonOption( "LeftCorner_PlaceLeftScale.xml")

{
	FindXMLFileNames();
	PutChoicesOnDashboard();
}

//---------------------------------------------------------------------
// Method: 		GetSelectedAutoFile
// Description: This returns the selected auton file to run.  If it
//  			returns "Do Nothing", it is indicating no auton should
//				be run.
// Returns:		std::string			auton file to run
//---------------------------------------------------------------------
std::string AutonSelector::GetSelectedAutoFile()
{
	// initialize output
	std::string autonFile;

	m_autonPositionModifier.clear();

	bool hasError = false;

	// Get FMS data
	FMS* fms = FMS::GetFMS();
	FMS::POS switchPos = (fms != nullptr ) ? fms->GetSwitchPos() : FMS::UNKNOWN;
	FMS::POS scalePos = (fms != nullptr ) ? fms->GetScalePos() : FMS::UNKNOWN;

	if ( switchPos == FMS::UNKNOWN )
	{
		hasError = true;
		printf( "==>> Didn't read FMS Switch Information (if not in competition, set on the Driver Station) \n " );
	}
	if ( scalePos == FMS::UNKNOWN )
	{
		hasError = true;
		printf( "==>> Didn't read FMS Scale Information (if not in competition, set on the Driver Station) \n " );
	}
	int fmsSwitch = ( switchPos == FMS::LEFT ) ? 0 : 1;
	int fmsScale = ( scalePos == FMS::LEFT ) ? 0 : 10;


	// Get Starting Location and strategy
	AutonSelector::AUTON_POSITION  position = GetRobotStartPosition();
	int posOpt = 100 * position;

	// Handle the strategy
	AutonSelector::AUTON_OPTION strategy = GetDesiredOption();

	int state = (fmsSwitch + fmsScale + posOpt);
	switch ( strategy )
	{
		  case AutonSelector::CROSS_LINE:
			  autonFile = GetCrossLineFile( state );
			  break;

		  case AutonSelector::SWITCH:
			  autonFile = GetSwitchFile( state );
			  break;

		  case AutonSelector::SCALE_PLACE_FAR:
			  autonFile = GetScalePlaceFarFile( state );
			  break;

		  case AutonSelector::SCALE_HALFWAY:
			  autonFile = GetScaleHalfwayFile( state );
			  break;

		  case AutonSelector::SCALE_BACKUP_PLACE_FAR:
			  autonFile = GetScaleBackUpPlaceFarFile( state );
			  break;

		  case AutonSelector::SCALE_BACKUP_HALFWAY:
			  autonFile = GetScaleBackUpHalfwayFile( state );
			  break;

		  case AutonSelector::END_SCALE_PLACE_FAR:
			  autonFile = GetEndScalePlaceFarFile( state );
			  break;

		  case AutonSelector::END_SCALE_HALFWAY:
			  autonFile = GetEndScaleHalfwayFile( state );
			  break;

		  case AutonSelector::SWITCH_SCALE:
			  autonFile = GetSwitchScaleFile( state );
			  break;

		  case AutonSelector::SMART:
			  hasError = true;  // not implemented
			 // hasError = ProcessSmartOptions( position, switchPos, scalePos );
			  break;

		  default:
			  hasError = true;
			  printf( "==>> AutonSelector::GetSelectedAutoFile ... invalid strategy specified \n" );
			  break;
	}

	if ( hasError )
	{
		autonFile = GetCrossLineFile( state );
	}
	autonFile = m_autonDir + autonFile;

	frc::SmartDashboard::PutString("Auton file var", autonFile);

	return autonFile;
}


//---------------------------------------------------------------------
// Method: 		GetCrossLineFile
// Description: This determines which Cross line file to run based on starting
//				position and FMS feedback
// Returns:		std::string		filename to run
//---------------------------------------------------------------------
std::string AutonSelector::GetCrossLineFile
(
	int state			// <I> - FIELD_STATE enum value from the AutonSelector.h
)
{
	std::string file;

	// TODO:  need new auton files so we don't cream the cubes from the center position
	switch ( state )
	{
		case LEFTSWITCH_LEFTSCALE_LEFT:
		case RIGHTSWITCH_LEFTSCALE_LEFT:
		case LEFTSWITCH_RIGHTSCALE_LEFT:
		case RIGHTSWITCH_RIGHTSCALE_LEFT:
			file = "CrossAutonLine.xml";
			break;

		case LEFTSWITCH_LEFTSCALE_CENTER:
		case RIGHTSWITCH_LEFTSCALE_CENTER:
		case LEFTSWITCH_RIGHTSCALE_CENTER:
		case RIGHTSWITCH_RIGHTSCALE_CENTER:
			file = "CrossAutonLine.xml";
			break;

		case LEFTSWITCH_LEFTSCALE_RIGHT:
		case RIGHTSWITCH_LEFTSCALE_RIGHT:
		case LEFTSWITCH_RIGHTSCALE_RIGHT:
		case RIGHTSWITCH_RIGHTSCALE_RIGHT:
			file = "CrossAutonLine.xml";
			break;

		default:
			printf( "==>> AutonSelector::GetCrossLineFile ... invalid state %d \n", state );
			file = "CrossAutonLine.xml";
			break;

	}

	return file;
}

//---------------------------------------------------------------------
// Method: 		GetSwitchFile
// Description: This determines which Switch file to run based on starting
//				position and FMS feedback
// Returns:		std::string		filename to run
//---------------------------------------------------------------------
std::string AutonSelector::GetSwitchFile
(
	int state			// <I> - FIELD_STATE enum value from the AutonSelector.h
)
{
	std::string file;
	switch ( state )
	{
		case LEFTSWITCH_LEFTSCALE_LEFT:
			file = "LeftCorner_PlaceLeftSwitch.xml";
			// TODO: Add boolean to show if Evan is dumb or not
			break;

		case RIGHTSWITCH_LEFTSCALE_LEFT:
			file = "LeftCorner_PlaceRightSwitch.xml";
			// TODO: Add boolean to show if Evan is dumb or not
			break;

		case LEFTSWITCH_RIGHTSCALE_LEFT:
			file = "LeftCorner_PlaceLeftSwitch.xml";
			// TODO: Add boolean to show if Evan is dumb or not
			break;

		case RIGHTSWITCH_RIGHTSCALE_LEFT:
			file = "LeftCorner_PlaceRightSwitch.xml";
			// TODO: Add boolean to show if Evan is dumb or not
			break;

		case LEFTSWITCH_LEFTSCALE_CENTER:
			file = "Center_PlaceLeftSwitch.xml";
			break;

		case RIGHTSWITCH_LEFTSCALE_CENTER:
			file = "Center_PlaceRightSwitch.xml";
			break;

		case LEFTSWITCH_RIGHTSCALE_CENTER:
			file = "Center_PlaceLeftSwitch.xml";
			break;

		case RIGHTSWITCH_RIGHTSCALE_CENTER:
			file = "Center_PlaceRightSwitch.xml";
			break;

		case LEFTSWITCH_LEFTSCALE_RIGHT:
			file = "RightCorner_PlaceLeftSwitch.xml";
			// TODO: Add boolean to show if Evan is dumb or not
			break;

		case RIGHTSWITCH_LEFTSCALE_RIGHT:
			file = "RightCorner_PlaceRightSwitch.xml";
			// TODO: Add boolean to show if Evan is dumb or not
			break;

		case LEFTSWITCH_RIGHTSCALE_RIGHT:
			file = "RightCorner_PlaceLeftSwitch.xml";
			// TODO: Add boolean to show if Evan is dumb or not
			break;

		case RIGHTSWITCH_RIGHTSCALE_RIGHT:
			file = "RightCorner_PlaceRightSwitch.xml";
			// TODO: Add boolean to show if Evan is dumb or not
			break;

		default:
			printf( "==>> AutonSelector::GetCrossLineFile ... invalid state %d \n", state );
			file = "CrossAutonLine.xml";
			break;
	}

	return file;
}

//---------------------------------------------------------------------
// Method: 		GetScaleFile
// Description: This determines which Scale file to run based on starting
//				position and FMS feedback
// Returns:		std::string		filename to run
//---------------------------------------------------------------------
std::string AutonSelector::GetScalePlaceFarFile
(
	int state			// <I> - FIELD_STATE enum value from the AutonSelector.h
)
{
	std::string file;
	switch ( state )
	{
		case LEFTSWITCH_LEFTSCALE_LEFT:
			file = "LeftCorner_PlaceLeftScaleCorner.xml";
			break;

		case RIGHTSWITCH_LEFTSCALE_LEFT:
			file = "LeftCorner_PlaceLeftScaleCorner.xml";
			break;

		case LEFTSWITCH_RIGHTSCALE_LEFT:
			file = "LeftCorner_PlaceRightScaleCorner.xml";
			break;

		case RIGHTSWITCH_RIGHTSCALE_LEFT:
			file = "LeftCorner_PlaceRightScaleCorner.xml";
			break;

		case LEFTSWITCH_LEFTSCALE_CENTER:
			file = "Center_PlaceLeftScaleCorner.xml";
			// TODO: Add boolean to show if Evan is dumb or not
			break;

		case RIGHTSWITCH_LEFTSCALE_CENTER:
			file = "Center_PlaceLeftScaleCorner.xml";
			// TODO: Add boolean to show if Evan is dumb or not
			break;

		case LEFTSWITCH_RIGHTSCALE_CENTER:
			file = "Center_PlaceRighttScaleCorner.xml";
			// TODO: Add boolean to show if Evan is dumb or not
			break;

		case RIGHTSWITCH_RIGHTSCALE_CENTER:
			file = "Center_PlaceRightScaleCorner.xml";
			// TODO: Add boolean to show if Evan is dumb or not
			break;

		case LEFTSWITCH_LEFTSCALE_RIGHT:
			file = "RightCorner_PlaceLeftScaleCorner.xml";
			break;

		case RIGHTSWITCH_LEFTSCALE_RIGHT:
			file = "RightCorner_PlaceLeftScaleCorner.xml";
			break;

		case LEFTSWITCH_RIGHTSCALE_RIGHT:
			file = "RightCorner_PlaceRightScaleCorner.xml";
			break;

		case RIGHTSWITCH_RIGHTSCALE_RIGHT:
			file = "RightCorner_PlaceRightScaleCorner.xml";
			break;

		default:
			printf( "==>> AutonSelector::GetCrossLineFile ... invalid state %d \n", state );
			file = "CrossAutonLine.xml";
			break;
	}

	return file;
}

//---------------------------------------------------------------------
// Method: 		GetScaleFile
// Description: This determines which Scale file to run based on starting
//				position and FMS feedback
// Returns:		std::string		filename to run
//---------------------------------------------------------------------
std::string AutonSelector::GetScaleHalfwayFile
(
	int state			// <I> - FIELD_STATE enum value from the AutonSelector.h
)
{
	std::string file;
	switch ( state )
	{
		case LEFTSWITCH_LEFTSCALE_LEFT:
			file = "LeftCorner_PlaceLeftScaleCorner.xml";
			break;

		case RIGHTSWITCH_LEFTSCALE_LEFT:
			file = "LeftCorner_PlaceLeftScaleCorner.xml";
			break;

		case LEFTSWITCH_RIGHTSCALE_LEFT:
			file = "LeftCorner_Halfway.xml";
			break;

		case RIGHTSWITCH_RIGHTSCALE_LEFT:
			file = "LeftCorner_Halfway.xml";
			break;

		case LEFTSWITCH_LEFTSCALE_CENTER:
			file = "Center_PlaceLeftScaleCorner.xml";
			// TODO: Add boolean to show if Evan is dumb or not
			break;

		case RIGHTSWITCH_LEFTSCALE_CENTER:
			file = "Center_PlaceLeftScaleCorner.xml";
			// TODO: Add boolean to show if Evan is dumb or not
			break;

		case LEFTSWITCH_RIGHTSCALE_CENTER:
			file = "Center_PlaceRightScaleCorner.xml";
			// TODO: Add boolean to show if Evan is dumb or not
			break;

		case RIGHTSWITCH_RIGHTSCALE_CENTER:
			file = "Center_PlaceRightScaleCorner.xml";
			// TODO: Add boolean to show if Evan is dumb or not
			break;

		case LEFTSWITCH_LEFTSCALE_RIGHT:
			file = "RightCorner_Halfway.xml";
			break;

		case RIGHTSWITCH_LEFTSCALE_RIGHT:
			file = "RightCorner_Halfway.xml";
			break;

		case LEFTSWITCH_RIGHTSCALE_RIGHT:
			file = "RightCorner_PlaceRightScaleCorner.xml";
			break;

		case RIGHTSWITCH_RIGHTSCALE_RIGHT:
			file = "RightCorner_PlaceRightScaleCorner.xml";
			break;

		default:
			printf( "==>> AutonSelector::GetCrossLineFile ... invalid state %d \n", state );
			file = "CrossAutonLine.xml";
			break;
	}

	return file;
}

std::string AutonSelector::GetEndScalePlaceFarFile
(
	int state			// <I> - FIELD_STATE enum value from the AutonSelector.h
)
{
	std::string file;
		switch ( state )
		{
			case LEFTSWITCH_LEFTSCALE_LEFT:
				file = "LeftCorner_PlaceLeftScaleEnd.xml";
				break;

			case RIGHTSWITCH_LEFTSCALE_LEFT:
				file = "LeftCorner_PlaceLeftScaleEnd.xml";
				break;

			case LEFTSWITCH_RIGHTSCALE_LEFT:
				file = "LeftCorner_PlaceRightScaleCorner.xml";
				break;

			case RIGHTSWITCH_RIGHTSCALE_LEFT:
				file = "LeftCorner_PlaceRightScaleCorner.xml";
				break;

			case LEFTSWITCH_LEFTSCALE_CENTER:
				file = "Center_PlaceLeftScaleEnd.xml";
				// TODO: Add boolean to show if Evan is dumb or not
				break;

			case RIGHTSWITCH_LEFTSCALE_CENTER:
				file = "Center_PlaceLeftScaleEnd.xml";
				// TODO: Add boolean to show if Evan is dumb or not
				break;

			case LEFTSWITCH_RIGHTSCALE_CENTER:
				file = "Center_PlaceRightScaleEnd.xml";
				// TODO: Add boolean to show if Evan is dumb or not
				break;

			case RIGHTSWITCH_RIGHTSCALE_CENTER:
				file = "Center_PlaceRightScaleEnd.xml";
				// TODO: Add boolean to show if Evan is dumb or not
				break;

			case LEFTSWITCH_LEFTSCALE_RIGHT:
				file = "RightCorner_PlaceLeftScaleCorner.xml";
				break;

			case RIGHTSWITCH_LEFTSCALE_RIGHT:
				file = "RightCorner_PlaceLeftScaleCorner.xml";
				break;

			case LEFTSWITCH_RIGHTSCALE_RIGHT:
				file = "RightCorner_PlaceRightScaleEnd.xml";
				break;

			case RIGHTSWITCH_RIGHTSCALE_RIGHT:
				file = "RightCorner_PlaceRightScaleEnd.xml";
				break;

			default:
				printf( "==>> AutonSelector::GetCrossLineFile ... invalid state %d \n", state );
				file = "CrossAutonLine.xml";
				break;
		}

		return file;
}

std::string AutonSelector::GetEndScaleHalfwayFile
(
	int state			// <I> - FIELD_STATE enum value from the AutonSelector.h
)
{
	std::string file;
		switch ( state )
		{
			case LEFTSWITCH_LEFTSCALE_LEFT:
				file = "LeftCorner_PlaceLeftScaleEnd.xml";
				break;

			case RIGHTSWITCH_LEFTSCALE_LEFT:
				file = "LeftCorner_PlaceLeftScaleEnd.xml";
				break;

			case LEFTSWITCH_RIGHTSCALE_LEFT:
				file = "LeftCorner_Halfway.xml";
				break;

			case RIGHTSWITCH_RIGHTSCALE_LEFT:
				file = "LeftCorner_Halfway.xml";
				break;

			case LEFTSWITCH_LEFTSCALE_CENTER:
				file = "Center_PlaceLeftScaleEnd.xml";
				// TODO: Add boolean to show if Evan is dumb or not
				break;

			case RIGHTSWITCH_LEFTSCALE_CENTER:
				file = "Center_PlaceLeftScaleEnd.xml";
				// TODO: Add boolean to show if Evan is dumb or not
				break;

			case LEFTSWITCH_RIGHTSCALE_CENTER:
				file = "Center_PlaceRightScaleEnd.xml";
				// TODO: Add boolean to show if Evan is dumb or not
				break;

			case RIGHTSWITCH_RIGHTSCALE_CENTER:
				file = "Center_PlaceRightScaleEnd.xml";
				// TODO: Add boolean to show if Evan is dumb or not
				break;

			case LEFTSWITCH_LEFTSCALE_RIGHT:
				file = "RightCorner_Halfway.xml";//TODO: this is temporary
				break;

			case RIGHTSWITCH_LEFTSCALE_RIGHT:
				file = "RightCorner_Halfway.xml";//TODO: this is temporary
				break;

			case LEFTSWITCH_RIGHTSCALE_RIGHT:
				file = "RightCorner_PlaceRightScaleEnd.xml";//TODO: this is temporary
				break;

			case RIGHTSWITCH_RIGHTSCALE_RIGHT:
				file = "RightCorner_PlaceRightScaleEnd.xml";//TODO: this is temporary
				break;

			default:
				printf( "==>> AutonSelector::GetCrossLineFile ... invalid state %d \n", state );
				file = "CrossAutonLine.xml";
				break;
		}

		return file;
}


//---------------------------------------------------------------------
// Method: 		GetSwitchFile
// Description: This determines which Switch file to run based on starting
//				position and FMS feedback
// Returns:		std::string		filename to run
//---------------------------------------------------------------------
std::string AutonSelector::GetSwitchScaleFile
(
	int state			// <I> - FIELD_STATE enum value from the AutonSelector.h
)
{
	std::string file;
	switch ( state )
	{
		case LEFTSWITCH_LEFTSCALE_LEFT:
			file = "LeftCorner_PlaceLeftScaleLeftSwitch.xml";	// Place Left Scale, grab second block, place in left switch
			break;

		case RIGHTSWITCH_LEFTSCALE_LEFT:
			file = "LeftCorner_PlaceLeftScaleRightSwitch.xml";	// Place Left Scale, Grab second block, place in right switch
			break;

		case LEFTSWITCH_RIGHTSCALE_LEFT:
			file = "LeftCorner_PlaceRightScaleLeftSwitch.xml";	// Place Left Switch, Grab second block, Place in right Scale
			break;

		case RIGHTSWITCH_RIGHTSCALE_LEFT:
			file = "LeftCorner_PlaceRightScaleRightSwitch.xml";		// Place Right scale, grab second block, Place in right switch
			break;

		case LEFTSWITCH_LEFTSCALE_CENTER:
			file = "Center_PlaceLeftScaleLeftSwitch.xml";
			// Todo: Bool to say evan is dumb
			break;

		case RIGHTSWITCH_LEFTSCALE_CENTER:
			file = "Center_PlaceLeftScaleRightScale.xml";
			// Todo: Bool to say evan is dumb
			break;

		case LEFTSWITCH_RIGHTSCALE_CENTER:
			file = "Center_PlaceRightScaleLeftSwitch.xml";
			// Todo: Bool to say evan is dumb
			break;

		case RIGHTSWITCH_RIGHTSCALE_CENTER:
			file = "Center_PlaceRightScaleRightSwitch.xml";
			// Todo: Bool to say evan is dumb
			break;

		case LEFTSWITCH_LEFTSCALE_RIGHT:
			file = "RightCorner_PlaceLeftScaleLeftSwitch.xml";	// Place left scale, grab second block, place in right switch
			break;

		case RIGHTSWITCH_LEFTSCALE_RIGHT:
			file = "RightCorner_PlaceLeftScaleRightSwitch.xml";	// Place right switch, grab second block, place in left scale
			break;

		case LEFTSWITCH_RIGHTSCALE_RIGHT:
			file = "RightCorner_PlaceRightScaleLeftSwitch.xml";	// Place right scale, grab second block, place in left switch
			break;

		case RIGHTSWITCH_RIGHTSCALE_RIGHT:
			file = "RightCorner_PlaceRightScaleRightSwitch.xml";// Place right scale, grab second block, place in right switch
			break;

		default:
			printf( "==>> AutonSelector::GetCrossLineFile ... invalid state %d \n", state );
			file = "CrossAutonLine.xml";
			break;
	}

	return file;
}

//---------------------------------------------------------------------
// Method: 		GetScaleFile
// Description: This determines which Scale file to run based on starting
//				position and FMS feedback
// Returns:		std::string		filename to run
//---------------------------------------------------------------------
std::string AutonSelector::GetScaleBackUpPlaceFarFile
(
	int state			// <I> - FIELD_STATE enum value from the AutonSelector.h
)
{
	std::string file;
	switch ( state )
	{
		case LEFTSWITCH_LEFTSCALE_LEFT:
			file = "LeftCorner_PlaceLeftScaleBackUp.xml";
			break;

		case RIGHTSWITCH_LEFTSCALE_LEFT:
			file = "LeftCorner_PlaceLeftScaleBackUp.xml";
			break;

		case LEFTSWITCH_RIGHTSCALE_LEFT:
			file = "LeftCorner_PlaceRightScaleCorner.xml";
			break;

		case RIGHTSWITCH_RIGHTSCALE_LEFT:
			file = "LeftCorner_PlaceRightScaleCorner.xml";
			break;

		case LEFTSWITCH_LEFTSCALE_CENTER:
			file = "Center_PlaceLeftScaleBackUp.xml";
			// TODO: Add boolean to show if Evan is dumb or not
			break;

		case RIGHTSWITCH_LEFTSCALE_CENTER:
			file = "Center_PlaceLeftScaleBackUp.xml";
			// TODO: Add boolean to show if Evan is dumb or not
			break;

		case LEFTSWITCH_RIGHTSCALE_CENTER:
			file = "Center_PlaceRightScaleBackUp.xml";
			// TODO: Add boolean to show if Evan is dumb or not
			break;

		case RIGHTSWITCH_RIGHTSCALE_CENTER:
			file = "Center_PlaceRightScaleBackUp.xml";
			// TODO: Add boolean to show if Evan is dumb or not
			break;

		case LEFTSWITCH_LEFTSCALE_RIGHT:
			file = "RightCorner_PlaceLeftScaleCorner.xml";
			break;

		case RIGHTSWITCH_LEFTSCALE_RIGHT:
			file = "RightCorner_PlaceLeftScaleCorner.xml";
			break;

		case LEFTSWITCH_RIGHTSCALE_RIGHT:
			file = "RightCorner_PlaceRightScaleBackUp.xml";
			break;

		case RIGHTSWITCH_RIGHTSCALE_RIGHT:
			file = "RightCorner_PlaceRightScaleBackUp.xml";
			break;

		default:
			printf( "==>> AutonSelector::GetCrossLineFile ... invalid state %d \n", state );
			file = "CrossAutonLine.xml";
			break;
	}

	return file;
}

std::string AutonSelector::GetScaleBackUpHalfwayFile
(
	int state			// <I> - FIELD_STATE enum value from the AutonSelector.h
)
{
	std::string file;
	switch ( state )
	{
		case LEFTSWITCH_LEFTSCALE_LEFT:
			file = "LeftCorner_PlaceLeftScaleBackUp.xml";
			break;

		case RIGHTSWITCH_LEFTSCALE_LEFT:
			file = "LeftCorner_PlaceLeftScaleBackUp.xml";
			break;

		case LEFTSWITCH_RIGHTSCALE_LEFT:
			file = "LeftCorner_Halfway.xml";
			break;

		case RIGHTSWITCH_RIGHTSCALE_LEFT:
			file = "LeftCorner_Halfway.xml";
			break;

		case LEFTSWITCH_LEFTSCALE_CENTER:
			file = "Center_PlaceLeftScaleBackUp.xml";
			// TODO: Add boolean to show if Evan is dumb or not
			break;

		case RIGHTSWITCH_LEFTSCALE_CENTER:
			file = "Center_PlaceLeftScaleBackUp.xml";
			// TODO: Add boolean to show if Evan is dumb or not
			break;

		case LEFTSWITCH_RIGHTSCALE_CENTER:
			file = "Center_PlaceRightScaleBackUpp.xml";
			// TODO: Add boolean to show if Evan is dumb or not
			break;

		case RIGHTSWITCH_RIGHTSCALE_CENTER:
			file = "Center_PlaceRightScaleBackUp.xml";
			// TODO: Add boolean to show if Evan is dumb or not
			break;

		case LEFTSWITCH_LEFTSCALE_RIGHT:
			file = "RightCorner_Halfway.xml";
			break;

		case RIGHTSWITCH_LEFTSCALE_RIGHT:
			file = "RightCorner_Halfway.xml";
			break;

		case LEFTSWITCH_RIGHTSCALE_RIGHT:
			file = "RightCorner_PlaceRightScaleBackUp.xml";
			break;

		case RIGHTSWITCH_RIGHTSCALE_RIGHT:
			file = "RightCorner_PlaceRightScaleBackUp.xml";
			break;

		default:
			printf( "==>> AutonSelector::GetCrossLineFile ... invalid state %d \n", state );
			file = "CrossAutonLine.xml";
			break;
	}

	return file;
}


bool AutonSelector::ProcessSmartOptions
(
	AUTON_POSITION		position,				    // <I> - robot starting position
	FMS::POS			switchPos,					// <I> - FMS setting for our switch
	FMS::POS			scalePos					// <I> - FMS setting for the scale
)
{
	bool hasError = false;
	switch ( position )
	{
		case AutonSelector::LEFT_CORNER:
			break;

		case AutonSelector::CENTER:
			break;

		case AutonSelector::RIGHT_CORNER:
			break;
		default:
			break;
	}

	return hasError;
}


//---------------------------------------------------------------------
// Method: 		GetRobotStartPosition
// Description: Read the starting position from the smart dashboard
// Returns:		AutonSelector::AUTON_POSITION		starting position
//---------------------------------------------------------------------
AutonSelector::AUTON_POSITION AutonSelector::GetRobotStartPosition()
{
	AutonSelector::AUTON_POSITION position = AUTON_POSITION::LEFT_CORNER;

	auto selection = m_chooserPosition.GetSelected();
	if ( selection.compare( LEFT_CORNER_STR ) == 0 )
	{
		position = AutonSelector::LEFT_CORNER;
	}
	else if ( selection.compare( RIGHT_CORNER_STR ) == 0  )
	{
		position = AutonSelector::RIGHT_CORNER;
	}
	else
	{
		position = AutonSelector::CENTER;
	}
	return position;
}

//---------------------------------------------------------------------
// Method: 		GetDesiredOption
// Description: Read the desired behavior from the smart dashboard
// Returns:		AutonSelector::AUTON_OPTION		desired behavior
//---------------------------------------------------------------------
AutonSelector::AUTON_OPTION AutonSelector::GetDesiredOption()
{
	AutonSelector::AUTON_OPTION option = AUTON_OPTION::CROSS_LINE;

	std::string selection = m_chooserOptions.GetSelected();
	frc::SmartDashboard::PutString("selected auton: ", selection);
	if ( selection.compare( CROSS_AUTON_LINE_STR ) == 0 )
	{
		option = AutonSelector::CROSS_LINE;
	}
	else if ( selection.compare( PLACE_IN_SWITCH_STR ) == 0 )
	{
		option = AutonSelector::SWITCH;
	}
	else if ( selection.compare( PLACE_ON_CORNER_SCALE_FAR_STR ) == 0 )
	{
		option = AutonSelector::SCALE_PLACE_FAR;
	}
	else if (selection.compare( PLACE_ON_CORNER_SCALE_HALFWAY_STR ) == 0)
	{
		option = AutonSelector::SCALE_HALFWAY;
	}
	else if (selection.compare( PLACE_ON_CORNER_SCALE_BACKUP_FAR_STR ) == 0)
	{
		option = AutonSelector::SCALE_BACKUP_PLACE_FAR;
	}
	else if (selection.compare( PLACE_ON_CORNER_SCALE_BACKUP_HALFWAY_STR ) == 0)
	{
		option = AutonSelector::SCALE_BACKUP_HALFWAY;
	}
	else if (selection.compare( PLACE_ON_END_SCALE_FAR_STR ) == 0)
	{
		option = AutonSelector::END_SCALE_PLACE_FAR;
	}
	else if (selection.compare( PLACE_ON_END_SCALE_HALFWAY_STR ) == 0)
	{
		option = AutonSelector::END_SCALE_HALFWAY;
	}
	else if (selection.compare( PLACE_ON_SWITCH_SCALE_STR ) == 0)
	{
		option = AutonSelector::SWITCH_SCALE;
	}

	return option;
}



//---------------------------------------------------------------------
// Method: 		FindXMLFileNames
// Description: This builds up a list of XML files in the directory and
//				stores them in the attributes.
// Returns:		void
//---------------------------------------------------------------------
void AutonSelector::FindXMLFileNames()
{
	DIR* directory;
	struct dirent* files;

	directory = opendir("/home/lvuser/auton/");
	if (directory != nullptr)
	{
		bool moreFiles = true;
		while (moreFiles)
		{
			files = readdir(directory);
			if (files == nullptr)
			{
				moreFiles = false;
				break;
			}

			std::string fileName = std::string( files->d_name );

			// skip the current directory and parent directory filenames
			if ( fileName.compare( "." ) )
			{
				continue;
			}
			if ( fileName.compare( ".." ) )
			{
				continue;
			}

			auto foundPos = fileName.find( XML );
			if ( foundPos != std::string::npos )		// has xml extension
			{
				foundPos = fileName.find( LEFT_CORNER );
				if ( foundPos != std::string::npos )
				{
					m_leftXMLFiles.emplace_back( fileName );
				}
				else
				{
					foundPos = fileName.find( RIGHT_CORNER );
					if ( foundPos != std::string::npos )
					{
						m_rightXMLFiles.emplace_back( fileName );
					}
					else
					{
						foundPos = fileName.find( CENTER );
						if ( foundPos != std::string::npos )
						{
							m_centerXMLFiles.emplace_back( fileName );
						}
					}
				}
			}
			else
			{
				// skip dtd files
				foundPos = fileName.find( DTD );
				if ( foundPos != std::string::npos )
				{
					continue;
				}

				// else invalid file name
				printf( "==>> invalid auton file %s \n", fileName.c_str() );
			}
		}
	}
	else
	{
		printf( "==>> auton directory not found \n" );
	}
}

//---------------------------------------------------------------------
// Method: 		PutChoicesOnDashboard
// Description: This puts the list of files in the m_csvFiles attribute
//				up on the dashboard for selection.
// Returns:		void
//---------------------------------------------------------------------
void AutonSelector::PutChoicesOnDashboard()
{
	// Where is the robot located
	m_chooserPosition.SetDefaultOption( LEFT_CORNER_STR, LEFT_CORNER_STR );
	m_chooserPosition.AddOption( CENTER_STR, CENTER_STR );
	m_chooserPosition.AddOption( RIGHT_CORNER_STR, RIGHT_CORNER_STR );
	frc::SmartDashboard::PutData( "Auton: Robot Start Position", &m_chooserPosition );

	// What is our desired action
	// AUTOLINE Option
	m_chooserOptions.SetDefaultOption( CROSS_AUTON_LINE_STR, CROSS_AUTON_LINE_STR );
	// SWITCH Option
	m_chooserOptions.AddOption( PLACE_IN_SWITCH_STR, PLACE_IN_SWITCH_STR );
	// CORNER SCALE Option
	m_chooserOptions.AddOption( PLACE_ON_CORNER_SCALE_FAR_STR, PLACE_ON_CORNER_SCALE_FAR_STR );
	m_chooserOptions.AddOption( PLACE_ON_CORNER_SCALE_HALFWAY_STR, PLACE_ON_CORNER_SCALE_HALFWAY_STR );
	// SAFE SCALE Option
	m_chooserOptions.AddOption( PLACE_ON_END_SCALE_FAR_STR, PLACE_ON_END_SCALE_FAR_STR );
	m_chooserOptions.AddOption( PLACE_ON_END_SCALE_HALFWAY_STR, PLACE_ON_END_SCALE_HALFWAY_STR );
	// BACKUP SCALE Option
	m_chooserOptions.AddOption( PLACE_ON_CORNER_SCALE_BACKUP_FAR_STR, PLACE_ON_CORNER_SCALE_BACKUP_FAR_STR );
	m_chooserOptions.AddOption( PLACE_ON_CORNER_SCALE_BACKUP_HALFWAY_STR, PLACE_ON_CORNER_SCALE_BACKUP_HALFWAY_STR );
	// SWITCH SCALE Option
//	m_chooserOptions.AddOption( PLACE_ON_SWITCH_SCALE_STR, PLACE_ON_SWITCH_SCALE_STR);
	// SMART Option
	//	Todo: Make this work
	frc::SmartDashboard::PutData( "Auton: Robot Scoring Action", &m_chooserOptions);

	// Partners
	m_chooserPartners.SetDefaultOption( PARTNER_IN_MIDDLE_STR, PARTNER_IN_MIDDLE_STR );
	m_chooserPartners.AddOption( PARTNER_GET_THEIR_SIDE_SWITCH_STR, PARTNER_GET_THEIR_SIDE_SWITCH_STR );
	m_chooserPartners.AddOption( PARTNER_GET_THEIR_SIDE_SCALE_STR, PARTNER_GET_THEIR_SIDE_SCALE_STR );
	m_chooserPartners.AddOption( PARTNERS_ONLY_MOVE, PARTNERS_ONLY_MOVE );
	m_chooserPartners.AddOption( PARTNERS_DO_NOT_MOVE, PARTNERS_DO_NOT_MOVE );
	frc::SmartDashboard::PutData( "Auton: Partner ", &m_chooserPartners );
}
