/*
 * Author: Bro Code -> https://youtu.be/_889aB2D1KI?list=PLZPZq0r_RZOOzY_vR4zJM32SqsSInGMwe
 *
 * Modified by: Ife Sunmola
 * */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

// prototypes
void resetBoard();

void printBoard();

int checkFreeSpaces();

void playerMove();

void computerMove();

char checkWinner();

void printWinner(char);

int main() {
    char winner = ' ';
    char response = ' ';
    int playerScore = 0;
    int computerScore = 0;
    int roundCount = 0;
    do {
        winner = ' ';
        response = ' ';
        resetBoard();
        roundCount++;
        system("cls");
        printf("Round %d, the score is (PLAYER) %d - %d (COMPUTER)\n", roundCount, playerScore, computerScore);


        // while there's no winner and there are still spaces on the board
        while (winner == ' ' && checkFreeSpaces() != 0) {
            printBoard();
            playerMove();
            winner = checkWinner(); // check if the player has won
            // if there is a winner OR there's no space left on the board,
            // break out of the current loop and print the result
            if (winner != ' ' || checkFreeSpaces() == 0) {
                break;
            }

            computerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0) {
                break;
            }
        }
        getchar(); // clear the buffer so the "play again" response could be read properly
        printBoard();
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
 * This function resets each value of the board (2d array) to an empty character
 * It is called before a new round begins
 * */
void resetBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

/*
 * This function prints the tic-tac-toe board.
 * This function shows the player the board after every move is made
 * */
void printBoard() {
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

/*
 * This function returns the amount of empty spaces left on the board
 * If the amount of empty spaces is <= 0, that means the game will end in a tie
 * */
int checkFreeSpaces() {
    int freeSpaces = 9;
    // loop through the board and decrement freeSpaces anytime a board content is ' '
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != ' ') {
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
}

/*
 * This function enables the player to make a move by asking for the row and column they want to move to
 * This function also makes sure the player selects a valid move. If not, it will keep asking till the user makes
 * a valid selection
 * */
void playerMove() {
    int rowNum;
    int colNum;

    do {
        printf("Enter row #(1-3): ");
        scanf("%d", &rowNum);
        rowNum--; // decrementing because of 0 index
        printf("Enter column #(1-3): ");
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
void computerMove() {
    //creates a seed based on current time
    srand(time(0));
    int rowNum;
    int colNum;

    if (checkFreeSpaces() > 0) { // if there's still space on the board
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
 * This function checks for a winner by checking each row, column and the diagonals
 * It returns the char of the WINNER
 * */
char checkWinner() {
    //check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            return board[i][0];
        }
    }
    //check columns
    for (int i = 0; i < 3; i++) {
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
