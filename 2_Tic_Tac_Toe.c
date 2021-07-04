/*****************************************************************************
 * Author: Meng-Shiun, Tsai | Date: 2015/12/16
 * Problem definition:
 * Basic: Please complete the Tic Tac Toe game
          1. Player takes the first step. The input format is "r c" where r and c indicate the row NO. and column NO. respectively. 
          2. Neither Player nor Boss can input the repeated position.
          3. When the line is connected, it is necessary to determine who won this game.
          4. If there is no any line connected, please show tied game。

 * Advanced: Continue the Basic.
          1. Please improve the win rate of Boss.
          2. When Boss has a chance to connect to a line, the program must input a specific position.
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void show_board(char[3][3], int[3][3], int, int, char, int);
int judgment(int[3][3], int);

int main() {
    char board_display[3][3] = {32, 32, 32, 32, 32, 32, 32, 32, 32};
    int board_check[3][3] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int row_p=0, col_p=0, row_b=0, col_b=0, check_result=0;

    srand((unsigned)time(NULL)); // Set random number to be different per game

    do {
        printf("Choose a position: ");

        // Let Player choose a non-repeated position
        for( ; ; ) {
            scanf("%d %d", &row_p, &col_p);

            if(board_check[row_p][col_p] == 0) {
                show_board(board_display, board_check, row_p, col_p, 'O', 1);
                break;
            } else {
                printf("Repeated position! Please choose a position again: ");
            }
        }

        // Check if the Player wins
        check_result = judgment(board_check, 3);
        if(check_result) {
            printf("Player wins !!\n");
            break;
        }

        // Check if it's a tied game
        check_result = judgment(board_check, 0);
        if(check_result) {
            printf("Tie !!");
            break;
        }

        printf("--------------next---------------\n");

        // Let Boss choose a non-repeated position
        for( ; ; ) {
            row_b = rand() % 3;
            col_b = rand() % 3;

            if(board_check[row_b][col_b] == 0) {
                show_board(board_display, board_check, row_b, col_b, 'X', -1);
                break;
            }
        }

        // Check if the Boss wins
        check_result = judgment(board_check, -3);
        if(check_result) {
            printf("Boss wins !!\n");
            break;
        }
    } while(1);

    return 0;
}

// Show a status of current board
void show_board(char board_display[3][3], int board_check[3][3], int row, int col, char symbol, int check) {
    board_display[row][col] = symbol;
    board_check[row][col] = check;

    printf("\n");

    int x=0, y=0;
    for(x=0 ; x<3 ; x++) {
        for(y=0 ; y<3 ; y++) {
            printf("%c", board_display[x][y]);
            printf((y != 2) ? " | " : "");
        }
        printf("\n");
        printf((x != 2) ? "-----------\n" : "");
    }

    printf("\n");
}

// Check who wins this game
int judgment(int board_check[3][3], int condition) {
    if(condition == 3 || condition == -3) {
        if(board_check[0][0] + board_check[0][1] + board_check[0][2] == condition ||
           board_check[1][0] + board_check[1][1] + board_check[1][2] == condition ||
           board_check[2][0] + board_check[2][1] + board_check[2][2] == condition ||
           board_check[0][0] + board_check[1][0] + board_check[2][0] == condition ||
           board_check[0][1] + board_check[1][1] + board_check[2][1] == condition ||
           board_check[0][2] + board_check[1][2] + board_check[2][2] == condition ||
           board_check[0][0] + board_check[1][1] + board_check[2][2] == condition ||
           board_check[0][2] + board_check[1][1] + board_check[2][0] == condition ) {
            return 1;
        } else {
            return 0;
        }
    } else if(condition == 0) {
        int x=0, y=0;
        for(x=0; x<3; x++) {
            for(y=0; y<3; y++) {
                if(board_check[x][y] == condition) {
                    return 0;
                }
            }
        }
        return 1;
    }
}
