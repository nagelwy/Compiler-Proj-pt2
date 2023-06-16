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
    "buffer", "const", "var", "procedure", "call", "begin", "end", "if", "then", "xor",
    "else", "while", "do", "read", "write", "skip", "becomes", NULL
};

typedef struct Token {
	token_type type;
	char ident[12];
	int num;
} Token;

FILE* loadFile(char *filename);

char** getSource(FILE *fp, char **source);
void printSource(char **source);

void createTokens(char** source);
void addToken(char* string);

int checkNumber(int num);
int getType(Token t);

void printLexemeTable();
void printLexemeList();

int isNumber(char *string);
int isKeyword(char *lexeme);
int isSpecial(char c);
int isSpecialCase(char *string);

int progLen = 0;

Token lexemeTable[MAX_ARRAY];
int lexemeCount = 0;

int main(int argc, char **argv)
{
    // Opens file for reading
    FILE *fp = loadFile(argv[1]);

    char **source = NULL;
    source = getSource(fp, source);FILE *loadFile(char *filename);

	createTokens(source);

	// printLexemeTable();
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
	// Reset file pointer to the beginning
	rewind(file);

	printf("\n");
	return file;
}
// Function that scans the source program file
char** getSource(FILE *fp, char **source) {
	source = malloc(MAX_ARRAY * sizeof(char*));
	do {
		char temp[50];
		fscanf(fp, "%s ", temp);

		if (strcmp(temp, "/*") == 0)
		{
			while(strcmp(temp, "*/") != 0)
			{
				fscanf(fp, "%s", temp);
			}
			fscanf(fp, "%s", temp);
		}

		source[progLen] = malloc((strlen(temp) + 1) * sizeof(char));
		strcpy(source[progLen], temp);

		progLen++;
	} while (!feof(fp));

	// Close the file and return the program array
	fclose(fp);
	return source;
}

// Creates the lexeme table and adds each token to it
void createTokens(char** source) {
	printf("\nLexeme Table:\n");
    printf("\tlexeme\t\ttoken type\n");
	// Loop through the entire source program
	for (int i = 0; i < progLen; i++) {
		if (strlen(source[i]) > 12 && isSpecial(source[i][strlen(source[i]) - 1]))
		{
			printf("Error : Identifier names cannot exceed 11 characters\n");

			char special[2];
			special[0] = source[i][strlen(source[i]) - 1];
			special[1] = '\0';
			addToken(special);

			continue;
		}
		else if (strlen(source[i]) > 11)
		{
			printf("Error : Identifier names cannot exceed 11 characters\n");
			continue;
		}
		
		// Current instruction to be tokenized
		char curr[12];
		strcpy(curr, source[i]);

		char temp[3] = {curr[strlen(curr) - 2], curr[strlen(curr) - 1]};

		// If it is a special character
		if (isSpecial(curr[strlen(curr) - 1]) && !isSpecialCase(temp) && strlen(curr) > 1)
		{
			char newCurr[strlen(curr)];

			memset(newCurr, '\0', sizeof(newCurr));
			strncpy(newCurr, curr, strlen(curr) - 1);
			addToken(newCurr);

			memset(newCurr, '\0', sizeof(newCurr));
			newCurr[0] = curr[strlen(curr) - 1];
			addToken(newCurr);

			continue;
		}
		
		addToken(curr);
	}
}
// Adds a lexeme token to the lexeme table
void addToken(char* string) {
	Token t;

	// Flag that checks for errors
	int errorFlag = 0;

	// Checks if it is identifier
    if (isKeyword(string) == 0 && 
		!isNumber(string) && 
		!isSpecial(string[0]) && 
		!isSpecialCase(string))
	{
		if (string[0] > 47 && string[0] < 58) {
			printf("Error : Identifiers cannot begin with a digit\n");
			return;
		} else if (string[0] <= 96 || string[0] >= 123) {
			printf("Error : Invalid Symbol\n");
			return;
		}	

		t.type = identsym;
		strcpy(t.ident, string);
		lexemeTable[lexemeCount++] = t;
	}
	// Checks if it is an operator
	else if (isSpecial(string[0]) && !isSpecialCase(string))
	{	
		switch (string[0])
		{
			case '+':
				t.type = plussym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case '-':
				t.type = minussym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case '*':
				t.type = multsym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case '/':
				t.type = slashsym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case '(':
				t.type = lparentsym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case ')':
				t.type = rparentsym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case '=':
				t.type = eqlsym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case ',':
				t.type = commasym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case '.':
				t.type = periodsym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case '<':
				t.type = lessym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case '>':
				t.type = gtrsym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case ';':
				t.type = semicolonsym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case ':':
				t.type = 9999;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			default:
				break;
		}
	}
	// Checks if it is a special case
	else if (isSpecialCase(string))
	{
		switch (string[0])
		{
			case ':':
				t.type = becomessym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case '<':
				t.type = leqsym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case '>':
				t.type = geqsym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			default:
				break;
		}
		// else if (strcmp(string, "<>"))
		// {
		// 	t.type = xorsym;
		// 	strcpy(t.ident, string);
		// 	lexemeTable[lexemeCount++] = t;
		// }
	}
	else if (isKeyword(string) > 0)
	{
		switch (isKeyword(string))
		{
			case 1:
				t.type = constsym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case 2:
				t.type = varsym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case 3:
				t.type = procsym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case 4:
				t.type = callsym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case 5:
				t.type = beginsym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case 6:
				t.type = endsym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case 7:
				t.type = ifsym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case 8:
				t.type = thensym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case 9:
				t.type = xorsym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case 10:
				t.type = elsesym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case 11:
				t.type = whilesym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case 12:
				t.type = dosym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case 13:
				t.type = readsym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case 14:
				t.type = writesym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case 15:
				t.type = skipsym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			case 16:
				t.type = becomessym;
				strcpy(t.ident, string);
				lexemeTable[lexemeCount++] = t;
				break;
			default:
				break;
		}
	}
	else if (isNumber(string) > 0)
	{
		if (checkNumber(isNumber(string)) > 5) {
			printf("Error : Numbers cannot exceed 5 digits\n");
			errorFlag++;
		} else {
			t.type = numbersym;
			t.num = isNumber(string);
			lexemeTable[lexemeCount++] = t;
		} 
	}
	else
	{
		printf("Error : Invalid Symbol\n");
		errorFlag++;
	}

	// Prints the token depending on token type
	if (!errorFlag)
	{
		if (t.type != numbersym)
			printf("\t%s\t\t%d\n", t.ident, t.type);
		else 
			printf("\t%d\t\t%d\n", t.num, t.type);
	}
}
int checkNumber(int num) {
	int i = 0;
	for (i = 0; num != 0; i++, num = num/10) {}
	return i;
}
// Checks if token type is a string or number
int getType(Token t) {
	if ((t.type == constsym ||
		t.type == varsym ||
		t.type == procsym ||
		t.type == callsym ||
		t.type == beginsym ||
		t.type == endsym ||
		t.type == ifsym ||
		t.type == thensym ||
		t.type == xorsym ||
		t.type == elsesym ||
		t.type == whilesym ||
		t.type == dosym ||
		t.type == readsym ||
		t.type == writesym ||
		t.type == skipsym ||
		t.type == becomessym ||
		t.type == identsym ||
		isSpecial(t.ident[0])) &&
		t.type != numbersym)
		return 1;
	else
		return 0;
}
// Function to check if string is a number or has other symbols in it
int isNumber(char *string) {
	int i = strlen(string);
	while (i--) {
		if (string[i] > 47 && string[i] < 58)
			continue;
		return 0;
	}
	return atoi(string);
}
// Checks if string is a keyword or not
int isKeyword(char *string) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(keywords[i], string) == 0) {
			return i;
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
}
// Checks if string is one of the the following
int isSpecialCase(char *string) {
	if (!strcmp(string, ":=") || 
		!strcmp(string, "<>") || 
		!strcmp(string, "<=") || 
		!strcmp(string, ">="))
		return 1;
	return 0;
}
// Prints the lexeme list
void printLexemeList() {
    printf("\nToken List:\n");
    for (int i = 0; i < lexemeCount; i++) {
		// Checks if to print identifier or not
		if (lexemeTable[i].type == identsym)
			printf("%d %s ", lexemeTable[i].type, lexemeTable[i].ident);
		else if (lexemeTable[i].type == numbersym)
			printf("%d %d ", lexemeTable[i].type, lexemeTable[i].num);
		else 
			printf("%d ", lexemeTable[i].type);
	}
    printf("\n");
}

void printSource(char **source) {
	for (int i = 0; i < progLen; i++)
		printf("%s\n", source[i]);
}