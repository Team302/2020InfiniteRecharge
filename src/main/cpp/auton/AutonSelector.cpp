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

	// Get Starting Location and strategy
	AutonSelector::AUTON_POSITION  position = GetRobotStartPosition();

	// Handle the strategy
	AutonSelector::AUTON_OPTION strategy = GetDesiredOption();
	switch ( strategy )
	{
		  case AutonSelector::CROSS_LINE:
			  autonFile = GetCrossLineFile();
			  break;

		  default:
			  hasError = true;
			  printf( "==>> AutonSelector::GetSelectedAutoFile ... invalid strategy specified \n" );
			  break;
	}

	if ( hasError )
	{
		autonFile = GetCrossLineFile();
	}
	autonFile = m_autonDir + autonFile;

	frc::SmartDashboard::PutString("Auton file var", autonFile);

	return autonFile;
}


//---------------------------------------------------------------------
// Method: 		GetCrossLineFile
// Description: This determines which Cross line file to run based on starting
//				position 
// Returns:		std::string		filename to run
//---------------------------------------------------------------------
std::string AutonSelector::GetCrossLineFile()
{
	std::string file = "CrossAutonLine.xml";
	return file;
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
	frc::SmartDashboard::PutData( "Auton: Robot Scoring Action", &m_chooserOptions);
}
