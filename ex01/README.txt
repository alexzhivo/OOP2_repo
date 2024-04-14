oop2_ex01
=====================================================================
		ex01
=====================================================================

	Author: Alex Zhivotovsky.
	ID: Alex - 319257903.

=====================================================================
		Description
===================================================================== 	 

	In this exercise i implemented a programmable shape calculator.
 	the user will be able to produce basic shapes, enlarge and reduce them 
	and add and create additional shapes from the existing shapes by duplicating 
	a shape or stacking shapes one top of each other.

=====================================================================
		Included files
=====================================================================

the files added inside include directory:

	- AppManager.h
	- Shape.h
	- Square.h
	- Rectangle.h
	- Triangle.h
	- Stack.h
	- Duplicate.h

the files added inside src directory:

	- main.cpp
	- AppManager.cpp
	- Square.cpp
	- Rectangle.cpp
	- Triangle.cpp
	- Stack.cpp
	- Duplicate.cpp

=====================================================================
                          Data Structures
=====================================================================
	
	I used Vector as the main data structure to contain all the shapes.
	the complex shapes(stack,duplicate) have pointers to shapes.

=====================================================================
                     Algorithms worth mention
=====================================================================

=====================================================================
                              Design
=====================================================================
	
	AppManager - Responsible for all program operations and holds
	 the vector that stores all the shapes in it
	Shape - abstract class that all the shape are derived from.
	Triangle, Square, Rectangle, Stack, Duplicate are shape classes.

=====================================================================
                            Known bugs
=====================================================================

=====================================================================
                             Comments
=====================================================================