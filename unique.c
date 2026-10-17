#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_lines(FILE *fp){
	size_t buffer_size = 0;
	char *current_line = NULL;
	char *prev_line = NULL;

	while(getline(&current_line, &buffer_size, fp) != -1){
		//if prev_line is null or the two lines are different, print the current line
		if(prev_line == NULL || strcmp(prev_line, current_line) != 0){
			printf("%s", current_line);

			//move prev_line to the next line
			free(prev_line);
			prev_line = current_line;
			
			//getline allocates a new buffer because prev_line is now using current_line
			current_line = NULL;
			buffer_size = 0; 
		}
	}
	
	//free both pointers
	free(current_line);
	free(prev_line);
}

int main(int argc, char *argv[]){
	//set file pointer to stdin as default
        FILE *fp = stdin;

        if(argc > 2){
                printf("Too many arguments.");
                return 0;
        }

        //check if command line argument is a file name
        if(argc == 2){
                fp = fopen(argv[1], "r");
                //check if file pointer is null
                if(fp == NULL){
                        printf("Error opening file.");
                        return 0;
                }
        }

        //print the unique lines 
	print_lines(fp);

        //close fp if it was not stdin
        if(fp != stdin){
                fclose(fp);
        }

	return 0;
}

