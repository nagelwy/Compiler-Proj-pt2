// COP 3402 HW 2: Lexical Analyzer
// Wyatt Nagel
// Ian Ragan

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY 500
#define MAX_IDENT 11
#define MAX_NUM 5

FILE* loadFile(char *filename);
char** getSource(FILE *fp, char **source);
void printSource(char **source);
int isNumber(char *string);
void addToken(int token, char *lexeme);
void printLexemeTable();
void printLexemeList();
int isKeyword(char *lexeme);

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

typedef struct Token {
	int num;
	char ident[12];
} Token;

Token lexemeTable[MAX_ARRAY];
int lexemeCount = 0;


int main(int argc, char **argv) {
	// Opens file for reading
	FILE *fp = loadFile(argv[1]);

	char **source = NULL;
	source = getSource(fp, source);

	printSource(source);

	//addToken(numbersym, "test");

	/* Here we can start the switch and go through the array (probably a while loop)
	 * We check if it's a character, digit, or symbol.
	 * we check if the characters are a special keyword via the isKeyword function
	 * use the add token function and add them and then call the print function
	 *
	 * if the token is a keyword it will return the number from the isKeyword function,
	 * if it isn't a keyword the token will be the identsym
	 * i.e.  int token = isKeyword(lexeme) ? isKeyword(lexeme) : identsym;
             addToken(token, lexeme);
	 *
	 * then we check the numbers and add those to the token
	 * i.e. addToken(numbersym, lexeme);
	 *
	 * then we check the symbols and use a switch statement and add them that way
	 * i.e.  case '+': addToken(plussym, lexeme); break;
	 */

	printLexemeTable();
	printLexemeList();

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

void addToken(int token, char *lexeme) {
    Token t;
    t.num = token;
    strncpy(t.ident, lexeme, sizeof(t.ident));
    lexemeTable[lexemeCount++] = t;
}



void printLexemeTable() {
    printf("Lexeme Table:\n\n");
    printf("lexeme\t\ttoken type\n");
    printf("------------------------\n");
    for (int i = 0; i < lexemeCount; i++) {
        printf("%s\t\t%d\n", lexemeTable[i].ident, lexemeTable[i].num);
    }
    printf("\n");
}


void printLexemeList() {
    printf("Lexeme List:\n");
    for (int i = 0; i < lexemeCount; i++) {
        printf("%d %s ", lexemeTable[i].num, lexemeTable[i].ident);
    }
    printf("\n");
}


int isKeyword(char *lexeme) {
	int i;
    for (i = 0; keywords[i] != NULL; i++) {
        if (strcmp(keywords[i], lexeme) == 0) {
            switch (i) {
                case 0:
                	return constsym;
                case 1:
                	return varsym;
                case 2:
                	return procsym;
                case 3:
                	return callsym;
                case 4:
                	return beginsym;
                case 5:
                	return endsym;
                case 6:
                	return ifsym;
                case 7:
                	return thensym;
                case 8:
                	return xorsym;
                case 9:
                	return elsesym;
                case 10:
                	return whilesym;
                case 11:
                	return dosym;
                case 12:
                	return readsym;
                case 13:
                	return writesym;
                default:
                    return 0;   // Invalid keyword
            }
        }
    }
    return 0; // Not a keyword
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
