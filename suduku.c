/**************
* Matan Shamir
* 206960239
* 01
* ass03
**************/

#include <stdio.h>
#include <string.h>

#define SIZE 3
#define REPLACE_LENGTH 14
#define CHANGE_LENGTH 12
#define ADD_LENGTH 9
#define DELETE_LENGTH 10
#define SPACE ' '
#define BORDER " | "

/*********************************************************************************************************************
* Function name: validBackslash
* Input: char str[]
* Output: boolean value (0 or 1).
* Function Operation: The function receives a string and counts the amount of backslashes it has, and determines
                      whether or not the amount is valid for creating a board for a sudoku game.
*********************************************************************************************************************/
int validBackslash(char str[]) {
    int count = 0;

    //this loop iterates as long as the string is, and counts every '/'.
    for (int i = 0; i < strlen(str); ++i) {
        if (str[i] == '/')
            count++;
    }

    //the needed amount of backslashes is the size of the board minus 1.
    if (count != (SIZE * SIZE) - 1)
        return 0;
    //if the amount was valid, we don't return 0 and return 1 instead.
    return 1;
}

/*********************************************************************************************************************
* Function name: createBoard
* Input: char board[][SIZE * SIZE], char str[]
* Output: none.
* Function Operation: The function receives a string and a two-dimensional array(the sudoku board) and checks if the
                      string received is valid. if it suites the values needed to be entered to the board, the
                      function translates it to variables or to spaces in the board and saves it.
*********************************************************************************************************************/
void createBoard(char board[][SIZE * SIZE], char str[]) {

    //first, we check that the amount of backslashes is valid.
    if (!validBackslash(str)) {
        printf("Error\n");
        return;
    }
    /*we create a pointer to the start of the string that points to different parts of it for us to know which
    value we need to insert at a every iteration. a second pointer points to the beginning of the array for
     further calculations of length.*/
    char *p1 = str, *p2 = str;
    unsigned int length = strlen(str);
    //a temp board is created so we change the original board only if the string is indeed valid.
    char tempBoard[SIZE * SIZE][SIZE * SIZE];

    //this double for loop is a matrix for us to go through every cell in the array.
    for (int i = 0; i < SIZE * SIZE; i++) {
        for (int j = 0; j < SIZE * SIZE; j++) {

            /*this condition tells us if a given char in the string is a char that signals blank cells. if it is,
            fill the amount of spaces needed and progress to next 'j' after every iteration.*/
            if ((*p1 >= 'a') && (*p1 < 'a' + (SIZE * SIZE))) {

                for (int k = 0; k <= *p1 - 'a'; k++) {

                    //the only case in which we dont need to enlarge 'j's value is when we only change one cell.
                    if (k > 0)
                        j++;
                    tempBoard[i][j] = SPACE;
                }

                //this condition tells us if we filled to many spaces in the array and thus got an invalid string.
                if (j >= SIZE * SIZE) {
                    printf("Error\n");
                    return;
                }

                /*the only case in which this condition works is if we receive a backslash before the end of a line, in
                 which case we need to fill the remaining cells in the line with spaces. the condition after the logical
                 'OR' is if we got to the final iteration so we dont have a backslash, in which case the string has
                 ended but still the final line needs to be filled with spaces.*/
            } else if ((*p1 == '/') || ((char *) p1 - (char *) p2 == length)) {
                for (int k = j; k < SIZE * SIZE; k++) {
                    tempBoard[i][j] = SPACE;
                    j++;
                }
                //after filling the needed cells, no further action is needed so we break out of the iteration.
                break;

                /*if the pointer points to anything else but what was mentioned, it is a variable and is inserted 'as is'
                to the fitting cell.*/
            } else {
                tempBoard[i][j] = *p1;
            }

            /*this condition tells us if the next char in the string after the last char in the line is not a
            backslash and thus invalid for being too long. it doesn't fit for the last line though.*/
            if ((j == (SIZE * SIZE) - 1) && (*(p1 + 1) != '/') && (i != (SIZE * SIZE - 1))) {
                printf("Error\n");
                return;
            }
            p1++;
        }
        p1++;
    }

    //if the function didn't stop bu now, the string was valid and temp board is copied to board.
    for (int i = 0; i < SIZE * SIZE; ++i) {
        strcpy(board[i], tempBoard[i]);
    }
}

/*********************************************************************************************************************
* Function name: printBoard
* Input: char board[][SIZE * SIZE]
* Output: none.
* Function Operation: The function receives a two-dimensional array(the sudoku board) and prints it to the user.
                      it adds spaces and borders so it would look like a board.
*********************************************************************************************************************/
void printBoard(char board[][SIZE * SIZE]) {

    //this double for loop is a matrix for us to go through every cell in the array.
    for (int i = 0; i < SIZE * SIZE; i++) {

        //a line drop is made when we passed to the end of a box.
        if ((i % SIZE == 0) && (i > 0))
            printf("\n");
        for (int j = 0; j < SIZE * SIZE; j++) {

            //if we reached the right side of the box, we print the border between the boxes.
            if (((j % SIZE) == 0) && (j > 0))
                printf("%s",BORDER);
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/*********************************************************************************************************************
* Function name: makeMove
* Input: char board[][SIZE * SIZE], char move[]
* Output: none.
* Function Operation: The function receives a two-dimensional array(the sudoku board) and a string for which move
                      needs to be committed, and makes it if the string is valid. if it isn't it prints 'Error',
                      and doesn't change the board at all.
*********************************************************************************************************************/
void makeMove(char board[][SIZE * SIZE], char move[]) {
    //the strings are made in order to make comparison and determine if the 'move' input is valid.
    char rep[] = "replaceAll";
    char change[] = "change";
    char add[] = "add";
    char del[] = "delete";
    //we use the rows and columns integers to have access to certain locations in the board given by the user.
    unsigned short int rows, columns;

    //if the given string is as long as the replace command:
    if (strlen(move) == REPLACE_LENGTH) {

        //this loop makes sure that the string is valid and each char of the command is right.
        for (int i = 0; i < strlen(rep); i++) {
            if (move[i] != rep[i]) {
                printf("Error\n");
                return;
            }
        }
        //flag is used to mark if any changes were made in the board. if its not lit, the move isn't valid.
        int flag = 0;

        /*this condition prevents strings with invalid places or input chars from being done. if the string is
        fine, we go through the board and insert the given char to every cell in which it is found. if the
        char doesn't exist in the board, 'error' is printed and no changes are made.*/
        if ((move[11] != ' ') && (move[13] != ' ') && (move[13] != ',') && (move[13] != '/') &&
        ((move[13] < 'a') || (move[13] > 'a' + (SIZE * SIZE)))) {
            for (int i = 0; i < SIZE * SIZE; i++) {
                for (int j = 0; j < SIZE * SIZE; j++) {
                    if (board[i][j] == move[11]) {
                        board[i][j] = move[13];
                        flag = 1;
                    }
                }
            }
            //in case that no changes were made, print error and return.
            if (flag == 0) {
                printf("Error\n");
                return;
            }
        } else {
            printf("Error\n");
            return;
        }

        //if the given string is as long as the change command:
    } else if (strlen(move) == CHANGE_LENGTH) {

        //this loop makes sure that the string is valid and each char of the command is right.
        for (int i = 0; i < strlen(change); i++) {
            if (move[i] != change[i]) {
                printf("Error\n");
                return;
            }
        }
        /*the 'rows' and 'columns' integers are made to turn the chars from the string into accessible places
        from the board. the calculation is according to the 'ascii' table.*/
        rows = move[7] - '0', columns = move[9] - '0';

        //this condition is almost the same as the one in 'replace', besides that it checks the rows and columns.
        if (((rows >= 0) && (rows < SIZE * SIZE)) && ((columns >= 0) && (columns < SIZE * SIZE)) &&
        (move[11] != '/') && (move[11] != SPACE) && (move[11] != ',') && ((move[11] < 'a') ||
        (move[11] > 'a' + SIZE * SIZE))) {
            //this condition makes sure that the given place we want to change is not space.
            if (board[rows][columns] != SPACE)
                board[rows][columns] = move[11];
            else {
                printf("Error\n");
                return;
            }
        } else {
            printf("Error\n");
            return;
        }

        //if the given string is as long as the add command:
    } else if (strlen(move) == ADD_LENGTH) {

        //again, we check that every char is indeed valid.
        for (int i = 0; i < strlen(add); ++i) {
            if (move[i] != add[i]) {
                printf("Error\n");
                return;
            }
        }
        //the same translation into accessible cells is made here according to ascii.
        rows = move[4] - '0', columns = move[6] - '0';

        //the condition is the same as the one in change.
        if (((rows >= 0) && (rows < SIZE * SIZE)) && ((columns >= 0) && (columns < SIZE * SIZE)) &&
        (move[8] != '/') && (move[8] != SPACE) && (move[8] != ',') &&
        ((move[8] < 'a') || (move[8] > 'a' + SIZE * SIZE))) {

            //this time, the only case in which 'add' is possible, is if the given cell is blank.
            if (board[rows][columns] == ' ')
                board[rows][columns] = move[8];
            else {
                printf("Error\n");
                return;
            }
        } else {
            printf("Error\n");
            return;
        }

        //if the given string is as long as the delete command:
    } else if (strlen(move) == DELETE_LENGTH) {

        //again, we check that each char is valid in the string.
        for (int i = 0; i < strlen(del); ++i) {
            if (move[i] != del[i]) {
                printf("Error\n");
                return;
            }
        }
        rows = move[7] - '0', columns = move[9] - '0';

        //this time, the only needed condition is that the rows and columns are valid cells.
        if (((rows >= 0) && (rows < SIZE * SIZE)) && ((columns >= 0) && (columns < SIZE * SIZE))) {

            //as in change, we can only delete cells that has values in them.
            if (board[rows][columns] != SPACE)
                board[rows][columns] = SPACE;
            else {
                printf("Error\n");
                return;
            }
        } else {
            printf("Error\n");
            return;
        }

        //if the length doesn't suite any of the commands, the string isn't valid and 'error' in printed.
    } else {
        printf("Error\n");
        return;
    }
}

/*********************************************************************************************************************
* Function name: testBoard
* Input: char board[][SIZE * SIZE]
* Output: boolean value (0 or 1).
* Function Operation: The function receives a two-dimensional array(the sudoku board) and determines if the board is
                      valid according to the sudoku rules: only valid numbers and blank spaces with only one
                      appearance for each number in a line, row and square.
*********************************************************************************************************************/
int testBoard(char board[][SIZE * SIZE]) {

    /*'counter' is made for us to be able to compare different cells, and 'startRow' and 'startColumn' are used for
     us to be able to access different squares when checking them.*/
    int counter = 0, startRow = 0, startColumn = 0;
    for (int i = 0; i < SIZE * SIZE; i++) {

        /*'startRow' is enlarged every 'SIZE' iterations, and thus determines from where to where the loop that
        each square begins.*/
        if ((i % SIZE == 0) && (i != 0))
            startRow += SIZE;
        for (int j = 0; j < SIZE * SIZE; j++) {

            //for 'startColumn, the same calculation is done as in startRow.
            if ((j % SIZE == 0) && (j != 0))
                startColumn += SIZE;

            //'space' is a valid char, so we only check other chars comparing to others in their rows/columns/squares.
            if (board[i][j] != SPACE) {

                //the only valid chars are '1' to 'SIZE*SIZE', we add '0' to turn in to the ascii char.
                if ((board[i][j] < '1') || (board[i][j] > SIZE * SIZE + '0'))
                    return 0;

                /*this double loop is a mini-matrix that checks there are no similar values in different cells
                 in each squares*/
                for (int k = startRow; k < startRow + SIZE; k++) {
                    for (int l = startColumn; l < startColumn + SIZE; l++) {

                        //the only case in which the condition isn't true is if its the same cell
                        if ((board[i][j] == board[k][l]) && ((i != k) && (j != l))) {
                            return 0;
                        }
                    }
                }

                /*this loop compares each cell to the others in its row and column using counter which grows by 1
                in every iteration*/
                while (counter < SIZE * SIZE) {
                    if ((counter != j) && (board[i][counter] == board[i][j]))
                        return 0;
                    if ((counter != i) && (board[counter][j] == board[i][j]))
                        return 0;
                    counter++;
                }
                //counter is set to 0 again after every iteration because it need to go through the whole row again.
                counter = 0;
            }
        }
        /*after checking a row, startColumn is set to 0 because we shift to the most left square again, so the loop
        that checks the square need to start at 0.*/
        startColumn = 0;
    }
    //if the test has gone by and no condition has stopped it- the board is valid and '1' is returned.
    return 1;
}

/*********************************************************************************************************************
* Function name: isSameBoard
* Input: char board[][SIZE * SIZE], char board1[][SIZE * SIZE]
* Output: boolean value (0 or 1).
* Function Operation: The function receives 2 two-dimensional arrays and determines if they are identical, by
                      checking cell by cell that they are the same. if they aren't, '0' is returned and the
                      first place that they dont fit is printed to the user.
*********************************************************************************************************************/
int isSameBoard(char board[][SIZE * SIZE], char board1[][SIZE * SIZE]) {

    //this double loop allows us to go through the whole 2 sudoku boards.
    for (int i = 0; i < SIZE * SIZE; i++) {
        for (int j = 0; j < SIZE * SIZE; j++) {

            //we check in every cell if there is inequality between the boards. if there is, the place is printed.
            if (board[i][j] != board1[i][j]) {
                printf("Found inequality on row %d col %d.\n", i, j);
                return 0;
            }
        }
    }
    //if the function didn't find any inequality, it reaches this part of the code and returns 1.
    return 1;
}

/*********************************************************************************************************************
* Function name: onlyOneEmpty
* Input: char board[][SIZE * SIZE]
* Output: boolean value (0 or 1).
* Function Operation: The function receives a two-dimensional array(the sudoku board) and determines if the board
                      has as far as one empty cell in each row, column and square. if it doesn't, '0' is returned.
                      if it does, '1' is returned.
*********************************************************************************************************************/
int onlyOneEmpty(char board[][SIZE * SIZE]) {
    /*the same as in the function 'testBoard', for us to be able to go check different squares, we need to set
    different values for startRow and startColumn to iterate.*/
    int startRow = 0, startColumn = 0, counter = 0;
    for (int i = 0; i < SIZE * SIZE; i++) {
        //startRow is enlarged every 'SIZE' long iterations.
        if ((i % SIZE == 0) && (i != 0))
            startRow += SIZE;
        for (int j = 0; j < SIZE * SIZE; j++) {

            //the same goes for startColumn.
            if ((j % SIZE == 0) && (j != 0))
                startColumn += SIZE;

            /*the only case in which we need to check if there are more than one empty cell is if there is one
            in the first place.*/
            if (board[i][j] == SPACE) {

                //if we found a space, we check in its box for other spaces. if another space is found, return 0.
                for (int k = startRow; k < startRow + SIZE; k++) {
                    for (int l = startColumn; l < startColumn + SIZE; l++) {
                        if ((board[k][l] == SPACE) && ((i != k) && (j != l))) {
                            return 0;
                        }
                    }
                }

                /*now we check for other spaces in the cell's rows and columns using growing 'counter'.
                if another space is found, return 0.*/
                while (counter < SIZE * SIZE) {
                    if ((counter != j) && (board[i][counter] == SPACE))
                        return 0;
                    if ((counter != i) && (board[counter][j] == SPACE))
                        return 0;
                    counter++;
                }
                counter = 0;
            }
        }
        startColumn = 0;
    }
    //if the loop went all the way and didn't find excessive spaces, the board is valid and '1' is returned.
    return 1;
}

/*********************************************************************************************************************
* Function name: completeBoard
* Input: char board[][SIZE * SIZE]
* Output: none.
* Function Operation: The function receives a two-dimensional array(the sudoku board) and, if the board has only one
                      empty cell in each row, column and square- it completes it according to the sudoku rules.
*********************************************************************************************************************/
void completeBoard(char board[][SIZE * SIZE]) {
    //'option' is used for us to be able to fill each row and check if its right.
    char option = '1';
    /*we make all changes on tempBoard and if everything passed we copy it to the original board. this loop copies
     each line as a string from one board to the other.*/
    char tempBoard[SIZE * SIZE][SIZE * SIZE];
    for (int i = 0; i < SIZE * SIZE; ++i) {
        strcpy(tempBoard[i], board[i]);
    }

    /*the only case in which we try to solve the board, is if the board is valid: only one empty cell in each row,
    column and square, and that the board only contains valid chars.*/
    if (testBoard(tempBoard) && (onlyOneEmpty(tempBoard))) {
        for (int i = 0; i < SIZE * SIZE; i++) {
            for (int j = 0; j < SIZE * SIZE; j++) {

                //if we encounter 'space', we try to solve the board: we insert a certain option starting at '1'.
                if (tempBoard[i][j] == SPACE) {
                    tempBoard[i][j] = option;

                    /*after entering the option, we check if the board is valid. if it is, we continue to the next
                    if it isn't, we return to the prior cell and enlarge option to try again.*/
                    if (!testBoard(tempBoard)) {
                        tempBoard[i][j] = SPACE;
                        j--;
                        option++;
                    }
                }
            }
            //here we set option back to '1' for the next line and next set of checks.
            option = '1';
        }
    } else {
        printf("Error\n");
        return;
    }
    /*if we reach this part of the code and the function didn't return it means that the board was completed
    and its copied back to the original board.*/
    for (int i = 0; i < SIZE * SIZE; ++i) {
        strcpy(board[i], tempBoard[i]);
    }
}

