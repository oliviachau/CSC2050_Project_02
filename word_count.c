#include <stdio.h>
#include <stdbool.h>

void print_wc(FILE *fp){
	int ch = fgetc(fp);
	int chars = 0;
	int words = 0;
	int lines = 0;
	bool isWord = true;

	while(ch != EOF){
		ch = fgetc(fp);
		chars ++; //char should be updated every time a char is read		
		
		//ensures a word is not counted until consecutive whitespace is over
		if((char)ch == ' ' || (char)ch == '\n' || (char)ch == '\t'){
			isWord = false;
		}
		
		else if(!isWord){
			isWord = true;
			words++;
		}

		//increments number of lines when a newline char is read
		if((char)ch == '\n'){
			lines ++;
		}
	}
	
	//print out number of lines, words, and chars on separate lines
	printf("%d\n", lines);
	printf("%d\n", words);
	printf("%d\n", chars);
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
	
	//print number of lines, words, and characters
	print_wc(fp);

	//close fp if it was not stdin
	if(fp != stdin){
		fclose(fp);
	}	

	return 0;
}
