/*--- Magic square ------------------------------------------
  Program to check if a n * n matrix is a magic square and to 
  generate an odd magic square. 

  Created by Pavel Saladkou, January 2019
 ----------------------------------------------------------*/
#include <iostream>
#include <iomanip>

using namespace std;

const int NUM_ROWS = 15;
const int NUM_COLS = 15;

typedef int TwoDimArray[NUM_ROWS][NUM_COLS];

/*--------------------------------------------------------
  Output n * n matrix where n <= 15. 

  Precondition:  number of rows and columns (0 < n <= 15).
  Postcondition: n * n matrix is printed. 
 -------------------------------------------------------*/
void printTable(int rows, int cols, TwoDimArray);
/*--------------------------------------------------------------------------
  Check if n * n matrix is a magic square.

  Precondition:  Number of rows and columns (0 < n <= 15), matrix to output.
  Postcondition: the message stating whether the matrix is a magic square
				 and its magic sum if it is.
 -------------------------------------------------------------------------*/
void isMagic(int rows, int cols, TwoDimArray);
/*------------------------------------------------------------
  Generate an odd n * n magic square.

  Precondition:  number of rows and columns (0 < n <= 15).
  Postcondition: odd magic square n * n is generated.
 -----------------------------------------------------------*/
void squareConstructor(int n, TwoDimArray);

int main() {
	TwoDimArray aTable;
	int rows,
		cols;
	cout << "Hello! This program will let you check if the matrix you "
		<< "put in is a magic square. Please, be aware that you'll need to fill the matrix n*n with elements. If you " 
		<< "decide to go for 15*15 it'll be 225 elements." << endl;
	cout << "\nPlease, enter the number of rows (greater than 0 and up to 15): ";
	cin >> rows;
	while (rows > 15 || rows <= 0) {
		cout << "The number of rows is a non-negative integer not greater then 15. "
			<< " Please, try again: ";
		cin >> rows;
	}
	cols = rows; //let it be n*n square
	cout << "\n" << "We matched the number of rows you entered with the number of columns and now have \n"
		 << rows << " by " << cols << " matrix. Let's fill it with elements. " << "\n\n";

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++) {
			cout << "Enter the element [" << i << ", " << j << "]: ";
			cin >> aTable[i][j];
		}

	cout << "\nThe matrix you entered looks like this: \n\n" ;
	printTable(rows, cols, aTable);
	cout << "\n";
	isMagic(rows, cols, aTable);
	cout << "\n";

	cout << "Let's generate a magic square automatically. Enter the number of rows (odd integer from 3 to 15): ";
	TwoDimArray magic = {}; //initialize matrix to all 0
	cin >> rows; 
	while (rows % 2 == 0 || rows > 15) {
		cout << "!*** This algorithm works only for odd numbers. ***! "
			<< "\n" << "Please, enter odd number from 3 to 15: ";
		cin >> rows;
	}
	cols = rows; //let it be n*n square
	cout << "\n" << "We matched the number of rows you entered with the number of columns and now have \n" 
		 << rows << " by " << cols << " matrix which looks as follows: \n\n";
	squareConstructor(rows, magic);
	printTable(rows, cols, magic);
	cout << "\n";
	isMagic(rows, cols, magic);
	cout << "\n";

	system("pause");
}

/*--------------------------------------------------------
  Output n * n matrix where n <= 15.

  Precondition:  number of rows and columns (0 < n <= 15).
  Postcondition: n * n matrix is printed.
 -------------------------------------------------------*/
void printTable(int rows, int cols, TwoDimArray arr) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
			cout << setw(4) << arr[i][j];
		cout << "\n";
	}
}

/*--------------------------------------------------------------------------
  Check if n * n matrix is a magic square.

  Precondition:  Number of rows and columns (0 < n <= 15), matrix to output.
  Postcondition: the message stating whether the matrix is a magic square 
				 and its magic sum if it is.
 -------------------------------------------------------------------------*/
void isMagic(int rows, int cols, TwoDimArray arr) {
	int checkSum = 0; //the sum of the first row 
	int sum;

	//calculate the sum of the first row
	for (int j = 0; j < cols; j++)
		checkSum += arr[0][j];

	//check if the sum of each remaining row is the same as the first row (checksum)
	for (int i = 1; i < rows; i++) {
		sum = 0; //reset
		for (int j = 0; j < cols; j++)
			sum += arr[i][j];
		if (sum != checkSum) {
			cout << "This matrix is not a magic square." << endl;
			return; //stop execution
		}
			
	}

	//check if the sum of each column is the same as the first row
	for (int j = 0; j < cols; j++) {
		sum = 0; //reset
		for (int i = 0; i < rows; i++)
			sum += arr[i][j];
		if (sum != checkSum) {
			cout << "This matrix is not a magic square." << endl;
			return; //stop execution
		}
	}

	//check if the sum of main diagonal is the same as the first row
	sum = 0; //reset
	for (int i = 0; i < rows; i++) {
		sum += arr[i][i];
	}
	if (sum != checkSum) {
		cout << "This matrix is not a magic square." << endl;
		return; //stop execution
	}

	//check if the sum of counterdiagonal is the same as the first row
	sum = 0; //reset
	for (int i = 0; i < rows; i++)
		sum += arr[i][rows - i - 1]; 
	if (sum != checkSum) {
		cout << "This matrix is not a magic square." << endl;
		return; //stop execution
	}

	//if all conditions are met
	cout << "This matrix is a magic square. It's magic sum is " << checkSum << "." << endl;
}
/*------------------------------------------------------------
  Generate an odd n * n magic square.

  Precondition:  number of rows and columns (0 < n <= 15).
  Postcondition: odd magic square n * n is generated.
 -----------------------------------------------------------*/
void squareConstructor(int n, TwoDimArray arr) {
	int row = 0, //start at the first row
		col = n/2; //start at the center column
	
	for (int i = 1; i <= n*n; i++) {
		arr[row][col] = i;  //start from 1
		row--;
		col++;

		//handle upper right corner out of range
		if (row < 0 && col >= n) {
			row += 2;
			col--;
		}
		//handle top row out of range
		else if (row < 0)
			row = n - 1;
		//handle right column out of range
		else if (col > n - 1)
			col = 0;
		//handle already filled position
		else if (arr[row][col] != 0) {
			row += 2;
			col --;
		}
	}
}