#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

char *args[255];


int main() {
	while (1) {
		int i = 0;
		char *command = readline("Shit_shell> ");
		if (!command) {
			exit(1);
		}
		if (*command) {
			add_history(command);
		}
		
		
		args[i] = strtok(command, " "); // Get first token
		
		if (args[0] == NULL) {
			printf("Please enter a command\n");
			free(command);
			continue;
		}
		
		i = 0;
		while (i <= 255) {
			args[++i] = strtok(NULL, " "); 
			if (args[i] == NULL) {
				break;
			}
		}

		
		i = 0;
		
		if (args[0] == NULL) {
			perror("Invalid command");
		}


		if (strcmp(args[0], "cd") == 0) {
	
		if (strcmp(args[1], "~") == 0) {
			args[1] = getenv("HOME");
			free(command);	
		}

		else if (strncmp(args[1], "~/", 2) == 0) {
			const char *home = getenv("HOME");
			char expanded[255];
			snprintf(expanded, sizeof(expanded), "%s/%s", home, args[1] + 2);
			args[1] = expanded;
		}
		
		if (args[1] == NULL) {
			printf("cd: No arguments\n");
		}
	
		else if (chdir(args[1]) != 0) {
			perror("cd: Error in changing directory");
		}

		
		continue;
	}
	
	if (strcmp(args[0], "exit") == 0) {
		free(command);
		args[i] = NULL;
		exit(0);
	}
	
	pid_t pid = fork();
	if (pid == 0) {
		execvp(args[0], args);
		perror("Error in execvp");
		exit(1);
	}
	
	else {
		waitpid(pid, NULL, 0);
	}	
		free(command);
	}

	}

