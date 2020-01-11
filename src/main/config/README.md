*************************************************************************************************************
# Team 302 FIRST Robot Configuration
*************************************************************************************************************

1. **DTD files** are in the main folder since they are shared
2. **XML files** are in sub-folders based on the robot.  These files get deployed at the same level as the DTD files on the robot.

The types of files are:
1. **Robot.dtd** defines the structure for defining a configurable robot.
2. **Robot.xml** defines the specific hardware and mechanisms on a particular robot.  Thus, the practice robot and the compentition
   robot could be almost exactly the same with maybe different CAN IDs or motor inversions or they could have different or 
   missing mechanisms.   This file indicates all of this information.
3. **control.dtd** defines the format (attributes/elements) for the XML files that define the PID control parameters
4. **XXX_Control.xml** defines the control parameters for mechanism (class) XXX
5. **mechdata.dtd** defines the format (attributes/elements) for the XML files that define the parematers for mechanisms such as 
   pre-defined set positions
6. **XXX_data.xml** defines the specific parameters for mechanisms
   
