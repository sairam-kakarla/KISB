#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<fcntl.h>
#include "myshell_history.c"

#define MAX_WORD 20
#define MAX_CHAR 100
#define MAX_ROUTE 300

char buf[MAX_ROUTE];
char *cdir,*dir,*todir;
int input_redirection_flag;
int output_redirection_flag;
int piping_flag;
char* input_file = NULL;
char*output_file = NULL;
char* username;

void init_cwd(){
	cdir=getcwd(buf,MAX_ROUTE);
}

void change_cwd(char *newd){
	cdir=getcwd(buf,MAX_ROUTE);
	dir=strcat(cdir,"/");
	if(newd[0]=='~'){
		todir=getenv("HOME");
		chdir(todir);
	    cdir=getcwd(buf,MAX_ROUTE);
		return ;
		
	}
	if(newd[0]=='/'){
		todir=newd;
	}
	else{
	todir=strcat(dir,newd);
	}
    chdir(todir);
	cdir=getcwd(buf,MAX_ROUTE);
	
}


void remove_endOfLine(char line[]) {
	int i = 0;
	while (line[i] != '\n')
		i++;
	line[i] = '\0';
}


void piping_handle(char* args[], char* piping_args[], int pipefd[]) {
	int pid, i;
	pid = fork();
	if (pid == 0) {
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		execvp(args[0], args);
		perror(args[0]);
	}
	else {
		dup2(pipefd[0], 0);
		close(pipefd[1]);
		close(pipefd[1]);
		execvp(piping_args[0], piping_args);
		perror(piping_args[0]);
	}

}


void read_line(char line[]) {
	printf("\033[0;36m");
	printf("%s:",username);
	printf("\033[0m");
	printf("\033[0;31m");
	printf("%s>",cdir);
	printf("\033[0m");
	char* value = fgets(line, MAX_CHAR, stdin);
	remove_endOfLine(line);
	if (strcmp(line, "bye") == 0 || value == NULL)
		exit(0);
}

int process_line(char* temp[], char line[]) {

	int i = 0;
	temp[i] = strtok(line," ");
	if (temp[i] == NULL) {
		printf("ERR:\nNo Command\n");
		return 1;
	}
	while (temp[i] != NULL) {
		temp[++i] = strtok(NULL, " ");
	}
	return 1;
}

int pipe_and_redirection_check(char* temp[])
{
	int i = 0;
	while (temp[i] != NULL)
	{
		if (strcmp(temp[i], ">") == 0)
		{
			output_redirection_flag = 1;
			output_file = temp[i + 1];
			return i;
		}
		if (strcmp(temp[i], "<") == 0)
		{
			input_redirection_flag = 1;
			input_file = temp[i + 1];
			return i;
		}
		if (strcmp(temp[i], "|") == 0)
		{
			piping_flag = 1;
			return i;
		}
		i++;
	}
	return i;
}

void check_line(char* temp[]) {
	int i = 0;
	int pipe_cnt = 0;
	int output_redirection_cnt = 0;
	int input_redirection_cnt = 0;
	while (temp[i] != NULL) {
		if (strcmp(temp[i], ">") == 0)
			output_redirection_cnt++;
		if (strcmp(temp[i], "<") == 0)
			input_redirection_cnt++;
		if (strcmp(temp[i], "|") == 0)
			pipe_cnt++;
		i++;
	}
	int total_count = pipe_cnt + input_redirection_cnt + output_redirection_cnt;
	if (total_count > 1) {
		printf("ERR:\nmyshell can't handle this case\n");
		temp[0] = NULL;
	}

}

int read_parse_line(char* arg[], char line[], char* piping_args[],HSTACK *session) {
	char* temp[MAX_WORD];
	read_line(line);
	push_HSTACK(session,line);
	int i = 0, pos;
	process_line(temp, line);
	check_line(temp);
	pos = pipe_and_redirection_check(temp);
	while (i < pos) {
		arg[i] = temp[i];
		i++;
	}
	arg[i] = NULL;
	i++;
	if (piping_flag == 1);
	{	int j = 0;
		while (temp[i] != NULL) {
			piping_args[j] = temp[i];
			i++;
			j++;
		}
	}
	
	return 1;
}


int main() {
	HSTACK session;
	init_HSTACK(&session);
	char *cli_arg[MAX_WORD];
	char cli_line[MAX_CHAR];
	char* piping_args[MAX_WORD];
	username = getlogin();
	init_cwd();
	printf("-----------------------------KISB----------------------------\n");
	printf("-----------------------Home Brewed Shell----------------------\n");
	int pipefd[2];
	pipe(pipefd);
	while (read_parse_line(cli_arg, cli_line, piping_args,&session)) {
		if (strcmp(cli_line, "clean") == 0) {
			printf("\033[2J\033[1;1H");
			continue;
		}
		if(strcmp(cli_arg[0],"history")==0){
			display(&session);
			continue;
		}
		if(!strcmp(cli_arg[0],"cd")){
			change_cwd(cli_arg[1]);
			continue;
		}
		pid_t child_pid = fork();
		if (child_pid == 0) {
			if (input_redirection_flag == 1 && input_file != NULL)
				dup2(open(input_file, O_RDWR | O_CREAT, 0777), 0);
			if (output_redirection_flag == 1 && output_file != NULL)
				dup2(open(output_file, O_RDWR | O_CREAT, 0777), 1);
			if (piping_flag == 1) {
				piping_handle(cli_arg, piping_args, pipefd);
				exit(0);
			}
			printf("\e[1;92m");
	        int result=execvp(cli_arg[0], cli_arg);
	        printf("\e[0m");
			if(result==-1){
				printf("ERR:\n%s: Command not found\n",cli_line);
			}
			exit(0);

		}
		else if(child_pid==-1){
			printf("ERR:\nChild Process Creation Failed\n");
		}
		else {
			wait(NULL);
			input_redirection_flag = 0;
			output_redirection_flag = 0;
			piping_flag = 0;
			input_file = NULL;
			output_file = NULL;
		}
	}
	return 0;
}