#include <stdio.h>

int main(int argc, char **argv) {
    char bytes[30000] = {0};
    char *pointer = bytes;
    int bracketCounter = 0;

    if (argc < 2) {
        printf("No file name entered.");
        return 0;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("File with the specified name does not exist.");
        return 0;
    }

    char ch = (char) fgetc(file);
    while (ch != EOF) {
        switch (ch) {
            case '>':
                pointer++;
                break;
            case '<':
                pointer--;
                break;
            case '+':
                (*pointer)++;
                break;
            case '-':
                (*pointer)--;
                break;
            case '.':
                printf("%c", *pointer);
                break;
            case ',':
                scanf("%c", pointer);
                break;
            case '[':
                bracketCounter++;
                if (*pointer == 0) {
                    int endBracketCounter = bracketCounter - 1;
                    do {
                        ch = (char) fgetc(file);
                        if (ch == '[') bracketCounter++;
                        else if (ch == ']') bracketCounter--;
                    } while (bracketCounter != endBracketCounter);
                }
                break;
            case ']':
                bracketCounter--;
                if (*pointer != 0) {
                    int endBracketCounter = bracketCounter + 1;
                    do {
                        fseek(file, -2, SEEK_CUR);
                        ch = (char) fgetc(file);
                        if (ch == '[') bracketCounter++;
                        else if (ch == ']') bracketCounter--;
                    } while (bracketCounter != endBracketCounter);
                }
                break;
            default:
                break;
        }
        ch = (char) fgetc(file);
    }

    return 0;
}