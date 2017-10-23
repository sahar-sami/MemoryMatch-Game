//Simple Matching Game

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <Windows.h>
#include <ctime>

#define MyTest

class Card {
private:
	char back;
	char front;
	bool status; // true = matched, false = not matched
public:
	void setFront (char f) {front = f;}
	void setBack (char b) {back = b;}
	char getFront() {return front;}
	char getBack() {return back;}
};

class Game{
private:
	Card board [4][5];
	int turns;
public:
	Game(); // creates and displays original board
	bool turn(int, int, int, int);
	void displayBoard();
	bool isGuessed(int, int);
	void increment(){turns += 1;}
	int getTurns(){return turns;}
};

Game::Game(){
turns = 0;
for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++){board[i][j].setFront('*');}
	}

const char* const nums = "0123456789";
char pairs[10];
for (int i = 0; i < 10; i++)
{
	pairs[i] = nums[i];
}
srand(time(NULL));
random_shuffle(&pairs[0], &pairs[9]);

for (int i = 0; i < 4; i++){
	for (int j = 0; j < 5; j++){
		if (i < 2) {board[i][j].setBack(pairs[j]);}
		else if (i == 2) {board[i][j].setBack(pairs[i + j + 3]);}
		else {board[i][j].setBack(pairs[i+j+2]);}
	}
}
srand(time(NULL));
random_shuffle(&board[0][0], &board[3][4]);

cout << "Welcome to Memory Match! The rules are simple.\nTry to match all of the cards with less than 20 mistakes"
	<< "\nin rows 0-3 and columns 0-4. Good luck!" << endl;

}

bool Game::turn(int i1, int j1, int i2, int j2){ // tests for a match and returns the value of the match
Card a = board[i1][j1];
Card b = board[i2][j2];
cout << "  0 1 2 3 4" << endl;
for (int i = 0; i < 4; i++){
		cout << i;
		for (int j = 0; j < 5; j++)
		{
			cout << setw(2);
			if ((i == i1 && j == j1 )|| (i==i2 && j == j2) )
				{
					cout << board[i][j].getBack();
					if (a.getBack() == b.getBack()) {board[i][j].setFront(a.getBack());}
				}
			else {cout << board[i][j].getFront();}
		}
		cout << endl;
	}
if (a.getBack() == b.getBack()) {
	cout << "Match!" << endl;
	return true;}
else {
	cout << "No match." << endl;
	Sleep(1000);
	system("CLS");
	return false; }
}

void Game::displayBoard() {
	cout << "  0 1 2 3 4" << endl;
	for (int i = 0; i < 4; i++){
		cout << i;
		for (int j = 0; j < 5; j++){
			cout << setw(2) << board[i][j].getFront();
		}
		cout << endl;
	}
}

bool Game::isGuessed(int i, int j) {
	if (board[i][j].getFront() != '*') {return true;}
	else {return false;}
}

int main(){
	Game game;
	game.displayBoard();
	int i1, i2, j1, j2, matchCT = 0, missCT = 0;
	bool match;
do{
	cout << "\nEnter the coordinates of the FIRST card with a space in between (ex. 0 0): ";
	cin >> i1 >> j1;
	while (i1 > 3 || i1 < 0 || j1 > 4 || j1 < 0) {
		cout << "Error: Coordinate is out of bounds, please try again: ";
		cin >> i1 >> j1;
	}
	while (game.isGuessed(i1, j1) == true) {
		cout <<"Error: Please enter a coordinate that hasn't been guessed: ";
		cin >> i1 >> j1;
	}
	cout << "\nEnter the coordinates of the SECOND card with a space in between (ex. 0 0): ";
	cin >> i2 >> j2;
	while (i2 > 3 || i2 < 0 || j2 > 4 || j2 < 0) {
		cout << "Error: Coordinate is out of bounds, please try again: ";
		cin >> i2 >> j2;
	}
	while (i1 == i2 && j1 == j2) {
		cout << "Error: Please enter different coordinates: ";
		cin >> i2 >> j2;
	}
	while (game.isGuessed(i2, j2) == true) {
		cout <<"Error: Please enter a coordinate that hasn't been guessed: ";
		cin >> i2 >> j2;
	}
	match = game.turn(i1, j1, i2, j2);
	if (match == false) {game.displayBoard(); missCT++;}
	else {++matchCT;}
	game.increment();
}while (matchCT < 10 && missCT < 20);
if (matchCT == 10) {cout << "You win! You finished the game in " << game.getTurns() << " turns" << endl
	<< "with " << missCT << " mistakes." << endl;}
else if (missCT == 20) {cout << "20 turns have passed. You lose." << endl;}
	return 0;
}

