#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <errno.h>

typedef enum {
    false = 0, true = !false
} bool;

typedef int sudoku[9 * 9];

sudoku IMPORT_SUDOKU;
char DIRECTORY[209];

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
static int getIndexBySudokuPosition(int row, int column) {
    int index = 0;
    for (int i = 0; i < row - 1; i++) {
        index = index + 9;
    }
    index = index + column;
    return index - 1;
}

/* msleep(): Sleep for the requested number of milliseconds. */
int msleep(long msec) {
    struct timespec ts;
    int res;

    if (msec < 0) {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

//fills the given row parameter with according sudoku row values
void getRowValuesByIndex(const sudoku s, int index, int row[9]) {
    for (int field = 1; field <= 9; field++) {
        row[field - 1] = s[getIndexBySudokuPosition(index, field)];
    }
}

//fills the given column parameter with according sudoku row values
void getColumnValuesByIndex(const sudoku s, int index, int column[9]) {
    for (int field = 1; field <= 9; field++) {
        column[field - 1] = s[getIndexBySudokuPosition(field, index)];
    }
}

//fills the given column parameter with according sudoku row values
void getBoxValuesByIndex(const sudoku s, int row, int column, int box[9]) {
    int columnStart, columnEnd, rowStart, rowEnd;

    //1-3
    if (row < 4) {
        rowStart = 1,
                rowEnd = 3;
    }
        //4-6
    else if (row < 7) {
        rowStart = 4,
                rowEnd = 6;
    }
        //7-9
    else {
        rowStart = 7,
                rowEnd = 9;
    }

    //1-3
    if (column < 4) {
        columnStart = 1,
                columnEnd = 3;
    }
        //4-6
    else if (column < 7) {
        columnStart = 4,
                columnEnd = 6;
    }
        //7-9
    else {
        columnStart = 7,
                columnEnd = 9;
    }

    int i = 0;
    for (int rowIndex = rowStart; rowIndex <= rowEnd; rowIndex++) {
        for (int columnIndex = columnStart; columnIndex <= columnEnd; columnIndex++) {
            box[i] = s[getIndexBySudokuPosition(rowIndex, columnIndex)];
            i++;
        }
    }
}

int decodeSudokuFromFile(char path[259]) {
    //read file from path and parse into sudoku
    //WARNING: return can be empty / something could go wrong
    char lineFromFile[9] = {};
    FILE *stream;
    stream = fopen(path, "r");
    int row = 0;
    int counter = 0;
    if (stream != NULL) {
        while (row < 9) {
            fscanf(stream, "%s", lineFromFile);
            for (int position = 0; position < 9; position++) {
                // Deactivated as long as getIndexBySudokuPosition is broken
                //int index = t[getIndexBySudokuPosition(position, row)];
                char singleDigit = lineFromFile[position];
                int sudokuNumber = singleDigit - '0';
                //t[index] = sudokuNumber;
                IMPORT_SUDOKU[getIndexBySudokuPosition(row + 1, position + 1)] = sudokuNumber;
                counter++;
            }
            row++;
        }
    } else {
        return 1;
    }
    fclose(stream);

    return 0;
}

void encodeSudokuToFile(const char *path, const sudoku s) {
    //write file from sudoku data into a file under path
    //WARNING: something could go wrong
    unsigned long int index = 0;
    unsigned int saved = 0;
    while (!saved) {
        size_t length = 2 + strlen(path) + 3;
        if (index != 0) length += 4;
        char *newPath = malloc(length);
        if (index != 0) {
            sprintf(newPath, "%s%s%s%s%lu%s", DIRECTORY, "/", path, " (", index, ").su");
        } else {
            sprintf(newPath, "%s%s%s%s", DIRECTORY, "/", path, ".su");
        }
        if (!fileExists(newPath)) {
            FILE *fileToWrite = fopen(newPath, "w+");
            for (unsigned int row = 0; row < 9; row++) {
                char *rowString = malloc(11);
                for (unsigned int column = 0; column < 9; column++) {
                    char value[100];
                    sprintf(value, "%d", s[row * 9 + column]);
                    memcpy(rowString + column, value, 1);
                }
                memcpy(rowString + 9, "\n\0", 2);
                fputs(rowString, fileToWrite);
                free(rowString);
            }
            saved = 1;
            fclose(fileToWrite);
            printf("%s%s%s\n", "Successfully saved file ", newPath, "!");
        }
        free(newPath);
        index++;
    }
}

unsigned int fileExists(char *path) {
    FILE *file = fopen(path, "r");
    unsigned int exists = file != NULL;
    fclose(file);
    return exists;
}

//print sudoku to the console...
void printSudoku(const sudoku s) {
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

int input() {
    //ask for input file (.su)
    char fileName[50] = {};
    char path[259] = {};
    printf("Please provide the full path to a .su file:");
    scanf("%s", DIRECTORY);
    printf("Please provide the file name:");
    scanf("%s", fileName);
    sprintf(path, "%s%s%s%s", DIRECTORY, "/", fileName, ".su");

    printf("Detected path: %s\n", path);

    //Delay for better readability
    msleep(2000);

    //read input file
    if (!decodeSudokuFromFile(path)) {
        //print sudoku to the console
        printf("The following sudoku puzzle will be solved:\n");

        printSudoku(IMPORT_SUDOKU);
    } else {
        printf("Something went wrong while reading the content of the given path.\n");
        return 1;
    }
    return 0;
}

bool arrayContains(int value, const int array[9]) {
    for (int i = 0; i < 9; i++) {
        if (array[i] == value) {
            return true;
        }
    }
    return false;
}

//algorithm which correctly fills empty sudoku fields
bool solve(sudoku s) {
    //row index of an empty field
    int row;

    //column index of an empty field
    int column;

    //loops through every field in sudoku and searches for empty fields
    bool foundField = false;
    for (int rowIndex = 1; rowIndex <= 9; rowIndex++) {
        for (int columnIndex = 1; columnIndex <= 9; columnIndex++) {
            //if value is 0 -> field is empty
            if (s[getIndexBySudokuPosition(rowIndex, columnIndex)] == 0) {
                row = rowIndex;
                column = columnIndex;

                foundField = true;
                break;
            }
        }

        //stop search if field was found
        if (foundField == true) {
            break;
        }
    }

    //if no field was found stop recursive call -> done
    if (foundField == false) return true;

    //create individual arrays for the current index / row-column position
    int rowArray[9] = {};
    int columnArray[9] = {};
    int boxArray[9] = {};
    getRowValuesByIndex(s, row, rowArray);
    getColumnValuesByIndex(s, column, columnArray);
    getBoxValuesByIndex(s, row, column, boxArray);

    //test out every value between 1 - 9
    for (int guess = 1; guess <= 9; guess++) {

        //check if the row would be correct with guess as value
        if (arrayContains(guess, rowArray) == true) {
            continue;
        }

        //check if the column would be correct with guess as value
        if (arrayContains(guess, columnArray) == true) {
            continue;
        }

        //check if the box would be correct with guess as value
        if (arrayContains(guess, boxArray) == true) {
            continue;
        }

        //at this point guess is correct
        s[getIndexBySudokuPosition(row, column)] = guess;

        if (solve(s)) return true;
        s[getIndexBySudokuPosition(row, column)] = 0;
    }
    return false;
}

void output(const sudoku s) {
    //print solved sudoku to the console
    printSudoku(s);

    //ask the user if he wants to save the solution (Y/n)

    char input[1] = {};
    printf("Do you want to save the solution?\nYour answer (Y/n):");
    scanf("%s", input);
    if (strcmp(input, "y") == 0 || strcmp(input, "Y") == 0) {
        char fileName[50] = {};
        printf("Please enter a file name:");
        scanf("%s", fileName);

        char completeFileName[100] = {};

        sprintf(completeFileName, "%s%s", fileName, "_solution");

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

int main() {
    //------main program-------
    if (input()) {
        return 1;
    }

    //Delay for better readability
    msleep(400);

    printf("Solving the sudoku puzzle...\n");

    //Delay for better readability
    // msleep(2500);
    //copySudoku(IMPORT_SUDOKU, o);

    solve(IMPORT_SUDOKU);

    output(IMPORT_SUDOKU);

    return 0;
}
