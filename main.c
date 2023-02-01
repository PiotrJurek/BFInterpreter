#include <stdio.h>
#include <string.h>

int validate(FILE* file, int printWarnings){
    int pointer = 0;
    int bracketCounter = 0;
    int charNumber = 1;

    char ch = (char) fgetc(file);
    while (ch != EOF) {
        switch (ch) {
            case '>':
                pointer++;
                if(printWarnings && pointer >= 30000){
                    printf("WARNING: Pointer outside of scope on char %d\n", charNumber);
                }
                break;
            case '<':
                pointer--;
                if(printWarnings && pointer < 0){
                    printf("WARNING: Pointer outside of scope on char %d\n", charNumber);
                }
                break;
            case '+':
            case '-':
            case ',':
                if(pointer < 0 || pointer >= 30000){
                    printf("ERROR: Writing outside of scope on char %d\n", charNumber);
                    return 1;
                }
                break;
            case '.':
                if(pointer < 0 || pointer >= 30000){
                    printf("ERROR: Reading outside of scope on char %d\n", charNumber);
                    return 1;
                }
                break;
            case '[':
                bracketCounter++;
                ch = (char) fgetc(file);
                if(ch == ']'){
                    printf("ERROR: Infinite loop on char %d\n", charNumber);
                    return 1;
                }
                charNumber++;
                continue;
            case ']':
                bracketCounter--;
                if(bracketCounter < 0){
                    printf("ERROR: ']' without corresponding '[' on char %d\n", charNumber);
                    return 1;
                }
                break;
            default:
                break;
        }
        ch = (char) fgetc(file);
        charNumber++;
    }

    if(bracketCounter != 0){
        printf("ERROR: Unclosed '[' at end of file\n");
        return 1;
    }

    fseek(file, 0, SEEK_SET);
    return 0;
}

int main(int argc, char **argv) {

    if (argc < 2) {
        printf("ERROR: No file name entered.");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("ERROR: File with the specified name does not exist.");
        return 2;
    }

    int printWarnings = 0;
    if(argc == 3){
        if(strcmp(argv[2], "-Warn") == 0){
            printWarnings = 1;
        }
        else{
            printf("ERROR: Entered not existing argument.");
            return 3;
        }
    }

    if(validate(file, printWarnings)){
        return 4;
    }

    char bytes[30000] = {0};
    char *pointer = bytes;
    int bracketCounter = 0;

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