
//====================================================================================================================================================
// Copyright 2020 Lake Orion Robotics FIRST Team 302
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

//Includes
#include <string>
#include <vector>
#include <dirent.h>

#include <frc/SmartDashboard/SendableChooser.h>
#include <frc/SmartDashboard/SmartDashboard.h>

//Team302 includes
#include <auton/AutonSelector.h>
#include <utils/Logger.h>


using namespace std;

//---------------------------------------------------------------------
// Method: 		<<constructor>>
// Description: This creates this object and reads the auto script (CSV)
//  			files and displays a list on the dashboard.
//---------------------------------------------------------------------
AutonSelector::AutonSelector() : m_xmlFiles(),
								 m_chooser()
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
	//Logger::GetLogger()->LogError(string("Auton Selector Get Selected Auton"), m_chooser.GetSelected());
	return m_chooser.GetSelected();
	//return "balltest.xml";
}

//---------------------------------------------------------------------
// Method: 		FindXMLFileNames
// Description: This builds up a list of CSV files in the directory and
//				stores them in the m_csvFiles attribute.
// Returns:		void
//---------------------------------------------------------------------
void AutonSelector::FindXMLFileNames()
{
	DIR* directory = opendir("/home/lvuser/auton/");
	if (directory != nullptr)
	{
		bool moreFiles = true;
		while (moreFiles)
		{
            struct dirent* files = readdir(directory);
			if (files != nullptr)
			{
				auto filename = string( files->d_name);
				if ( filename != "." && filename != ".." && filename != "auton.dtd" )
				{
					m_xmlFiles.emplace_back(string(files->d_name));
				}
			}
            else
            {
                moreFiles = false;
            }
		}
	}
	else
	{
		// error condition need to handle
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
	auto gotDefault = false;
	for (unsigned int inx = 0; inx < m_xmlFiles.size(); ++inx)
	{
		if(m_xmlFiles[inx] != "." && m_xmlFiles[inx] != "..")
		{
			if ( !gotDefault )
			{
				m_chooser.SetDefaultOption(  m_xmlFiles[inx], m_xmlFiles[inx] );
				gotDefault = true;
			}
			else
			{
				m_chooser.AddOption( m_xmlFiles[inx], m_xmlFiles[inx]);	
			}
		}
	}
	frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
}

