#include <stdio.h>

typedef int sudoku[9 * 9];

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

void encodeSudokuToFile(char path[], sudoku s) {
    //write file from sudoku data into a file under path
    //WARNING: something could go wrong
}

void printSudoku(sudoku s) {
    //print sudoku to the console...
    printf("...\n");
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

    //print sudoku to the console
    printSudoku(s);
}

void solve(sudoku input, sudoku output) {
    //solve sudoku
    //...

    //write solution into output sudoku
    output[0] = input[0];
}

void output(sudoku s) {
    //print solved sudoku to the console
    printSudoku(s);

    //ask the user if he wants to save the solution (Y/n)

    //if no finish application

    //if yes, create a new file [input_name]_solution.su
    //HINT: HANDLE EDGE CASES!
    //if such a file already exists, give numbers for example:
    //[input_name]_solution (1).su
    encodeSudokuToFile("path", s);

    //print a success message + path into the console
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
