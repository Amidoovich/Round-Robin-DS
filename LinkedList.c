#include "LinkedList.h"
#include"Process.h"
#include <stdlib.h>
#include <stdio.h>


void CreateList(List *pl)
{
    pl->head=NULL;
    pl->size=0;
    pl->current=NULL;
    pl->time_quantum=0;
}

int ListEmpty(List *pl)
{
   return pl->size==0;
}

int ListFull(List *pl)
{
   return 0;
}

void InsertList(int pos,List *pl, ListEntry e)
{
    ListNode *p,*q=NULL;
    p=(ListNode*)malloc(sizeof(ListNode));
    p->entry=e;
    if(pos==0)
    {
    if(pl->size==0)
    {
        p->next=pl->head;
        pl->head=p;
        pl->current=pl->head;
    }
    else
    {
        int i;
        for(q=pl->head,i=0;i<pl->size-1;i++)
            q=q->next;
        p->next=q->next;
        q->next=p;
    }
   }else{
        int i;
        for(q=pl->head,i=0;i<pos-1;i++)
            q=q->next;
        p->next=q->next;
        q->next=p;
   }
   pl->size++;
}
 int DeleteList(int pos,List *pl,ListEntry *pe)
{
    ListNode *p=NULL,*n=NULL,*c=pl->current;
    if(pl->current->next)
        pl->current=pl->current->next;
    else
        pl->current=pl->head;
    if(pos==0)
    {
         n=pl->head->next;
         if(c->entry.burst_time>pl->time_quantum)
         {
             c->entry.burst_time-=pl->time_quantum;
             *pe=pl->head->entry;
             return 1;
         }
         else
         {
             c->entry.burst_time=0;
             *pe=pl->head->entry;
             free(pl->head);
             pl->head=n;
             if(pl->head==NULL)
                pl->current=pl->head;
             pl->size--;
             return 0;
         }
    }
    else
    {
        int i;
        for(p=pl->head,i=0;i<pos-1;i++)
            p=p->next;
         n=p->next->next;
         if(c->entry.burst_time>pl->time_quantum)
         {
             c->entry.burst_time-=pl->time_quantum;
             *pe=c->entry;
             return 1;
         }
         else
         {
             c->entry.burst_time=0;
             *pe=c->entry;
             free(p->next);
             p->next=n;
             pl->size--;
             return 0;
         }
    }
}

int NumberOfProcess(List *pl)
{
    return pl->size;
}

void TraverseList(List *pl,void (*Display)(ListEntry))
{
    ListNode *p=pl->current;
    (*Display)(p->entry);
    p=p->next;
    if(pl->size!=1){
    while(p!=pl->current)
    {
        if(p==NULL){
            p=pl->head;
            continue;
        }
        (*Display)(p->entry);
        p=p->next;
    }
    }
}

int CurrentPosition(List *pl)
{
         ListNode *q=pl->head;
         int CurrentPos=0;
         while(q!=pl->current)
         {
             q=q->next;
             CurrentPos++;
         }
         return CurrentPos;
}

int TotalBurstTime(List *pl)
{
    int TotalTime =0;
    ListNode *pn=pl->head;
    while(pn)
    {
        TotalTime=TotalTime+pn->entry.burst_time;
        pn=pn->next;
    }
    return TotalTime;
}

int CloseProgram(List *pl) {
    FILE *file = fopen("Processes.txt", "w");
    if (file == NULL) {
        return 0;
    }

    if (pl->size == 0) {
        fclose(file);
        return -1;
    }

    ListNode *p = pl->current;
    ListNode *q = p->next;

    if (pl->size == 1) {
        fprintf(file, "%d\n", p->entry.id);
        fprintf(file, "%d\n", p->entry.burst_time);
        free(p);
        pl->size = 0;
        pl->head = NULL;
        pl->current = NULL;
        fclose(file);
        return 1;
    }

    do {
        fprintf(file, "%d\n", p->entry.id);
        fprintf(file, "%d\n", p->entry.burst_time);
        free(p);
        pl->size--;

        p = q;
        if (p != NULL)
            q = p->next;
        else {
            p = pl->head;
            q = p->next;
        }

    } while (pl->size != 0);

    pl->head = NULL;
    pl->current = NULL;
    fclose(file);
    return 1;
}


int OpenProgram(List *pl)
{
    FILE *file = fopen("processes.txt", "r");
    if (file == NULL) {
         return 0;
    }
    int id,burst_time;
    while (fscanf(file, "%d %d", &id, &burst_time) == 2) {
    ListNode *p,*q;
    p=(ListNode*)malloc(sizeof(ListNode));
    p->entry.id=id;
    p->entry.burst_time=burst_time;
    if(pl->size==0)
    {
        p->next=pl->head;
        pl->head=p;
        pl->current=pl->head;
    }
    else
    {
        int i;
        for(q=pl->head,i=0;i<pl->size-1;i++)
            q=q->next;
        p->next=q->next;
        q->next=p;
    }
    pl->size++;
    }
    fclose(file);
    return 1;
}

int checkId(int id, List *pl) {
    if (id <= 0) {
        return -1;
    }

    ListNode *p = pl->head;
    while (p) {
        if (p->entry.id == id) {
            return 0;
        }
        p = p->next;
    }

    return 1;
}

void SetTimeQuantum(List *pl,int quantum)
{
    pl->time_quantum=quantum;
}

int OpenTimeQuantum(List *pl)
{
    FILE *file = fopen("TimeQuantum.txt", "r");
    if (file == NULL) {
         return 0;
    }
    int quantum;
    fscanf(file,"%d",&quantum);
    pl->time_quantum=quantum;
    fclose(file);
    return 1;
}
int CloseTimeQuantum(List *pl)
{
    FILE *file = fopen("TimeQuantum.txt", "w");
    if (file == NULL) {
         return 0;
    }
    fprintf(file, "%d\n", pl->time_quantum);
    fclose(file);
    return 1;
}
