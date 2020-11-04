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
	printf("Press any key to continue...\n> ");
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
	        	// Get the length of the line
	        	int text_len = strlen(line);

	        	// If the text is not the last text
	        	if (random_line_number != NUMBER_OF_TEXTS - 1) {
	        		// Carry the end of the string to the last character of the line (get rid of \n)
	        		line[text_len - 1] = '\0';

	        		// Decrease the length of the line
	        		text_len--;
	        	}

	        	// Allocate space for a new text
	        	char *text = malloc(text_len + 1);

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
	// Allocate space for a new text
	char *input_text = malloc(text_len + 1);

	// For each character in the input text
	for (int i = 0; i < text_len; i++) {
		// Set it to null
		input_text[i] = 0;
	}

	// Set the last character as the null terminator
	input_text[text_len] = '\0';

	// Return the pointer to the newly allocated input text
	return input_text;
}

// Finds the index of the first empty character in the input text
int find_last_index(char *input_text, int text_len) {
	// For each character in the input text
	for (int i = 0; i < text_len; i++) {
		// If the character is empty
		if (input_text[i] == 0) {
			// Return the index
			return i;
		}
	}
}

// Returns if the user has typed correctly untill the last empty charracter
int typing_correct(char *text, char *input_text, int text_len) {
	// Get the index of the first empty character in the input text
	int last_index = find_last_index(input_text, text_len);

	// Loop over each character in the text until the last empty character
	for (int i = 0; i < last_index; i++) {
		// If the character in the text is not the same as the input text
		if (text[i] != input_text[i]) {
			// Returns 0
			return 0;
		}
	}

	// After the loop ends if they were all the same return 1
	return 1;
}

// Prints the color of the text according to the input
void print_text(char *text, char *input_text, int text_len) {
	clear();

	// If the user is typing correctly
	if (typing_correct(text, input_text, text_len) == 1) {
		// Change the color to bold green
		printf(CLI_BOLD_GREEN);
	}
	// Else if the user is not typing correctly
	else {
		// Change the color to bold red
		printf(CLI_BOLD_RED);
	}

	// Print the blinker
	printf("\n\n\n\n\t\t\t\t     ■\n");

	printf(CLI_BOLD_YELLOW);
	printf("\t\t  ==+==+==+==+==+==+==+==+==+==+==+==+==+==\n\n");
	printf(CLI_RESET);

	// Loop over each character in the text
	for (int i = 0; i < text_len; i++) {
		// If the inputted character is empty
		if (input_text[i] == 0) {
			// Print the character in bold
			printf(CLI_BOLD "%c", text[i]);
		}
		// Else if the inputted character is the same as the text character
		else if (input_text[i] == text[i]) {
			// If the character is a space
			if (text[i] == ' ') {
				// Print a underscore in bold green
				printf(CLI_BOLD_GREEN "_");
			}
			// Else
			else {
				// Print the character in bold green
				printf(CLI_BOLD_GREEN "%c", text[i]);
			}
		}
		// Else if the inputted character is not the same as the text character
		else if (input_text[i] != text[i]) {
			// If the character is a space
			if (text[i] == ' ') {
				// Print a underscore in bold red
				printf(CLI_BOLD_RED "_");
			}
			// Else
			else {
				// Print the character in bold red
				printf(CLI_BOLD_RED "%c", text[i]);
			}
		}
		// Clear the colors and fonts
		printf(CLI_RESET);
	}
	// Print a new line after the loop ends
	printf("\n");

	printf(CLI_BOLD_YELLOW);
	printf("\n\t\t  ==+==+==+==+==+==+==+==+==+==+==+==+==+==\n\n");
	printf(CLI_RESET);

	// Print some space for the input to be in the middle
	printf("\t\t\t\t     ");
}

// Adds the inputted character to the input text accordingly
void add_input(char *text, char *input_text, int text_len, char input) {
	// Get the index of the first empty character in the input text
	int last_index = find_last_index(input_text, text_len);

	// If the input is a backspace and not the first input
	if (input == 127 && last_index != 0) {
		// Set the character before the first empty cell in the input text to empty (delete the previous input)
		input_text[last_index - 1] = 0;
	}

	// Else if the last character of the input text is empty and not a backspace
	else if (input_text[text_len - 1] == 0 && input != 127) {
		// Set the input as the first empty character in the input text (append the input)
		input_text[last_index] =  input;
	}
}

// Checks if the user has finished typing the text
int check(char *text, char *input_text) {
	return strcmp(text, input_text);
}

// Calculates the number of words in the text
int cal_words(char *text, int text_len) {
	// Initialize the word count
	int word_count = 0;

	// Loop over each character 
	for (int i = 0; i < text_len; i++) {
		// If the character is a space
		if (text[i] == ' ') {
			// Increment the word count
			word_count++;
		}
	}

	// Increment the word count by one and return it
	return word_count + 1;
}

// Calculates the speed
float cal_speed(char *text, int text_len, time_t start_time, time_t end_time) {
	// Get the number of words in the text
	int word_count = cal_words(text, text_len);

	// Set the time taken in minutes
	float time_taken = ((float)(end_time - start_time)) / 60;

	// Return the speed
	return word_count / time_taken;
}

// Prints the speed with color
void print_speed(float speed) {
	printf(CLI_BOLD_CYAN);
	printf("\n\t\t\t      Speed: ");
	printf(CLI_RESET CLI_BOLD);

	// Print the speed up to two decimal places
	printf("%.2f", speed);

	printf(CLI_RESET);
	printf(" WPM\n\n\n");

	printf(CLI_RESET);
}


// Frees the texts
void free_texts(char *text, char *input_text) {
	// Free the text
	free(text);
	// Free the input text
	free(input_text);
}

int main() {
	// Introduction
	intro();

	// Get a random text
	char *text = get_text();

	// Get the length of the text
	int text_len = strlen(text);

	// Get the input text
	char *input_text = get_input_text(text_len);

	// Initialize the input character
	char input;

	// Initialize the start time
	time_t start_time = 0;

	// Typing loop
	while (1) {
		// Print the text
		print_text(text, input_text, text_len);

		// If the input is finish
		if (check(text, input_text) == 0) {
			// Get the end time
			time_t end_time = time(NULL);

			// Calculate the speed
			float speed = cal_speed(text, text_len, start_time, end_time);

			// Print the speed
			print_speed(speed);

			// Free the texts
			free_texts(text, input_text);

			// Exit the program
			return 0;
		}

		// Get the input
		input = get_input();

		// If the start time is 0
		if (start_time == 0) {
			// Get the start time
			start_time = time(NULL);
		}

		// If the input is the escape key
		if (input == 27) {
			// Print a new line
			printf("\n");

			// Free the texts
			free_texts(text, input_text);

			// Exit the program
			return 0;
		}

		// Add the input
		add_input(text, input_text, text_len, input);
	}

	// Free the texts
	free_texts(text, input_text);

	return 0;
}
