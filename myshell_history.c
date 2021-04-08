#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_LINE 30
typedef struct history_list_entry{
    char cmd[MAX_LINE];
    int rank;
    struct history_list_entry* next;
}HNODE;
typedef struct history_stack{
    HNODE* bottom;
    HNODE* top;
    int size;
}HSTACK;
void init_HSTACK(HSTACK* hstack){
    hstack->size=0;
}
HNODE* new_HNODE(char cmd[]){
    HNODE *temp=(HNODE * )malloc(sizeof(HNODE));
    strcpy(temp->cmd,cmd);
    temp->next=NULL;
    return temp;
}
void push_HSTACK(HSTACK* hstack,char cmd[]){
    HNODE *temp=new_HNODE(cmd);
    if(temp!=NULL){
    temp->rank=hstack->size+1;
if(hstack->size==0){
    hstack->top=hstack->bottom=temp;
}
else{
    hstack->top->next=temp;
    hstack->top=temp;
}
hstack->size++;
    }
    else{
        printf("Insufficient Memory\n");
    }
}
void display(HSTACK* hstack){
    HNODE* tempb=hstack->bottom;
    while(tempb!=NULL){
    printf("%d %s\n",tempb->rank,tempb->cmd);
    tempb=tempb->next;
    }
    printf("\n");
}
void remove_NLC(char string[]){
    int i=0;
    while(string[i]!='\n')i++;
    string[i]='\0';
}
void cleanHSTACK(HSTACK * hstack){
    /*Not all os supports the deallocation of memory after termination of program,also its a good habit coz it prevents memory leak;*/
   HNODE* temp=hstack->bottom;
   HNODE* next=temp->next;
   while(temp!=NULL){
       free(temp);
       temp=next;
       next=next->next;
   } 
}
int main(){
HSTACK session;
init_HSTACK(&session);
while(1){
    char cli_cmd[MAX_LINE];
    printf(">");
    fgets(cli_cmd,MAX_LINE,stdin);
    remove_NLC(cli_cmd);
    if(strcmp(cli_cmd,"exit")==0){
        cleanHSTACK(&session);
        break;
    }
    else{
        push_HSTACK(&session,cli_cmd);
        if(strcmp(cli_cmd,"history")==0){
            display(&session);
        }
    }
}
return 0;
}