#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_EXP 200
#define MAX_TOKEN 30

char expression[MAX_EXP];

void format_expression(char *cli_line){
    //extracts the expression for the command statement
    int intr=0;
    char *exp=strtok(cli_line," ");
    exp=strtok(NULL," ");
    strcat(expression,exp);
}
void evalExpression(char *expression){
    //evaluates the expression
}
int main(){
char cli_line[MAX_EXP];
fgets(cli_line,MAX_EXP,stdin);
format_expression(cli_line);
printf("%s",expression);
}