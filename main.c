#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT_SIZE 100
#define LINE_CHARACTER '$'

static void run_loop(void);
static void get_arguments(char *str, char **arguments, int *size);

int main(void) {
	printf("Welcome to MyShell!\n - type 'help' for a list of commands\n\n");

	run_loop();

	return 0;
}

static void run_loop(void) {
	while(1) {
		printf("%c ", LINE_CHARACTER);

		//git a
		char command[MAX_INPUT_SIZE];
		fgets(command, sizeof(command), stdin);
		size_t len = strlen(command);
		if (len > 0 && command[len - 1] == '\n') {
			command[len - 1] = '\0';
		}

		if (strlen(command) == 0) {
			continue;
		}
		
		char **arguments = malloc(sizeof(char) * 100);
		int size = 0;
		get_arguments(command, arguments, &size);

		if (strcmp(arguments[0], "pwd") == 0) {
		} else if (strcmp(arguments[0], "exit") == 0) {
			printf("exiting myShell...\n");
			break;
		}
	}
}

static void get_arguments(char *str, char **arguments, int *length) {
    bool in_single_quote = false;
    bool in_double_quote = false;
    char buffer[100];
    int buffer_index = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (!in_single_quote && !in_double_quote && (str[i] == ' ' || str[i+1] == '\0')) {
            if (str[i+1] == '\0' && str[i] != ' ') { // Add last character if it's not a space
                buffer[buffer_index] = str[i];
                buffer_index++;
            }
            buffer[buffer_index] = '\0'; // Null-terminate the string
            arguments[*length] = strdup(buffer); // Allocate memory and copy the buffer
            *length += 1;
            memset(buffer, 0, sizeof(buffer)); // Clear the buffer
            buffer_index = 0;
        } else if (str[i] == '\'') {
            in_single_quote = !in_single_quote;
        } else if (str[i] == '\"') {
            in_double_quote = !in_double_quote;
        } else {
            buffer[buffer_index] = str[i];
            buffer_index++;
        }
    }
}

