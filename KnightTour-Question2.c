#include "defines.h"
#include "helpers.h"
#include "Q1.h"
#include "Q2.h"
#include "Q3.h"
#include "Q4.h"



void display(chessPosList* list)
{
	int chessBoard[SIZE_BOARD][SIZE_BOARD] = { NOT_VISITED_CELL };
	removeDupPos(list, chessBoard);
	markThePlace(list, chessBoard);
}

void removeDupPos(chessPosList* posLst, int chessBoard[SIZE_BOARD][SIZE_BOARD])                 //remove duplicated cells
{
	chessPosCell* curr = posLst->head, * prev = posLst->head, * tmp = NULL;
	int row, col;

	while (curr != NULL) {
		convertToNumber(curr->position, &row, &col);
		chessBoard[row][col]++;

		if (chessBoard[row][col] > VISITED_CELL) {
			deleteCell(&curr, prev);

		}
		else {
			prev = curr;
			curr = curr->next;
		}
	}
}

void markThePlace(chessPosList* lst, int chessBoard[SIZE_BOARD][SIZE_BOARD])                           //mark on the chessboard the steps by the list
{
	chessPosCell* curr = lst->head;
	int numPos = 1;
	int row, col;

	while (curr != NULL) {
		convertToNumber(curr->position, &row, &col);
		chessBoard[row][col] = numPos;
		numPos++;
		curr = curr->next;
	}

	printBoard(chessBoard);
}

void printBoard(int board[][SIZE_BOARD])                                                   //print the chessboard 
{
	int i, j;
	char row = MIN_LETTER;

	printTheNumbers();
	for (i = 0; i < SIZE_BOARD; i++) {
		printf("%c ", row);
		for (j = 0; j < SIZE_BOARD; j++) {
			printf("%2d|", board[i][j]);
		}
		printf("\n");
		row++;
	}
}

void printTheNumbers()                                  //print columns numbers
{
	printf("   1  2  3  4  5\n");
}

void deleteCell(chessPosCell** curr, chessPosCell* prev) {                         //delete cell
	prev->next = (*curr)->next;
	free(*curr);
	*curr = prev->next;  // Move curr to the next node
}
