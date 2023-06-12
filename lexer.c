// COP 3402 HW 2: Lexical Analyzer
// Wyatt Nagel
// Ian Ragan

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY 500
#define MAX_IDENT 11
#define MAX_NUM 5


typedef enum {
    skipsym = 1, identsym, numbersym, plussym, minussym,
    multsym, slashsym, xorsym, eqlsym, neqsym, lessym, leqsym,
    gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
    periodsym, becomessym, beginsym, endsym, ifsym, thensym,
    whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
    readsym, elsesym
} token_type;

char *keywords[] = {
    "const", "var", "procedure", "call", "begin", "end", "if", "then", "xor",
    "else", "while", "do", "read", "write", NULL
};

typedef struct token {
	int num;
	char *ident;
} token;

FILE* loadFile(char *filename);
char** getSource(FILE *fp, char **source);
void printSource(char **source);
int isNumber(char *string);

int main(int argc, char **argv) {
	// Opens file for reading
	FILE *fp = loadFile(argv[1]);

	char **source = NULL;
	source = getSource(fp, source);

	printSource(source);

}
// Function to open file for reading and checks for NULL value
FILE* loadFile(char *filename) {
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("Error opening file");
		exit(1);
	}

	char c;
	printf("Source Program:\n");
	while ((c = fgetc(file)) != EOF) {
		putchar(c);
	}
	rewind(file);  // Reset file pointer to the beginning

	printf("\n\n");


	return file;
}
char** getSource(FILE *fp, char **source) {
	source = malloc(MAX_ARRAY * sizeof(char*));
	int i = 0;
	do {
		char *temp = malloc(12 * sizeof(char));
		fscanf(fp, "%s ", temp);

		if (strlen(temp) > MAX_IDENT) {
		}
		// error

		source[i] = malloc((strlen(temp) + 1) * sizeof(char));
		strcpy(source[i], temp);

		i++;
		free(temp);
	} while (!feof(fp));

	// Close the file and return the program array
	fclose(fp);
	return source;
}
void printSource(char **source) {
	int i = 0;
	while (source[i] != NULL) {
		printf("%s\n", source[i]);

		i++;
	}

}

// Function to check if string is a number or has other symbols in it
int isNumber(char *string) {
	int i = strlen(string);
	while (i--) {
		if (string[i] > 47 && string[i] < 58)
			continue;
		return 0;
	}
	return 1;
}
