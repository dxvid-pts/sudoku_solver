#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum {
    false = 0, true = !false
} bool;

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

void copySudoku(const sudoku i, sudoku o) {
    for (int index = 0; index <= 81; index++) {
        o[index] = i[index];
    }
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

bool arrayContains(int value, const int array[9]) {
    for (int i = 0; i < 9; i++) {
        if (array[i] == value) {
            return true;
        }
    }
    return false;
}

bool rowCorrect(const int row[9]) {
    //checks every field in the row (1-9)
    for (int innerField = 1; innerField <= 9; ++innerField) {
        //get the value of the field
        int innerValue = row[getIndexBySudokuPosition(1, innerField)];

        //skip if empty
        if (innerValue == 0) {
            continue;
        }

        //loop through the row again and check if another field has the same value
        for (int outerField = 1; outerField <= 9; ++outerField) {
            //skip same if the field is the same
            if (outerField == innerField) {
                continue;
            }

            //get value of the comparing field
            int outerValue = row[getIndexBySudokuPosition(1, outerField)];

            //if fields from both loops have the same value return false as at least one number is present twice
            if (outerValue == innerValue) {
                return false;
            }
        }
    }

    return true;
}

bool columnCorrect(int column[9]) {
    //checks every field in the column (1-9)
    for (int innerField = 1; innerField <= 9; ++innerField) {
        //get the value of the field
        int innerValue = column[innerField];

        //skip if empty
        if (innerValue == 0) {
            continue;
        }

        //loop through the column again and check if another field has the same value
        for (int outerField = 1; outerField <= 9; ++outerField) {
            //skip same if the field is the same
            if (outerField == innerField) {
                continue;
            }

            //get value of the comparing field
            int outerValue = column[outerField];

            //if fields from both loops have the same value return false as at least one number is present twice
            if (outerValue == innerValue) {
                return false;
            }
        }
    }

    return true;
}

bool sudokuCorrect(sudoku s) {
    //test rows
    for (int rowIndex = 1; rowIndex <= 9; ++rowIndex) {
        //create row array from sudoku
        int row[9] = {};
        for (int field = 1; field <= 9; field++) {
            row[field] = s[getIndexBySudokuPosition(rowIndex, field)];
        }

        //if a row is not correct the sudoku is not correct
        if (rowCorrect(row) == false) {
            return false;
        }
    }

    //test columns
    for (int columnIndex = 1; columnIndex <= 9; ++columnIndex) {
        //create column array from sudoku
        int column[9] = {};
        for (int field = 1; field <= 9; field++) {
            column[field] = s[getIndexBySudokuPosition(field, columnIndex)];
        }

        //if a column is not correct the sudoku is not correct
        if (columnCorrect(column) == false) {
            return false;
        }
    }

    return true;
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
    copySudoku(i, o);

    input(i);
    solve(o);
    output(o);

    return 0;
}
