/*****************************************************************************
 * Author: Meng-Shiun, Tsai
 * Problem definition:
 * Minesweeper:
     1. There are 9*9 cells in the board and totally 9 cells with mine.
     2. The value shows the number of mine around the cell.
*****************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void assign_initial(int cells[][11]);                               // Initialize the value of each cell to 0
void print_blanks(void);                                            // Visualize the initialized cells
void open_cell(int *op_x, int *op_y);                               // Let user enter the coordinate
void put_mine(int cells[][11], int op_x, int op_y);                 // Setup the location of mine
void calculate_num_of_cells(int cells[][11]);                       // Calculate the number of mine in non-mine area
void assign_info_after_open(int cells[][11], int op_x, int op_y);   // Assign new information according to the coordinate selected by user
void open_surrounding(int cells[][11], int p_x, int op_y);          // Open surrounding area while there are no mine around the selected coordinate
void check_no_mine(int cells[][11], int op_x, int op_y);            // Check if there is mine in the surrounding area
int  check_over(int cells[][11], int op_x, int op_y);               // Check the player wins or loses
void print_cells(int cells[][11], int op_x, int op_y, int over);    // Visualize the current cells
void print_condition_playing(int cells[][11]);                      // Visualize the playing condition
void print_condition_over(int cells[][11], int over);               // Visualize the end condition (the information of each cell)
char play_again(void);                                              // Ask play again or not

int main(void) {
    int  cells[11][11], open_x, open_y, over;
    char again;

    srand((unsigned)time(NULL)); // Set random number to be different per game

    do {
        system("cls");
        assign_initial(cells);                              // Initialize the value of each cell to 0
        print_blanks();                                     // Visualize the initialized cells
        open_cell(&open_x, &open_y);                        // Let user enter the coordinate
        put_mine(cells, open_x, open_y);                    // Setup the location of mine
        calculate_num_of_cells(cells);                      // Calculate the number of mine in non-mine area
        assign_info_after_open(cells, open_x, open_y);      // Assign new information according to the coordinate selected by user
        check_no_mine(cells, open_x, open_y);               // Check if there is mine in the surrounding area
        over = check_over(cells, open_x, open_y);           // Check the player wins or loses
        print_cells(cells, open_x, open_y, over);           // Visualize the current cells
        while(over == 0) {
            open_cell(&open_x, &open_y);                        // Let user enter the coordinate
            assign_info_after_open(cells, open_x, open_y);       // Assign new information according to the coordinate selected by user
            check_no_mine(cells, open_x, open_y);               // Check if there is mine in the surrounding area
            over = check_over(cells, open_x, open_y);           // Check the player wins or loses
            print_cells(cells, open_x, open_y, over);           // Visualize the current cells
        }
        again = play_again();                                   // Ask play again or not
    } while(again == 'Y' || again == 'y');

    return(0);
}

// Initialize the value of each cell to 0
void assign_initial(int cells[][11]) {
    int i=0, j=0;
    for(i=0; i<=10; i++) {
        for(j=0; j<=10; j++) {
            cells[i][j] = 0;
        }
    }
}

// Visualize the initialized cells
void print_blanks(void) {
    int i=0, j=0;
    printf("---------------------------- Minesweeper Introduction ----------------------------\n");
    printf("* Please enter the coordinate you want to open (e.g. 2 1 which is split by space).\n");
    printf("* You can enter multiple coordinates at one time (split by non mathematical symbol).\n");
    printf("----------------------------------------------------------------------------------\n\n");

    printf("      ");
    for(i=1; i<=9; i++) {
        printf("%2d", i);
    }

    printf("\n    -----------------------\n");
    for(i=1; i<=9; i++) {
        for(j=0; j<=10; j++) {
            if(j == 0) {
                printf("%4d%2c", i, '|');
            } else if(j == 10) {
                printf("%2c%2d", '|', i);
            } else {
                printf("%2c", '!');
            }
         }
         printf("\n");
    }
    printf("    -----------------------\n");

    printf("      ");
    for(i=1; i<=9; i++) {
        printf("%2d", i);
    }
    printf("\n");
}

// Let user enter the coordinate
void open_cell(int *op_x, int *op_y) {
    printf("\nPlease enter the coordinate: ");
    scanf("%d%d", op_x, op_y);
}

// Setup the location of mine
void put_mine(int cells[][11], int op_x, int op_y) {
    int n=0, rand_num, cell_x, cell_y;

    do {
        rand_num = rand() % 81;     // ( rand() % (最大值 - 最小值 + 1)) + 最小值
        cell_x = (rand_num % 9) + 1;
        cell_y = ((rand_num - cell_x) / 9) + 1;
        if(cells[cell_x][cell_y] != -1 && !(cell_x == op_x && cell_y == op_y)) {
            cells[cell_x][cell_y] = -1;
            n++;
        }
    } while(n < 10);
}

// Calculate the number of mine in non-mine area
void calculate_num_of_cells(int cells[][11]) {
    int i=0, j=0, u=0, v=0;
    for(i=1; i<=9; i++) {
        for(j=1; j<=9; j++) {
            if(cells[i][j] == 0) {
                for(u=i-1; u<=i+1; u++) {
                    for(v=j-1; v<=j+1; v++) {
                        if (cells[u][v] == -1) {
                            cells[i][j]++;
                        }
                    }
                }
            }
        }
    }
}

// Assign new information according to the coordinate selected by user
void assign_info_after_open(int cells[][11], int op_x, int op_y) {
    if(cells[op_x][op_y] == -1) {
        cells[op_x][op_y] = -2;
    }
    if(cells[op_x][op_y] >= 0 && cells[op_x][op_y] <= 8) {
        cells[op_x][op_y] += 10;
    }
}

// Open surrounding area while there are no mine around the selected coordinate
void open_surrounding(int cells[][11], int op_x, int op_y) {
    int i=0, j=0;
    for(i=op_x-1; i<=op_x+1; i++) {
        for(j=op_y-1; j<=op_y+1; j++) {
            if(cells[i][j] >= 0 && cells[i][j] <=8 && i % 10 != 0 && j % 10 != 0) {
                cells[i][j] += 10;
                check_no_mine(cells, i, j);
            }
        }
    }
}

// Check if there is mine in the surrounding area
void check_no_mine(int cells[][11], int op_x, int op_y) {
    if (cells[op_x][op_y] == 10) {
        open_surrounding(cells, op_x, op_y);
    }
}

// Visualize the playing condition
void print_condition_playing(int cells[][11]) {
    int i=0, j=0;
    printf("      ");
    for(i=1; i<=9; i++) {
        printf("%2d", i);
    }

    printf("\n    -----------------------\n");
    for(i=1; i<=9; i++) {
        for(j=0; j<=9; j++) {
            if(j == 0) {
                printf("%4d%2c", i, '|');
            } else if(cells[i][j] < 10) {
                printf("%2c", '!');
            } else if(cells[i][j] == 10) {
                printf("%2d", 0);
            } else if(cells[i][j] > 10 && cells[i][j] <= 18) {
                printf("%2d", cells[i][j]-10);
            }
            if(j == 9) {
                printf("%2c%2d", '|', i);
            }
        }
        printf("\n");
    }
    printf("    -----------------------\n");

    printf("      ");
    for(i=1; i<=9; i++) {
        printf("%2d", i);
    }
    printf("\n");
}

// Visualize the end condition (the information of each cell)
void print_condition_over(int cells[][11], int over) {
    int i=0, j=0;
    printf("      ");
    for(i=1; i<=9; i++) {
        printf("%2d", i);
    }

    printf("\n    -----------------------\n");
    for(i=1; i<=9; i++) {
        for(j=0; j<=10; j++) {
            if(j == 0) {
                printf("%4d%2c", i, '|');
            } else if(j == 10) {
                printf("%2c%2d", '|', i);
            } else if(cells[i][j] % 10 == 0) {
                printf("%2d", 0);
            } else if(cells[i][j] == -1) {
                printf("%2c", '*');
            } else if(cells[i][j] == -2) {
                printf("%2c", '+');
            } else {
                printf("%2d", cells[i][j] % 10);
            }
        }
        printf("\n");
    }
    printf("    -----------------------\n");

    printf("      ");
    for(i=1; i<=9; i++) {
        printf("%2d", i);
    }
    printf("\n");

    if(over == 1) {
        printf("\nCongratulations ~  You win !\n\n");
    } else {
        printf("\nYou lose QQ. \n\n");
    }
    printf("The value indicates the number of the mine around the location.\n");
    printf("* indicates the mine.\n");
    printf("0 indicates there are no mine around the location.\n");
    printf("+ indicates the mine which has exploded.\n");
    printf("Thanks !!\n");
}

// Visualize the current cells
void print_cells(int cells[][11], int op_x, int op_y, int over) {
    system("cls");
    printf("\n");
    if(over == 0) {
        print_condition_playing(cells);
    } else {
        print_condition_over(cells, over);
    }
}

// Check the player wins or loses
int check_over(int cells[][11], int op_x, int op_y) {
    //result == 0 ... continue / result == 1 ... win / result == -1 ... lose
    int i=0, j=0, result = 1;
    if(cells[op_x][op_y] == -2) {
        result = -1;
    } else {
        for(i=1; i<=9 && result==1; i++) {
            for (j=1; j<=9 && result==1; j++) {
                if ((cells[i][j] >= 0 && cells[i][j] <= 8)) {
                    result = 0;
                }
            }
        }
    }
    return(result);
}

// Ask play again or not
char play_again(void) {
    char again;
    printf("\nDo you want to play again (Y or N): ");
    do {
        scanf(" %c", &again);
    } while(again != 'Y' && again != 'y' && again != 'N' && again != 'n');

    return(again);
}
