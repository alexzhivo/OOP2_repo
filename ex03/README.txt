oop2_ex03
=====================================================================
		ex03
=====================================================================

	Author: Alex Zhivotovsky.
	ID: Alex - 319257903.

=====================================================================
		Description
===================================================================== 	 

		In this exercise, a simple game of docks was built 
		using SMFL library.

		The rules of the game are very simple: 
		the player is presented with a board on which colorful 
		sticks are scattered and he must pick them up after that 
		You can lift a dock only if there are no other docks 
		above it. If the player tries to pick up a token that 
		should not be picked up, the action will not be done.
		The game ends when the board is empty or when 
		the time is up. Each dock earns the player 
		a different number of points.

=====================================================================
		Included files
=====================================================================

the files added inside include directory:

	- Game.h
	- MenuWindow.h
	- GameWindow.h
	- EndingWindow.h
	- Stick.h

the files added inside src directory:

	- Game.cpp
	- MenuWindow.cpp
	- GameWindow.cpp
	- EndingWindow.cpp
	- Stick.cpp
	- main.cpp

=====================================================================
                          Data Structures
=====================================================================

	A STL vector of shared_ptr is used to store all the sticks in
	the game. each stick object has a vector of stick pointers 
	that intersect with it.

=====================================================================
                     Algorithms worth mention
=====================================================================
	
	- Intersected Check Of Two Sticks : found in Stick.cpp
	- Finding EndPoint : found in Stick.cpp
	- Is Stick On Top : found in Stick.cpp
	- Sorting Sticks by Color : found in GameWindow.cpp
	- Finding Pickable Sticks : found in GameWindow.cpp

=====================================================================
                              Design
=====================================================================
	
	The game is structured so that there is the main class 
	which is "Game" and it controls and holds all 
	three screens in the game: 
			   MenuWindow , GameWindow , EndingWindow 
	each class controls its window.
	GameWindow controls all the game aspect as well as saving and
	loading the savefile.txt from the game directory.
	
	Stick class is the object used to simulate the stick ingame.

=====================================================================
                            Known bugs
=====================================================================

	- if savegame.txt file is messed up by user it will not work.

=====================================================================
                             Comments
=====================================================================

	Up to this point, I haven't had enough time to insert a proper
	throw & catch exception to check the integrity of the file.