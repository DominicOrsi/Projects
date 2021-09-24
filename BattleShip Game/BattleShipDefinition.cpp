/*
Name: Dominic Orsi
Class: CPCS 121, Fall 2020
Date: November 20, 2020
Notes: Function Delcarations and Definition.cpp file of BattleShip
*/
#include "BattleShip.h"
/*
Function: displayBoard()
Date Created: 11/17/20  
Date Last Modified: 11/20/20 
Description: It takes in 2d array, rows and cols and then outputs onto the screen
Returns: none
Pre: 2d array not displayed
Post: 2d array displayed on screen
*/
void displayBoard(const char arr[NUM_ROWS][NUM_COLS], int rows, int cols) {
	int i = 0;
	int j = 0;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}
/*
Function: initializeBoard
Date Created: 11/17/20  
Date Last Modified: 11/20/20 
Description: Takes empty 2d array and places "~" into all its spots
Returns: none
Pre: Empty 2d array
Post: Filled with "~" after going through loops
*/
void initializeBoard(char arr[NUM_ROWS][NUM_COLS], int rows, int cols) {
	int i = 0;
	int j = 0;
	// outer loop iterates over each row
	for (i = 0; i < rows; i++) {
		// inner loop iterates over int in arr[i] (row)
		for (j = 0; j < cols; j++) {
			arr[i][j] = '~';
		}
	}
}
/*
Function: welcomeScreen
Date Created: 11/17/20  
Date Last Modified: 11/20/20 
Description: Outputs/displays welcome screen 
Returns: none
Pre: Empty screen
Post: Screen populated with welcome message to the game
*/
void welcomeScreen() {
	cout << "***** Welcome to BattleShip! *****\n";
	cout << "\nRules of the Game:\n";
	cout << "1. This is a two player game.\n2. Player1 is you and Player2 is the computer.\n";
	cout << "3. Place your ships on the board either horizontally or vertically.\n4. No ships can over lap or be placed diagonally.\n";
	cout << "5. You get one shot each turn.\n6. If the shot hits the opponents ship then a \"*\" appears and if you miss a \"m\" appears where the shot was fired.\n";
	cout << "7. The game ends once all ships are sunk for one player.\n8. Who ever sinks all of the opponenets ships is the winner.\n";
}
/*
Function: selectWhoStartsFirst
Date Created: 11/17/20  
Date Last Modified: 11/20/20 
Description: Takes a rand number and % it by 2 to see if player 1 or player 2 starts first
Returns: integer with 1 or 2 to say who starts first
Pre: Random number % by 2 to get who starts first
Post: Returns 0 or 1 as to who starts first
*/
int selectWhoStartsFirst() {
	int i = 10;	
	srand(time(NULL));
	i = rand() % 2;
	if (i == 0) {
		cout << "Player 1 starts first.\n";
	} else if (i == 1) {
		cout << "Player 2 starts first.\n";
	} else {
		cout << "We got a problem in selectWhoStartsFirst.\n";
	}
	return i;
}
/*
Function: manuallyPlaceShipsOnBoard
Date Created: 11/17/20  
Date Last Modified: 11/20/20 
Description: Asks user for inputs for rows and cols to see where they want to place there ships on the board.
Returns: none
Pre: Asks user for input on direction and then starting row and col to place ship and takes in a 2d array
Post:  Places ship in 2d array after users enters desired row and col and direction
*/
void manuallyPlaceShipsOnBoard(char grid[NUM_ROWS][NUM_COLS], const string shipNames[], const char shipSymbols[], const int shipSizes[]) {
	int i = 0;
	int p = 0;
	int k = 0;	
	int col = 0;
	int row = 0;
	char direction = ' ';

	// For loop for placing ships
	for(i = 0; i < 5; i++) { 
		cout << "Press \"h\" to place "<< shipNames[i] << " horizontally and \"v\" to place " << shipNames[i] << " vertically: ";
		cin >> direction;
		cout << "Enter what row you would want to place " << shipNames[i] << " on: ";
		cin >> row;
		cout << "Enter what col you would want to place " << shipNames[i] << " on: ";
		cin >> col;

		// Call checkRowOrColIsValid to check row or col
		checkRowOrColIsValid(direction, row, col, i, shipSizes);

		// Check if ship has been placed there before
		p = checkShipPlacement(grid, row, col, i, direction, shipSizes);
		
		// While loop to ask for new coords if ship cannot be placed there.
		while(p == -1) {
			cout << "Press \"h\" to place "<< shipNames[i] << " horizontally and \"v\" to place " << shipNames[i] << " vertically: ";
			cin >> direction;
			cout << "Enter what row you would want to place " << shipNames[i] << " on: ";
			cin >> row;
			cout << "Enter what col you would want to place " << shipNames[i] << " on: ";
			cin >> col;

			// Call checkRowOrColIsValid to check row or col
			checkRowOrColIsValid(direction, row, col, i, shipSizes);

			// Call checkShipPlacement again to see if it works now
			p = checkShipPlacement(grid, row, col, i, direction, shipSizes);
		}
		// If loop to set ships
		if(direction == 'h') {
			
			// For loop for H placement
			for(k = 0; k < shipSizes[i]; k++) {
				grid[row][col + k] = shipSymbols[i];
			}
		} else {

			// For loop for V placement
			for( k = 0; k < shipSizes[i]; k++) {
				grid[row + k][col] = shipSymbols[i];
			}
		}
	}
}
/*
Function: randomlyPlaceShipsOnBoard
Date Created: 11/17/20  
Date Last Modified: 11/20/20 
Description: Takes in a 2d array and then places ships on board according to direction and rand numbers given
Returns: none
Pre:  Takes 2d array and rand numbers to then assign a ship to those values
Post: Fills the 2d array with ship placements from rand numbers
*/
void randomlyPlaceShipsOnBoard(char grid[NUM_ROWS][NUM_COLS], const string shipNames[], const char shipSymbols[], const int shipSizes[]) {
	int i = 0;
	int p = 0;
	int k = 0;	
	int col = 0;
	int row = 0;
	char direction = ' ';
	srand(time(NULL));

	// For loop for placing ships
	for(i = 0; i < 5; i++) { 
		direction = getDirection();
	
		// If loop for placing ships horizonatally or vertically
		if(direction == 'h') {
			if(shipNames[i] == "carrier") {
				row = rand() % 10;
				col = rand() % 5;
			} else if(shipNames[i] == "battleship") {
				row = rand() % 10;
				col = rand() % 6;
			} else if(shipNames[i] == "cruiser" || shipNames[i] == "submarine") {
				row = rand() % 10;
				col = rand() % 7;
			} else if(shipNames[i] == "destroyer") {
				row = rand() % 10;
				col = rand() % 8;
			}
		} else {
			if(shipNames[i] == "carrier") {
				row = rand() % 5;
				col = rand() % 10;
			} else if(shipNames[i] == "battleship") {
				row = rand() % 6;
				col = rand() % 10;
			} else if(shipNames[i] == "cruiser" || shipNames[i] == "submarine") {
				row = rand() % 7;
				col = rand() % 10;
			} else if(shipNames[i] == "destroyer") {
				row = rand() % 8;
				col = rand() % 10;
			}
		} // End of if loop for ships being H or V
		// Call Function to check if ship can be placed there
		p = checkShipPlacement(grid, row, col, i, direction, shipSizes);

		// While loop to replace ship if wrong
		while(p == -1) {
			direction = getDirection();
			
			// If loop on direction again :D
			if(direction == 'h') {
				if(shipNames[i] == "carrier") {
					row = rand() % 10;
					col = rand() % 5;
				} else if(shipNames[i] == "battleship") {
					row = rand() % 10;
					col = rand() % 6;
				} else if(shipNames[i] == "cruiser" || shipNames[i] == "submarine") {
					row = rand() % 10;
					col = rand() % 7;
				} else if(shipNames[i] == "destroyer") {
					row = rand() % 10;
					col = rand() % 8;
				}
			} else {
				if(shipNames[i] == "carrier") {
					row = rand() % 5;
					col = rand() % 10;
				} else if(shipNames[i] == "battleship") {
					row = rand() % 6;
					col = rand() % 10;
				} else if(shipNames[i] == "cruiser" || shipNames[i] == "submarine") {
					row = rand() % 7;
					col = rand() % 10;
				} else if(shipNames[i] == "destroyer") {
					row = rand() % 8;
					col = rand() % 10;
				}
			}
			// Check placement again before leaving loop
			p = checkShipPlacement(grid, row, col, i, direction, shipSizes); 
		}
					
		// If loop to set ships
		if(direction == 'h') {
			
			// For loop for H placement
			for(k = 0; k < shipSizes[i]; k++) {
				grid[row][col + k] = shipSymbols[i];
			}
		} else {

			// For loop for V placement
			for( k = 0; k < shipSizes[i]; k++) {
				grid[row + k][col] = shipSymbols[i];
			}
		} // End of if loop to set ships
	}
}
/*
Function: getDirection
Date Created: 11/17/20  
Date Last Modified: 11/20/20 
Description: Asks rand for a number then % it by 2 to then determine whether the direction will be horizontal or vertical and then spits out char h for horiznal and v for vertical
Returns: char of either h or v
Pre: Takes a rand number and then %s it by 2 to determine horizontal or vertical
Post: Returns a char of h or v and allows then allows is calling it to continue one 
*/
char getDirection() {
	int d = 10;
	srand(time(NULL));
	d = rand() % 2;
	
	// if loop for direction char
	if(d == 0) {
		return 'h';
	} else {
		return 'v';
	}
}
/*
Function: checkShipPlacement
Date Created: 11/17/20  
Date Last Modified: 11/20/20 
Description: Checks ship placement of given row and col to see if the ship can be placed there
Returns: An integer saying yes a ship can go there or no a ship cannot
Pre: Takes in a 2d array, rows, cols, direction, and then shipSizes array to check if that ship can fit in the given row and col without hitting another ship 
Post: Returns a 10 if yes the ships fits or a -1 if it doesn't and then allows the program to continue
*/
int checkShipPlacement(char grid[NUM_ROWS][NUM_COLS], int row, int col, int i, char direction, const int shipSizes[]) {
	int k = 0;	
	int l = 0 ;
	
	// If statement for direction
	if(direction == 'h') {
		// For loop for checking every row and col
		for(k = 0; k < shipSizes[i]; k++) {

			// If statement to test cols
			if(grid[row][col + k] == '~') {
				l += 1;
			} else {
				l += -1;
			}
		}
	} else {
		// For loop for checking every row and col
		for(k = 0; k < shipSizes[i]; k++) {		

			// If statement to test rows
			if(grid[row + k][col] == '~') {
			 	l += 1;
			} else {
				l += -1;
			}
		}
	} // End of if statement on direction

	// If statement to check if any points are wrong
	if(l == shipSizes[i]) {
		l = 10;
	} else {
		l = -1;
	}	
	return l;
}
/*
Function: checkRowOrColsIsValid
Date Created: 11/17/20  
Date Last Modified: 11/20/20 
Description: Takes in entered row or col and checks it to see if the manual placement of ships is okay and that the ships wont run into each other for the manual placement
Returns: none
Pre: Takes in direction, row, col, int i, and shipSizes array to see if the ship doesnt go over 10 - shipSizes[i] so that it will fit in the 2d array on the same row or col
Post: Says that while direction == to h or v and col or row is greater than 10 - shipSize it askes the user to re enter a row and col so tha the ship fits
*/
void checkRowOrColIsValid(char direction, int& row, int& col, int i, const int shipSizes[]) {
	// While loop to make sure col is in bounds
	while(direction == 'h' && col > 10 - shipSizes[i]) {
		cout << "Please enter a column between 0-" << 10 - shipSizes[i] << ": ";
		cin >> col;
	}
	
	// While loop to make sure row is in bounds
	while(direction == 'v' && row > 10 - shipSizes[i]) {
		cout << "Please enter a row between 0-" << 10 - shipSizes[i] << ": ";
		cin >> row;
	}
}
/*
Function: checkShot
Date Created: 11/17/20  
Date Last Modified: 11/20/20 
Description: Takes in row and col and checks it against a 2d array to see if those coords have a ship or not
Returns: Integer i to added to hits if the shot is a hit
Pre: 2d array and row and col to check if coords have a ship or not
Post: Tells you whether you hit a ship or not at the row and col entered
*/
int checkShot(char grid[NUM_ROWS][NUM_COLS], int row, int col) {
	int i = 0;	

	// If loop to check for hit or miss
	if(grid[row][col] != '~') {
		cout << "hit an enemy ship at " << row << ", " << col << endl;
		i = 1;
	} else {
		cout << "didn't hit any ships at " << row << ", " << col << endl;
	}
	return i;
} 
/*
Function: isWinner
Date Created: 11/17/20  
Date Last Modified: 11/20/20 
Description: Takes in player 1 and player 2s hits to see if they either of them equals 17 to then declare than one a winner of the game
Returns: Integer i being 1 or 2 for player 1 or 2 winning the game
Pre: Takes in hits of player 1 and player 2 and checks to see if either equal 17 and then declare them a winner or to just keep playing
Post: Returns i saying either one of the players one or not
*/
int isWinner(int p1Hits, int p2Hits) {
	int i = 0;	

	// If loop to check if players have hit all of opponents ships
	if(p1Hits == 17) {
		cout << "Player 1 wins the game!!\n";
		i = 1;
	} else if(p2Hits == 17) {
		cout << "Player 2 wins the game!!\n";
		i = 2;
	}
	return i;
}
/*
Function: updateBoard
Date Created: 11/17/20  
Date Last Modified: 11/20/20 
Description: Takes in 2d array, row, col, and playerHits to see if if they replace a char on the 2d array with a * or m
Returns: int pHits to add to players hits if they hit a ship
Pre: 2d array, row, col, and pHits taken in and then replaces 2d array with * or m
Post: Array is given either a * or m for the coords fired at and then returns pHits so that the hit if any is added to players total hits
*/
int updateBoard(char grid[NUM_ROWS][NUM_COLS], int row, int col, int& pHits) {
	// Call function to check if hit
	pHits += checkShot(grid, row, col);
	
	// If loop to add * to a hit spot
	if(grid[row][col] != '~') {
		grid[row][col] = '*';
	} else { 
		grid[row][col] = 'm';
	}
	return pHits;
}
/*
Function: checkIfSunkShip
Date Created: 11/17/20  
Date Last Modified: 11/20/20 
Description: Checks to see if in 2d array a ship has been been sunk
Returns: none
Pre: takes in 2d array along with ships ints and then adds them to see if any of one ship is there
Post: Has the ints passed by reference saying whether a ship is sunk or not 
*/
void checkIfSunkShip(char arr[NUM_ROWS][NUM_COLS], int& cv, int& bb, int& ca, int& sub, int& dd) {
	int i = 0;
	int j = 0;
	// outer loop iterates over each row
	for (i = 0; i < NUM_ROWS; i++) {
		// inner loop iterates over int in arr[i] (row)
		for (j = 0; j < NUM_COLS; j++) {
			// If loop to count ships			
			if(arr[i][j] == 'c') {
				cv += 1;
			} else if(arr[i][j] == 'b') {
				bb += 1;
			} else if(arr[i][j] == 'r') {
				ca += 1;
			} else if(arr[i][j] == 's') {
				sub += 1;
			} else if(arr[i][j] == 'd') {
				dd += 1;
			}	
		}
	}
}
/*
Function: checkCoords
Date Created: 11/17/20  
Date Last Modified: 11/20/20 
Description: Takes in 2d array, row, and cols to see if that those coords have been fired at before nd then returns l to say if they have been hit before
Returns: Int l saying a coord has been shot at before or not
Pre: Takes in 2d array, row , and col and compares row and col to that of the 2d array
Post: Says whether or not those row and cords have been used before
*/
int checkCoords(char grid[NUM_ROWS][NUM_COLS], int row, int col) {
	int l = 10;	
	// If statement to ask about coords
	if(grid[row][col] == 'm') {
		l = -1;
	} else if(grid[row][col] == '*') {
		l = -1;
	}
	return l;
}
/*
Function: outputCurrentMove
Date Created: 11/17/20  
Date Last Modified: 11/20/20 
Description: Takes in row, col, ship ints, and ship bools to see if a ship has been hit or not and whether one was sunk or not and then outputs that info to the outfile
Returns: none
Pre: Takes in hits, row, col, ship ints, and ship bools to determine if a ship has been hit or not and then if a ship is sunk it only says that once
Post: Outputs players move and if a ship was sunk or not
*/		
void outputCurrentMove(ofstream& outfile, int logHit, int lastValue, int row, int col, int cv, int bb, int ca, int sub, int dd, bool& cV, bool& bB, bool& cA, bool& suB, bool& dD, string player) {
	// If loop for hit or not
	if(logHit > lastValue) {
		outfile << player << " hit a ship at " << row << ", " << col << endl;
	} else { 
		outfile << player << " missed a ship at " << row << ", " << col << endl;
	}

	// If statement for ship sunk
	if(cv == 0 && cV) {
		outfile << player << " sunk the opponents carrier!\n";
		cV = false;
	} else if(bb == 0 && bB) {
		outfile << player << " sunk the opponents battleship!\n";
		bB = false;
	} else if(ca == 0 && cA) {
		outfile << player << " sunk the opponents cruiser!\n";
		cA = false;
	} else if(sub == 0 && suB) {
		outfile << player << " sunk the opponents sub!\n";
		suB =  false;
	} else if(dd == 0 && dD) {
		outfile << player << " sunk the opponents destroyer!\n";
		dD = false;
	}
}
/*
Function: outputStats
Date Created: 11/17/20  
Date Last Modified: 11/20/20 
Description: Takes in shots and hits from both players and then who the winner and then outputs who won and the stats of each player
Returns: none
Pre: Takes in shots of the players and then divides hits to shots taken to give you a percentage of your hit to miss ratio and then subtracts hits from shots to give you your misses
Post: Outputs the players stats to the log, from shots fired, to hit, missed and what there hit to miss ratio was in a percentage
*/
void outputStats(ofstream& outfile, int p1Shots, int p2Shots, int p1Hits, int p2Hits, int winner) {
	// Player 1 stats	
	outfile << endl << "***** STATS FOR PLAYER 1 *****" << endl;	
	outfile << "Player 1 fired " << p1Shots << " and hit " << p1Hits << " and missed " << p1Shots - p1Hits << " to average a hit to miss ratio of " << ((static_cast<double>(p1Hits)) / (static_cast<double>(p1Shots))) * 100 << "%." << endl;
	
	// If statement if winner	
	if(winner == 1) {
		outfile << "Player 1 won the game!!\n";
	} else {
		outfile << "Player 1 lost the game D.:\n";
	}
	
	// Player 2 stats
	outfile << endl << "***** STATS FOR PLAYER 2 *****" << endl;	
	outfile << "Player 2 fired " << p2Shots << " and hit " << p2Hits << " and missed " << p2Shots - p2Hits << " to average a hit to miss ratio of " << ((static_cast<double>(p2Hits)) / (static_cast<double>(p2Shots))) * 100 << "%." << endl;
	
	// If statement if winner	
	if(winner == 2) {
		outfile << "Player 2 won the game!!\n";
	} else {
		outfile << "Player 2 lost the game D.:\n";
	}
}
