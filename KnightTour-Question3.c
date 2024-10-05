#include "defines.h"
#include "helpers.h"
#include "Q1.h"
#include "Q2.h"
#include "Q3.h"
#include "Q4.h"


treeNode* createTreeNode(chessPos position)                              //Create new tree node from position
{
	treeNode* node = (treeNode*)malloc(sizeof(treeNode));
	checkAllocation(node);

	node->position[0] = position[0];
	node->position[1] = position[1];
	makeEmptyList(&(node->next_possible_positions));                   //making list for each node
	return node;
}

chessPosArray arrayOfPos(int row, int col)                             //Building position array
{
	chessPosArray structArray;

	int countJumpOptions = posCounter(row, col);
	chessPos* optionArray = posOptions(row, col, countJumpOptions);

	structArray.size = countJumpOptions;
	structArray.positions = optionArray;

	return structArray;
}

treeNodeListCell* createListCell(treeNode* node)                                      // Create new list cell
{
	treeNodeListCell* cell = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	checkAllocation(cell);

	cell->node = node;
	cell->next = NULL;
	return cell;
}

chessPosArray* findPositionKnightMove(chessPos* startingPosition, chessPosArray**** movesBoard) {                     //Finding the array of possible moves for single position
	int row, col;
	convertToNumber(*startingPosition, &row, &col);

	chessPosArray*** knightBoard = validKnightMoves();                                  //Bring the 3D array from Q1 to know the possible moves for each position
	chessPosArray* result = (knightBoard[col][row]);
	*movesBoard = knightBoard;
	return result;
}

pathTree findAllPossibleKnightPaths(chessPos* startingPosition)                             //Building a tree with all possible paths of the starting position
{
	int chessboard[SIZE_BOARD][SIZE_BOARD] = { NOT_VISITED_CELL };
	int row, col;
	chessPosArray*** knightBoard;
	pathTree tree;
	treeNode* rootNode = createTreeNode(*startingPosition);
	chessPosArray* rootMoves = findPositionKnightMove(startingPosition, &knightBoard);
	treeNodeList rootList = buildList(*rootMoves, chessboard);                            //Build list for the root
	rootNode->next_possible_positions = rootList;                                         //Connect the root list to root node
	convertToNumber(*startingPosition, &row, &col);
	chessboard[row][col] = VISITED_CELL;                                                 //Update the chess board that we visited in the root
	findAllPossibleKnightPathsHelper(rootNode, chessboard);
	tree.root = rootNode;                                                                //Connect the root with the tree
	freeMovesArray(knightBoard);
	return tree;
}

treeNodeList buildList(chessPosArray arr, int chessBoard[][SIZE_BOARD])                    //Building list of cells for current position
{
	int row, col;
	treeNode* node;
	treeNodeListCell* cell;
	treeNodeList lst;
	chessPos currentPos;

	makeEmptyList(&lst);
	for (int i = 0; i < arr.size; i++) {                                       //Iterate on the array to insert to the current position list
		currentPos[0] = arr.positions[i][0];
		currentPos[1] = arr.positions[i][1];
		convertToNumber(currentPos, &row, &col);

		if (chessBoard[row][col] == NOT_VISITED_CELL) {                           //If we didn't visited in this cell in the paths insert him to the end
			node = createTreeNode(arr.positions[i]);
			cell = createListCell(node);
			insertCellToEndList(&lst, cell);
		}
	}
	return lst;
}

void findAllPossibleKnightPathsHelper(treeNode* root, int chessboard[][SIZE_BOARD])                   //Helper function that recursively find all the possible path
{
	if (root == NULL)
		return;

	treeNodeListCell* curr = root->next_possible_positions.head;
	chessPosArray currMoves;

	int row, col;

	while (curr != NULL) {                                                                 // Iterate through each position in the list of next possible positions
		convertToNumber(curr->node->position, &row, &col);
		if (chessboard[row][col] == VISITED_CELL)                                           // Check if the current position on the chessboard is already visited
			return;                                                                        // If visited, return to avoid processing further

		chessboard[row][col] = VISITED_CELL;                                               // Mark the current position on the chessboard as visited
		currMoves = arrayOfPos(row, col);                                                 // Generate knight moves from the current position
		curr->node->next_possible_positions = buildList(currMoves, chessboard);           // Build a list of valid next positions from the generated moves
		findAllPossibleKnightPathsHelper(curr->node, chessboard);                          // Recursively explore paths from the current next node
		chessboard[row][col] = NOT_VISITED_CELL;                                               // Unmark the current position on the chessboard after recursive exploration
		curr = curr->next;
	}
}

void freeMovesArray(chessPosArray*** arr)
{
	for (int i = 0; i < SIZE_BOARD; i++) {
		for (int j = 0; j < SIZE_BOARD; j++) {
			free(arr[i][j]->positions);
			free(arr[i][j]);
		}
		free(arr[i]);
	}
	free(arr);
}