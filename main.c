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

int main() {
    //example usage
    sudoku s = {};

    //get the index for the field 1 / 8
    int index = getIndexBySudokuPosition(1, 8);

    //write a value into the field
    s[index] = 7;

    printf("The value of field 8 in column 1 is %d. \n", s[index]);
    return 0;
}
