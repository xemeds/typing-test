// Author: Muhammed Ali Dilek (xemeds)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <termios.h>

#define NUMBER_OF_TEXTS 3

#define CLI_RESET "\033[0m"
#define CLI_BOLD "\033[1m"
#define CLI_UNDERLINE "\033[4m"
#define CLI_BOLD_YELLOW "\033[1;33m"
#define CLI_BOLD_CYAN "\033[1;36m"
#define CLI_BOLD_RED "\033[1;31m"
#define CLI_BOLD_GREEN "\033[1;32m"

// Gets keyboard input
int get_input() {
	struct termios oldattr, newattr;
	tcgetattr(STDIN_FILENO, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
	char input = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	return input;
}

// Clears the screen
void clear() {
	system("clear");
}

// Prints the introduction ASCII art
void print_intro_art() {
	printf(CLI_BOLD_YELLOW);
	printf("\n");
	printf("\t\t████████╗██╗░░░██╗██████╗░██╗███╗░░██╗░██████╗░\n");
	printf("\t\t╚══██╔══╝╚██╗░██╔╝██╔══██╗██║████╗░██║██╔════╝░\n");
	printf("\t\t░░░██║░░░░╚████╔╝░██████╔╝██║██╔██╗██║██║░░██╗░\n");
	printf("\t\t░░░██║░░░░░╚██╔╝░░██╔═══╝░██║██║╚████║██║░░╚██╗\n");
	printf("\t\t░░░██║░░░░░░██║░░░██║░░░░░██║██║░╚███║╚██████╔╝\n");
	printf("\t\t░░░╚═╝░░░░░░╚═╝░░░╚═╝░░░░░╚═╝╚═╝░░╚══╝░╚═════╝░\n");
	printf("  ░██████╗██████╗░███████╗███████╗██████╗░  ████████╗███████╗░██████╗████████╗\n");
	printf("  ██╔════╝██╔══██╗██╔════╝██╔════╝██╔══██╗  ╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝\n");
	printf("  ╚█████╗░██████╔╝█████╗░░█████╗░░██║░░██║  ░░░██║░░░█████╗░░╚█████╗░░░░██║░░░\n");
	printf("  ░╚═══██╗██╔═══╝░██╔══╝░░██╔══╝░░██║░░██║  ░░░██║░░░██╔══╝░░░╚═══██╗░░░██║░░░\n");
	printf("  ██████╔╝██║░░░░░███████╗███████╗██████╔╝  ░░░██║░░░███████╗██████╔╝░░░██║░░░\n");
	printf("  ╚═════╝░╚═╝░░░░░╚══════╝╚══════╝╚═════╝░  ░░░╚═╝░░░╚══════╝╚═════╝░░░░╚═╝░░░\n\n");
	printf(CLI_RESET);
}

// Introduction
void intro() {
	clear();
	print_intro_art();
	printf(CLI_BOLD_CYAN CLI_UNDERLINE "How it works:\n");
	printf(CLI_RESET CLI_BOLD);
	printf("TODO\n\n");
	printf("Press any key to start...\n> ");
	get_input();
	printf(CLI_RESET);
}

// Gets a random text from the texts file
char *get_text() {
	// Get the time
	time_t t;

	// Initialize the random number generator
	srand((unsigned) time(&t));

	// Get a random line number
	int random_line_number = rand() % NUMBER_OF_TEXTS;

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

// Initializes the input text
char *get_input_text(int text_len) {
	// Allocate space as big as the text
	char *input_text = malloc(sizeof(text_len));

	// For each character in the input text
	for (int i = 0, len = text_len; i < len; i++) {
		// Set it to null
		input_text[i] = 0;
	}

	// Return the pointer to the newly allocated input text
	return input_text;
}

// Prints the color of the text according to the input
void print_text(char *text, char *input_text, int text_len) {
	// Loop over each character in the text
	for (int i = 0; i < text_len; i++) {
		// If the inputted character is empty
		if (input_text[i] == 0) {
			// Print the character in bold
			printf(CLI_BOLD "%c", text[i]);
		}
		// Else if the inputted character is the same as the text character
		else if (input_text[i] == text[i]) {
			// Print the character in bold green
			printf(CLI_BOLD_GREEN "%c", text[i]);
		}
		// Else if the inputted character is not the same as the text character
		else if (input_text[i] != text[i]) {
			// Print the character in bold red
			printf(CLI_BOLD_RED "%c", text[i]);
		}
		// Clear the colors and fonts
		printf(CLI_RESET);
	}
	// Print a new line after the loop ends
	printf("\n");
}

int main() {
	//char string[10];
	//fgets(string, 10, stdin);

	//time_t start = time(NULL);
	//time_t end = time(NULL);
	//printf("Time taken: %li", (end - start));

	//char input = get_input();
	//if (input == 'A') {
		//stuff
	//}

	intro();

	char *text = get_text();
	int text_len = strlen(text);
	char *input_text = get_input_text(text_len);

	print_text(text, input_text, text_len);

	free(text);
	free(input_text);

	return 0;
}
