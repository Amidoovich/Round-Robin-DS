#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED
#include "Process.h"
typedef Process ListEntry;

typedef struct listnode{
       ListEntry entry;
       struct listnode *next;
}ListNode;

typedef struct list{
       ListNode *head;
       ListNode *current;
       int time_quantum;
       int size;
}List;

void CreateList(List *pl);
int ListEmpty(List *pl);
int ListFull(List *pl);
void InsertList(int pos,List *pl, ListEntry e);
int DeleteList(int pos,List *pl,ListEntry *pe);
///////////////////////////////////////////////////////////////////
int NumberOfProcess(List *pl);
void DestroyList(List *pl);
void TraverseList(List *pl,void (*Display)(ListEntry));
void RetriveList(int pos,List *pl,ListEntry *pe);
void replaceList(int pos,List *pl,ListEntry e);
void ReverseList(List *pl);
void ReverseHalfList(List *pl);
int CurrentPosition(List *pl);
int TotalBurstTime(List *pl);
int CloseProgram(List *pl);
int OpenProgram(List *pl);
void SetTimeQuantum(List *pl,int quantum);
int OpenTimeQuantum(List *pl);
int CloseTimeQuantum(List *pl);
#endif // LINKEDLIST_H_INCLUDED
