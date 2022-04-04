#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "console.h"
#include <fstream>

using namespace std;

/*Create a log file that records the name of anybody who uses the game and the result[DONE]
of each game they play (make sure this list is appended and stores all of the name ofthe people that have played the game)

The monsters are to try and capture the character by landing on the same location as the main character. 
The monsters will need some simple strategy to move towards the character and not simply move in a random direction.

Add a user selected difficulty level which will alter the number of monsters and traps.*/

class Object
{
protected:
	int numberGenerated;
	string name;
	string objectSymbol;
	string directions[4] = { "LEFT", "RIGHT", "DOWN", "UP" };
	int xPosition;
	int yPosition; 
	int xSpawnedPosition;
	int ySpawnedPosition;
	int lastXPosition;
	int lastYPosition;
	bool liveStatus;
public:
	Object()
	{
		name = "Default Object Name";
		objectSymbol = "O";
		xPosition = 0;
		yPosition = 0;
		liveStatus = true;
	}
	string getName()
	{
		return name;
	}
	void setLiveStatus(bool status)
	{
		liveStatus = status;
	}
	void setRandomSpawnPosition(int xRange, int yRange)
	{
		int generatedXPosition = rand() % xRange;
		int generatedYPosition = rand() % yRange;

		xSpawnedPosition = generatedXPosition;
		ySpawnedPosition = generatedYPosition;
	}
	void setObjectSymbol(string symbol)
	{
		objectSymbol = symbol;
	}
	string getObjectSymbol()
	{
		return objectSymbol;
	}
	int getNumberGenerated()
	{
		return numberGenerated;
	}
	int getXPosition()
	{
		return xPosition;
	}
	void setXPosition(int setXPosition)
	{
		xPosition = setXPosition;
	}
	int getYPosition()
	{
		return yPosition;
	}
	void setYPosition(int setYPosition)
	{
		yPosition = setYPosition;
	}
	void setLastPosition(int setLastXPosition, int setLastYPosition)
	{
		lastXPosition = setLastXPosition;
		lastYPosition = setLastYPosition;
	}
	void setXSpawnedPosition(int xPos)
	{
		xSpawnedPosition = xPos;
	}
	int getXSpawnedPosition()
	{
		return xSpawnedPosition;
	}
	void setYSpawnedPosition(int yPos)
	{
		ySpawnedPosition = yPos;
	}
	int getYSpawnedPosition()
	{
		return ySpawnedPosition;
	}
	int getLastXPosition()
	{
		return lastXPosition;
	}
	int getLastYPosition()
	{
		return lastYPosition;
	}
};

class Player : public Object
{
public:
	Player(string username)
	{
		name = username;
		objectSymbol = "P";
		xPosition = 0;
		yPosition = 0;
		xSpawnedPosition = 0;
		ySpawnedPosition = 0;
		lastXPosition = 0;
		lastYPosition = 0;
		liveStatus = true;
	}
	string playerMovement(int position)
	{
		string direction;

		switch (position)
		{
		case 2:
			direction = directions[2];
			xPosition += 1;
			break;
		case 4:
			direction = directions[0];
			yPosition -= 1;
			break;
		case 6:
			direction = directions[1];
			yPosition += 1;
			break;
		case 8:
			direction = directions[3];
			xPosition -= 1;
			break;
		default:
			cout << "Invalid direction, Try again: " << endl;
		}

		return direction;
	}
};

class Trap : public Object
{
public:
	Trap(int number)
	{
		numberGenerated = number;
		name = "Man Hole";
		objectSymbol = "T";
		xPosition = 0;
		yPosition = 0;
		xSpawnedPosition = 0;
		ySpawnedPosition = 0;
		lastXPosition = 0;
		lastYPosition = 0;
		liveStatus = true;
	}
};

class Monster : public Object
{
public:
	Monster(int number)
	{
		numberGenerated = number;
		name = "Monster";
		objectSymbol = "M";
		xPosition = 0;
		yPosition = 0;
		xSpawnedPosition = 0;
		ySpawnedPosition = 0;
		lastXPosition = 0;
		lastYPosition = 0;
		liveStatus = true;
	}
	string movement(int playerX, int playerY)
	{
		//This can be added in the future to make it easier for players

		//int choice = rand() % 4;

		/*if (liveStatus)
		{
			switch (choice)
			{
			case 0:
				yPosition -= 1;
				return directions[0];
				break;
			case 1:
				yPosition += 1;
				return directions[1];
				break;
			case 2:
				xPosition += 1;
				return directions[2];
				break;
			case 3:
				xPosition -= 1;
				return directions[3];
				break;
			}
		}*/

		if (liveStatus)
		{
			if (yPosition > playerY)
			{
				yPosition -= 1;
				return directions[0];
			}
			else if (yPosition < playerY)
			{
				yPosition += 1;
				return directions[1];
			}
			else if (xPosition < playerX)
			{
				xPosition += 1;
				return directions[2];
			}
			else if (xPosition > playerX)
			{
				xPosition -= 1;
				return directions[3];
			}
		}
	}
};

class Game
{
private:
	int gridRow;
	int gridCol;
	int gameMode;
	bool gameEnd = false;
	bool won = false;
	bool reset = false;
	string directions[4] = { "LEFT", "RIGHT", "DOWN", "UP" };
	vector<vector<string>> grid;	//Two 2d Vector which holds the grid
public:
	Game()
	{
		createGrid();
		game();
	}
	void setGridRow(int userRow)
	{
		gridRow = userRow;
	}
	int getGridRow()
	{
		return gridRow;
	}
	void setGridCol(int userCol)
	{
		gridCol = userCol;
	}
	int getGridCol()
	{
		return gridCol;
	}
	void setGameEnd(bool gameStatus)
	{
		gameEnd = gameStatus;
	}
	bool getGameEnd()
	{
		return gameEnd;
	}
	void setWon(bool gameWon)
	{
		won = gameWon;
	}
	bool getWon()
	{
		return won;
	}
	void moveObject(string objectMovement, string objectSymbol, int currentX, int currentY)
	{
		int previousX = currentX;
		int previousY = currentY;

		grid[previousX][previousY] = "-";

		if (objectMovement == directions[0])
		{
			if (currentY - 1 > gridCol || currentY - 1 < 0)
			{
				grid[currentX][currentY] = objectSymbol;
			}
			else
			{
				grid[currentX][currentY -= 1] = objectSymbol;
			}
		}
		else if (objectMovement == directions[1])
		{
			if (currentY >= gridCol - 1)
			{
				grid[currentX][currentY] = objectSymbol;
			}
			else
			{
				grid[currentX][currentY += 1] = objectSymbol;
			}
		}
		else if (objectMovement == directions[2])
		{
			if (currentX >= gridRow - 1)
			{
				grid[currentX][currentY] = objectSymbol;
			}
			else
			{
				grid[currentX += 1][currentY] = objectSymbol;
			}
		}
		else if (objectMovement == directions[3])
		{
			if (currentX - 1 > gridRow || currentX - 1 < 0)
			{
				grid[currentX][currentY] = objectSymbol;
			}
			else
			{
				grid[currentX -= 1][currentY] = objectSymbol;
			}
		}
		else
		{
			grid[previousX][previousY] = objectSymbol;
		}
	}
	void createGrid()
	{
		int userInput;
		
		cout << "Enter the amount of rows you want the grid to have: ";
		
		cin >> userInput;

		setGridRow(userInput);

		cout << "Enter the amount of colums you want the grid to have: ";

		cin >> userInput;

		setGridCol(userInput);

		for (int x = 0; x < gridRow; x++)
		{
			vector<string> firstDimensionalVector;

			for (int y = 0; y < gridCol; y++)
			{
				firstDimensionalVector.push_back("-");
			}

			grid.push_back(firstDimensionalVector);
		}
	}
	void displayGrid()
	{
		//vector<vector<string>> grid(gridRow, vector<string>(gridCol, "-"));

		for (int i = 0; i < gridRow; i++)
		{
			/*Need to fix to work for bigger grids so far works on
			20 and below maybe works for just over 20 values*/

			if (reset)
			{
				Console::setCursorPosition(3 + i, 20 - gridCol);
			}
			else
			{
				Console::setCursorPosition(7 + i, 20 - gridCol);
			}

			for (int j = 0; j < gridCol; j++)
			{
				cout << grid[i][j] << " ";
			}

			cout << endl; 
		}
	}
	int getGameMode(int gameMode)
	{
		int amountOfObjects;

		switch (gameMode)
		{
		case 1:
			amountOfObjects = 2;
			return amountOfObjects;
			break;
		case 2:
			amountOfObjects = 4;
			return amountOfObjects;
			break;
		case 3:
			amountOfObjects = 10;
			return amountOfObjects;
			break;
		case 4:
			amountOfObjects = rand() % (gridRow * gridCol) / 5 + 3;
			return amountOfObjects;
			break;
		}
	}
	void endMessage(string playerName, bool gameEnd, bool gameWon)
	{
		if (gameEnd == true && gameWon == true)
		{
			Console::setColour(Console::GREEN);
			cout << "=============================================" << endl;
			cout << "               GAME GRID" << endl;
			cout << "=============================================" << endl;
			displayGrid();
			cout << "=============================================" << endl;
			Console::setColour(Console::LIGHT_GREEN);
			cout << "Game over " << playerName << ", YOU HAVE WON :)" << endl;
		}
		else
		{
			Console::setColour(Console::RED);
			cout << "=============================================" << endl;
			cout << "               GAME GRID" << endl;
			cout << "=============================================" << endl;
			displayGrid();
			cout << "=============================================" << endl;
			Console::setColour(Console::LIGHT_RED);
			cout << "Game over " << playerName << ", YOU HAVE DIED :(" << endl;
		}

	}
	void exportLog(string playerName, int gameMode, bool gameWon)
	{
		string gameModes[4] = {"EASY", "MEDIUM", "HARD", "CUSTOM"};

		//Creates Zombie_Island_Game_log.txt
		string logFileName = "Zombie_Island_Game_log.txt";
		ofstream logFile;

		logFile.open(logFileName, ios_base::app);
		if (getWon() == 1)
		{
			logFile << "Game Mode: " << gameModes[gameMode] << " [-] Player: " << playerName << " [-] Game Status: WIN" << endl;
		}
		else
		{
			logFile << "Game Mode: " << gameModes[gameMode] << " [-] Player: " << playerName << " [-] Game Status: LOSS" << endl;
		}

	}
	void game()
	{
		string userName;

		cout << "Enter your name: ";

		cin >> userName;

		cout << "Choose your game mode: [1:EASY] [2:MEDIUM] [3:HARD] [4:CUSTOM]: ";
		
		cin >> gameMode;

		//Creates the player object
		Player player(userName);

		//Sets the player's random position then sets the spawned x and y to the x and y of the player.
		player.setRandomSpawnPosition(gridRow, gridCol);
		player.setXPosition(player.getXSpawnedPosition());
		player.setYPosition(player.getYSpawnedPosition());

		/*My formula which generates the random range of monstersand traps. 
		For example if the grid is 10x10 it will do 10x10 = 100 and then divide it by 5 
		and the the rand function would generated a value from 3 - 20*/

		vector<Monster> monsterInstances;
		vector<Trap> trapInstances;

		//Adds each of the created objects into the vector and looks at the selected gamemode and generates the amount specified
		for (int i = 0; i < getGameMode(gameMode); i++)
		{
			monsterInstances.push_back(Monster(i));
			trapInstances.push_back(Trap(i));
		}

		//Sets the spawn location of each element in monsterInstances vector and check if's the spawn positions isin't the same with player or trap
		for (int i = 0; i < monsterInstances.size(); i++)
		{			
			//Sets random spawn position and assigns the positions to the xPosition and yPosition of the monster
			monsterInstances[i].setRandomSpawnPosition(gridRow, gridCol);
			monsterInstances[i].setXPosition(monsterInstances[i].getXSpawnedPosition());
			monsterInstances[i].setYPosition(monsterInstances[i].getYSpawnedPosition());

			//If the monster position is the same as the player it will generated and set the new positions of the monster on the grid
			if (monsterInstances[i].getXSpawnedPosition() == player.getXSpawnedPosition() && monsterInstances[i].getYSpawnedPosition() == player.getYSpawnedPosition())
			{
				monsterInstances[i].setRandomSpawnPosition(gridRow, gridCol);
				monsterInstances[i].setXPosition(monsterInstances[i].getXSpawnedPosition());
				monsterInstances[i].setYPosition(monsterInstances[i].getYSpawnedPosition());

				grid[monsterInstances[i].getXSpawnedPosition()][monsterInstances[i].getYSpawnedPosition()] = monsterInstances[i].getObjectSymbol();
			}
			else if (monsterInstances[i].getXSpawnedPosition() == trapInstances[i].getXSpawnedPosition() && monsterInstances[i].getYSpawnedPosition() == trapInstances[i].getYSpawnedPosition())
			{
				monsterInstances[i].setRandomSpawnPosition(gridRow, gridCol);
				monsterInstances[i].setXPosition(monsterInstances[i].getXSpawnedPosition());
				monsterInstances[i].setYPosition(monsterInstances[i].getYSpawnedPosition());

				grid[monsterInstances[i].getXSpawnedPosition()][monsterInstances[i].getYSpawnedPosition()] = monsterInstances[i].getObjectSymbol();
			}
			else
			{
				grid[monsterInstances[i].getXSpawnedPosition()][monsterInstances[i].getYSpawnedPosition()] = monsterInstances[i].getObjectSymbol();
			}
		}

		//Sets the spawn location of each element in trapInstances vector and check if's the spawn positions isin't the same with player or trap
		for (int i = 0; i < trapInstances.size(); i++)
		{
			//Sets random spawn position and assigns the positions to the xPosition and yPosition of the trap
			trapInstances[i].setRandomSpawnPosition(gridRow, gridCol);
			trapInstances[i].setXPosition(trapInstances[i].getXSpawnedPosition());
			trapInstances[i].setYPosition(trapInstances[i].getYSpawnedPosition());

			if (trapInstances[i].getXSpawnedPosition() == player.getXSpawnedPosition() && trapInstances[i].getYSpawnedPosition() == player.getYSpawnedPosition())
			{
				trapInstances[i].setRandomSpawnPosition(gridRow, gridCol);
				trapInstances[i].setXPosition(trapInstances[i].getXSpawnedPosition());
				trapInstances[i].setYPosition(trapInstances[i].getYSpawnedPosition());

				grid[trapInstances[i].getXSpawnedPosition()][trapInstances[i].getYSpawnedPosition()] = trapInstances[i].getObjectSymbol();
			}
			else if (trapInstances[i].getXSpawnedPosition() == monsterInstances[i].getXSpawnedPosition() && trapInstances[i].getYSpawnedPosition() == monsterInstances[i].getYSpawnedPosition())
			{
				trapInstances[i].setRandomSpawnPosition(gridRow, gridCol);
				trapInstances[i].setXPosition(trapInstances[i].getXSpawnedPosition());
				trapInstances[i].setYPosition(trapInstances[i].getYSpawnedPosition());

				grid[trapInstances[i].getXSpawnedPosition()][trapInstances[i].getYSpawnedPosition()] = trapInstances[i].getObjectSymbol();
			}
			else
			{
				grid[trapInstances[i].getXSpawnedPosition()][trapInstances[i].getYSpawnedPosition()] = trapInstances[i].getObjectSymbol();
			}
		}

		//Shows the player's object symbol on the grid
		grid[player.getXSpawnedPosition()][player.getYSpawnedPosition()] = player.getObjectSymbol();

		while (!gameEnd)
		{
			cout << "=============================================" << endl;
			cout << "               GAME GRID" << endl;
			cout << "=============================================" << endl;
			displayGrid();
			cout << "=============================================" << endl;
			cout << "            PLAYER DIRECTION" << endl;
			cout << "		    8	" << endl;
			cout << "	    4		   6 " << endl;
			cout << "		    2	" << endl;
			cout << " [4 = LEFT] [6 = RIGHT] [2 = DOWN] [8 = UP]" << endl;
			cout << "=============================================" << endl;
			cout << "Enter the direction you want to move in: ";

			int userDirection;

			cin >> userDirection;

			reset = true;

			//Sets players last position
			player.setLastPosition(player.getXPosition(), player.getYPosition());
			//Moves the player on the grid
			moveObject(player.playerMovement(userDirection), player.getObjectSymbol(), player.getXPosition(), player.getYPosition());

			//Checks the boundries of the player
			if (player.getYPosition() > gridCol - 1 || player.getYPosition() < 0)
			{
				player.setYPosition(player.getLastYPosition());
			}
			else if (player.getXPosition() > gridRow - 1 || player.getXPosition() < 0)
			{
				player.setXPosition(player.getLastXPosition());
			}

			//Checks the boundries of monsters
			for (int i = 0; i < monsterInstances.size(); i++)
			{
				monsterInstances[i].setLastPosition(monsterInstances[i].getXPosition(), monsterInstances[i].getYPosition());
				moveObject(monsterInstances[i].movement(player.getXPosition(), player.getYPosition()), monsterInstances[i].getObjectSymbol(), monsterInstances[i].getXPosition(), monsterInstances[i].getYPosition());
			
				if (monsterInstances[i].getYPosition() > gridCol - 1 || monsterInstances[i].getYPosition() < 0)
				{
					monsterInstances[i].setYPosition(monsterInstances[i].getLastYPosition());
				}
				else if (monsterInstances[i].getXPosition() > gridRow - 1 || monsterInstances[i].getXPosition() < 0)
				{
					monsterInstances[i].setXPosition(monsterInstances[i].getLastXPosition());
				}
			}

			grid[player.getXPosition()][player.getYPosition()] = player.getObjectSymbol();

			//If the player lands on a monster they die and if the monster lands on a monster they die
			for (int i = 0; i < monsterInstances.size(); i++)
			{
				//Get the position of the previous vector in the array
				int previousMonster = monsterInstances[i].getNumberGenerated() - 1;
				//Get the position of the next vector in the array
				int nextMonster = monsterInstances[i].getNumberGenerated() + 1;

				//If the player lands on the monster they die and the game ends
				if (player.getXPosition() == monsterInstances[i].getXPosition() && player.getYPosition() == monsterInstances[i].getYPosition())
				{
					player.setLiveStatus(false);
					setGameEnd(true);
					setWon(false);
				}
			}

			//If monster lands on a trap they die
			for (int x = 0; x < trapInstances.size(); x++)
			{

				if (player.getXPosition() == trapInstances[x].getXPosition() && player.getYPosition() == trapInstances[x].getYPosition())
				{
					player.setLiveStatus(false);
					setGameEnd(true);
					setWon(false);
				}

				//If there's monsters left then keep checking if they are on a trap else finish the game and show that the player won
				if (monsterInstances.size() != 0)
				{
					for (int i = 0; i < monsterInstances.size(); i++)
					{
						if (monsterInstances[i].getXPosition() == trapInstances[i].getXPosition() && monsterInstances[i].getYPosition() == trapInstances[i].getYPosition())
						{
							monsterInstances[i].setLiveStatus(false);
							monsterInstances.erase(monsterInstances.begin() + i);
						}
					}
				}
				else
				{
					setGameEnd(true);
					setWon(true);
				}
				grid[trapInstances[x].getXPosition()][trapInstances[x].getYPosition()] = trapInstances[x].getObjectSymbol();
			}


			//Clears the console so the new updated positions show on the grid
			Console::clear();
		}

		endMessage(player.getName(), getGameEnd(), getWon());
		exportLog(player.getName(), gameMode-1, getWon());
	}
};

int main()
{
	Console::setWindowTitle("Zombie Island - 30028170");
	Console::setColour(Console::LIGHT_BLUE);
	srand(unsigned(time(NULL)));
	Game game;
	return 0;
}