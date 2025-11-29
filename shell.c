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
		
	args[i] = strtok(command, " "); // Every time there is a space, It will split it and make it a seperate command. It will store it in a diffrent index in args. So args[0], args[1], etc.


	while (args[i] != NULL && i < 31) { // If args are not NULL (empty) then do this for 31 times (to ensure the user can type a very long command) 
		args[++i] = strtok(NULL, " "); // Every time there is a space, It will split it and make it a seperate command. It will store it in a diffrent index in args. So args[0], args[1], etc.

	}

	
	
	if (args[1] != NULL && strcmp(args[1], "~") == 0) { // If the second argument has '~' in it (home directory symbol) and is not empty then do the following:
		args[1] = getenv("HOME"); // Replace the '~' sign with the HOME enviroment variable (A system variable that has the user's home directory) 
	}
	else if (args[1] != NULL && strncmp(args[1], "~/", 2) == 0) { // If the first two letters are "~/" then the user is typing /home/[usernam]/[directory] then:
		static char realcmd[256];
		const char *home = getenv("HOME"); // Store the HOME enviroment variable (The variable that has the home directory for the user) in this variable
		const char *restcmd = args[1] + 2; // Skip the "~/" symbol and store the rest of the command in this variable
		snprintf(realcmd, sizeof(realcmd), "%s/%s", home, restcmd); // Merge home and restcmd (Rest of the command the user inputed) to realcmd (The actual command the user wants to run)
		args[1] = realcmd; // Set args index 1 (args[1]) to the actual command the user wants to run (realcmd)
	}
	// Built-in command: cd, Because execvc cannot change directory. The child process will change it's directory, exit. but any external program cannot change the parent's process directory 
	if (strcmp(args[0], "cd") == 0) { // If the command that the user wants to run is 'cd' then
		if (args[1] == NULL) { // If the user didn't enter anything after the "cd" command
			printf("cd: Missing argument\n"); // Print a missing argument error
		} else {
		if (chdir(args[1]) != 0) { // It should return 0 if the command ran succesfully, So if it didn't
			perror("cd: Command error"); // Print an error message
		}
	
	}
	continue;
}
	// Built-in command: exit
	if (strcmp(args[0], "exit") == 0) { // Linux or UNIX don't have an "exit" command, It's actually a command your terminal implemented
		printf("Exiting the shell...");
		exit(0); // Exit without an error
	}

	pid_t pid = fork(); // So C has a typedef called "pid_t" typically used to store process id(s), Session id(s), etc.. Oh, Also, fork() creates the child process
	if (pid == 0) { // Check if we're in the child process
		execvp(args[0], args); // Run the command
		perror("Error in execvp"); // perror() will print this message if execvp failed and it will print the value of errno, errno is a variable that contains an error message (ex: Permission denied, No such file or directory, etc.) it will print that too
		exit(1); // Exit the program with an error
	}
	else {
		waitpid(pid, NULL, 0); // Wait for the child process to execute
	}
		free(command); // Free (delete/remove) all the stuff that the user inputed for the next command to run
		args[0] = NULL;	// Free the stuff again by adding NULL to the first index of args to end it at it's start (delete it until the user inputs something again)
	
	}	

}
