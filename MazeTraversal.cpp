/*
Maze Traversal
Author: Vedhas Walke
Description: Given ANY 12x12 array of characters(that form a maze), traverse through 
			 from the left to the right side. Display the maze in every move.
*/
#include <iostream>
#include <vector>
using namespace std;



// Global Variables

	char board[12][12];
	vector<int> current; // [y,x]
	vector<int> last = {0,0};
	vector<vector<int>> history;
	vector<vector<int>> branchList;
	vector<vector<int>> starlist; //v vector to store open areas


// Important Functions

//$$$$$$$$$$$$$$$
bool IsValid(int x, int y) {
		// Checking for 1) valid dimension
		//              2) nonrepeating dimension
		//				3) has not been visited historically
		//				4) is an open location (star = '*')
		


		// 2)
		bool SameAsLast = 0;
		if (x == last[1] && y == last[0])
		SameAsLast = true;

		// 3)
		bool historical = 0;
		for (int i = 0; i < history.size(); i++) {
			if (x == history[i][1] && y == history[i][0])
				historical = 1;
		}

		if (x >= 0 && x < 12 && y < 12 && y >= 0 && !SameAsLast && !historical && board[x][y] == '*')
			return true;
		return false;
	}

void PrintBoard() {
	for (int i = 0; i < 100; i++)
		cout << "\n";

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			if(current[1] != i || current[0] != j)
				cout << board[i][j];
			else
				cout << "X";
		}
		cout << "\n";
	}

}


void Move(int x, int y) {
	bool currentSet = false;
	if (IsValid(x, y + 1)) {
			history.push_back(last);
			last = current;
			current = { y+1, x };
			currentSet = true;
	}


	if (IsValid(x, y - 1)) {
		if (!currentSet) {
			history.push_back(last);
			last = current;
			current = { y-1, x };
			currentSet = true;
		}else{
			vector<int> coor = {y-1,x};
			branchList.push_back(coor);
		}
	}

	if (IsValid(x+1, y)) {
		if (!currentSet) {
			history.push_back(last);
			last = current;
			current = { y, x+1 };
			currentSet = true;
		} else {
		vector<int> coor = { y,x+1 };
		branchList.push_back(coor);
	}
	}


	if (IsValid(x - 1, y)) {
		if (!currentSet) {
			history.push_back(last);
			last = current;
			current = { y, x-1 };
			currentSet = true;
		}
		else {
			vector<int> coor = { y,x - 1 };
			branchList.push_back(coor);
		}
	}


	if (!currentSet) {
		if (branchList.size() != 0) {
			current = branchList.back();
			branchList.pop_back();
		}
		else {
			cout << "\nUnsolvable";
		}
	}
		
}



int main() {

	for (int i = 0; i < 12; i++) //s Inputting Board
	{
		for (int j = 0; j < 12; j++) {
			cin >> board[i][j];
		}
	}

	
	
	for (int i = 0; i < 12; i++) //s Creating List of Open Areas
	{
		for (int j = 0; j < 12; j++) {
			if (board[i][j] == '*') {
				vector<int> coor = { j, i };
				starlist.push_back(coor);
			}

		}
	}

	
	for (int i = 0; i < starlist.size(); i++) // Finding all possible starting points
	{
		if (starlist[i][0] == 11) {
			vector<int> coor = {11, starlist[i][1]};
			branchList.push_back(coor);
		}
	}

	current = branchList.back();
	branchList.pop_back();

	//$$$$$$$$$$$$$$$$
	while (current[0] != 0) {
		int x = current[1];
		int y = current[0];
		Move(x, y);
		PrintBoard();
		cout << "Current: " << current[1] << " " << current[0] << '\n';
		char trash;
		cin.get(trash);
	}
	
	cout << "\nSolved.";

	return 0;
}


