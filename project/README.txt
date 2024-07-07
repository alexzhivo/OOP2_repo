oop2_project
=====================================================================
		project	: brickbuster
=====================================================================

	Author:		Alex Zhivotovsky
	ID:			319257903
	Date:		07/07/2024

=====================================================================
		Description
===================================================================== 	 

	- BrickBuster is an fast-paced arcade game project inspired by
	  the classic game 'Breakout'. In this captivating game, players
	  control a platform to bounce a ball and break a vibrant array
	  of bricks. With each level, the challenge intensifies, 
	  featuring more complex brick arrangements and varying brick 
	  durability. Players will enjoy intuitive controls that allow 
	  them to seamlessly maneuver the platform to keep the ball 
	  in play and destroy bricks. The game offers dynamic levels 
	  with unique brick patterns and obstacles, as well as many 
	  power-ups like multi-ball, platform expansion, and more! 
	  that enhance gameplay. With stunning graphics and colorful 
	  bricks, accompanied by smooth animations and an energetic 
	  soundtrack, BrickBuster immerses players in a visually 
	  appealing and engaging game environment.

=====================================================================
		Included files
=====================================================================

the files added inside include directory:

	- GameManager.h
	- Window.h
	- GameWindow.h
	- StartWindow.h
	- MenuWindow.h
	- HelpWindow.h
	- SettingsWindow.h
	- LeaderboardWindow.h
	- FinishWindow.h
	- Ball.h
	- Brick.h
	- GameClock.h
	- CollisionHandler.h
	- ObjectCreator.h
	- Platform.h
	- PowerUp.h
	- SoundManager.h

the files added inside src directory:

	- main.cpp
	- GameManager.cpp
	- GameWindow.cpp
	- StartWindow.cpp
	- MenuWindow.cpp
	- HelpWindow.cpp
	- SettingsWindow.cpp
	- LeaderboardWindow.cpp
	- FinishWindow.cpp
	- Ball.cpp
	- Brick.cpp
	- GameClock.cpp
	- CollisionHandler.cpp
	- ObjectCreator.cpp
	- Platform.cpp
	- PowerUp.cpp
	- SoundManager.cpp

the files added inside resources directory:

	- fonts dir
	- levels dir
	- media dir (imgs and sound)
	- initilized leaderboard.txt

=====================================================================
                          Data Structures
=====================================================================

	- Vectors, Lists, Maps and UnorderedMaps

=====================================================================
                     Algorithms worth mention
=====================================================================
	
	- Mainly Collision Handling & PowerUps use

=====================================================================
                              Design
=====================================================================
	
	- all the windows inherit from the Window class and each window 
	  controls its own window with the elements inside it.
	  The timing of the windows and their activation as well as 
	  the communication between them is managed by the main 
	  GameManager class. Inside it are the SoundManager and 
	  ObjectCreator which are important classes whose address is 
	  in each of the windows and therefore they can be implemented 
	  in each window. In addition, the game elements Platform, 
	  Brick, Ball, PowerUp are game elements that are all found 
	  in the GameWindow and are only used there.

=====================================================================
                            Known bugs
=====================================================================

	- None

=====================================================================
                             Comments
=====================================================================

	Things I wanted to add and due to time were not added:

	- try & catch on error handling
	- Template Code for better code use
	- GameObject Base Class
	- Solution for Player name under 3 characters
	- reconsider other STL containers
	- better Collisions and Angles
	- ESCAPE use in more windows
