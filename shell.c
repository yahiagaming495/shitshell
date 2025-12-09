#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

char *args[255];
char *CurrentHomePrint = "false";

int main() {
  char cwd[60];
  char *UserHome = getenv("HOME"); // Store the user home into this variable
  char *ConfigFile = "shitshell"; // The actual file we are going to try to look for
  char buffer[255]; // The contents of the file
  char FinalPath[512]; // Contains filepath + ConfigFile
  const char *SearchFor = "CurrentDicPrint=True"; // What the program should search for
  char filepath[512]; // Contains the user home with a slash at the end
  snprintf(filepath, sizeof(filepath), "%s/", UserHome); // Add a slash at the end of the user home
  snprintf(FinalPath, sizeof(FinalPath), "%s%s", filepath, ConfigFile); // Join UserHome and ConfigFile together and put them in FinalPath to make a path

  while (1) {

    FILE *fp = fopen(FinalPath, "r"); // Because we saved the final path in UserHome "r" means reading mode
    if (fp == NULL) { // If we can't open the file
		CurrentHomePrint = "false"; // Default to false


  	} else {
		while (fgets(buffer, sizeof(buffer), fp) != NULL) { // Read every line in the ConfigFile and store them in buffer 
  	  		if (strstr(buffer, SearchFor)) { // If we found the SearchFor variable in the contents of ConfigFile
       			CurrentHomePrint = "true"; // Default to print the current directory
			}
		   
			else {
				CurrentHomePrint = "false";
			}
		}
		fclose(fp);	
	}


    if (strcmp(CurrentHomePrint, "true") == 0) {
        if (getcwd(cwd, sizeof(cwd)) == NULL) { // getcwd() gets the current directory so if tha                                                   // is NULL (an error happened) clarify that a                                                 error happened
      		perror("getcwd error"); // Print the error
	
	  }	else {
		  printf("Current working directory: %s\n", cwd); // Now actually print the current directory               
		}
    }
    char *command = readline("Shit_shell> "); // Using GNU Readline for command history and auto-completion 
				//	so the user will see "Shit_shell> " and will be able to type the command
				// Didn't merge the current directory printf() with the readline because readline
				// Doesn't support format specifiers (as far as i know)


				
		int i = 0; // Used for the while loop
		if (!command) { // If no command got entered
			exit(1); // Exit with an error
		}

		if (*command) { // If the user entered a command
			add_history(command); // Save it to the command history using Readline
		}
		
		
		args[i] = strtok(command, " "); // Get first token
		
		if (args[0] == NULL) { // If no command was entered
      		printf("Please enter a command\n");
			free(command); // Clear the command variable from the heap memory
			continue; 
		}
		
		i = 0;
		while (i <= 255 && args[i] != NULL) { // Do this for 255 times
			args[++i] = strtok(NULL, " "); // Every time there is a space, Take the text after the space as an argument
			if (args[i] == NULL) { // If we reached the end of the text
				break; // Stop the loop
			}
		}

		
		i = 0; // Reset i's value
		
		if (args[0] == NULL) { 
			perror("Invalid command");
		}


		if (strcmp(args[0], "cd") == 0) { // Compare args[0] with "cd" and see if args[0] is cd

		if (args[1] == NULL) {
			chdir(getenv("HOME"));
			continue;
		}
		
    	else if (strcmp(args[1], "~") == 0) { // If args[1] is "~" (the home directory symbol)
			args[1] = getenv("HOME"); // Replace args[1] with the home enviroment variable
			free(command);	
		}

		if (strncmp(args[1], "~/", 2) == 0) {
			const char *home = getenv("HOME"); // Make a non-changeable variable that contains the home directory
			char expanded[512];
			snprintf(expanded, sizeof(expanded), "%s/%s", home, args[1] + 2); // Join the home variable and args[1] without the first two chracters strings and put the result in expanded
			chdir(expanded);
		}
		
	
		else if (chdir(args[1]) != 0) { // If changing the directory failed, Print an error
			perror("cd: Error in changing directory");
		}

		continue;
	}
	
		if (strcmp(args[0], "exit") == 0) {
			free(command);
			args[i] = NULL;
			exit(0); // Exit without an error
		}

		pid_t pid = fork(); // Create a child process stored/made in a variable that is of type (pid_t) which is used to store process ids, Group ids, etc.

		if (pid == 0) { // Check if we're in the child process
			execvp(args[0], args); // Try to run the command
			perror("Error in execvp"); // If execvp() failed, Print an error
			exit(1); // If execvp() failed, Exit with an error
		}

		else { // If we're in the parent process
			waitpid(pid, NULL, 0); // Wait for the child process to run
			free(command);
		}
	
}
	
}

