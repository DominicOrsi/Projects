/*
Name: Dominic Orsi
Class: CPCS 121, Fall 2020
Date: November 20, 2020
Notes: Main cpp file of the game battleship. See inline comments for details
*/
#include "BattleShip.h"

int main() {
	int whoStarts = 10;
	int p1Hits = 0;
	int p2Hits = 0;
	int p1Shots = 0;
	int p2Shots = 0;
	int row = 0;
	int col = 0;
	int winner = 0;
	int h = 0;
	int p = 0;
	int logHit = 0;
	int lastValue1 = 0;
	int lastValue2 = 0;
	int run = 0;
	int cv1 = 0, bb1 = 0, ca1 = 0, sub1 = 0, dd1 = 0;
	int cv2 = 0, bb2 = 0, ca2 = 0, sub2 = 0, dd2 = 0;
	bool cV1 = true, bB1 = true, cA1 =true, suB1 = true, dD1 = true;
	bool cV2 = true, bB2 = true, cA2 =true, suB2 = true, dD2 = true;
	bool cV11 = true, bB11 = true, cA11 =true, suB11 = true, dD11 = true;
	bool cV22 = true, bB22 = true, cA22 =true, suB22 = true, dD22 = true;
	char placementType = ' ';
	char p1SolutionGrid[NUM_ROWS][NUM_COLS];
	char p2SolutionGrid[NUM_ROWS][NUM_COLS];
	char p2GridToShowP1[NUM_ROWS][NUM_COLS];
	string player1 = "Player 1";
	string player2 = "Player 2";
	string outputFileName = "battleship.log";
	ofstream outfile;

	// Opens file
	outfile.open(outputFileName);
	
	// Calls fuction to display welcome msg
	welcomeScreen();

	// Calls function to fill P1 and P2 array
	initializeBoard(p1SolutionGrid, NUM_ROWS, NUM_COLS);
	initializeBoard(p2SolutionGrid, NUM_ROWS, NUM_COLS);
	initializeBoard(p2GridToShowP1, NUM_ROWS, NUM_COLS);

	// Asks user to hit enter to continue
	cout << "\nTo continue press enter...\n";
	cin.get(); 


	// Clearing the screen
	system ("clear");

	// Start of player placing ships
	cout << "Would you like to place your ships randomly or manually? Press \"r\" to place randomly and \"m\" to place manually (Random takes 10 secs to proecess): ";
	cin >> placementType;
	cout << endl;
	
	// If statement to assign ships randomaly or manually
	if(placementType == 'm') {
		
		// Call function to place manually
		manuallyPlaceShipsOnBoard(p1SolutionGrid, shipNames, shipSymbols, shipSizes);
	} else if(placementType == 'r') {
		
		// Call fucntion to place randomly
		randomlyPlaceShipsOnBoard(p1SolutionGrid, shipNames, shipSymbols, shipSizes);
	}

	// Call function to display player 1's board
	cout << "Player 1's Board\n";
	displayBoard(p1SolutionGrid, NUM_ROWS, NUM_COLS);
	
	// Call function to radomly place p2 grid
	randomlyPlaceShipsOnBoard(p2SolutionGrid, shipNames, shipSymbols, shipSizes);
	cout << endl;

	// Check who starts first
	whoStarts = selectWhoStartsFirst();
	cout << endl;

	// If statement for player 1 or player 2 starting first
	if(whoStarts == 0) {

		// While loop to play the game
		while(p1Hits <= 16 && p2Hits <= 16) {

			// Call function to display player 2's grid board
			cout << "Player 2's Board\n";
			displayBoard(p2GridToShowP1, NUM_ROWS, NUM_COLS);

			cout << "Please enter row you would like to fire on: ";
			cin >> row;
			cout << "Please enter col you would like to fire on: ";
			cin >> col;

			// Call function to check coords
			p = checkCoords(p2GridToShowP1, row, col);

			// While loop to check if coords are fixed
			while(p == -1) {
				cout << "Please enter new row you would like to fire on: ";
				cin >> row;
				cout << "Please enter new col you would like to fire on: ";
				cin >> col;
			
				// Call function again to check coords
				p = checkCoords(p2GridToShowP1, row, col);
			}
			
			// Call function to update player 2's board and check shot
			h = p1Hits;
			cout << "Player 1 ";
			logHit = updateBoard(p2SolutionGrid,row, col, p1Hits);
			p1Shots++;
		
			// If statement on whether to mark p2Grid
			if(h < p1Hits) {
				p2GridToShowP1[row][col] = '*';
			} else {
				p2GridToShowP1[row][col] = 'm';
			}

			// Set ints to zero so not to screw up count for p2
			cv2 = 0;
			bb2 = 0;
			ca2 = 0;
			sub2 = 0;
			dd2 = 0;
				
			// Call function to checkships sunk
			checkIfSunkShip(p2SolutionGrid, cv2, bb2, ca2, sub2, dd2);

			// If loop to check if any ships are sunk
			if(cv2 == 0 && cV2) {
				cout << "Player 2's carrier has been sunk!\n";
				cV2 = false;
			} else if(bb2 == 0 && bB2) {
				cout << "Player 2's battleship has been sunk!\n";
				bB2 = false;
			} else if(ca2 == 0 && cA2) {
				cout << "Player 2's crusier has been sunk!\n";
				cA2 = false;
			} else if(sub2 == 0 && suB2) {
				cout << "Player 2's sub as been sunk!\n";
				suB2 = false;
			} else if(dd2 == 0 && dD2) {
				cout << "Player 2's destroyer has been sunk!\n";
				dD2 = false;
			}

			// Call function to output to log
			outputCurrentMove(outfile, logHit, lastValue1, row, col, cv2, bb2, ca2, sub2, dd2, cV22, bB22, cA22, suB22, dD22, player1);
			lastValue1 = logHit;

			// Call function to check winner
			winner = isWinner(p1Hits, p2Hits);

			// If statement on winner
			if(winner == 1) {
				cout << "Congrats Player 1 you won!\n";
				break;
			} else if(winner == 2) {
				cout << "Congrats Player 2 you won!\n";
				break;
			}

			cin.get();
			// Asks user to hit enter to continue
			cout << "\nTo continue press enter...\n";
			cin.get(); 

			// Clear the screen
			system("clear");

			// Call function to display 
			cout << "Player 1's Board\n";			
			displayBoard(p1SolutionGrid, NUM_ROWS, NUM_COLS);
			cout << endl;
			cout << "Player 2's Board\n";
			displayBoard(p2GridToShowP1, NUM_ROWS, NUM_COLS);

			// Rand numbers to guess that 
			row = rand() % 10;
			col = rand() % 10; 

			// Call function to check coords
			p = checkCoords(p1SolutionGrid, row, col);

			// While loop to check if coords are fixed
			while(p == -1) {
				row = rand() % 10;
				col = rand() % 10;

				// Call function again to check coords
				p = checkCoords(p1SolutionGrid, row, col);
			}

			// Call function to update player 1's board and check shot
			cout << "Player 2 ";
			logHit = updateBoard(p1SolutionGrid,row, col, p2Hits);
			cout << endl;
			p2Shots++;

			// Set ints to zero so not to screw up count for p1
			cv1 = 0;
			bb1 = 0;
			ca1 = 0;
			sub1 = 0;
			dd1 = 0;
				
			// Call function to checkships sunk
			checkIfSunkShip(p1SolutionGrid, cv1, bb1, ca1, sub1, dd1);
	
			// If loop to check if any ships are sunk
			if(cv1 == 0 && cV1) {
				cout << "Player 1's carrier has been sunk!\n";
				cV1 = false;
			} else if(bb1 == 0 && bB1) {
				cout << "Player 1's battleship has been sunk!\n";
				bB1 = false;
			} else if(ca1 == 0 && cA1) {
				cout << "Player 1's crusier has been sunk!\n";
				cA1 = false;
			} else if(sub1 == 0 && suB1) {
				cout << "Player 1's sub as been sunk!\n";
				suB1 = false;
			} else if(dd1 == 0 && dD1) {
				cout << "Player 1's destroyer has been sunk!\n";
				dD1 = false;
			}

			// Call function to output to log
			outputCurrentMove(outfile, logHit, lastValue2, row, col, cv1, bb1, ca1, sub1, dd1, cV11, bB11, cA11, suB11, dD11, player2);
			lastValue2 = logHit;			

			// Call function to check winner
			winner = isWinner(p1Hits, p2Hits);

			// If statement on winner
			if(winner == 1) {
				cout << "Congrats Player 1 you won!\n";
				break;
			} else if(winner == 2) {
				cout << "Congrats Player 2 you won!\n";
				break;
			}

			// Asks user to hit enter to continue
			cout << "\nTo continue press enter...\n";
			cin.get(); 

			// Clear the screen
			system("clear");
			
		} // End of while loop
	} else if(whoStarts == 1) {

		// While loop to play the game
		while(p1Hits <= 16 && p2Hits <= 16) {

			// Call function to display 
			cout << "Player 1's Board\n";			
			displayBoard(p1SolutionGrid, NUM_ROWS, NUM_COLS);
			cout << endl;
			cout << "Player 2's Board\n";
			displayBoard(p2GridToShowP1, NUM_ROWS, NUM_COLS);

			// Rand numbers to guess that 
			row = rand() % 10;
			col = rand() % 10; 

			// Call function to check coords
			p = checkCoords(p1SolutionGrid, row, col);

			// While loop to check if coords are fixed
			while(p == -1) {
				row = rand() % 10;
				col = rand() % 10;

				// Call function again to check coords
				p = checkCoords(p1SolutionGrid, row, col);
			}
				
			// Call function to update player 1's board and check shot
			cout << "Player 2 ";
			logHit = updateBoard(p1SolutionGrid,row, col, p2Hits);
			cout << endl;
			p2Shots++;

			// Set ints to zero so not to screw up count for p1
			cv1 = 0;
			bb1 = 0;
			ca1 = 0;
			sub1 = 0;
			dd1 = 0;
				
			// Call function to checkships sunk
			checkIfSunkShip(p1SolutionGrid, cv1, bb1, ca1, sub1, dd1);
	
			// If loop to check if any ships are sunk
			if(cv1 == 0 && cV1) {
				cout << "Player 1's carrier has been sunk!\n";
				cV1 = false;
			} else if(bb1 == 0 && bB1) {
				cout << "Player 1's battleship has been sunk!\n";
				bB1 = false;
			} else if(ca1 == 0 && cA1) {
				cout << "Player 1's crusier has been sunk!\n";
				cA1 = false;
			} else if(sub1 == 0 && suB1) {
				cout << "Player 1's sub as been sunk!\n";
				suB1 = false;
			} else if(dd1 == 0 && dD1) {
				cout << "Player 1's destroyer has been sunk!\n";
				dD1 = false;
			}

			// Call function to output to log
			outputCurrentMove(outfile, logHit, lastValue2, row, col, cv1, bb1, ca1, sub1, dd1, cV11, bB11, cA11, suB11, dD11, player2);
			lastValue2 = logHit;			

			// Call function to check winner
			winner = isWinner(p1Hits, p2Hits);

			// If statement on winner
			if(winner == 1) {
				cout << "Congrats Player 1 you won!\n";
				break;
			} else if(winner == 2) {
				cout << "Congrats Player 2 you won!\n";
				break;
			}

			// If statement so this get only pops up on first run through
			if(run == 0) {			
				cin.get();
			}

			// Asks user to hit enter to continue
			cout << "To continue press enter...\n";
			cin.get(); 

			// Clear the screen
			system("clear");

			// Call function to display player 2's grid board
			cout << "Player 2's Board\n";
			displayBoard(p2GridToShowP1, NUM_ROWS, NUM_COLS);

			cout << "Please enter row you would like to fire on: ";
			cin >> row;
			cout << "Please enter col you would like to fire on: ";
			cin >> col;

			// Call function to check coords
			p = checkCoords(p2GridToShowP1, row, col);

			// While loop to check if coords are fixed
			while(p == -1) {
				cout << "Please enter new row you would like to fire on: ";
				cin >> row;
				cout << "Please enter new col you would like to fire on: ";
				cin >> col;
			
				// Call function again to check coords
				p = checkCoords(p2GridToShowP1, row, col);
			}
			
			// Call function to update player 2's board and check shot
			h = p1Hits;
			cout << "Player 1 ";
			logHit = updateBoard(p2SolutionGrid,row, col, p1Hits);
			p1Shots++;
		
			// If statement on whether to mark p2Grid
			if(h < p1Hits) {
				p2GridToShowP1[row][col] = '*';
			} else {
				p2GridToShowP1[row][col] = 'm';
			}

			// Set ints to zero so not to screw up count for p2
			cv2 = 0;
			bb2 = 0;
			ca2 = 0;
			sub2 = 0;
			dd2 = 0;
				
			// Call function to checkships sunk
			checkIfSunkShip(p2SolutionGrid, cv2, bb2, ca2, sub2, dd2);

			// If loop to check if any ships are sunk
			if(cv2 == 0 && cV2) {
				cout << "Player 2's carrier has been sunk!\n";
				cV2 = false;
			} else if(bb2 == 0 && bB2) {
				cout << "Player 2's battleship has been sunk!\n";
				bB2 = false;
			} else if(ca2 == 0 && cA2) {
				cout << "Player 2's crusier has been sunk!\n";
				cA2 = false;
			} else if(sub2 == 0 && suB2) {
				cout << "Player 2's sub as been sunk!\n";
				suB2 = false;
			} else if(dd2 == 0 && dD2) {
				cout << "Player 2's destroyer has been sunk!\n";
				dD2 = false;
			}

			// Call function to output to log
			outputCurrentMove(outfile, logHit, lastValue1, row, col, cv2, bb2, ca2, sub2, dd2, cV22, bB22, cA22, suB22, dD22, player1);
			lastValue1 = logHit;

			// Call function to check winner
			winner = isWinner(p1Hits, p2Hits);

			// If statement on winner
			if(winner == 1) {
				cout << "Congrats Player 1 you won!\n";
				break;
			} else if(winner == 2) {
				cout << "Congrats Player 2 you won!\n";
				break;
			}

			cin.get();
			// Asks user to hit enter to continue
			cout << "\nTo continue press enter...\n";
			cin.get(); 

			// Clear the screen
			system("clear");

			run++;
		}
	}
	
	cout << "Writing stats to battleship.log file\n";
	
	// Call function output stats to log	
	outputStats(outfile, p1Shots, p2Shots, p1Hits, p2Hits, winner);
		
	cout << "Closing file\n";		
	outfile.close();
	
	return 0;
}
