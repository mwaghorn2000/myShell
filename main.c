#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_nav.h"

#define MAX_INPUT_SIZE 100

static void run_loop(void);
static void split_str(char *str, char **arguments, int *size);

int main(void) {
	printf("Welcome to MyShell!\n - type 'help' for a list of commands\n\n");

	run_loop();

	return 0;
}

static void run_loop(void) {
	while(1) {
		printf("$ ");
		char command[MAX_INPUT_SIZE];
		fgets(command, sizeof(command), stdin);
		
		char **arguments = malloc(sizeof(char) * 100);
		int size = 0;
		split_str(command, arguments, &size);

		if (strcmp(arguments[0], "pwd") == 0) {
			pwd();
		} else if (strcmp(arguments[0], "exit") == 0) {
			printf("exiting myShell...\n");
			break;
		}
	}
}

static void split_str(char *str, char **arguments, int *size) {
	char *token;
	const char *delim = " \t\n";
	token = strtok(str, delim);

	while (token != NULL) {
		arguments[*size] = token;
		*size += 1;
		token = strtok(NULL, delim);
	}
}
