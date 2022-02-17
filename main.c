#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int sudoku[9 * 9];

char *appendStrings(const char *old, const char *new);

unsigned int fileExists(char *path);

/*
 *
    1   2   3   4   5   6   7   8   9
    10  11  12  13  14  15  16  17  18
    19  20  21  22  23  24  25  26  27
    28  29  30  31  32  33  34  35  36
    37  38  39  40  41  42  43  44  45
    46  47  48  49  50  51  52  53  54
    55  56  57  58  59  60  61  62  63
    64  65  66  67  68  69  70  71  72
    73  74  75  76  77  78  79  80  81
 *
 */

//returns the array index of the given position.
//see the table above for an explanation.
static int getIndexBySudokuPosition(int column, int field) {
    int index = 0;
    for (int i = 0; i < column - 1; i++) {
        index = index + 9;
    }
    index = index + field;
    return index - 1;
}

void decodeSudokuFromFile(char path[], sudoku s) {
    //read file from path and parse into sudoku
    //WARNING: return can be empty / something could go wrong
}

void encodeSudokuToFile(const char *path, const sudoku s) {
    //write file from sudoku data into a file under path
    //WARNING: something could go wrong
    for (int i = 0; i < 1000; i++) {
        size_t length = 2 + strlen(path) + 3;
        if (i != 0) length += 4;
        char *newPath = malloc(length);
        if (i != 0) {
            sprintf(newPath, "%s%s%s%i%s", "./", path, " (", i, ").su");
        } else {
            sprintf(newPath, "%s%s%s", "./", path, ".su");
        }
        unsigned int saved = 0;
        if (!fileExists(newPath)) {
            FILE *fileToWrite = fopen(newPath, "w+");
            for (unsigned int row = 0; row < 9; row++) {
                char *rowString = malloc(11);
                for (unsigned int column = 0; column < 9; column++) {
                    char value[1];
                    sprintf(value, "%d", s[row * 9 + column]);
                    memcpy(rowString + column, value, 1);
                }
                memcpy(rowString + 9, "\n\0", 2);
                fputs(rowString, fileToWrite);
                free(rowString);
            }
            saved = 1;
            fclose(fileToWrite);
            printf("%s%s%s\n", "Saved file ", newPath, " successfully!");
        }
        free(newPath);
        if (saved == 1) break;
    }
}

unsigned int fileExists(char *path) {
    FILE *file = fopen(path, "r");
    unsigned int exists = file != NULL;
    fclose(file);
    return exists;
}

//print sudoku to the console...
void printSudoku(sudoku s) {
    printf("|-----------------------------------|\n");
    for (int row = 1; row <= 9; ++row) {

        for (int field = 1; field <= 9; ++field) {
            if (field == 1) {
                printf("| ");
            }
            int index = getIndexBySudokuPosition(row, field);
            printf(" %d ", s[index]);
            if (field == 3 || field == 6 || field == 9) {
                printf(" | ");
            }
        }

        if (row == 3 || row == 6 || row == 9) {
            printf("\n|-----------------------------------|");
        }

        printf("\n");
    }
}

void input(sudoku s) {
    //123456789
    //123456781
    //...
    //0 = leer
    //ask for input file (.su)

    //read input file
    decodeSudokuFromFile("path", s);

    //if valid: write data into "s" by performing array manipulation such as
    s[0] = 1;
    s[78] = 5;
    s[54] = 2;
    s[23] = 9;

    //print sudoku to the console
    printSudoku(s);
}

void solve(const sudoku input, sudoku output) {
    //solve sudoku
    //...

    //write solution into output sudoku
    for (int i = 0; i < 81; ++i) {
        output[i] = input[i];
    }
}

void output(const sudoku s) {
    //print solved sudoku to the console
    printSudoku(s);

    //ask the user if he wants to save the solution (Y/n)

    const char input[1];
    printf("Do you want to save the solution?\nYour answer (Y/n):");
    scanf("%s", input);
    if (strcmp(input, "y") == 0 || strcmp(input, "Y") == 0) {
        char fileName[30];
        printf("Please enter a file name:");
        scanf("%s", fileName);
        const char *completeFileName = appendStrings(fileName, "_solution");
        encodeSudokuToFile(completeFileName, s);
    }

    //if no finish application

    //if yes, create a new file [input_name]_solution.su
    //HINT: HANDLE EDGE CASES!
    //if such a file already exists, give numbers for example:
    //[input_name]_solution (1).su


    //print a success message + path into the console
    printf("Program finished!\n");
}

char *appendStrings(const char *old, const char *new) {
    char *out = malloc(strlen(old) + strlen(new) + 1);
    sprintf(out, "%s%s", old, new);
    return out;
}

int main() {
    //------example to create and manipulate a sudoku-------
    sudoku s = {};

    //get the index for the field 1 / 8
    int index = getIndexBySudokuPosition(1, 8);

    //write a value into the field
    s[index] = 7;

    printf("The value of field 8 in column 1 is %d. \n", s[index]);

    //------main program-------
    sudoku i = {};
    sudoku o = {};

    input(i);
    solve(i, o);
    output(o);

    return 0;
}
