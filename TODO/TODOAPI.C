#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "todo.h"

static struct todoItem *list;

void printNode(struct todoItem node) {
	printf("ID:%d Priority:%d Description:%s Completed:%c\n",
			 node.id,
			 node.priority,
			 node.description,
			 node.completed);
	return;
}

struct todoItem * buildNodeComplex(short priority, char *description,
											  int id, char completed) {

	struct todoItem *newItem;

	/* Prepare the new node for insertion into the list */
	newItem = (struct todoItem *) malloc(sizeof(struct todoItem));

	/* newItem->id = rand(); */
	newItem->id = id;
	newItem->priority = priority;
	newItem->description = strdup(description);
	newItem->completed = completed;
	newItem->next = NULL;

	return newItem;
}

struct todoItem * buildNode(short priority, char *description) {
	static int id = 0;
	return buildNodeComplex(priority, description, id++, 'F');
}

int addToDo(short priority, char *description) {
	struct todoItem *newItem, *follow;

	newItem = buildNode(priority, description);

	if(newItem == NULL) {
		return -1;
	}

	/* Empty list, add to beginning */
	if (list == NULL) {
		list = newItem;
	}
	else {

		/* Add to the end of the list think about sorting routines in the
			future*/
		follow = list;
		while(follow->next) {
			follow = follow->next;
		}
		follow->next = newItem;
	}
	return newItem->id;
}

int deleteToDo(short id) {
	removeToDo(id);
}

int removeToDo(short id) {
    struct todoItem *follow = list;
    struct todoItem *prev = NULL;

    while (follow) {
        if (follow->id == id) {
            if (prev == NULL) {
					 /* Deleting the head node */
                list = follow->next;
            } else {
                prev->next = follow->next;
            }
            free(follow->description);
            free(follow);
            return id;
        }
        prev = follow;
        follow = follow->next;
    }
    return -2;
}

struct todoItem returnItem(int id) {
	struct todoItem *follow;
	struct todoItem copy;

	copy.id = -1;


	follow = list;

	while (follow) {
		if (follow->id == id) {
			copy.id = follow->id;
			copy.priority = follow->priority;
			strcpy(copy.description, follow->description);
			copy.completed = follow->completed;
			return copy;
		}
		follow = follow->next;
	}

	return copy;
}

void init() {
	struct todoItem *follow, *prev;

	/* Clear out the list if it exists */
	if (list) {
	  follow = list;
	  while(follow) {
		  prev = follow;
		  follow = follow->next;
		  free(prev);
	  }
	}

	/* Mark list as empty */
	list = NULL;
	return;
}

int countNumberOfElements() {

	struct todoItem *follow;
	int numElements = 0;
	follow = list;
	while(follow) {
		numElements++;
		follow = follow->next;
	}
	return numElements;
}

void printList() {

	struct todoItem *follow;
	int numElements = countNumberOfElements();
	int sizeOfNode = sizeof(struct todoItem);
	follow = list;
	printf("Size of node: %d\n", sizeOfNode);
	printf("Size of %d elements in memory: %d\n", numElements,
			 (numElements * sizeOfNode));
	while (follow) {
		printNode(*follow);
		follow = follow->next;
	}
	return;
}

void exportToDosToCSV(char *filename){
	FILE *fptr;
	struct todoItem *follow;

	fptr = fopen(filename, "w+");

	if (fptr == NULL) {
		printf("The file is not opened.\n");
	}

	follow = list;
	while(follow) {
		fprintf(fptr, "%d,%d,%s,%c\n",
				  follow->id,
				  follow->priority,
				  follow->description,
				  follow->completed);
		follow = follow->next;
	}

	fclose(fptr);

	return;
}

void saveAllToDos(char *filename) {
	FILE *fptr;
	int sizeOfDescToWrite = 0;
	struct todoItem *follow;
	fptr = fopen(filename, "w+b");

	follow = list;
	while(follow) {
		fwrite(&(follow->id),sizeof(int),1,fptr);
		fwrite(&(follow->priority),sizeof(int),1,fptr);
		sizeOfDescToWrite = strlen(follow->description) * sizeof(char);
		fwrite(&sizeOfDescToWrite, sizeof(int), 1, fptr);
		fwrite(follow->description,sizeOfDescToWrite,1,fptr);
		fwrite(&(follow->completed),sizeof(char),1,fptr);

		follow = follow->next;
	}


	fclose(fptr);
	return;
}

void loadAllToDos(char *filename) {
	FILE *fptr;
	struct todoItem *newNode;
	int id, sizeOfDescStr;
	char *description;
	short priority;
	char completed;

	if (list != NULL) {
		init();
	}

	fptr = fopen(filename, "r");
	while(fread(&id,sizeof(int),1,fptr)) {
		fread(&priority,sizeof(int),1,fptr);
		fread(&sizeOfDescStr,sizeof(int),1,fptr);
		description = (char *) malloc(sizeOfDescStr);
		fread(description,sizeOfDescStr,1,fptr);
		fread(&completed,sizeof(char),1,fptr);
		newNode = buildNodeComplex(priority, description, id, completed);
		printNode(*newNode);
	}
	fclose(fptr);
	return;
}