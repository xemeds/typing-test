// Author: Muhammed Ali Dilek (xemeds)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUMER_OF_TEXTS 3

#define CLI_RESET "\033[0m"
#define CLI_BOLD "\033[1m"
#define CLI_UNDERLINE "\033[4m"
#define CLI_BOLD_YELLOW "\033[1;33m"
#define CLI_BOLD_CYAN "\033[1;36m"
#define CLI_RED "\033[0;31m"
#define CLI_BOLD_GREEN "\033[1;32m"

#ifdef __linux
	// Clears the screen for linux
	void clear() {
		system("clear");
	}
#elif _WIN32
	// Clears the screen for windows
	void clear() {
		system("cls");
	}
#endif

// Prints the ASCII art
void print_art() {
	printf(CLI_BOLD_YELLOW);
	printf("\t\t████████╗██╗░░░██╗██████╗░██╗███╗░░██╗░██████╗░\n");
	printf("\t\t╚══██╔══╝╚██╗░██╔╝██╔══██╗██║████╗░██║██╔════╝░\n");
	printf("\t\t░░░██║░░░░╚████╔╝░██████╔╝██║██╔██╗██║██║░░██╗░\n");
	printf("\t\t░░░██║░░░░░╚██╔╝░░██╔═══╝░██║██║╚████║██║░░╚██╗\n");
	printf("\t\t░░░██║░░░░░░██║░░░██║░░░░░██║██║░╚███║╚██████╔╝\n");
	printf("\t\t░░░╚═╝░░░░░░╚═╝░░░╚═╝░░░░░╚═╝╚═╝░░╚══╝░╚═════╝░\n");
	printf("  ░██████╗██████╗░███████╗███████╗██████╗░ ████████╗███████╗░██████╗████████╗\n");
	printf("  ██╔════╝██╔══██╗██╔════╝██╔════╝██╔══██╗ ╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝\n");
	printf("  ╚█████╗░██████╔╝█████╗░░█████╗░░██║░░██║ ░░░██║░░░█████╗░░╚█████╗░░░░██║░░░\n");
	printf("  ░╚═══██╗██╔═══╝░██╔══╝░░██╔══╝░░██║░░██║ ░░░██║░░░██╔══╝░░░╚═══██╗░░░██║░░░\n");
	printf("  ██████╔╝██║░░░░░███████╗███████╗██████╔╝ ░░░██║░░░███████╗██████╔╝░░░██║░░░\n");
	printf("  ╚═════╝░╚═╝░░░░░╚══════╝╚══════╝╚═════╝░ ░░░╚═╝░░░╚══════╝╚═════╝░░░░╚═╝░░░\n\n");
	printf(CLI_RESET);
}

// Introduction
void intro() {
	clear();
	print_art();
	printf(CLI_BOLD_CYAN CLI_UNDERLINE "How it works:\n");
	printf(CLI_RESET CLI_BOLD);
	printf("TODO\n\n");
	printf("Press enter to start...\n> ");
	getchar();
	printf(CLI_RESET);
}

// Gets a random text from the texts file
char *get_text() {
	// Get the time
	time_t t;

	// Initialize the random number generator
	srand((unsigned) time(&t));

	// Get a random line number
	int random_line_number = rand() % NUMER_OF_TEXTS;

	// Open the file
	FILE *file = fopen("texts.txt", "r");

	// Check if the file pointer is empty
	if (file != NULL) {
		// Create the max read size per line
		char line[256];

	    // Declare the line number of the file
	    int line_number = 0;

	    // Read each line one by one
	    while (fgets(line, sizeof line, file) != NULL)
	    {
	    	// If the current line number is the random line number
	        if (line_number == random_line_number) {

	        	// Allocate space for a new text
	        	char *text = malloc(sizeof(line));

	        	// Copy the line to the text
	        	strcpy(text, line);

	        	// Close the file
	        	fclose(file);

	        	// Return the pointer to the newly allocated text
	        	return text;
	        }
	        // Else
	        else {
	        	// Increment the line number
	        	line_number++;
	        }
	    }
	}
	// Just in case close the file
	fclose(file);
}

int main() {
	//char string[10];
	//fgets(string, 10, stdin);

	//time_t start = time(NULL);
	//time_t end = time(NULL);
	//printf("Time taken: %li", (end - start));

	//char *text = get_text();
	//printf("%s", text);
	//free(text);

	intro();

	return 0;
}
