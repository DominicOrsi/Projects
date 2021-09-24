/*
Name: Dominic Orsi
Class: CPCS 121, Fall 2020
Date: November 20, 2020
Notes: Header File
*/
#ifndef BATTLESHIP_H
#define BattleShip_H


#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

// Const Nums
const int NUM_ROWS = 10;
const int NUM_COLS = 10;

// Const Arrays
const string shipNames[] = {"carrier", "battleship", "cruiser", "submarine", "destroyer"};
const char shipSymbols[] = {'c', 'b', 'r', 's', 'd'};
const int shipSizes[] = {5, 4, 3, 3, 2};

// Function Prototypes
void initializeBoard(char[NUM_ROWS][NUM_COLS], int rows, int cols);
void displayBoard(const char[NUM_ROWS][NUM_COLS], int rows, int cols);
void welcomeScreen(); 
int selectWhoStartsFirst();
void manuallyPlaceShipsOnBoard(char grid[NUM_ROWS][NUM_COLS], const string shipNames[], const char shipSymbols[], const int shipSizes[]);
void randomlyPlaceShipsOnBoard(char grid[NUM_ROWS][NUM_COLS], const string shipNames[], const char shipSymbols[], const int shipSizes[]);
char getDirection();
int checkShipPlacement(char grid[NUM_ROWS][NUM_COLS], int row, int col, int i, char direction, const int shipSizes[]);
void checkRowOrColIsValid(char direction, int& row, int& col, int i, const int shipSizes[]);
int checkShot(char grid[NUM_ROWS][NUM_COLS], int row, int col);
int checkShotGrid(char grid[NUM_ROWS][NUM_COLS], int row, int col);
int isWinner(int p1Hits, int p2Hits);
int updateBoard(char grid[NUM_ROWS][NUM_COLS], int row, int col, int& pHits);
void updateBoardGrid(char grid[NUM_ROWS][NUM_COLS], char grid2[NUM_ROWS][NUM_COLS], int row, int col, int pHits);
void checkIfSunkShip(char arr[NUM_ROWS][NUM_COLS], int& cv, int& bb, int& ca, int& sub, int& dd);
int checkCoords(char grid[NUM_ROWS][NUM_COLS], int row, int col);
void outputCurrentMove(ofstream& outfile, int logHit, int lastValue, int row, int col, int cv, int bb, int ca, int sub, int dd, bool& cV, bool& bB, bool& cA, bool& suB, bool& dD, string player);
void outputStats(ofstream& outfile, int p1Shots, int p2Shots, int p1Hits, int p2Hits, int winner);

#endif
