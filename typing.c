// Author: Muhammed Ali Dilek (xemeds)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUMER_OF_TEXTS 3

// Gets a random text from the texts file
char *get_text() {
	// Get the time
	time_t t;

	// Initialize the random number generator
	srand((unsigned) time(&t));

	// Get a random line number for the text
	int random_line_number = rand() % NUMER_OF_TEXTS;

	// Open the file
	FILE *file = fopen("texts.txt", "r");

	// Check if the file pointer is empty
	if (file != NULL)
	{
		// Create the max read size per line
	    char line[256];

	    // Declare the line number of the file
	    int line_number = 0;

	    // Read each line one by one
	    while (fgets(line, sizeof line, file) != NULL)
	    {
	    	// If the current line number is the random line number
	        if (line_number == random_line_number)
	        {
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
	        else
	        {
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

	char *text = get_text();
	printf("%s", text);
	free(text);

	return 0;
}
