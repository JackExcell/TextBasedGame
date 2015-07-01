#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <random>

#include "Player.h"
#include "Monster.h"

using namespace std;

//Forward function declarations
void clearScreen();
void waitForKeypress();
void loadLevel(int level);
void buildUI(string state[20]);
void printUI();
void initialiseMonsters();
void monstersRoam();
void singleMonsterRoam(Monster &monster);
void initiateCombat(Monster &monster);
void fight(Monster &monster, string name);
void play();
void moveUp();
void moveRight();
void moveLeft();
void moveDown();
bool quitGame();
void clearLog();

char input;
bool quit = false;
bool loopMenu = true;

//Initialise FileIO
ofstream outStream;
ifstream inStream;

//Array containing current game state
string currentGameState[20];

//Current user interface made up of the current game state and player stats
string UI[24];

//Game Data
Player player;
int currentLevel = 0;
string gameLog[3];

//Monsters, maximum of 10 per level
Monster monster0;
Monster monster1;
Monster monster2;
Monster monster3;
Monster monster4;
Monster monster5;
Monster monster6;
Monster monster7;
Monster monster8;
Monster monster9;

//RNG Data
default_random_engine rng;
uniform_int_distribution<int> randomDirection(1, 4);

int main()
{
	//Clear screen once to push text to bottom of the page, for consistency.
	clearScreen();

	cout << "Welcome to Dragon Castle, an ASCII adventure game by Jack Excell" << endl;
	cout << "Be sure to maximise the console window before you start to make\nsure you can see the whole interface.\n" << endl;
	while (true)
	{
		while (loopMenu)
		{
			cout << "Select an Option:" << endl;
			cout << "1 - New Game" << endl;
			cout << "2 - Load Game" << endl;
			cout << "3 - Quit" << endl;

			input = _getch();

			if (input != '1' && input != '2' && input != '3')
			{
				cout << "Invalid input, please try again.\n\n";
			}
			else
			{
				clearScreen();
				loopMenu = false;
			}
		}

		loopMenu = true;

		switch (input)
		{
		case '1':
			//New Game
			loadLevel(1);
			player.newGame();
			initialiseMonsters();
			buildUI(currentGameState);
			printUI();
			play();
			break;
		case '2':
			//Load Game
			cout << "User pressed 2";
			break;
		case '3':
			//Quit
			cout << "Goodbye!\n";
			quit = true;
			break;
		}

		if (quit)
		{
			return 0;
		}
	}
}

void clearScreen()
{
	cout << string(25, '\n');
}

void waitForKeypress()
{
	_getch();
}

void loadLevel(int level)
{
	string levelString = to_string(level);
	string file = "Level" + levelString + ".txt";
	currentLevel = level;

	//Open text file, check for errors.
	inStream.open(file);
	if (inStream.fail())
	{
		//Convert to C-String to comply with perror function parameters.
		const char * fileCString = file.c_str();
		perror(fileCString);
		cout << endl;
		return;
	}

	string line;
	for (int x = 0; x < 20; x++)
	{
		getline(inStream, line);
		currentGameState[x] = line;
	}

	inStream.close();

}

void buildUI(string state[20])
{
	string line;

	for (int x = 0; x < 24; x++)
	{
		line = "";

		if (x < 20)
		{
			line += state[x];
		}

		if (x == 1)
		{
			line += "  STATS";
		}

		if (x == 3)
		{
			int level = player.getLevel();
			string sLevel = to_string(level);
			line += " Lvl: " + sLevel;
		}

		if (x == 4)
		{
			int strLev = player.getStr();
			string sStrLev = to_string(strLev);
			line += " Str: " + sStrLev;
		}

		if (x == 5)
		{
			int defLev = player.getDef();
			string sDefLev = to_string(defLev);
			line += " Def: " + sDefLev;
		}

		if (x == 7)
		{
			line += " Health:";
		}

		if (x == 8)
		{
			int currHP = player.getCurrentHP();
			int maxHP = player.getMaxHP();
			string sCurrHP = to_string(currHP);
			string sMaxHP = to_string(maxHP);

			line += " " + sCurrHP + "/" + sMaxHP;
		}

		if (x == 9)
		{
			int currHP = player.getCurrentHP();
			int maxHP = player.getMaxHP();
			int percentage = (currHP / maxHP)*100;

			if (percentage <= 20)
			{
				line += " [#    ]";
			}
			else if (percentage <= 40)
			{
				line += " [##   ]";
			}
			else if (percentage <= 60)
			{
				line += " [###  ]";
			}
			else if (percentage <= 80)
			{
				line += " [#### ]";
			}
			else
			{
				line += " [#####]";
			}
		}

		if (x == 12)
		{
			line += " SYMBOLS";
		}

		if (x == 14)
		{
			line += " @ Player";
		}

		if (x == 15)
		{
			line += " T Treasure";
		}

		if (x == 16)
		{
			line += " H Ladder";
		}

		if (x == 17)
		{
			line += " S Snake";
		}

		if (x == 18)
		{
			line += " O Ogre";
		}

		if (x == 19)
		{
			line += " D Dragon";
		}

		if (x == 20)
		{
			line += "                                        K King";
		}

		if (x == 21)
		{
			line += gameLog[0];
		}

		if (x == 22)
		{
			line += gameLog[1];
		}

		if (x == 23)
		{
			line += gameLog[2];
		}

		UI[x] = line += "\n";
	}
}

void printUI()
{
	clearScreen();

	for (int x = 0; x < 24; x++)
	{
		cout << UI[x];
	}
}

void play()
{
	bool quit = false;

	while (!quit)
	{
		clearLog();

		input = _getch();

		if (input == 'w' || input == 'W')
		{
			moveUp();
			monstersRoam();
		}
		else if (input == 'a' || input == 'A')
		{
			moveLeft();
			monstersRoam();
		}
		else if (input == 's' || input == 'S')
		{
			moveDown();
			monstersRoam();
		}
		else if (input == 'd' || input == 'D')
		{
			moveRight();
			monstersRoam();
		}
		else if (input == 'q' || input == 'Q')
		{
			quit = quitGame();

			if (quit)
			{
				clearScreen();
				clearLog();
			}
			else
			{
				clearScreen();
			}
		}
		else
		{
			gameLog[0] = "Invalid input, try again.";
		}

		if (!quit)
		{
			buildUI(currentGameState);
			printUI();
		}
	}
}

void moveUp()
{
	int currentLine = 0;
	int currentColumn = 0;

	for (int x = 0; x < 20; x++)
	{
		size_t search = currentGameState[x].find("@");

		//If @ is found
		if (search != std::string::npos)
		{
			currentLine = x;
			currentColumn = search;
		}
	}

	char destination = currentGameState[currentLine-1].at(currentColumn);
	if (destination == '.')
	{
		currentGameState[currentLine - 1].replace(currentColumn, 1, "@");
		currentGameState[currentLine].replace(currentColumn, 1, ".");
	}
	else if (destination == '#')
	{
		gameLog[0] = "There's a wall in the way.";
	}
}

void moveRight()
{
	int currentLine = 0;
	int currentColumn = 0;

	for (int x = 0; x < 20; x++)
	{
		size_t search = currentGameState[x].find("@");

		//If @ is found
		if (search != std::string::npos)
		{
			currentLine = x;
			currentColumn = search;
		}
	}

	char destination = currentGameState[currentLine].at(currentColumn+1);
	if (destination == '.')
	{
		currentGameState[currentLine].replace(currentColumn+1, 1, "@");
		currentGameState[currentLine].replace(currentColumn, 1, ".");
	}
	else if (destination == '#')
	{
		gameLog[0] = "There's a wall in the way.";
	}
}

void moveLeft()
{
	int currentLine = 0;
	int currentColumn = 0;

	for (int x = 0; x < 20; x++)
	{
		size_t search = currentGameState[x].find("@");

		//If @ is found
		if (search != std::string::npos)
		{
			currentLine = x;
			currentColumn = search;
		}
	}

	char destination = currentGameState[currentLine].at(currentColumn-1);
	if (destination == '.')
	{
		currentGameState[currentLine].replace(currentColumn-1, 1, "@");
		currentGameState[currentLine].replace(currentColumn, 1, ".");
	}
	else if (destination == '#')
	{
		gameLog[0] = "There's a wall in the way.";
	}
}

void moveDown()
{
	int currentLine = 0;
	int currentColumn = 0;

	for (int x = 0; x < 20; x++)
	{
		size_t search = currentGameState[x].find("@");

		//If @ is found
		if (search != std::string::npos)
		{
			currentLine = x;
			currentColumn = search;
		}
	}

	char destination = currentGameState[currentLine + 1].at(currentColumn);
	if (destination == '.')
	{
		currentGameState[currentLine + 1].replace(currentColumn, 1, "@");
		currentGameState[currentLine].replace(currentColumn, 1, ".");
	}
	else if (destination == '#')
	{
		gameLog[0] = "There's a wall in the way.";
	}
}

//Returns a boolean specifying if the user wants to quit or not.
bool quitGame()
{
	clearScreen();
	cout << "Are you sure you want to quit? (Y/N) \n";
	
	input = _getch();

	if (input == 'y' || input == 'Y')
	{
		clearScreen();
		return true;
	}
	else
	{
		return false;
	}
}

void clearLog()
{
	for (int x = 0; x < 3; x++)
	{
		gameLog[x] = "";
	}
}

//Searches for monsters from the current game state and gives them attributes and an AI.
void initialiseMonsters()
{
	string file = "Level" + to_string(currentLevel) + "MonsterData.txt";
	inStream.open(file);
	if (inStream.fail())
	{
		//Convert to C-String to comply with perror function parameters.
		const char * fileCString = file.c_str();
		perror(fileCString);
		cout << endl;
		return;
	}

	//First line of the MonsterData file is the number of monsters on this level
	string sAmount;
	int amount;
	getline(inStream, sAmount);
	amount = stoi(sAmount, nullptr, 10);

	for (int x = 0; x < amount; x++)
	{
		//Read 3 lines of monster data from the file.
		string s_type;
		string s_xPos;
		string s_yPos;
		getline(inStream, s_type);
		getline(inStream, s_xPos);
		getline(inStream, s_yPos);

		//Process strings into suitable parameter types.
		int xPos;
		int yPos;
		xPos = stoi(s_xPos, nullptr, 10);
		yPos = stoi(s_yPos, nullptr, 10);
		char type = s_type[0];

		switch (x)
		{
		case 0:
			monster0.initialise(xPos, yPos, currentLevel, type);
			break;
		case 1:
			monster1.initialise(xPos, yPos, currentLevel, type);
			break;
		case 2:
			monster2.initialise(xPos, yPos, currentLevel, type);
			break;
		case 3:
			monster3.initialise(xPos, yPos, currentLevel, type);
			break;
		case 4:
			monster4.initialise(xPos, yPos, currentLevel, type);
			break;
		case 5:
			monster5.initialise(xPos, yPos, currentLevel, type);
			break;
		case 6:
			monster6.initialise(xPos, yPos, currentLevel, type);
			break;
		case 7:
			monster7.initialise(xPos, yPos, currentLevel, type);
			break;
		case 8:
			monster8.initialise(xPos, yPos, currentLevel, type);
			break;
		case 9:
			monster9.initialise(xPos, yPos, currentLevel, type);
			break;
		}
		
	}

	inStream.close();

}

void monstersRoam()
{
		singleMonsterRoam(monster0);
		singleMonsterRoam(monster1);
		singleMonsterRoam(monster2);
		singleMonsterRoam(monster3);
		singleMonsterRoam(monster4);
		singleMonsterRoam(monster5);
		singleMonsterRoam(monster6);
		singleMonsterRoam(monster7);
		singleMonsterRoam(monster8);
		singleMonsterRoam(monster9);
}

void singleMonsterRoam(Monster &monster)
{
	//Ensure that the monster is active in the current level.
	if (monster.isMonsterActive() == true)
	{
		bool successfulMovement = false;

		int direction = randomDirection(rng);

		//variable initialisation outside of switch/case statement to avoid multiple initialization errors.
		int currentX = monster.getXPosition();
		int currentY = monster.getYPosition();
		int newX;
		int newY;
		char type;
		char valueAtCoordinates;
		string line;
		string destinationLine;
		string s_Type;

		switch (direction)
		{
		case 1:
			//Monster moves UP

			//Verify that the monster is in fact at these coordinates.
			type = monster.getType();
			line = currentGameState[currentY];
			valueAtCoordinates = line[currentX];

			if ( valueAtCoordinates == type)
			{
				//Verification of location checks out, prepare destination data.
				newX = currentX;
				newY = currentY - 1 ;
				destinationLine = currentGameState[newY];
				if (destinationLine[newX] == '.')
				{
					//The destination is available, move this monster to the new destination and free up the current one.
					s_Type = type;
					currentGameState[newY].replace(newX, 1, s_Type);
					currentGameState[currentY].replace(currentX, 1, ".");

					//Set the new position in the Monster object to reflect changes to the game state.
					monster.setXPosition(newX);
					monster.setYPosition(newY);
				}
			}
			break;
		case 2:
			//Monster moves RIGHT
			//Verify that the monster is in fact at these coordinates.
			type = monster.getType();
			line = currentGameState[currentY];
			valueAtCoordinates = line[currentX];

			if (valueAtCoordinates == type)
			{
				//Verification of location checks out, prepare destination data.
				newX = currentX + 1;
				newY = currentY;
				destinationLine = currentGameState[newY];
				if (destinationLine[newX] == '.')
				{
					//The destination is available, move this monster to the new destination and free up the current one.
					s_Type = type;
					currentGameState[newY].replace(newX, 1, s_Type);
					currentGameState[currentY].replace(currentX, 1, ".");

					//Set the new position in the Monster object to reflect changes to the game state.
					monster.setXPosition(newX);
					monster.setYPosition(newY);
				}
			}
			break;
		case 3:
			//Monster moves DOWN
			//Verify that the monster is in fact at these coordinates.
			type = monster.getType();
			line = currentGameState[currentY];
			valueAtCoordinates = line[currentX];

			if (valueAtCoordinates == type)
			{
				//Verification of location checks out, prepare destination data.
				newX = currentX;
				newY = currentY + 1;
				destinationLine = currentGameState[newY];
				if (destinationLine[newX] == '.')
				{
					//The destination is available, move this monster to the new destination and free up the current one.
					s_Type = type;
					currentGameState[newY].replace(newX, 1, s_Type);
					currentGameState[currentY].replace(currentX, 1, ".");

					//Set the new position in the Monster object to reflect changes to the game state.
					monster.setXPosition(newX);
					monster.setYPosition(newY);
				}
			}
			break;
		case 4:
			//Monster moves LEFT
			//Verify that the monster is in fact at these coordinates.
			type = monster.getType();
			line = currentGameState[currentY];
			valueAtCoordinates = line[currentX];

			if (valueAtCoordinates == type)
			{
				//Verification of location checks out, prepare destination data.
				newX = currentX - 1;
				newY = currentY;
				destinationLine = currentGameState[newY];
				if (destinationLine[newX] == '.')
				{
					//The destination is available, move this monster to the new destination and free up the current one.
					s_Type = type;
					currentGameState[newY].replace(newX, 1, s_Type);
					currentGameState[currentY].replace(currentX, 1, ".");

					//Set the new position in the Monster object to reflect changes to the game state.
					monster.setXPosition(newX);
					monster.setYPosition(newY);
				}
			}
			break;
		}

		initiateCombat(monster);
	}
}

void initiateCombat(Monster &monster)
{
	//Check if the monster has landed in a square adjacent to the player
	int xPos = monster.getXPosition();
	int yPos = monster.getYPosition();
	string lineAbove = currentGameState[(yPos - 1)];
	string lineMiddle = currentGameState[yPos];
	string lineBelow = currentGameState[(yPos + 1)];
	if (lineAbove[(xPos - 1)] == '@' ||
		lineAbove[xPos] == '@' ||
		lineAbove[(xPos + 1)] == '@' ||
		lineMiddle[(xPos - 1)] == '@' ||
		lineMiddle[(xPos + 1)] == '@' ||
		lineBelow[(xPos - 1)] == '@' ||
		lineBelow[xPos] == '@' ||
		lineBelow[(xPos + 1)] == '@')
	{
		//Monster found next to player, start fight.
		char type = monster.getType();
		string monsterName;
		switch (type)
		{
		case 'S':
			gameLog[0] = "You have encountered a Snake!";
			gameLog[1] = "Prepare for battle! Press any key...";
			monsterName = "Snake";
			buildUI(currentGameState);
			printUI();
			waitForKeypress();
			clearLog();
			break;
		case 'O':
			gameLog[0] = "You have encountered an Ogre!";
			gameLog[1] = "Prepare for battle! Press any key...";
			monsterName = "Ogre";
			break;
		case 'D':
			gameLog[0] = "A fearsome Dragon blocks your path!";
			gameLog[1] = "Prepare for battle! Press any key...";
			monsterName = "Dragon";
			break;
		case 'K':
			gameLog[0] = "You stand before the Dragon King.";
			gameLog[1] = "Prepare for the final battle! Press any key...";
			monsterName = "Dragon King";
			break;
		}

		fight(monster, monsterName);
	}
}

void fight(Monster &monster, string name)
{
	clearScreen();
	bool battleComplete = false;
	bool validAction = false;
	cout << "You have engaged a Level " + to_string(currentLevel) + " " + name + "." << endl << endl;
	while (battleComplete == false)
	{
		cout << "You have " + to_string(player.getCurrentHP()) + "/" + to_string(player.getMaxHP()) + " HP" << endl;
		cout << "The " + name + " has " + to_string(monster.getHP()) + "." << endl;
		validAction = false;
		while (validAction == false)
		{
			cout << "\nSelect action:" << endl;
			cout << "1 - Attack" << endl;
			cout << "2 - Inventory" << endl;
			cout << "3 - Flee" << endl;

			input = _getch();

			if (input == '1')
			{
				cout << "Attack!" << endl;
				validAction = true;
			}
			else if (input == '2')
			{
				cout << "item!" << endl;
				validAction = true;
			}
			else if (input == '3')
			{
				cout << "You attempt to flee." << endl;
				validAction = true;
			}
			else
			{
				cout << "Invalid selection, try again." << endl;
			}
		}
	}

	waitForKeypress();
	battleComplete = true;
	clearScreen();
}