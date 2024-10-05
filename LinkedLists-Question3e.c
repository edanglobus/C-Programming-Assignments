#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


typedef struct XlistNode {
	int x_value;
	struct XListNode* prevX;
	struct XListNode* nextX;
	struct YList* valuesY;
} XListNode;
typedef struct YlistNode {
	int y_value;
	struct YListNode* nextY;
} YListNode;
typedef struct Ylist
{
	YListNode* head;
	YListNode* tail;
} YList;
typedef struct list
{
	XListNode* head;
	XListNode* tail;
} List;


void checkAllocation(void* pmalloc);
bool isEmpty(List lst);
void makeEmptyList(List* lst);
void makeEmptyYList(YList* lst);
void insertToEndYnode(YList* lst_y, YListNode* Ynode);
void insertToEndXnode(List* lst_x, XListNode* Xnode);
List getCoordList();
YListNode* getPairOccurrences(List* coordList, int x, int y, int* outputCounter, XListNode** Xappearance);
void freeList(List* coordList);
void printCoord(List lst);



void main()

{


	List coordList;

	int x, y;

	int res;

	coordList = getCoordList();

	// get the (x,y) to remove

	scanf("%d%d", &x, &y);



	res = removeCoordinate(&coordList, x, y);

	if (res == 1)

		printf("The point (%d,%d) didn't appear\n", x, y);

	else if (res == 2)

		printf("The point (%d,%d) has another occurrence\n", x, y);

	else if (res == 3)

		printf("The point (%d,%d) was the only point with this x\n", x, y);

	else

		printf("Other\n");

	printf("Updated list: ");

	printCoord(coordList);

	freeList(&coordList);

}


void checkAllocation(void* pmalloc) {
	if (pmalloc == NULL) {
		printf("Memory allocation failed");
		exit(1);
	}
}
bool isEmpty(List lst) {
	return lst.head == NULL && lst.tail == NULL;
}
void makeEmptyList(List* lst) {
	lst->head = NULL;
	lst->tail = NULL;
}
void makeEmptyYList(YList* lst) {
	lst->head = NULL;
	lst->tail = NULL;
}
void insertToEndYnode(YList* lst_y, YListNode* Ynode) {
	if (lst_y->head == NULL && lst_y->tail == NULL) {
		lst_y->head = Ynode;
		lst_y->tail = Ynode;
	}
	else {
		lst_y->tail->nextY = Ynode;
		lst_y->tail = Ynode;
		Ynode->nextY = NULL;
	}
}
void insertToEndXnode(List* lst_x, XListNode* Xnode) {
	if (lst_x->head == NULL && lst_x->tail == NULL) {
		lst_x->head = Xnode;
		lst_x->tail = Xnode;
		Xnode->prevX = NULL;
	}
	else
	{
		Xnode->prevX = lst_x->tail;
		lst_x->tail->nextX = Xnode;
		lst_x->tail = Xnode;
		Xnode->nextX = NULL;
	}
}
List getCoordList() {
	int size;
	int currentX;
	int currentY;

	List lst;
	makeEmptyList(&lst);

	scanf("%d", &size);

	for (int i = 0; i < size; i++) {
		//maybe an issue here with the double scanf and the loop condition. maybe size*2
		scanf("%d %d", &currentX, &currentY);

		XListNode* Xnode = (XListNode*)malloc(sizeof(XListNode));
		checkAllocation(Xnode);
		Xnode->prevX = NULL;
		Xnode->nextX = NULL;
		Xnode->valuesY = NULL;
		Xnode->x_value = currentX;// put the scan value in x value

		YListNode* Ynode = (YListNode*)malloc(sizeof(YListNode));
		checkAllocation(Ynode);
		Ynode->nextY = NULL;
		Ynode->y_value = currentY; // insert y value to ynode.

		if (isEmpty(lst)) {
			lst.head = Xnode;
			lst.tail = Xnode;

			YList* lst_y = (YList*)malloc(sizeof(YList)); // creating y list 
			checkAllocation(lst_y);
			lst_y->head = Ynode;// connect first node
			lst_y->tail = Ynode;

			Xnode->valuesY = lst_y; // connect X to Y
		}
		else {
			if (currentX == lst.tail->x_value) {
				free(Xnode);
				insertToEndYnode(lst.tail->valuesY, Ynode);
			}
			else {
				YList* lst_y = (YList*)malloc(sizeof(YList)); // creating y list 
				checkAllocation(lst_y);
				makeEmptyYList(lst_y);
				insertToEndYnode(lst_y, Ynode);

				Xnode->valuesY = lst_y; // put y values in X node
				insertToEndXnode(&lst, Xnode); // insert node X to End.
			}

		}

	}
	return lst;
}
YListNode* getPairOccurrences(List* coordList, int x, int y, int* outputCounter, XListNode** Xappearance) {
	XListNode* currentX = coordList->head;
	YListNode* firstAppearance = NULL;
	XListNode* firstAppearanceX = NULL;
	int counter = 0;

	while (currentX->nextX != NULL && currentX->x_value != x) {
		currentX = currentX->nextX;
	}

	if (currentX->x_value != x) {
		return 0;
	}
	else {
		YList* lstY = currentX->valuesY;
		YListNode* currentY = lstY->head;
		while (currentY->nextY != NULL) {
			if (currentY->y_value == y) {
				if (counter == 0) {
					firstAppearanceX = currentX;
					firstAppearance = currentY;
				}
				counter++;
			}
			currentY = currentY->nextY;
		}
		if (currentY->y_value == y) {
			firstAppearanceX = currentX;
			firstAppearance = currentY;
			counter++;
		}
	}
	*outputCounter = counter;
	*Xappearance = firstAppearanceX;
	return firstAppearance;
}
void freeList(List* coordList) {
	XListNode* currentX = coordList->head;
	XListNode* tofreeXnode;
	YListNode* tofreeYnode;

	while (currentX->nextX != NULL) {
		YList* lstY = currentX->valuesY;
		YListNode* currentY = lstY->head;

		while (currentY->nextY != NULL) {
			tofreeYnode = currentY;
			currentY = currentY->nextY;
			free(tofreeYnode);
		}
		free(currentY);
		free(lstY);

		tofreeXnode = currentX;
		currentX = currentX->nextX;
		free(tofreeXnode);
	}

	YList* lstY = currentX->valuesY;
	YListNode* currentY = lstY->head;

	while (currentY->nextY != NULL) {
		tofreeYnode = currentY;
		currentY = currentY->nextY;
		free(tofreeYnode);
	}
	free(currentY);
	free(lstY);

	tofreeXnode = currentX;
	currentX = currentX->nextX;
	free(tofreeXnode);



}
void printCoord(List lst) {
	XListNode* currentX = lst.head;
	YList* lstY = currentX->valuesY;
	YListNode* currentY = lstY->head;

	while (currentX->nextX != NULL) {

		while (currentY->nextY != NULL) {
			printf("(%d,%d), ", currentX->x_value, currentY->y_value);
			currentY = currentY->nextY;
		}
		printf("(%d,%d), ", currentX->x_value, currentY->y_value);
		currentX = currentX->nextX;
		lstY = currentX->valuesY;
		currentY = lstY->head;
	}
	lstY = currentX->valuesY;
	currentY = lstY->head;
	while (currentY->nextY != NULL) {
		printf("(%d,%d) ", currentX->x_value, currentY->y_value);
		currentY = currentY->nextY;
	}
	printf("(%d,%d) ", currentX->x_value, currentY->y_value);
	currentX = currentX->nextX;
}
int removeCoordinate(List* coordList, int x, int y) {
	YListNode* firstYtoDelete;
	XListNode* addresX;
	int pointAppearance = -1;

	firstYtoDelete = getPairOccurrences(coordList, x, y, &pointAppearance, &addresX);
	YList* currentY = NULL;
	YListNode* currentYnode = NULL;
	YListNode* YnodeToFree = NULL;

	if (firstYtoDelete != NULL) {
		currentY = addresX->valuesY;
		currentYnode = currentY->head;
	}




	if (pointAppearance == 0) {
		return 1;
	}
	else if (pointAppearance > 2) {
		while (currentYnode->nextY != firstYtoDelete) {
			currentYnode = currentYnode->nextY;
		}
		currentYnode->nextY = firstYtoDelete->nextY;
		if (currentY->head == firstYtoDelete) {
			currentY->head = currentYnode;
		}
		free(firstYtoDelete);
		return 2;
	}
	else if (pointAppearance == 1 && firstYtoDelete->nextY == NULL && currentY->head == firstYtoDelete)
	{
		free(firstYtoDelete);
		free(currentY);

		if (coordList->head == addresX) {
			coordList->head = addresX->nextX;
			coordList->head->prevX == NULL;
			free(addresX);
		}
		else if (coordList->tail == addresX) {
			coordList->tail = addresX->prevX;
			coordList->tail->nextX == NULL;
			free(addresX);
		}
		else {
			XListNode* stepBackX = addresX->prevX;
			XListNode* forwordX = addresX->nextX;
			stepBackX->nextX = forwordX;
			forwordX->prevX = stepBackX;
			free(addresX);
		}
		return 3;
	}
	else {
		while (currentYnode->nextY != firstYtoDelete) {
			currentYnode = currentYnode->nextY;
		}
		currentYnode->nextY = firstYtoDelete->nextY;
		if (currentY->head == firstYtoDelete) {
			currentY->head = currentYnode;
		}
		free(firstYtoDelete);
		return 0;
	}


}
