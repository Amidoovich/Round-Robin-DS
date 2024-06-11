#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "process.h"

void Display(Process p){
    printf("the id of the process is %d\n",p.id);
    printf("the burst time of the process is %d\n",p.burst_time);
}
int main()
{

    int choice;
    List l;
    CreateList(&l);
    OpenProgram(&l);
    OpenTimeQuantum(&l);
    Process p;
    int count=0,booll;
    do
    {
    int quantum;
    int f2=1;
    char input_char3;
    if(ListEmpty(&l)){
        if(count>0){
            printf("\nif you want to continue Enter 1\n");
            printf("nif you want to Exit Enter 2\n");
            scanf("%d",&booll);
            if(booll==2){
                CloseProgram(&l);
                printf("Exiting=========>");
                break;
            }
        }
        while(f2==1){
            printf("please enter the quantum time:\n");
            scanf("%d",&quantum);
            if((input_char3 = getchar()) != '\n' && input_char3 != EOF){
            printf("Error: Please enter an integer not char value.\n");
            }
            else if(quantum<=0){
                printf("Error: Please enter a positive integer or not equal zero.\n");
            }else{
            SetTimeQuantum(&l,quantum);
            f2=0;
            count++;
            }
    }
    }
    printf("Main Menu: \n");
    printf("\n");
    printf("1. Add a process.\n");
    printf("2. Serve a process.\n");
    printf("3. How many waiting processes?\n");
    printf("4. Display information of waiting processes.\n");
    printf("5. Display total CPU burst time.\n");
    printf("6. Exit (Save in a file).\n");
    printf("\n");
    int f=1;
    while(f==1){
        char input_char2;
        printf("please enter your choice:\n");
        scanf("%d",&choice);
        if((input_char2 = getchar()) != '\n' && input_char2 != EOF){
        printf("Error: Please enter an integer not char value.\n");
            }
        else{
            f=0;
        }
    }
     switch(choice)
     {
     char input_char;
     case 1:
        printf("Enter process ID: ");
        scanf("%d", &p.id);
        if((input_char = getchar()) != '\n' && input_char != EOF){
        printf("Error: Please enter an integer not char value.\n");
        break;
        }
        if (checkId(p.id, &l)==1) {
            printf("Enter burst time: ");
            scanf("%d", &p.burst_time);
            if((input_char = getchar()) != '\n' && input_char != EOF){
            printf("Error: Please enter an integer not char value.\n");
            break;
            }
            else if(p.burst_time<=0){
                printf("Error: Please enter a positive integer or not equal zero.\n");
                break;
            }
            InsertList(CurrentPosition(&l), &l, p);
            printf("Process with ID %d added to the scheduler.\n", p.id);
        }else if(checkId(p.id, &l)==-1){
            printf("Error: Please enter a positive integer.\n");
        }else{
            printf("Error: ID %d already exists in the list.\n", p.id);
        }

        break;
     case 2:
        if(ListEmpty(&l))
        {
            printf("\nthe List is empty of processes\n");
        }
        else
        {
            int flag=DeleteList(CurrentPosition(&l),&l,&p);
            if(flag==1)
            {
                printf("\nthe process number %d and the time left for it is %d\n",p.id,p.burst_time);
            }
            else if(flag==0)
            {
                printf("\nthe process number %d is totally done\n",p.id);
            }
        }
         break;
     case 3:
         if(!ListEmpty(&l))
            printf("\nthe number of waiting process is %d\n",NumberOfProcess(&l));
         else
            printf("\nthe List is empty of processes\n");
         break;
     case 4:
        if(ListEmpty(&l))
        {
            printf("\nthe List is empty of processes\n");
        }
        else
        {
            TraverseList(&l,&Display);
        }
         break;
     case 5:
         if(!ListEmpty(&l))
            printf("\nThe Total BurstTime is %d\n",TotalBurstTime(&l));
         else
            printf("\nthe List is empty of processes\n");
        break;
     case 6:
           if(!ListEmpty(&l)){
            CloseTimeQuantum(&l);
           }
           CloseProgram(&l);
           printf("Exiting=========>");
        break;
     default:
        printf("please enter number from 1 to 6\n");
     }
    }while(choice!=6);
    return 0;
}
