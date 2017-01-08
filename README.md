apbattle - A Networked battleship game 

This package implements the classic Battleship! game over a TCP Socket.  The game protocol is simple but I will not go into the details in this readme, shoot me a message if you're curious.  Boost ASIO was used for basic network connections and and streaming.  Cereal and RapidJSON are used to send data over the socket (Cereal was a bit of overkill for this use case in retrospect) SFML (Simple and Fast Multimedia Library) was used for graphics, visualization, and for the GUI manual play mode. Doxygen is used to auto-generate the documentation API for this project, final documentation forthcoming... I'm sure you've heard that one before ;) 

Build:
	Disclaimer: I have only checked this on Ubuntu 14.04
	You will need the following system packages to run this code:

SFML:
	$ sudo apt-get install libsfml-dev

Boost (I used version 1.54.0) Should come with Ubuntu 14.04

Cereal (header-only)
	I have a symbolic link to the headers located in the include directory at "cereal"
	The "3rd_party" directory is excluded in my .gitignore for ease of use

	$ mkdir <apbattle_dir>/3rd_party
	$ cd <apbattle_dir>/3rd_party
	$ git clone https://github.com/USCiLab/cereal.git 
	$ ln -s <apbattle_dir>/3rd_party/cereal/include/cereal <apbattle_dir>/include/cereal


To Build the executables:

	$ mkdir <apbattle_dir>/build
	$ cd <apbattle_dir>/build
	$ cmake ..
	$ make

Executables should be generated to <bin>


Running the program:

You should see three run_agent scripts in the bin directory.  Their usage is described below

run_random_agent
	
	An agent that plays the game at random

Arguments (ordering enforced):

	hostIP - ip address of the host e.g. "127.0.0.1"
	hostport - port of the hosted game e.g. "8080"
	playername - arbritrary player name for logging and window title e.g. "player 1"
	isHost - designates if this agent should host the game or be a clien e.g. "true"

run_manual_agent
	
	An agent that allows the user to click on the desired guess coodinate.  
	The program was not designed for manual play, so some of the 
	game rules are not strictly enforced, like guessing the same coordinate twice.
	
Arguments (ordering enforced):

	hostIP - ip address of the host e.g. "127.0.0.1"
	hostport - port of the hosted game e.g. "8080"
	playername - arbritrary player name for logging and window title e.g. "player 1"
	isHost - designates if this agent should host the game or be a clien e.g. "true"

run_counting_agent
	
	An agent that uses combinatorics to select coordinates

Arguments (ordering enforced):

	hostIP - ip address of the host e.g. "127.0.0.1"
	hostport - port of the hosted game e.g. "8080"
	playername - arbritrary player name for logging and window title e.g. "player 1"
	isHost - designates if this agent should host the game or be a clien e.g. "true"
	enableLogging - enables logging functions, leave disabled with "false"
	inflationFactor - tunable parameter to designate how greed to play  e.g. "1" 


