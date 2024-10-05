#include "defines.h"
#include "helpers.h"
#include "Q1.h"                                                   
#include "Q2.h"
#include "Q3.h"
#include "Q4.h"

void main() {
	chessPosList* list;
	chessPos possition;


	if (getInput(&possition)) {                                           //Get the input from the user and check if it's valid
		pathTree tree = findAllPossibleKnightPaths(&possition);         // Build the all possible knight paths (Q3)
		list = findKnightPathCoveringAllBoard(&tree);                   //Find knight path that covering all the board (Q4) 
		if (list->head != NULL) {                                       //Check if path was found        
			display(list);                                              //build and print a chess board by the index moves(Q2)
		}
		freeAll(tree, list);                                         //Free the tree and the list
	}
	else {
		printf("Invalid input");
	}
}