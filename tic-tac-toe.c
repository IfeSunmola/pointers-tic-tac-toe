/*
 * Author: Bro Code -> https://youtu.be/_889aB2D1KI?list=PLZPZq0r_RZOOzY_vR4zJM32SqsSInGMwe
 *
 * Modified by: Ife Sunmola
 * */

/*
REMEMBER: An array is closely related to a pointer.
A 2d array in memory is in "row major order". i.e Row 0 is on a straight block of memory, followed by
row 1, row 2, etc. With this knowledge, we can use the pointers to access all the elements in the array by
just moving the pointer to the next memory address and dereference it to get the data stored there.
The entire matrix can be traversed using one for loop and the memory address

 *board returns a pointer to the first data in the 2d array
 *(*board) dereferences that pointer to get the data
 *(*board + 1) moves the pointer to the next location and gets the value
 this is how the 2d array will be traversed
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>


#define BOARD_SIZE 3

// prototypes
void printBoard(char (* board)[BOARD_SIZE]);

void resetBoard(char (* board)[BOARD_SIZE]);

int checkFreeSpaces(char (* board)[BOARD_SIZE]);

void playerMove(char (* board)[BOARD_SIZE], const char* PLAYER);

void computerMove(char (* board)[BOARD_SIZE], const char* computer);

char checkWinner(char (* board)[BOARD_SIZE]);

void printWinner(char winner, const char* PLAYER, const char* COMPUTER);

/*
 * This method returns true if there is a winner of if the board is full and false if not
 *
 * parameters: char board [][]
 *             pointer to the winner char
 * */
bool winnerOrTie(char (* board)[BOARD_SIZE], char* winner) {
    return (*winner != ' ' || checkFreeSpaces(board) == 0);
}

int main() {
    const char PLAYER = 'X';
    const char COMPUTER = 'O';
    char winner;
    char response = 'Y';// start the game. Not assigning this could break the game
    int playerScore = 0, computerScore = 0, roundCount = 0;

    char board[BOARD_SIZE][BOARD_SIZE];
    resetBoard(board);
    while (response != 'N') {
        winner = ' ';
        response = ' ';
        resetBoard(board);
        roundCount++;
        system("cls"); // clear the screen before each round begins
        printf("Round %d, the score is (PLAYER) %d - %d (COMPUTER)\n", roundCount, playerScore, computerScore);


        // while there's no winner and there are still spaces on the board, keep playing
        while (winner == ' ' && checkFreeSpaces(board) != 0) {
            printBoard(board);
            playerMove(board, &PLAYER);
            winner = checkWinner(board); // check if the player has won
            // if there is a winner OR there's no space left on the board,
            // break out of the current loop and print the result
            if (winnerOrTie(board, &winner)) {// if there is a winner or there's a tie (board is full)
                break;
            }

            computerMove(board, &COMPUTER);
            winner = checkWinner(board);
            if (winnerOrTie(board, &winner)) {
                break;
            }
        }
        getchar(); // clear the buffer so the "play again" response could be read properly
        printBoard(board);
        printWinner(winner, &PLAYER, &COMPUTER);
        if (winner == PLAYER) {
            playerScore++;
        }
        else if (winner == COMPUTER) {
            computerScore++;
        }
        printf("\nWould you like to play again? (Y/N): ");
        scanf("%c", &response);
        response = toupper(response);
    }
    //print out some basic game stats
    printf("Thanks for playing!");
    printf("\nRounds played: %d\nPlayer Score: %d\nComputer Score: %d", roundCount, playerScore, computerScore);
    return 0;
}

/*
 * This function prints the tic-tac-toe board.
 * parameters: char board [][]
 * */
void printBoard(char (* board)[BOARD_SIZE]) {
    // TODO: change this to use a loop
    // check comments are the beginning of the file
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
 * parameters: char board [][]
 * */
void resetBoard(char (* board)[BOARD_SIZE]) {
    // using board OR &board[0] works but gives a warning ??

    // start the loop at the pointer to the first item in the 2d matrix, and keep changing
    // the memory address till it gets to the last address.
    // remember: in memory, a 2d array is stored in row major order
    for (char* ptr = &board[0][0]; ptr <= &board[BOARD_SIZE - 1][BOARD_SIZE - 1]; ptr++) {
        *ptr = ' ';
    }
}

/*
 * This function returns the amount of empty spaces left on the board
 * If the amount of empty spaces is <= 0, that means the game will end in a tie
 *
 * parameters char [][] board
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
 * This function enables the PLAYER to make a move by asking for the row and column they want to move to
 * This function also makes sure the PLAYER selects a valid move. If not, it will keep asking till the user makes
 * a valid selection
 *
 * parameters: char board [][]
               A pointer to the player char
 * */
void playerMove(char (* board)[BOARD_SIZE], const char* PLAYER) {
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
            board[rowNum][colNum] = *PLAYER;// mark the spot has taken by PLAYER
            break;
        }
    } while (board[rowNum][colNum] != ' ');

}

/*
 * This function makes a move for the computer by using random numbers
 *
 * parameters: char[][] board
 *             A pointer to the COMPUTER char
 *
 * */
void computerMove(char (* board)[BOARD_SIZE], const char* COMPUTER) {
    //creates a seed based on current time
    srand(time(0));
    int rowNum;
    int colNum;

    if (checkFreeSpaces(board) > 0) { // if there's still space on the board
        do { // keep generating a random number between [1, 3] till an empty spot is found
            rowNum = rand() % 3;
            colNum = rand() % 3;
        } while (board[rowNum][colNum] != ' ');

        board[rowNum][colNum] = *COMPUTER;// mark the spot
    }
    else { // no more space on the board, it's a tie
        printWinner(' ', NULL, NULL);
    }
}

/*
 * This method prints the winner, based of the argument passed
 * If an empty char is passed, or a char that isn't PLAYER or Computer, it's a tie
 *
 * parameters: char winner: the winner of the current round, either PLAYER or COMPUTER
 *             char* PLAYER: pointer to the PLAYER char
 *             char* COMPUTER: pointer to the COMPUTER char
 * */
void printWinner(char winner, const char* PLAYER, const char* COMPUTER) {
    if (winner == *PLAYER) {
        printf("YOU WIN!");
    }
    else if (winner == *COMPUTER) {
        printf("YOU LOSE!");
    }
    else {
        printf("IT'S A TIE!");
    }
}

/*
 * This function checks for a winner by checking each row, column and the diagonals
 * It returns the char of the WINNER
 *
 * parameters: the board array
 * returns: a char containing the winner of this round or an empty char if there's no winner yet
 * */
char checkWinner(char (* board)[BOARD_SIZE]) {
    //todo: change this to be literally anything else
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


