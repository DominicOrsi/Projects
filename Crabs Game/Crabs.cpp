/*
Name: Dominic Orsi
Class CPCS 121, Fall 2020
Date: October 13, 2020
Description: Runs the game crabs. Was one of the first programs I made in C++.
*/
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main () {
	int dice1 = 0;
	int dice2 = 0;
	int point = 0;
	int i = 0;
	int pointCheck = 0;
	double bankBalance = 0.0;
	double initialWager = 0.0;
	double wagerRoll = 0.0;
	char gamePlay = 'n';

	srand(time(0));
	// Introduction and Rules
	cout << "Welcome to the game, Crabs. The rules are as follows...\n";
	cout << "Two dice are rolled that each have 6 sides and the numbers 1-6.\nThe top face of each die is read and then the total is your number.\nIf your total is 7 or 11 on your first role you win.\nIf your total is 2, 3, or 12 on your first roll you lose (called \"craps\") and the house wins.\nIf the sum is 4, 5, 6, 8, 9, or 10 on the first throw, then the sum becomes the player's \"point.\"\nTo win, you must continue rolling the dice until you \"make your point.\"\nYou lose by rolling a 7 before rolling your point.\n";

	// Asks to hit enter to move on
	cout << "\nTo continue press enter...\n";
	cin.get(); 
	
	// Asks for players bank balance
	cout << "Please enter a bank balance: $";
	cin	>> bankBalance;
	
	// While loop for bank balance, checks if valid
	while(cin.fail()) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Invalid input detected, please enter a valid bank balance: $";
		cin >> bankBalance;
	}
	
	// Gameplay check
	cout << "Do play enter \"Y\": ";
	cin >> gamePlay;
	cout << endl;
	
	// Loop for playing
	while(bankBalance > 0 && gamePlay == 'Y') {
		cout << "Bank balance: $" << bankBalance << endl;
		cout << "Enter initial wager: $";
		cin >> initialWager;
			
		// Loop to check wager
		while(initialWager > bankBalance || cin.fail()) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Invaild wager, please enter a vaild initial wager: $";
			cin >> initialWager;
		}
		
		// Dice rolling
		dice1 = (rand () % (6 - 1 + 1)) + 1;
		dice2 = (rand () % (6 - 1 + 1)) + 1;
		point = dice1 + dice2;
		cout << "Sum: " << point << " (die 1: " << dice1 << " die 2: " << dice2 << ")\n";
		
		// If else check for points
		// Checks for winning points
		if(point == 7 || point == 11) {
			cout << "Congratulations, you won!\n";
			bankBalance += initialWager;
			initialWager = 0;
			
			// Gameplay check
			cout << "To play enter \"Y\": ";
			cin >> gamePlay;
			cout << endl;
		// Checks for losing points
		}else if(point == 2 || point == 3 || point == 12) {
			cout << "Craps, you lost!\n";
			bankBalance -= initialWager;
			initialWager = 0;
	
			// Gameplay check
			cout << "To play enter \"Y\": ";
			cin >> gamePlay;
			cout << endl;
		// Continuation points
		} else {
			cout << "You need to continue rolling to make your point (" << point << ").\n";
			pointCheck = point;
			point = 0;			
			
			// Enter to move on
			cout << "To continue press enter...\n";
			cin.ignore(256, '\n');
			cin.get();
		}	
			
		// While loop to make point or lose
		while(point != pointCheck || point != 7) {
			cout << "Total wager so far $" << initialWager << endl;
			cout << "Your total bank balance is: $" << bankBalance << endl;
		
			// Ask for new wager
			cout << "Please enter your wager: $";
			cin >> wagerRoll;
			initialWager += wagerRoll;
		
			// Check of wagerRoll
			while(initialWager > bankBalance || cin.fail()) {
				cin.clear();
				cin.ignore(256, '\n');
				initialWager -= wagerRoll;
				cout << "Invalid input, please enter a vaild wager: $";
				cin >> wagerRoll;
				initialWager += wagerRoll;
			}
	
			// Roll dice
			dice1 = (rand () % (6 - 1 + 1)) + 1;
			dice2 = (rand () % (6 - 1 + 1)) + 1;
			point = dice1 + dice2;
			cout << "Sum: " << point << " (die 1: " << dice1 << " die 2: " << dice2 << ")\n";
			cout << "To make your point you need to roll (" << pointCheck << ").\n";
			
			// Point check
			if(point == pointCheck) {
				cout << "Congratulations you made your point and won!\n";
				bankBalance += initialWager;
				initialWager = 0;
				
				// Gameplay check
				cout << "To play enter \"Y\": ";
				cin >> gamePlay;
				cout << endl;
				break;
			} else if(point == 7) {
				cout << "Craps, you lost!\n";
				bankBalance -= initialWager;
				initialWager = 0;

				// Gameplay check
				cout << "To play enter \"Y\": ";
				cin >> gamePlay;
				cout << endl;
				break;
			} else {
				// Enter to move on
				cout << "To continue press enter...\n";
				cin.ignore(256, '\n');
				cin.get();
			}
		}
	}

	return 0;
}
