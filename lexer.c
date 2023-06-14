// COP 3402 HW 2: Lexical Analyzer
// Wyatt Nagel
// Ian Ragan

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY 500
#define MAX_IDENT 11
#define MAX_NUM 5

<<<<<<< Updated upstream
typedef struct token {
    int num;
    char *ident;
} token;

FILE *loadFile(char *filename);
char **getSource(FILE *fp, char **source);
=======
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
	token_type type;
	char ident[12];
	int num;
} Token;

FILE* loadFile(char *filename);

char** getSource(FILE *fp, char **source);
>>>>>>> Stashed changes
void printSource(char **source);

void createTokens(char** source);
void addToken(char* string);

int getType(Token t);

void printLexemeTable();
void printLexemeList();

int isNumber(char *string);
int isKeyword(char *lexeme);
int isSpecial(char c);

int progLen = 0;

Token lexemeTable[MAX_ARRAY];
int lexemeCount = 0;

int main(int argc, char **argv)
{
    // Opens file for reading
    FILE *fp = loadFile(argv[1]);

<<<<<<< Updated upstream
    char **source = NULL;
    source = getSource(fp, source);
=======
	char **source = NULL;
	source = getSource(fp, source);

	// printSource(source);

	// addToken(numbersym, "test");

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

	createTokens(source);

	printLexemeTable();
	printLexemeList();
>>>>>>> Stashed changes

    printSource(source);
}
// Function to open file for reading and checks for NULL value
<<<<<<< Updated upstream
FILE *loadFile(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file");
        exit(1);
    }
    return file;
}
char **getSource(FILE *fp, char **source)
{
    source = malloc(MAX_ARRAY * sizeof(char*));
=======
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
	// Reset file pointer to the beginning
	rewind(file);

	printf("\n");
	return file;
}
char** getSource(FILE *fp, char **source) {
	source = malloc(MAX_ARRAY * sizeof(char*));
	do {
		char *temp = malloc(12 * sizeof(char));
		fscanf(fp, "%s ", temp);
>>>>>>> Stashed changes

    int buffer;
    int i = 0;
    do {
        char *temp = malloc(12 * sizeof(char));
        fscanf(fp, "%s ", temp);

<<<<<<< Updated upstream
        if (strlen(temp) > MAX_IDENT) {}
            // error
        
        source[i] = malloc((strlen(temp) + 1) * sizeof(char));
        strcpy(source[i], temp);

        i++;
        free(temp);
    } while (!feof(fp));
=======
		source[progLen] = malloc((strlen(temp) + 1) * sizeof(char));
		strcpy(source[progLen], temp);

		progLen++;
		free(temp);
	} while (!feof(fp));
>>>>>>> Stashed changes

    // Close the file and return the program array
    fclose(fp);
    return source;
}
<<<<<<< Updated upstream
void printSource(char **source)
{
    int i = 0;
    while (source[i] != NULL)
    {
        printf("%s\n", source[i]);

        i++;
    }
    
}

// Function to check if string is a number or has other symbols in it
int isNumber(char *string)
{
    int i = strlen(string);
    while (i--) {
        if (string[i] > 47 && string[i] < 58)
            continue;
        return 0;
    }
    return 1;
=======

// Creates the lexeme table and adds each token to it
void createTokens(char** source) {
	// Loop through the entire source program
	for (int i = 0; i < progLen; i++) {
		// Current instruction to be tokenized
		char curr[12];
		strcpy(curr, source[i]);

		// If it is a special character
		if (isSpecial(curr[strlen(curr) - 1]))
		{
			char newCurr[strlen(curr)];

			memset(newCurr, '\0', sizeof(newCurr));
			strncpy(newCurr, curr, strlen(curr) - 1);
			addToken(newCurr);

			memset(newCurr, '\0', sizeof(newCurr));
			newCurr[0] = curr[strlen(curr) - 1];
			addToken(newCurr);
		}
	}
}
// Adds a lexeme token to the lexeme table
void addToken(char* string) {
	Token t;
	// Checks if it is identifier
    if (!isKeyword(string) && !isNumber(string) && !isSpecial(string[0]))
	{
		t.type = identsym;
		strcpy(t.ident, string);
		lexemeTable[lexemeCount++] = t;
	}
	else if (isSpecial(string[0]))
	{
		switch (string[0])
		{
			case '+':
				break;
			case '-':
				break;
			case '*':
				break;
			case '/':
				break;
			case '(':
				break;
			case ')':
				break;
			case '=':
				break;
			case ',':
				t.type = commasym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case '.':
				break;
			case '<':
				break;
			case '>':
				break;
			case ';':
				break;
			case ':':
				break;
			default:
				break;
		}
	}
}
// Checks if token type is a string or number
int getType(Token t) {
	if (t.type == skipsym || 
		t.type == identsym || 
		t.type == beginsym || 
		t.type == endsym || 
		t.type == ifsym || 
		t.type == thensym || 
		t.type == whilesym || 
		t.type == dosym || 
		t.type == readsym || 
		t.type == writesym ||
		isSpecial(t.ident[0]))
		return 1;
	else
		return 0;
}

// Prints the lexem table
void printLexemeTable() {
    printf("Lexeme Table:\n\n");
    printf("lexeme\t\ttoken type\n");
    printf("------------------------\n");
    for (int i = 0; i < lexemeCount; i++) {
		// Checks if lexeme is number or word
        if (getType(lexemeTable[i]))
			printf("%s\t\t%d\n", lexemeTable[i].ident, lexemeTable[i].type);
		else
			printf("%d\t\t%d\n", lexemeTable[i].num, lexemeTable[i].type);
    }
    printf("\n");
}
// Prints the lexeme list
void printLexemeList() {
    printf("Lexeme List:\n");
    for (int i = 0; i < lexemeCount; i++) {
		// Checks if to print identifier or not
		if (lexemeTable[i].type == identsym)
			printf("%d %s ", lexemeTable[i].type, lexemeTable[i].ident);
		else 
			printf("%d ", lexemeTable[i].type);
	}
    printf("\n");
}


void printSource(char **source) {
	for (int i = 0; i < progLen; i++)
		printf("%s\n", source[i]);
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
// Checks if string is a keyword or not
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
// Checks if character is special or not
int isSpecial(char c) {
	if (c == '+' || 
		c == '-' || 
		c == '*' || 
		c == '/' || 
		c == '(' || 
		c == ')' || 
		c == ',' || 
		c == '=' || 
		c == '.' || 
		c == '<' || 
		c == '>' || 
		c == ';' || 
		c == ':')
		return 1;
	return 0;
>>>>>>> Stashed changes
}