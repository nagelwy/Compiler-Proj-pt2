// COP 3402 HW 2: Lexical Analyzer
// Wyatt Nagel
// Ian Ragan

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY 500
#define MAX_IDENT 11
#define MAX_NUM 5

typedef struct token {
    int num;
    char *ident;
} token;

FILE *loadFile(char *filename);
char **getSource(FILE *fp, char **source);

int main(int argc, char **argv)
{
    // Opens file for reading
    FILE *fp = loadFile(argv[1]);

    char **source = NULL;
    source = getSource(fp, source);
}
// Function to open file for reading and checks for NULL value
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

    int buffer;
    do {

    } while (!feof(fp));

    // Close the file and return the program array
    fclose(fp);
    return source;
}