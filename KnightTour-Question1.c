#include "defines.h"
#include "helpers.h"
#include "Q1.h"
#include "Q2.h"
#include "Q3.h"
#include "Q4.h"


chessPosArray*** validKnightMoves() {

	chessPosArray*** pointToColum = (chessPosArray***)malloc(SIZE_BOARD * sizeof(chessPosArray**));
	checkAllocation(pointToColum);

	for (int i = 0; i < SIZE_BOARD; i++) {                                                                   // Allocate memory for each column in the chessboard
		pointToColum[i] = (chessPosArray**)malloc(SIZE_BOARD * sizeof(chessPosArray*));
		checkAllocation(pointToColum[i]);
	}

	int posCount = 0;
	for (int i = 0; i < SIZE_BOARD; i++) {                                                                    // Iterate through each cell in the chessboard

		for (int j = 0; j < SIZE_BOARD; j++) {                                                                // Allocate memory for each chessPosArray (knight moves from this position)             
			pointToColum[i][j] = (chessPosArray*)malloc(sizeof(chessPosArray));
			checkAllocation(pointToColum[i][j]);

			int posCount = posCounter(j, i);                                                                 // Calculate the number of possible knight moves from position (j, i)
			pointToColum[i][j]->size = posCount;
			pointToColum[i][j]->positions = posOptions(j, i, posCount);
		}
	}
	return pointToColum;                                                                                     // Return the 3D array of knight moves
}

int posCounter(int iletter, int number) {                                       // count possible positions                                                                     
	char letter = MIN_LETTER + iletter;
	number = number + ONE_STEP;
	int counter = 0;

	if (number + TWO_STEP <= SIZE_BOARD) {
		if (letter - ONE_STEP >= MIN_LETTER) counter++;
		if (letter + ONE_STEP <= MAX_LETTER) counter++;
	}
	if (number - TWO_STEP >= MIN_NUMBER) {
		if (letter - ONE_STEP >= MIN_LETTER) counter++;
		if (letter + ONE_STEP <= MAX_LETTER) counter++;
	}
	if (letter + TWO_STEP <= MAX_LETTER) {
		if (number - ONE_STEP >= MIN_NUMBER) counter++;
		if (number + ONE_STEP <= SIZE_BOARD) counter++;
	}
	if (letter - TWO_STEP >= MIN_LETTER) {
		if (number - ONE_STEP >= ONE_STEP) counter++;
		if (number + ONE_STEP <= SIZE_BOARD) counter++;
	}
	return counter;
}

int insertJumpOption(chessPos** posOptionsArr, char letter, int number, int numPos) {                             // Extract the array of chess positions from the pointer to the pointer
	int fullPos = 0;
	chessPos* array = *posOptionsArr;

	array[numPos][fullPos] = letter;
	fullPos++;
	array[numPos][fullPos] = number + '0';
	numPos++;

	return numPos;
}

chessPos* posOptions(int iletter, int number, int posCount) {          // function allocate memory for an array size posCount and insert all the vailed knight moves
	char letter = MIN_LETTER + iletter;
	number = number + ONE_STEP;        // index that run between (0-1) to insert each char (A-E) and each num (1-5)
	int numPos = 0;     // index runs from 0 to posCount to make sure each move is in the right position in the array 

	chessPos* posOptionsArr = (chessPos*)malloc(posCount * sizeof(chessPos));
	checkAllocation(posOptionsArr);

	if (letter - TWO_STEP >= MIN_LETTER) {
		if (number + ONE_STEP <= SIZE_BOARD) numPos = insertJumpOption(&posOptionsArr, letter - TWO_STEP, number + ONE_STEP, numPos);
	}
	if (number + TWO_STEP <= SIZE_BOARD) {
		if (letter - ONE_STEP >= MIN_LETTER) numPos = insertJumpOption(&posOptionsArr, letter - ONE_STEP, number + TWO_STEP, numPos);
		if (letter + ONE_STEP <= MAX_LETTER) numPos = insertJumpOption(&posOptionsArr, letter + ONE_STEP, number + TWO_STEP, numPos);
	}
	if (letter + TWO_STEP <= MAX_LETTER) {
		if (number + ONE_STEP <= SIZE_BOARD) numPos = insertJumpOption(&posOptionsArr, letter + TWO_STEP, number + ONE_STEP, numPos);
		if (number - ONE_STEP >= MIN_NUMBER) numPos = insertJumpOption(&posOptionsArr, letter + TWO_STEP, number - ONE_STEP, numPos);
	}
	if (number - TWO_STEP >= MIN_NUMBER) {
		if (letter + ONE_STEP <= MAX_LETTER) numPos = insertJumpOption(&posOptionsArr, letter + ONE_STEP, number - TWO_STEP, numPos);
		if (letter - ONE_STEP >= MIN_LETTER) numPos = insertJumpOption(&posOptionsArr, letter - ONE_STEP, number - TWO_STEP, numPos);
	}
	if (letter - TWO_STEP >= MIN_LETTER) {
		if (number - ONE_STEP >= MIN_NUMBER) numPos = insertJumpOption(&posOptionsArr, letter - TWO_STEP, number - ONE_STEP, numPos);
	}

	return posOptionsArr;
}


