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

void checkWinner(char* board, char* winner);

void printWinner(char winner, const char* PLAYER, const char* COMPUTER);

void requestPlayAgain(char* playAgain);

int main() {
    const char PLAYER = 'X';
    const char COMPUTER = 'O';
    char winner;
    char playAgain = 'Y';// start the game. Not assigning this could break the game
    int playerScore = 0, computerScore = 0, numTies = 0, roundCount = 0;

    char* board = (char*) malloc(NUM_ELEMENTS * sizeof(char));// reserve memory for 9 chars
    resetBoard(board);// set them to ' '
    while (playAgain != 'N') {
        winner = ' ';
        resetBoard(board);
        system("cls"); // clear the screen before each round begins
        roundCount++;
        printf("Round %d, the score is (PLAYER) %d - %d (COMPUTER)\n", roundCount, playerScore, computerScore);


        // while there's no winner and there are still spaces on the board, keep playing
        while (winner == ' ' && checkFreeSpaces(board) != 0) {
            printBoard(board);

            playerMove(board, &PLAYER); //player makes a move
            checkWinner(board, &winner); // check if the player has won. winner will be updated using its memory address
            // if the PLAYER has not won OR there's no space left on the board, break out of the current loop and print the result
            if (winner != ' ' || checkFreeSpaces(board) == 0) {// if there is a winner or there's a tie (board is full)
                break;
            }

            computerMove(board, &COMPUTER);// computer makes a move
            checkWinner(board, &winner);//check if the computer has won. winner will be updated using its memory address
            // if the COMPUTER has not won OR there's no space left on the board, break out of the current loop and print the result
            if (winner != ' ' || checkFreeSpaces(board) == 0) {
                break;
            }
        }

        printBoard(board); // show the final board state
        printWinner(winner, &PLAYER, &COMPUTER);// winner, loser or tie

        // update the stats
        if (winner == PLAYER) {
            playerScore++;
        }
        else if (winner == COMPUTER) {
            computerScore++;
        }
        else {
            numTies++;
        }

        //ask the user if they want to play another round
        requestPlayAgain(&playAgain); // playAgain char variable is updated here
    }
    free(board);
    //print out some basic game stats
    printf("Thanks for playing!");
    printf("\nRounds played: %d\nPlayer Score: %d\nComputer Score: %d\nNumber of ties: %d", roundCount, playerScore,
           computerScore, numTies);
    return 0;
}

/*
 * Prints the board in a standard tic-tac-toe form
 * parameters: char* board: a pointer to the board array
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
 * parameters: char* board
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
 * parameters: char* board
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
 * parameters: char* board
               const char* PLAYER: A pointer to the player character
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
 * parameters: char* board
 *             const char * COMPUTER A pointer to the COMPUTER character
 *
 * */
void computerMove(char* board, const char* COMPUTER) {
    //creates a seed based on current time
    srand(time(0));
    int index;// where the computer will play to

    if (checkFreeSpaces(board) > 0) { // if there's still space on the board
        do { // keep generating a random number between [1, 9] till an empty spot is found
            index = rand() % NUM_ELEMENTS;
        } while (board[index] != ' ');

        board[index] = *COMPUTER;// mark the spot
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
 *             const char* PLAYER: pointer to the PLAYER character
 *             const char* COMPUTER: pointer to the COMPUTER character
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
 * THIS FUNCTION UPDATES THE winner VARIABLE DECLARED IN MAIN
 *
 * parameters: char* board
 * */
void checkWinner(char* board, char* winner) {
    //todo: change this to be literally anything else
    //rows
    if (board[0] == board[1] && board[1] == board[2]) {
        *winner = board[0];
    }
    if (board[3] == board[4] && board[4] == board[5]) {
        *winner = board[3];
    }
    if (board[6] == board[7] && board[7] == board[8]) {
        *winner = board[6];
    }

    //cols
    if (board[0] == board[3] && board[3] == board[6]) {
        *winner = board[0];
    }
    if (board[1] == board[4] && board[4] == board[7]) {
        *winner = board[1];
    }
    if (board[2] == board[5] && board[5] == board[8]) {
        *winner = board[2];
    }

    //diagonals
    if (board[0] == board[4] && board[4] == board[8]) {
        *winner = board[0];
    }
    if (board[2] == board[4] && board[4] == board[6]) {
        *winner = board[2];
    }
}

/*
 * This function asks the user if they would like to play another round
 * Valid inputs are y, Y, N AND n
 * The function will keep asking the user to enter something valid
 *
 * THIS FUNCTION UPDATES THE playAgain VARIABLE THAT WAS DECLARED IN MAIN
 *
 * */
void requestPlayAgain(char* playAgain) {
    bool validInput = false;// will change in the loop when something valid is entered
    while (!validInput) {
        printf("\nWould you like to play again? (Y/N): ");
        scanf(" %c", playAgain);
        fflush(stdin);// clear the stdin so there are no dangling characters
        *playAgain = toupper(*playAgain);// convert to upper case
        if (*playAgain == 'Y' || *playAgain == 'N') { // valid input was entered, exit the loop
            validInput = true;
        }
        else {// invalid input, show error message and repeat
            printf("Enter either Y or N (not case sensitive)");
        }
    }
}