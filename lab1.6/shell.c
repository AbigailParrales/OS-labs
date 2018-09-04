#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

#define MAX_LINE 80
#define HISTORY_SIZE 10

int args_no = 0;
int process_cnt=0;


void parser(char *line, char **line_content){
	args_no = 0;
	while (*line != '\0') {       			//waits for end of line
		while (*line == ' ' || *line == '\t' || *line == '\n')
			*line++ = '\0';     			// replace white spaces with 0 
		*line_content++ = line;         	//save the argument position
		while (*line != '\0' && *line != ' ' && *line != '\t' && *line != '\n') 
			line++;             			//skip the argument until
		args_no++;
	}
	*line_content = '\0';                 	//mark the end of argument list
	//printf("No args: %d\n", args_no);
}

void execute(char **arg){
	pid_t  child;
	int    status;

	if ((child = fork()) < 0) {     /* fork a child process           */
		printf("*** ERROR: forking child process failed\n");
	}
	else if (child == 0) {          /* for the child process:         */
		if (execvp(*arg, arg) < 0) {     /* execute the command  */
			exit(1);
		}
	}
	else {    
		if(strcmp(arg[args_no - 1], "&") != 0){    /* for the parent:      */
			waitpid(child, NULL, 0);
		}                              
	}
}

int hist_i = 1;

struct process{
	int id;
	char command[MAX_LINE+1];
}history[HISTORY_SIZE];

void addProcess(char line[]){
	int i;
	for (i = 0; i < HISTORY_SIZE - 1; i++) {
		history[i] = history[i + 1];
	}
	history[HISTORY_SIZE - 1].id = hist_i ++;
	strcpy(history[HISTORY_SIZE - 1].command, line);
	process_cnt++;
}

void printHistory(){
	int i;
	for (i = HISTORY_SIZE - 1; i >= 0 && history[i].id > 0; i--) {
		printf("%d %s\n", history[i].id, history[i].command);
	}
}

int get_hist_i(char arg[]){
	if (arg[0] == '!' &&arg[1] != '\0') {
		int i;
		for (i = 1; arg[i] != '\0'; i++) {
			if (!isdigit(arg[i])) { //Validate the input is an int
				return -1;
			}
		}
		return atoi(&arg[1]);
	}
	return -1; //Returns "error" code
}

int main(void){
	char *args[MAX_LINE/2 + 1]; /* command line arguments */
	int shouldrun = 1; /* flag to determine when to exit program*/
	char line[MAX_LINE + 1];
	char backup[MAX_LINE + 1];
	int actIndex=0;
	struct process tmp;

	while (shouldrun) {
		printf("osh> ");
		fflush(stdout);
		gets(line);

		//diferent options

		//first check if the command is exit
		if (strcmp(line, "exit") == 0){
			shouldrun = 0; 
			continue;
		}

		//else, parse the line to get the separate commands
		parser(line,args);

		//once parsed

		//if line empty
		if(args_no == 0){
			continue;
		}

		//history

		//if line contains "!!" -> last command excecuted
		if (strcmp(args[0], "!!") == 0) {
			if(actIndex==0){
				printf("No commands in bash. \n");
				continue;
			}
			else{
				int i;
				for(i=0; i<HISTORY_SIZE;i++){
					tmp=history[i];
					if (args_no == tmp.id){
						parser(tmp.command,args);
						break;
					}
				}
			}
		}


		//if line contains "!"+N -> excecute command in pos N
        /*if(args[0][0] == '!'){
            if(args[0][1] == '0'){
                printf("No such command in history.\n");
                continue;
            }
            int index = parse_index(args[0]);
                if(index<0){
                    printf("No such command in history.\n");
                    continue;
                }
                int x;
                for(x=0; x < MAX_HISTORY;x++) {
                    aux = historyQueue[x];
                    if(index == aux.id) {
                        arg_count = parse_command(aux.line, args);
                        break;
                    }
                }    
        }*/

		//If the command is not history nor NULL
		if(args_no == 1){
			actIndex=get_hist_i(args[0]);
			strcpy(backup, line);
			parser(line,args);	
		}
		addProcess(backup);

		if (actIndex == 1 &&strcmp(args[0], "history") == 0) {
			printHistory();
		}

		execute(args);
	}
	return 0;
}

