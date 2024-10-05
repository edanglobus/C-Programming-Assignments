#include "defines.h"
#include "helpers.h"
#include "Q1.h"
#include "Q2.h"
#include "Q3.h"
#include "Q4.h"


chessPosList* findKnightPathCoveringAllBoard(pathTree* pathTree) {                         //Finding paths covering all board
	chessPosList* lst = (chessPosList*)malloc(sizeof(chessPosList));                       // Allocate memory for the chess position list
	int lvl = 0;
	makeEmptyChessList(lst);
	treeNode* root = pathTree->root;                                                       // Get the root node of the path tree
	findLongPath(root, &lvl, lst);                                                         // Find a long path starting from the root node
	if (lst->head == NULL) {                                                            // If no path was found, print a message and return the empty list
		printf("No knight's tour");
		return lst;
	}
	else {
		insertDataToStartChessList(lst, root->position);                                 // Insert the starting position of the knight to the list     
	}
	return lst;
}

void findLongPath(treeNode* root, int* lvl, chessPosList* lst) {                      // a recursively function that helps us to find paths that covering all board
	bool found = false;                                                               // Flag to indicate if the path of maximum length is found
	if (root == NULL) {                                                            // If root node is NULL, decrement the level and return
		(*lvl)--;
		return;
	}
	else {
		treeNodeListCell* currCell = root->next_possible_positions.head;                    // Pointer to traverse through the list of possible next positions
		while (currCell != NULL && found == false)
		{
			if ((*lvl) == MAX_PATH) {                                                         // If maximum path length (MAX_PATH) is reached, insert current position into the list and mark path found
				insertDataToStartChessList(lst, currCell->node->position);
				found == true;
				return;
			}
			else {
				(*lvl)++;
				findLongPath(currCell->node, lvl, lst);                                       // Recursively search for the next position in the path
				if ((*lvl) != MAX_PATH) {                                                     // If maximum path length is not reached, move to the next possible position
					currCell = currCell->next;
					(*lvl)--;
				}
			}
		}
		return;
	}
}


