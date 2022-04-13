/*
 * Author: Bro Code -> https://youtu.be/_889aB2D1KI?list=PLZPZq0r_RZOOzY_vR4zJM32SqsSInGMwe
 *
 * Modified by: Ife Sunmola
 * */

/*
REMEMBER: An array is closely related to a pointer.
A 2d array in memory is in "row major order". i.e Row 0 is on a straight block of memory, followed by
 row 1, row 2, etc. With this knowledge, we can use the pointers to access all the elements in the array by
 just moving the pointer to the next memory address and dereference it to get the data stored there
 the entire matrix can be traversed using one for loop and the memory address

 *board returns a pointer to the first data in the 2d array
 *(*board) dereferences the that pointer to get the data
 *(*board + 1) moves the pointer to the next location and gets the value
 this is how the 2d array will be traversed
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>


#define BOARD_SIZE 3
const char PLAYER = 'X';
const char COMPUTER = 'O';

// prototypes
void printBoard(char (* board)[BOARD_SIZE]);

void resetBoard(char (* board)[BOARD_SIZE]);

int checkFreeSpaces(char (* board)[BOARD_SIZE]);

void playerMove(char (* board)[BOARD_SIZE]);

void computerMove(char (* board)[BOARD_SIZE]);

char checkWinner(char (* board)[BOARD_SIZE]);

void printWinner(char winner);


int main() {
    char b[BOARD_SIZE][BOARD_SIZE] = {
            {' ', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '},
    };
    char winner = ' ';
    char response = ' ';
    int playerScore = 0;
    int computerScore = 0;
    int roundCount = 0;

    do {
        winner = ' ';
        response = ' ';
        resetBoard(b);
        roundCount++;
        system("cls");
        printf("Round %d, the score is (PLAYER) %d - %d (COMPUTER)\n", roundCount, playerScore, computerScore);


        // while there's no winner and there are still spaces on the board
        while (winner == ' ' && checkFreeSpaces(b) != 0) {
            printBoard(b);
            playerMove(b);
            winner = checkWinner(b); // check if the player has won
            // if there is a winner OR there's no space left on the board,
            // break out of the current loop and print the result
            if (winner != ' ' || checkFreeSpaces(b) == 0) {
                break;
            }

            computerMove(b);
            winner = checkWinner(b);
            if (winner != ' ' || checkFreeSpaces(b) == 0) {
                break;
            }
        }
        getchar(); // clear the buffer so the "play again" response could be read properly
        printBoard(b);
        printWinner(winner);
        if (winner == PLAYER) {
            playerScore++;
        }
        else if (winner == COMPUTER) {
            computerScore++;
        }
        printf("\nWould you like to play again? (Y/N): ");
        scanf("%c", &response);
        response = toupper(response);
    } while (response == 'Y');
    //print out some basic game stats
    printf("Thanks for playing!");
    printf("\nRounds played: %d\nPlayer Score: %d\nComputer Score: %d", roundCount, playerScore, computerScore);
    return 0;
}

/*
 * This function prints the tic-tac-toe board.
 * This function shows the player the board after every move is made
 * */
void printBoard(char (* board)[BOARD_SIZE]) {
    printf(" %c | %c | %c ", *(*board), *(*board + 1), *(*board + 2));
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", *(*board + 3), *(*board + 4), *(*board + 5));
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", *(*board + 6), *(*board + 7), *(*board + 8));
    printf("\n");
}

/*
 * This function resets each value of the board (2d array) to an empty character
 * It is called before a new round begins
 * */
void resetBoard(char (* board)[BOARD_SIZE]) {
    for (char* ptr = &board[0][0]; ptr <= &board[BOARD_SIZE - 1][BOARD_SIZE - 1]; ptr++) {
        *ptr = ' ';
    }
}

/*
 * This function returns the amount of empty spaces left on the board
 * If the amount of empty spaces is <= 0, that means the game will end in a tie
 * */
int checkFreeSpaces(char (* board)[BOARD_SIZE]) {
    int freeSpaces = 9;
    for (char* ptr = &board[0][0]; ptr <= &board[BOARD_SIZE - 1][BOARD_SIZE - 1]; ptr++) {
        if (*ptr != ' ') {
            freeSpaces--;
        }
    }
    return freeSpaces;
}

/*
 * This function enables the player to make a move by asking for the row and column they want to move to
 * This function also makes sure the player selects a valid move. If not, it will keep asking till the user makes
 * a valid selection
 * */
void playerMove(char (* board)[BOARD_SIZE]) {
    int rowNum;
    int colNum;

    do {
        printf("Enter row # (1-3): ");
        scanf("%d", &rowNum);
        rowNum--; // decrementing because of 0 index
        printf("Enter column # (1-3): ");
        scanf("%d", &colNum);
        colNum--;
        if (board[rowNum][colNum] != ' ') {// spot has been played on
            printf("Invalid move!\n");
        }
        else {
            board[rowNum][colNum] = PLAYER;// mark the spot has taken by player
            break;
        }
    } while (board[rowNum][colNum] != ' ');

}

/*
 * This function makes a move for the computer by using random numbers
 *
 * */
void computerMove(char (* board)[BOARD_SIZE]) {
    //creates a seed based on current time
    srand(time(0));
    int rowNum;
    int colNum;

    if (checkFreeSpaces(board) > 0) { // if there's still space on the board
        do { // keep generating a random number between [1, 3] till an empty spot is found
            rowNum = rand() % 3;
            colNum = rand() % 3;
        } while (board[rowNum][colNum] != ' ');

        board[rowNum][colNum] = COMPUTER;// mark the spot
    }
    else { // no more space on the board, it's a tie
        printWinner(' ');
    }
}

/*
 * This method prints the winner, based of the argument passed
 * If an empty char is passed, or a char that isn't PLAYER or Computer, it's a tie
 * */
void printWinner(char winner) {
    if (winner == PLAYER) {
        printf("YOU WIN!");
    }
    else if (winner == COMPUTER) {
        printf("YOU LOSE!");
    }
    else {
        printf("IT'S A TIE!");
    }
}

/*
 * This function checks for a winner by checking each row, column and the diagonals
 * It returns the char of the WINNER
 * */
char checkWinner(char (* board)[BOARD_SIZE]) {
    //check rows
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            return board[i][0];
        }
    }
    //check columns
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
            return board[0][i];
        }
    }
    //check diagonals
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        return board[0][2];
    }

    return ' ';
}


