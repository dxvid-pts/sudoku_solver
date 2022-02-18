# sudoku_solver README

A command line application for solving sudoku puzzles written in C.

## Usage

1. Sudoku puzzles are stored using the `.su` file format.

   Create a file named `[name].su` and open it with your prefered text editor.
2. Save the sudoku you want to solve using the file structure below.

   A `.su` contains 9 rows. Each row has 9 fields and is written in a separate line. Zeros are representing empty
   fields. Example:

<p float="left">
  <img src="https://user-images.githubusercontent.com/98170949/154613964-cd23f411-a3c3-43d8-9552-6e65671c0c57.png" width="250" height="250">
  <img src="https://user-images.githubusercontent.com/98170949/154614494-a483d31d-d8b0-4c7f-89e9-44681bb31949.png" width="250" height="250">
</p>

3. After executing the script you will be prompted to provide the path and the filename. Copy&Paste both without the file
ending. The script will now solve your provided Sudoku.
4. Once the sudoku has been successfully solved, you will be asked if you want to save the solution to a new file.

    Enter `n` to exit the program.

    Enter `Y` to receive a copy of the solution in the `.su` format. You therefore will have to specify a file name.
