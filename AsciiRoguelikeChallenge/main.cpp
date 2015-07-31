#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <random>
#include <vector>

#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "Shop.h"

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
void addItemToInventory(int itemId);
void useItem(Item item);
void openInventory();
void emptyInventory();
void treasure();
void play();
void moveUp();
void moveRight();
void moveLeft();
void moveDown();
bool quitGame();
void clearLog();
void gameOverDisplay();
void saveGame();
void loadGameFromSave();
void initialiseMonstersFromSave();
int countNumberOfActiveMonsters();
void nextStage();
void setAllMonstersInactive();
void startShop();
void buyItem(Item item);

char input;
bool gameOver = false;
bool gameBeaten = false;
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
Shop shop;
vector<Item> inventory;
int currentLevel = 0; //Level as in stage of the game, not character level.
string gameLog[3];
int fleeing = 0;

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
uniform_int_distribution<int> damageVariation(3, 7);
uniform_int_distribution<int> criticalHitRoll(1, 100);
uniform_int_distribution<int> treasureRoll(0, 10);

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
			gameOver = false;
			gameBeaten = false;
			loadLevel(1);
			player.newGame();
			emptyInventory();
			addItemToInventory(0);
			addItemToInventory(0);
			initialiseMonsters();
			buildUI(currentGameState);
			printUI();
			play();
			break;
		case '2':
			//Load Game
			gameOver = false;
			gameBeaten = false;
			loadGameFromSave();
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
			int level = player.getLevel();
			string sLevel = to_string(level);
			line += " Lvl: " + sLevel;
		}

		if (x == 2)
		{
			int strLev = player.getStr();
			string sStrLev = to_string(strLev);
			line += " Str: " + sStrLev;
		}

		if (x == 3)
		{
			int defLev = player.getDef();
			string sDefLev = to_string(defLev);
			line += " Def: " + sDefLev;
		}

		if (x == 4)
		{
			int gold = player.getGold();
			line += " Gold: " + to_string(gold);
		}

		if (x == 5)
		{
			int items = inventory.size();
			line += " Items: " + to_string(items) + "/5";
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

		if (x == 10)
		{
			line += " EXP:";
		}

		if (x == 11)
		{
			line += " " + to_string(player.getCurrentExp()) + "/" + to_string(player.getTotalExpNeededToLevel());
		}

		if (x == 13)
		{
			line += " @ Player";
		}

		if (x == 14)
		{
			line += " T Treasure";
		}

		if (x == 15)
		{
			line += " H Ladder";
		}

		if (x == 16)
		{
			line += " S Snake";
		}

		if (x == 17)
		{
			line += " O Ogre";
		}

		if (x == 18)
		{
			line += " D Dragon";
		}

		if (x == 19)
		{
			line += " K King";
		}

		if (x == 20)
		{
			line += "                                        M Merchant";
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
			if (fleeing > 0)
			{
				fleeing--;
			}
		}
		else if (input == 'a' || input == 'A')
		{
			moveLeft();
			monstersRoam();
			if (fleeing > 0)
			{
				fleeing--;
			}
		}
		else if (input == 's' || input == 'S')
		{
			moveDown();
			monstersRoam();
			if (fleeing > 0)
			{
				fleeing--;
			}
		}
		else if (input == 'd' || input == 'D')
		{
			moveRight();
			monstersRoam();
			if (fleeing > 0)
			{
				fleeing--;
			}
		}
		else if (input == 'i' || input == 'I')
		{
			openInventory();
		}
		else if (input == ' ')
		{
			clearScreen();
			saveGame();
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

		if (gameOver)
		{
			clearScreen();
			gameOverDisplay();
			quit = true;
		}

		if (!quit)
		{
			if (fleeing > 0)
			{
				gameLog[2] = "You are fleeing! (" + to_string(fleeing) + " more steps)";
			}
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
	else if (destination == 'T')
	{
		currentGameState[currentLine - 1].replace(currentColumn, 1, "@");
		currentGameState[currentLine].replace(currentColumn, 1, ".");
		treasure();
	}
	else if (destination == 'H')
	{
		nextStage();
	}
	else if (destination == 'M')
	{
		startShop();
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
	else if (destination == 'T')
	{
		currentGameState[currentLine].replace(currentColumn + 1, 1, "@");
		currentGameState[currentLine].replace(currentColumn, 1, ".");
		treasure();
	}
	else if (destination == 'H')
	{
		nextStage();
	}
	else if (destination == 'M')
	{
		startShop();
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
	else if (destination == 'T')
	{
		currentGameState[currentLine].replace(currentColumn - 1, 1, "@");
		currentGameState[currentLine].replace(currentColumn, 1, ".");
		treasure();
	}
	else if (destination == 'H')
	{
		nextStage();
	}
	else if (destination == 'M')
	{
		startShop();
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
	else if (destination == 'T')
	{
		currentGameState[currentLine + 1].replace(currentColumn, 1, "@");
		currentGameState[currentLine].replace(currentColumn, 1, ".");
		treasure();
	}
	else if (destination == 'H')
	{
		nextStage();
	}
	else if (destination == 'M')
	{
		startShop();
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
//Requires the relevant monster data file in the source folder.
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
		xPos = stoi(s_xPos);
		yPos = stoi(s_yPos);
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

		if (fleeing == 0)
		{
			initiateCombat(monster);
		}
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
			buildUI(currentGameState);
			printUI();
			waitForKeypress();
			clearLog();
			break;
		case 'D':
			gameLog[0] = "A fearsome Dragon blocks your path!";
			gameLog[1] = "Prepare for battle! Press any key...";
			monsterName = "Dragon";
			buildUI(currentGameState);
			printUI();
			waitForKeypress();
			clearLog();
			break;
		case 'K':
			gameLog[0] = "You stand before the Dragon King.";
			gameLog[1] = "Prepare for the final battle! Press any key...";
			monsterName = "Dragon King";
			buildUI(currentGameState);
			printUI();
			waitForKeypress();
			clearLog();
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
	bool alive = true;
	cout << "You have engaged a Level " + to_string(currentLevel) + " " + name + "." << endl << endl;
	while (battleComplete == false)
	{
		cout << "You have " + to_string(player.getCurrentHP()) + "/" + to_string(player.getMaxHP()) + " HP" << endl;
		cout << "The " + name + " has " + to_string(monster.getHP()) + " HP." << endl;
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
				int baseDamage = player.getStr();
				int bonusDamage = damageVariation(rng);
				int totalDamage = baseDamage + bonusDamage;
				int critRoll = criticalHitRoll(rng);
				clearScreen();
				cout << "You attack the " + name + "." << endl;
				if (critRoll > 90)
				{
					cout << "Critical hit!" << endl;
					totalDamage = totalDamage * 1.5;
				}
				totalDamage -= monster.getDefence();
				if (totalDamage < 1)
				{
					totalDamage = 1;
				}
				cout << "You inflict " + to_string(totalDamage) + " damage." << endl << endl;
				monster.takeDamage(totalDamage);
				alive = monster.checkIfDead();
				if (alive == false)
				{
					//Enemy defeated
					cout << "You defeated the " + name + "!" << endl;
					cout << "You earned " + to_string(monster.getExp()) + " Experience points. " << endl;
					cout << "You found " + to_string(monster.getGoldReward()) + " gold on the " + name + "s corpse." << endl;
					cout << "Press any key to continue." << endl;
					player.earnExp(monster.getExp());
					player.earnGold(monster.getGoldReward());
					player.levelUp();
					waitForKeypress();
					monster.dead();
					
					//Remove the enemies symbol from the game state
					int xPos = monster.getXPosition();
					int yPos = monster.getYPosition();
					string line = currentGameState[yPos];
					line[xPos] = '.';
					currentGameState[yPos] = line;

					battleComplete = true;
				}
				else
				{
					//Enemies turn to attack
					int baseDamage = monster.getStrength();
					int bonusDamage = damageVariation(rng);
					int totalDamage = baseDamage + bonusDamage;
					int critRoll = criticalHitRoll(rng);
					cout << "The " + name + " attacks you." << endl;
					if (critRoll > 90)
					{
						cout << "Ouch, you took Critical hit!" << endl;
						totalDamage = totalDamage * 1.5;
					}
					totalDamage -= player.getDef();
					if (totalDamage < 1)
					{
						totalDamage = 1;
					}
					cout << "You take " + to_string(totalDamage) + " damage." << endl << endl;
					player.takeDamage(totalDamage);
					if (player.isPlayerDead())
					{
						cout << "\nYou have been defeated..." << endl;
						waitForKeypress();
						gameOver = true;
						battleComplete = true;
					}
				}
				validAction = true;
			}
			else if (input == '2')
			{
				clearScreen();
				openInventory();
				clearScreen();
				validAction = true;
			}
			else if (input == '3')
			{
				int fleeDamage = monster.getStrength() + 10;
				cout << "\nYou fight off the "+ name +" long enough to make your escape,\nbut you took " + to_string(fleeDamage) + " damage in the process." <<endl;
				player.takeDamage(fleeDamage);
				if (player.isPlayerDead())
				{
					cout << "\nYou have been defeated..." << endl;
					waitForKeypress();
					gameOver = true;
				}
				else
				{
					fleeing = 3;
				}
				cout << "Press any key." << endl;
				waitForKeypress();
				battleComplete = true;
				validAction = true;
			}
			else
			{
				cout << "Invalid selection, try again." << endl;
			}
		}
	}

	battleComplete = true;
	clearScreen();
}

void addItemToInventory(int itemId)
{
	if (inventory.size() < 5)
	{
		Item item(itemId);
		inventory.push_back(item);
	}
}

void openInventory()
{
	if (inventory.size() == 0)
	{
		clearScreen();
		cout << "There are no items in your Inventory..." << endl;
		waitForKeypress;
	}
	else
	{
		bool closeInventory = false;
		while (closeInventory == false)
		{
			clearScreen();
			cout << "-----------------" << endl;
			cout << "|   INVENTORY   |" << endl;
			cout << "-----------------" << endl << endl;
			for (int x = 0; x < inventory.size(); x++)
			{
				int itemNumber = x + 1;
				cout << to_string(itemNumber) + " - " + inventory[x].getName() << endl;
			}

			cout << "\nType the corresponding number to inspect the item or press I again to exit your inventory." << endl;

			input = _getch();

			if (input == 'I' || input == 'i')
			{
				//Close inventory
				closeInventory = true;
			}

			if (input == '1' && inventory.size()>0)
			{
				clearScreen();
				cout << inventory[0].getName() << endl;
				cout << "\n" + inventory[0].getDescription() << endl;
				cout << "\nUse this item? (Y/N)" << endl;

				input = _getch();

				if (input == 'y' || input == 'Y')
				{
					useItem(inventory[0]);
					inventory.erase(inventory.begin());
					closeInventory = true;
				}
			}

			if (input == '2' && inventory.size()>1)
			{
				clearScreen();
				cout << inventory[1].getName() << endl;
				cout << "\n" + inventory[1].getDescription() << endl;
				cout << "\nUse this item? (Y/N)" << endl;

				input = _getch();

				if (input == 'y' || input == 'Y')
				{
					useItem(inventory[1]);
					inventory.erase(inventory.begin()+1);
					closeInventory = true;
				}
			}

			if (input == '3' && inventory.size()>2)
			{
				clearScreen();
				cout << inventory[2].getName() << endl;
				cout << "\n" + inventory[2].getDescription() << endl;
				cout << "\nUse this item? (Y/N)" << endl;

				input = _getch();

				if (input == 'y' || input == 'Y')
				{
					useItem(inventory[2]);
					inventory.erase(inventory.begin() + 2);
					closeInventory = true;
				}
			}

			if (input == '4' && inventory.size()>3)
			{
				clearScreen();
				cout << inventory[3].getName() << endl;
				cout << "\n" + inventory[3].getDescription() << endl;
				cout << "\nUse this item? (Y/N)" << endl;

				input = _getch();

				if (input == 'y' || input == 'Y')
				{
					useItem(inventory[3]);
					inventory.erase(inventory.begin() + 3);
					closeInventory = true;
				}
			}

			if (input == '5' && inventory.size()>4)
			{
				clearScreen();
				cout << inventory[4].getName() << endl;
				cout << "\n" + inventory[4].getDescription() << endl;
				cout << "\nUse this item? (Y/N)" << endl;

				input = _getch();

				if (input == 'y' || input == 'Y')
				{
					useItem(inventory[4]);
					inventory.erase(inventory.begin() + 4);
					closeInventory = true;
				}
			}
		}
	}
}

void useItem(Item item)
{
	int healAmount = item.getHealAmount();
	int healthLossAmount = item.getHealthLossAmount();
	int strengthUp = item.getStrUp();
	int strengthDown = item.getStrDown();
	int defenceUp = item.getDefUp();
	int defenceDown = item.getDefDown();
	int maxHpUp = item.getMaxHpUp();
	int maxHpDown = item.getMaxHpDown();

	player.heal(healAmount);
	player.loseHealth(healthLossAmount);
	player.increaseStrength(strengthUp);
	player.decreaseStrength(strengthDown);
	player.increaseDefence(defenceUp);
	player.decreaseDefence(defenceDown);
	player.maxHpUp(maxHpUp);
	player.maxHpDown(maxHpDown);
}

void emptyInventory()
{
	inventory.clear();
}

void treasure()
{
	//This value needs to be updated as new items are added to ensure ill items are randomly obtainable.
	int roll = treasureRoll(rng);
	Item loot(roll);

	//Interface
	clearScreen();
	cout << "--------------------" << endl;
	cout << "|  Treasure Chest  |" << endl;
	cout << "--------------------" << endl;
	cout << "\nYou open the treasure chest..." << endl;
	cout << "\nAnd find a " + loot.getName() + "!" << endl;
	cout << "\nEffect: " + loot.getDescription() << endl;

	if (inventory.size() < 5)
	{
		cout << "\nYou put the " + loot.getName() + " into your inventory." << endl;
		addItemToInventory(roll);
	}
	else
	{
		cout << "\nYour inventory is full, use this item now? (Y/N)" << endl;
		bool decided = false;

		while (decided == false)
		{
			input = _getch();

			if (input == 'y' || input == 'Y')
			{
				cout << "You used the " + loot.getName() << endl;
				useItem(loot);
				decided = true;
			}
			else if (input == 'n' || input == 'N')
			{
				cout << "You discarded the " + loot.getName() + "..." << endl;
				decided = true;
			}
		}

	}

	cout << "\n\nPress any key to continue." << endl;
	waitForKeypress();
	buildUI(currentGameState);
	printUI();
}

void gameOverDisplay()
{
	if (gameBeaten)
	{
		clearScreen();
		cout << "                                CONGRATULATIONS!" << endl;
		cout << "                               You beat the game!\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
	}
	else
	{
		cout << "                                   GAME OVER\n\n\n\n\n\n\n\n\n\n\n\nPress any key..." << endl;
		waitForKeypress();
		clearScreen();
	}
}

void saveGame()
{
	cout << "Save game? This will overwrite any previous saves. (Y/N)" << endl;

	input = _getch();

	if (input == 'y' || input == 'Y')
	{
		outStream.open("save.txt");

		if (outStream.fail())
		{
			cout << "Error Saving" << endl;
		}

		for (int i = 0; i < 20; i++)
		{
			outStream << currentGameState[i] << endl;
		}

		outStream << currentLevel << endl;
		outStream << player.getLevel() << endl;
		outStream << player.getCurrentHP() << endl;
		outStream << player.getMaxHP() << endl;
		outStream << player.getStr() << endl;
		outStream << player.getDef() << endl;
		outStream << player.getCurrentExp() << endl;
		outStream << player.getTotalExpNeededToLevel() << endl;
		outStream << player.getGold() << endl;
		outStream << inventory.size() << endl;

		for (int i = 0; i < inventory.size(); i++)
		{
			outStream << inventory[i].getId() << endl;
		}

		outStream.close();

		//Monster data for initialisation script when loading new levels, in this case loading saved game state
		outStream.open("saveMonsterData.txt");
		int amountOfActiveMonsters = countNumberOfActiveMonsters();
		outStream << amountOfActiveMonsters << endl;

		if (monster0.isMonsterActive())
		{
			outStream << monster0.getType() << endl;
			outStream << monster0.getXPosition() << endl;
			outStream << monster0.getYPosition() << endl;
			outStream << monster0.getHP() << endl;
		}
		if (monster1.isMonsterActive())
		{
			outStream << monster1.getType() << endl;
			outStream << monster1.getXPosition() << endl;
			outStream << monster1.getYPosition() << endl;
			outStream << monster1.getHP() << endl;
		}
		if (monster2.isMonsterActive())
		{
			outStream << monster2.getType() << endl;
			outStream << monster2.getXPosition() << endl;
			outStream << monster2.getYPosition() << endl;
			outStream << monster2.getHP() << endl;
		}
		if (monster3.isMonsterActive())
		{
			outStream << monster3.getType() << endl;
			outStream << monster3.getXPosition() << endl;
			outStream << monster3.getYPosition() << endl;
			outStream << monster3.getHP() << endl;
		}
		if (monster4.isMonsterActive())
		{
			outStream << monster4.getType() << endl;
			outStream << monster4.getXPosition() << endl;
			outStream << monster4.getYPosition() << endl;
			outStream << monster4.getHP() << endl;
		}
		if (monster5.isMonsterActive())
		{
			outStream << monster5.getType() << endl;
			outStream << monster5.getXPosition() << endl;
			outStream << monster5.getYPosition() << endl;
			outStream << monster5.getHP() << endl;
		}
		if (monster6.isMonsterActive())
		{
			outStream << monster6.getType() << endl;
			outStream << monster6.getXPosition() << endl;
			outStream << monster6.getYPosition() << endl;
			outStream << monster6.getHP() << endl;
		}
		if (monster7.isMonsterActive())
		{
			outStream << monster7.getType() << endl;
			outStream << monster7.getXPosition() << endl;
			outStream << monster7.getYPosition() << endl;
			outStream << monster7.getHP() << endl;
		}
		if (monster8.isMonsterActive())
		{
			outStream << monster8.getType() << endl;
			outStream << monster8.getXPosition() << endl;
			outStream << monster8.getYPosition() << endl;
			outStream << monster8.getHP() << endl;
		}
		if (monster9.isMonsterActive())
		{
			outStream << monster9.getType() << endl;
			outStream << monster9.getXPosition() << endl;
			outStream << monster9.getYPosition() << endl;
			outStream << monster9.getHP() << endl;
		}

		outStream.close();

	}

	clearScreen();
}

void loadGameFromSave()
{
	//Open text file, check for errors.
	string save = "save.txt";
	inStream.open(save);
	if (inStream.fail())
	{
		//Convert to C-String to comply with perror function parameters.
		const char * fileCString = save.c_str();
		perror(fileCString);
		cout << endl;
		return;
	}

	//Load game state
	string line;
	for (int x = 0; x < 20; x++)
	{
		getline(inStream, line);
		currentGameState[x] = line;
	}

	//Set game level
	string sGameLevel;
	getline(inStream, sGameLevel);
	int gameLevel = stoi(sGameLevel);
	currentLevel = gameLevel;

	//Set player stats
	string sPlayerLevel;
	string sHP;
	string sMaxHP;
	string sStr;
	string sDef;
	string sExp;
	string sExpNeeded;
	string sGold;
	string sNumberOfItems;

	getline(inStream, sPlayerLevel);
	getline(inStream, sHP);
	getline(inStream, sMaxHP);
	getline(inStream, sStr);
	getline(inStream, sDef);
	getline(inStream, sExp);
	getline(inStream, sExpNeeded);
	getline(inStream, sGold);
	getline(inStream, sNumberOfItems);

	int playerLevel = stoi(sPlayerLevel);
	int HP = stoi(sHP);
	int MaxHP = stoi(sMaxHP);
	int Str = stoi(sStr);
	int Def = stoi(sDef);
	int Exp = stoi(sExp);
	int ExpNeeded = stoi(sExpNeeded);
	int Gold = stoi(sGold);
	int NumberOfItems = stoi(sNumberOfItems);
	
	
	player.setLevel(playerLevel);
	player.setHP(HP);
	player.setMaxHP(MaxHP);
	player.setStrength(Str);
	player.setDefence(Def);
	player.setCurrentExp(Exp);
	player.setExpNeededToLevel(ExpNeeded);
	player.setGold(Gold);

	//Set items
	emptyInventory();
	string sItemId;
	int itemId;
	for (int i = 0; i < NumberOfItems; i++)
	{
		getline(inStream, sItemId);
		itemId = stoi(sItemId);
		addItemToInventory(itemId);
	}

	inStream.close();

	initialiseMonstersFromSave();

	buildUI(currentGameState);
	printUI();
	play();
}

int countNumberOfActiveMonsters()
{
	int counter = 0;

	if (monster0.isMonsterActive())
	{
		counter++;
	}
	if (monster1.isMonsterActive())
	{
		counter++;
	}
	if (monster2.isMonsterActive())
	{
		counter++;
	}
	if (monster3.isMonsterActive())
	{
		counter++;
	}
	if (monster4.isMonsterActive())
	{
		counter++;
	}
	if (monster5.isMonsterActive())
	{
		counter++;
	}
	if (monster6.isMonsterActive())
	{
		counter++;
	}
	if (monster7.isMonsterActive())
	{
		counter++;
	}
	if (monster8.isMonsterActive())
	{
		counter++;
	}
	if (monster9.isMonsterActive())
	{
		counter++;
	}

	return counter;
}

void initialiseMonstersFromSave()
{
	string file = "saveMonsterData.txt";
	inStream.open(file);
	if (inStream.fail())
	{
		//Convert to C-String to comply with perror function parameters.
		const char * fileCString = file.c_str();
		perror(fileCString);
		cout << endl;
		return;
	}

	//First line of the MonsterData file is the number of monsters remaining when the player saved
	string sAmount;
	int amount;
	getline(inStream, sAmount);
	amount = stoi(sAmount);

	for (int x = 0; x < amount; x++)
	{
		//Read 4 lines of monster data from the file.
		string s_type;
		string s_xPos;
		string s_yPos;
		string s_enemyHP;
		getline(inStream, s_type);
		getline(inStream, s_xPos);
		getline(inStream, s_yPos);
		getline(inStream, s_enemyHP);

		//Process strings into suitable parameter types.
		int xPos;
		int yPos;
		xPos = stoi(s_xPos);
		yPos = stoi(s_yPos);
		char type = s_type[0];
		int hp = stoi(s_enemyHP);

		switch (x)
		{
		case 0:
			monster0.initialise(xPos, yPos, currentLevel, type);
			monster0.setHP(hp);
			break;
		case 1:
			monster1.initialise(xPos, yPos, currentLevel, type);
			monster1.setHP(hp);
			break;
		case 2:
			monster2.initialise(xPos, yPos, currentLevel, type);
			monster2.setHP(hp);
			break;
		case 3:
			monster3.initialise(xPos, yPos, currentLevel, type);
			monster3.setHP(hp);
			break;
		case 4:
			monster4.initialise(xPos, yPos, currentLevel, type);
			monster4.setHP(hp);
			break;
		case 5:
			monster5.initialise(xPos, yPos, currentLevel, type);
			monster5.setHP(hp);
			break;
		case 6:
			monster6.initialise(xPos, yPos, currentLevel, type);
			monster6.setHP(hp);
			break;
		case 7:
			monster7.initialise(xPos, yPos, currentLevel, type);
			monster7.setHP(hp);
			break;
		case 8:
			monster8.initialise(xPos, yPos, currentLevel, type);
			monster8.setHP(hp);
			break;
		case 9:
			monster9.initialise(xPos, yPos, currentLevel, type);
			monster9.setHP(hp);
			break;
		}

	}

	inStream.close();
}

void nextStage()
{
	if (currentLevel == 10)
	{
		//Game completed
		gameBeaten = true;
		gameOver = true;
		gameOverDisplay();
		waitForKeypress();
		clearScreen();

	}
	else
	{
		clearScreen();
		setAllMonstersInactive();
		currentLevel++;
		cout << "You ascend the ladder to the next floor of the castle." << endl;
		cout << "\nPress any key to begin exploring floor number " + to_string(currentLevel) + "." << endl;
		waitForKeypress();
		loadLevel(currentLevel);
		initialiseMonsters();
		clearScreen();
	}
}

void setAllMonstersInactive()
{
	monster0.setInactive();
	monster1.setInactive();
	monster2.setInactive();
	monster3.setInactive();
	monster4.setInactive();
	monster5.setInactive();
	monster6.setInactive();
	monster7.setInactive();
	monster8.setInactive();
	monster9.setInactive();
}

void startShop()
{
	clearScreen();
	bool done = false;
	Item i(0);
	cout << "------------------" << endl;
	cout << "|    MERCHANT    |" << endl;
	cout << "------------------" << endl << endl;
	shop.prepareStock(currentLevel);
	while (!done)
	{
		shop.displayItemsForSale();
		cout << endl << endl << "You have " + to_string(player.getGold()) + " gold." << endl;
		cout << "\nChoose an item or press X to return to the map." << endl << endl;
		input = _getch();

		if (input == '1' && shop.getStockSize() > 0)
		{
			i = shop.getItem(1);
			cout << i.getName() << endl << endl;
			cout << i.getDescription() << endl << endl;
			cout << "Buy this item for " + to_string(i.getPrice()) + " gold? (Y/N)" << endl << endl;
			input = _getch();

			if (input == 'y' || input == 'Y')
			{
				buyItem(i);
			}
		}

		if (input == '2' && shop.getStockSize() > 1)
		{
			i = shop.getItem(2);
			cout << i.getName() << endl << endl;
			cout << i.getDescription() << endl << endl;
			cout << "Buy this item for " + to_string(i.getPrice()) + " gold? (Y/N)" << endl;
			input = _getch();

			if (input == 'y' || input == 'Y')
			{
				buyItem(i);
			}
		}

		if (input == '3' && shop.getStockSize() > 2)
		{
			i = shop.getItem(3);
			cout << i.getName() << endl << endl;
			cout << i.getDescription() << endl << endl;
			cout << "Buy this item for " + to_string(i.getPrice()) + " gold? (Y/N)" << endl;
			input = _getch();

			if (input == 'y' || input == 'Y')
			{
				buyItem(i);
			}
		}

		if (input == '4' && shop.getStockSize() > 3)
		{
			i = shop.getItem(4);
			cout << i.getName() << endl << endl;
			cout << i.getDescription() << endl << endl;
			cout << "Buy this item for " + to_string(i.getPrice()) + " gold? (Y/N)" << endl;
			input = _getch();

			if (input == 'y' || input == 'Y')
			{
				buyItem(i);
			}
		}

		if (input == '5' && shop.getStockSize() > 4)
		{
			i = shop.getItem(5);
			cout << i.getName() << endl << endl;
			cout << i.getDescription() << endl << endl;
			cout << "Buy this item for " + to_string(i.getPrice()) + " gold? (Y/N)" << endl;
			input = _getch();

			if (input == 'y' || input == 'Y')
			{
				buyItem(i);
			}
		}

		if (input == '6' && shop.getStockSize() > 5)
		{
			i = shop.getItem(6);
			cout << i.getName() << endl << endl;
			cout << i.getDescription() << endl << endl;
			cout << "Buy this item for " + to_string(i.getPrice()) + " gold? (Y/N)" << endl;
			input = _getch();

			if (input == 'y' || input == 'Y')
			{
				buyItem(i);
			}
		}

		if (input == '7' && shop.getStockSize() > 6)
		{
			i = shop.getItem(7);
			cout << i.getName() << endl << endl;
			cout << i.getDescription() << endl << endl;
			cout << "Buy this item for " + to_string(i.getPrice()) + " gold? (Y/N)" << endl;
			input = _getch();

			if (input == 'y' || input == 'Y')
			{
				buyItem(i);
			}
		}

		if (input == '8' && shop.getStockSize() > 7)
		{
			i = shop.getItem(8);
			cout << i.getName() << endl << endl;
			cout << i.getDescription() << endl << endl;
			cout << "Buy this item for " + to_string(i.getPrice()) + " gold? (Y/N)" << endl;
			input = _getch();

			if (input == 'y' || input == 'Y')
			{
				buyItem(i);
			}
		}

		if (input == '9' && shop.getStockSize() > 8)
		{
			i = shop.getItem(9);
			cout << i.getName() << endl << endl;
			cout << i.getDescription() << endl << endl;
			cout << "Buy this item for " + to_string(i.getPrice()) + " gold? (Y/N)" << endl;
			input = _getch();

			if (input == 'y' || input == 'Y')
			{
				buyItem(i);
			}
		}

		if (input == 'x' || input == 'X')
		{
			done = true;
		}
	}
}

void buyItem(Item item)
{
	if (inventory.size() >= 5)
	{
		cout << "Your backpack is too full for any more items..." << endl;
	}
	else if (player.getGold() > item.getPrice())
	{
		player.loseGold(item.getPrice());
		inventory.push_back(item);
		cout << "You purchase the " + item.getName() + "..." << endl;
	}
	else
	{
		cout << "You cannot afford the " + item.getName() + "..." << endl;
	}

	cout << "Press any key to continue." << endl;
	waitForKeypress();
	clearScreen();
}