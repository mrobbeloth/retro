#include <stdio.h>
#include <stdlib.h>
#include "todo.h"

int main(int argc, char **argv) {
	int i;
	struct todoItem daItem;
	char *fullDesc=NULL;
	char *baseStr = "Complete this beautiful task with id:";

	/* Use argc/argv so compiler doesn't complain */
	printf("%d %s\n", argc, " arguments entered at prompt");
	for(i = 0; i < argc; i++) {
		printf("%s\n", *(argv+i));
	}

	/* Prepare TODO list */
	init();

	/* Create and display 100 test todos */
	fullDesc = (char *) malloc(strlen(baseStr) + sizeof(int) + 1);
	for(i = 0; i < 10; i++) {
		sprintf(fullDesc, "%s %d", baseStr, i);
		addToDo(i, fullDesc);
	}
	printList();

	/* Delete every other todo and display */
	for(i = 0; i < 10; i+=2) {
		deleteToDo(i);
	}
	printList();

	/* Retrieve todo with id 5 and display */
	daItem = returnItem(5);
	printNode(daItem);

	/* Save contents of todo list in plaintext and binary */
	exportToDosToCSV("michael.csv");
	saveAllToDos("michael.bin");

	/* reset todo list */
	init();
	return 0;
}