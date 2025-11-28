#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

char *args[32];


int main() {
	while (1) {
	int i = 0;
	char *command = readline("Shit_shell< "); // GNU Readline does this to make storing stuff easier
	
	if (!command) break; // Break if the input is wrong
	
	if (*command)
		add_history(command); // Save command history to a file (Thanks GNU Readline)

	// -- Split the command from it's arguments -- //
		
	args[i] = strtok(command, " "); 


	while (args[i] != NULL && i < 31) {
		args[++i] = strtok(NULL, " ");
	}

	
	args[i] = NULL; // As far as i know, Put NULL at the end of the command

	// Built-in command: cd, Because execvc cannot change directory. The child process will change it's directory, exit. but the parent process cannot change it's directory 
	if (strcmp(args[0], "cd") == 0) {
		if (args[1] == NULL) {
			printf("cd: Missing argument\n");			
		} else {
		if (chdir(args[1]) != 0) {
			perror("cd: Command error");
		}
	
	}
	continue;
}
	// Built-in command: exit
	if (strcmp(args[0], "exit") == 0) {
		printf("Exiting the shell...");
		exit(0);
	}

	pid_t pid = fork(); // So C has a typedef called "pid_t" typically used to store process id(s), Session id(s), etc..
	if (pid == 0) {
		execvp(args[0], args); // Run the command
		perror("Error in execvp");
		exit(1);
	}
	else {
		waitpid(pid, NULL, 0); // Wait for the child process to execute
	}
		free(command);
		args[0] = NULL;	
	
	}	

}
