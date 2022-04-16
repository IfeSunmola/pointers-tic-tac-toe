/*
 * Author: Bro Code -> https://youtu.be/_889aB2D1KI?list=PLZPZq0r_RZOOzY_vR4zJM32SqsSInGMwe
 *
 * Modified by: Ife Sunmola
 * */

/*
An array is closely related to a pointer.
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


#define NUM_ELEMENTS 9

// prototypes
void printBoard(char* board);

void resetBoard(char* board);

int checkFreeSpaces(char* board);

void playerMove(char* board, const char* PLAYER);

void computerMove(char* board, const char* computer);

char checkWinner(char* board);

void printWinner(char winner, const char* PLAYER, const char* COMPUTER);

bool winnerOrTie(char* board, char* winner);

void requestPlayAgain(char* playAgain);

int main() {
    const char PLAYER = 'X';
    const char COMPUTER = 'O';
    char winner;
    char playAgain = 'Y';// start the game. Not assigning this could break the game
    int playerScore = 0, computerScore = 0, roundCount = 0;

    char* board = (char*) malloc(NUM_ELEMENTS * sizeof(char));
    resetBoard(board);
    while (playAgain != 'N') {
        winner = ' ';
        resetBoard(board);
        roundCount++;
        system("cls"); // clear the screen before each round begins
        printf("Round %d, the score is (PLAYER) %d - %d (COMPUTER)\n", roundCount, playerScore, computerScore);


        // while there's no winner and there are still spaces on the board, keep playing
        while (winner == ' ' && checkFreeSpaces(board) != 0) {
            printBoard(board);

            playerMove(board, &PLAYER); //player makes a move
            winner = checkWinner(board); // check if the player has won
            // if the PLAYER has not won OR there's no space left on the board, break out of the current loop and print the result
            if (winnerOrTie(board, &winner)) {// if there is a winner or there's a tie (board is full)
                break;
            }

            computerMove(board, &COMPUTER);// computer makes a move
            winner = checkWinner(board);// check if the computer has won
            // if the COMPUTER has not won OR there's no space left on the board, break out of the current loop and print the result
            if (winnerOrTie(board, &winner)) {
                break;
            }
        }

        printBoard(board); // show the final board state
        printWinner(winner, &PLAYER, &COMPUTER);// winner, loser or tie

        // update the scores
        if (winner == PLAYER) {
            playerScore++;
        }
        else if (winner == COMPUTER) {
            computerScore++;
        }

        //ask the user if they want to play another round
        requestPlayAgain(&playAgain); // playAgain char variable is updated here
    }
    free(board);
    //print out some basic game stats
    printf("Thanks for playing!");
    printf("\nRounds played: %d\nPlayer Score: %d\nComputer Score: %d", roundCount, playerScore, computerScore);
    return 0;
}

/*
 * *Changed to use a loop pointer instead of printing directly*
 * This function prints the tic-tac-toe board.
 * parameters: char board [][]
 * */
void printBoard(char* board) {
    int rowSize = NUM_ELEMENTS / 3; // num of elements in one row
    int counter = 1;// used to know when to go to a new line
    for (char* ptr = board; ptr < &board[NUM_ELEMENTS]; ptr++, counter++) {
        printf(" %c ", *ptr);
        if (counter % rowSize == 0 &&
            counter <= 6) {// if at the edge of a new row, go to a new line and print a seperator
            printf("\n---|---|---\n");// tracker <= 6 will prevent this from printing again at the last row
        }
        else if (counter != NUM_ELEMENTS) { // prevents | from being added to the last element
            printf("|");
        }
    }
    printf("\n");
}

/*
 * This function resets each value of the board (2d array) to an empty character
 * It is called before a new round begins
 * parameters: char board [][]
 * */
void resetBoard(char* board) {
    for (char* ptr = board; ptr <= &board[NUM_ELEMENTS]; ptr++) {
        *ptr = ' ';
    }
}

/*
 * This function returns the amount of empty spaces left on the board
 * If the amount of empty spaces is <= 0, that means the game will end in a tie
 *
 * parameters char [][] board
 * */
int checkFreeSpaces(char* board) {
    int freeSpaces = 9;
    for (char* ptr = board; ptr <= &board[NUM_ELEMENTS]; ptr++) {
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
void playerMove(char* board, const char* PLAYER) {
    int rowNum;
    int colNum;
    int rowSize = NUM_ELEMENTS / 3;
    int actualIndex = 0;// actual index to mark the PLAYER on. If a user enters row, num as (2, 3), actual index will
    // be gotten by (2 * rowSize) + 3
    do {
        printf("Enter row # (1-3): ");
        scanf("%d", &rowNum);
        rowNum--; // decrementing because of 0 index
        printf("Enter column # (1-3): ");
        scanf("%d", &colNum);
        colNum--;
        actualIndex = (rowNum * rowSize) + colNum;
        if (board[actualIndex] != ' ') {// spot has been played on
            printf("Invalid move!\n");
        }
        else {
            board[actualIndex] = *PLAYER;// mark the spot has taken by PLAYER
            break;
        }
    } while (board[actualIndex] != ' ');

}

/*
 * This function makes a move for the computer by using random numbers
 *
 * parameters: char[][] board
 *             A pointer to the COMPUTER char
 *
 * */
void computerMove(char* board, const char* COMPUTER) {
    //creates a seed based on current time
    srand(time(0));
    int num;

    if (checkFreeSpaces(board) > 0) { // if there's still space on the board
        do { // keep generating a random number between [1, 9] till an empty spot is found
            num = rand() % NUM_ELEMENTS;
        } while (board[num] != ' ');

        board[num] = *COMPUTER;// mark the spot
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
char checkWinner(char* board) {
    //todo: change this to be literally anything else
    //checking rows: Winner will have their char on 3 consecutive spaces
    //rows
    if (board[0] == board[1] == board[2]) {
        return board[0];
    }
    if (board[3] == board[4] == board[5]) {
        return board[3];
    }
    if (board[6] == board[7] == board[8]) {
        return board[6];
    }
    //cols
    if (board[0] == board[3] == board[6]) {
        return board[0];
    }
    if (board[1] == board[4] == board[7]) {
        return board[1];
    }
    if (board[2] == board[5] == board[8]) {
        return board[2];
    }
    //cols

//    //check rows
//    for (int i = 0; i < BOARD_SIZE; i++) {
//        if (board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
//            return board[i][0];
//        }
//    }
//    //check columns
//    for (int i = 0; i < BOARD_SIZE; i++) {
//        if (board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
//            return board[0][i];
//        }
//    }
//    //check diagonals
//    if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
//        return board[0][0];
//    }
//    if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
//        return board[0][2];
//    }
    return ' ';
}

/*
 * This method returns true if there is a winner of if the board is full and false if not
 *
 * parameters: char board [][]
 *             pointer to the winner char
 * */
bool winnerOrTie(char* board, char* winner) {
    return (*winner != ' ' || checkFreeSpaces(board) == 0);
}

void requestPlayAgain(char* playAgain) {
    bool validInput = false;
    while (!validInput) {
        printf("\nWould you like to play again? (Y/N): ");
        scanf(" %c", playAgain);
        fflush(stdin);
        *playAgain = toupper(*playAgain);
        if (*playAgain == 'Y' || *playAgain == 'N') {
            validInput = true;
        }
        else {
            printf("Enter either Y or N (not case sensitive)");
        }
    }
}