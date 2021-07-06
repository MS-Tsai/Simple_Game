/*****************************************************************************
 * Author: Meng-Shiun, Tsai | Date: 2016/01/01
 * Problem definition:
 * Kelp Fist Game:
    1. Player can play Kelp Fist game with computer.
    2. Attack and defense alternate with the number of rounds.
    3. Game ends when player and computer show the same "Kelp Fist"
    4. You should write some functions to implement "paper / scissors / stone", "Kelp Fist" and "judging win or loss"
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int paper_scissors_stone(); // Use a function to judge the result of paper / scissors / stone
void who_attack(int start, int round); // Use a function to judge who should attack currently
int Kelp_Fist_Game(); // Use a function to implement Kelp Fist Game
void result_judgment(int start, int round); // Use a function to judge the final result (who wins this game)

int main() {
    int start, result, round=0;

    srand((unsigned)time(NULL)); // Set random number to be different per game

    printf("This is a Kelp Fist Game\n");
    printf("Paper / sicssors / stone rule ... 1: Scissors | 2: Stone | 3: paper\n");
    printf("Kelp Fist rule ... 1: ↑↑ | 2: ↓↓ | 3: ←  →\n");
    printf("Please determine who attacks first by paper / scissors / stone\n\n");

    start = paper_scissors_stone(); // Judge who attacks first by "paper / scissors / stone"
    printf("------------ Game Start -------------\n\n");

    // Start Kelp Fist Game (1: ↑↑ | 2: ↓↓ | 3: ←  →)
    do {
        round++; // Update rounds
        printf("Round: %d ...\n\n", round);

        who_attack(start, round); // Judge who attacks currently

        result = Kelp_Fist_Game(); // Judge the result of "Kelp Fist Game"

    } while(result != 1);

    result_judgment(start, round); // Judge the final result of this game

    return 0;
}

int paper_scissors_stone() {
    // Rule ... 1: Scissors | 2: Stone | 3: paper

    int computer, player, first_attack;

    printf("Please enter an integer in a range [1, 2, 3]: ");
    for( ; ; ) {
        scanf("%d", &player);
        computer = (rand() % 3) + 1;

        if(player <= 3) {
            // Tie
            if(computer == player) {
                if(computer == 1 && player == 1) {
                    printf("\nComputer: Scissors  |  Player: Scissors");
                } else if(computer == 2 && player == 2) {
                    printf("\nComputer: Stone  |  Player: Stone");
                } else if(computer == 3 && player == 3) {
                    printf("\nComputer: Paper  |  Player: Paper");
                }
                printf("\nTie !  Please enter an integer in a range [1, 2, 3] again: ");
            } else {
                // Computer wins
                if(computer == 1 && player == 3) {
                    printf("\nComputer: Scissors  |  Player: Paper");
                    first_attack = 1;
                } else if(computer == 2 && player == 1) {
                    printf("\nComputer: Stone  |  Player: Scissors");
                    first_attack = 1;
                } else if(computer == 3 && player == 2) {
                    printf("\nComputer: Paper  |  Player: Stone");
                    first_attack = 1;
                }

                // Player wins
                if(computer == 1 && player == 2) {
                    printf("\nComputer: Scissors  |  Player: Stone");
                    first_attack = 2;
                } else if(computer == 2 && player == 3) {
                    printf("\nComputer: Stone  |  Player: Paper");
                    first_attack = 2;
                } else if(computer == 3 && player == 1) {
                    printf("\nComputer: Paper  |  Player: Scissors");
                    first_attack = 2;
                }

                if(first_attack == 1) {
                    printf("\nStart by computer !\n\n");
                } else if(first_attack == 2) {
                    printf("\nStart by player !\n\n");
                }

                return first_attack;
            }
        } else {
            printf("Wrong input !!  Please enter again: ");
        }
    }
}

void who_attack(int start, int round) {
    if(start == 1) {
        if(round % 2 == 1) {
            printf("Attacker: Computer\n\n");
        } else {
            printf("Attacker: Player\n\n");
        }
    } else if(start == 2) {
        if(round % 2 == 1) {
            printf("Attacker: Player\n\n");
        } else {
            printf("Attacker: Computer\n\n");
        }
    }
}

int Kelp_Fist_Game() {
    int computer, player, result=0;

    printf("Please enter an integer in a range [1, 2, 3]: ");
    for( ; ; ) {
        scanf("%d", &player);
        computer = (rand() % 3) + 1;

        if(player <= 3) {
            // Case: computer and player are not the same
            if(computer == 1) {
                if(player == 2) {
                    printf("\nComputer: ↑↑  |  Player: ↓↓\n\n");
                } else if(player == 3) {
                    printf("\nComputer: ↑↑  |  Player: ←  →\n\n");
                }
            } else if(computer == 2) {
                if(player == 1) {
                    printf("\nComputer: ↓↓  |  Player: ↑↑\n\n");
                } else if(player == 3) {
                    printf("\nComputer: ↓↓  |  Player: ←  →\n\n");
                }
            } else if(computer == 3) {
                if(player == 1) {
                    printf("\nComputer: ←  →  |  Player: ↑↑\n\n");
                } else if(player == 2) {
                    printf("\nComputer: ←  →  |  Player: ↓↓\n\n");
                }
            }

            // Case: computer and player are the same
            if(computer == player) {
                if(computer == 1 && player == 1) {
                    printf("\nComputer: ↑↑  |  Player: ↑↑\n\n");
                } else if(computer == 2 && player == 2) {
                    printf("\nComputer: ↓↓  |  Player: ↓↓\n\n");
                } else if(computer == 3 && player == 3) {
                    printf("\nComputer: ←  →  |  Player: ←  →\n\n");
                }
                result = 1;
            }

            printf("------------next-------------\n\n");

            return result;

        } else {
            printf("Wrong input !!  Please enter again: ");
        }
    }
}

void result_judgment(int start, int round) {
    if(start == 1) {
        if(round % 2 == 1) {
            printf("Game over~   Computer wins !\n");
        } else {
            printf("Game over~   Player wins !\n");
        }
    } else if(start == 2) {
        if(round % 2 == 1) {
            printf("Game over~   Player wins !\n");
        } else {
            printf("Game over~   Computer wins !\n");
        }
    }
}
