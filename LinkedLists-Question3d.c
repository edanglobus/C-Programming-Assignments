#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


typedef struct XlistNode {
	int x_value;
	struct XlistNode* prevX;
	struct XlistNode* nextX;
	struct YList* valuesY;
} XListNode;
typedef struct YlistNode {
	int y_value;
	struct YlistNode* nextY;
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
int insertCoordinate(List* coordList, int x, int y);
void freeList(List* coordList);
void printCoord(List lst);



void main()

{

	List coordList;

	int x, y;

	int res;

	coordList = getCoordList();

	// get the (x,y) to insert

	scanf("%d%d", &x, &y);



	res = insertCoordinate(&coordList, x, y);

	if (res == 0)

		printf("The point (%d,%d) didn't appear\n", x, y);

	else

		printf("The point (%d,%d) already appeared\n", x, y);

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
		Ynode->nextY = NULL;
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
int insertCoordinate(List* coordList, int x, int y) {
	XListNode* currentX = coordList->head;
	int counter = 0;

	while (currentX->nextX != NULL && currentX->x_value != x) {
		currentX = currentX->nextX;
	}

	if (currentX->nextX != NULL || currentX->x_value == x) 
	{
		bool foundXY = false;
		YList* lstY = currentX->valuesY;
		YListNode* currentY = lstY->head;
		YListNode* saverY = NULL;
		while (currentY->nextY != NULL && foundXY == false) {
			if (currentY->y_value == y) {
				saverY = currentY;
				foundXY = true;
			}
			currentY = currentY->nextY->; ///////////
		}
		if (currentY->y_value == y) {
			saverY = currentY;
			foundXY = true;
		}

		if (foundXY == true) {
			YListNode* Ynode = (YListNode*)malloc(sizeof(YListNode));
			checkAllocation(Ynode);
			Ynode->y_value = y;

			Ynode->nextY = saverY->nextY;
			saverY->nextY = Ynode;

			if (Ynode == NULL) {
				lstY->tail = Ynode;
			}
			return 1;
		}
		else {
			YListNode* Ynode = (YListNode*)malloc(sizeof(YListNode));
			checkAllocation(Ynode);
			Ynode->y_value = y;

			lstY->tail->nextY = Ynode;
			lstY->tail = Ynode;
			Ynode->nextY = NULL;
			return 0;
		}
	}
	
	XListNode* Xnode = (XListNode*)malloc(sizeof(XListNode));
	checkAllocation(Xnode);
	Xnode->x_value = x;

	YListNode* Ynode = (YListNode*)malloc(sizeof(YListNode));
	checkAllocation(Ynode);
	Ynode->y_value = y;

	YList* lst_y = (YList*)malloc(sizeof(YList)); // creating y list 
	checkAllocation(lst_y);
	lst_y->head = Ynode;// connect first node
	lst_y->tail = Ynode;

	Xnode->valuesY = lst_y; // connect X to Y
	insertToEndXnode(coordList, Xnode);
	return 0;

	///////////// need to insert it sorted
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

