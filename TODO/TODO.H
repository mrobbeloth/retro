#ifndef TODO_H
#define TODO_H

#include <time.h>

struct todoItem{
	int id;
	short priority;
	char *description;
	char completed;
	struct todoItem *next;
	time_t due_date;
};

void printNode(struct todoItem);
struct todoItem * buildNodeComplex(short, char*, int, char, time_t);
struct todoItem * buildNode(short, char*, time_t);
int addToDo(short, char*, time_t);
int removeToDo(short);
int deleteToDo(short);
struct todoItem returnItem(int);
void init();
void printList();
int countNumberOfElements();
void exportToDosToCSV(char *filename);
void saveAllToDos(char *filename);
void loadAllToDos(char *filename);
int insertBeginningList(struct todoItem *);

#endif