/*****************************************************************************
 * Author: Meng-Shiun, Tsai | Date: 2015/12/30
 * Problem definition:
 * Monopoly Game:
    1. Design a Monopoly game with 8 stations. At the beginning, you have NT 10,000 and start from rest station.
    2. Use dice to decide how many steps to take, and then decide whether to fine or reward according to where you go.
    3. The forward direction is clockwise, and the game ends when the player goes bankrupt.
    4. Design an opportunity to randomly produce 4 different instructions such like forward, backward, fine and reward. (decided by yourself)
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void opportunity(int *money, int *where);

int main() {
    FILE *output ;
    output=fopen("Monopoly_Game.txt", "w");

    int round=0, money=10000, where=0, at, chance;

    srand((unsigned)time(NULL));//隨著時間改變
    
    printf("  Rest      Taichung    Tainan\n\nKaohsiung       ↖        CCU  \n\n  Jail     Opportunity  Taipei\n\n");
    printf("--------- Game Start -----------\n\n");

    do {
        round++ ;
        printf("Round: %d ....\n\n", round);

        at = (rand() % 6) + 1;
        where = where + at;
        where = where % 8;

        printf("Dice result: %d\n\n",at);

        if(where == 0) {
            printf("  Rest      Taichung    Tainan\n\nKaohsiung       ↖        CCU  \n\n  Jail     Opportunity  Taipei\n\n");
        } else if(where == 1) {
            money = money - 500;
            printf("Tolls: NT 500.\n\n");
            printf("  Rest      Taichung    Tainan\n\nKaohsiung       ↑        CCU  \n\n  Jail     Opportunity  Taipei\n\n");
        } else if(where == 2) {
            money = money - 500;
            printf("Tolls: NT 500.\n\n");
            printf("  Rest      Taichung    Tainan\n\nKaohsiung       ↗        CCU  \n\n  Jail     Opportunity  Taipei\n\n");
        } else if(where == 3) {
            money = money + 1000;
            printf("Back to alum master, reward NT 1,000.\n\n");
            printf("  Rest      Taichung    Tainan\n\nKaohsiung       →        CCU  \n\n  Jail     Opportunity  Taipei\n\n");
        } else if(where == 4) {
            money = money - 5000;
            printf("Tolls: NT 5,000.\n\n");
            printf("  Rest      Taichung    Tainan\n\nKaohsiung       ↘        CCU  \n\n  Jail     Opportunity  Taipei\n\n");
        } else if(where == 5) {
            opportunity(&money, &where);
            printf("  Rest      Taichung    Tainan\n\nKaohsiung       ↓        CCU  \n\n  Jail     Opportunity  Taipei\n\n");
        } else if(where == 6) {
            round = round + 2;
            printf("Trapped in jail, stay for 2 rounds.\n\n");
            printf("  Rest      Taichung    Tainan\n\nKaohsiung       ↙        CCU  \n\n  Jail     Opportunity  Taipei\n\n");
        } else if(where == 7) {
            money = money - 500;
            printf("Tolls: NT 500.\n\n");
            printf("  Rest      Taichung    Tainan\n\nKaohsiung       ←        CCU  \n\n  Jail     Opportunity  Taipei\n\n");
        }

        printf("Current money: NT %d\n\n", money);
        printf("------------ next -------------\n\n");

        fprintf(output, "Round: %d      Money: NT %d\n\n", round, money);
    } while(money >= 0);

    printf("You are bankrupt ... The game is over~~");

    fclose(output);

    return 0;
}

// Opportunity ... Next action is determined by random opportunity card
void opportunity(int *money, int *where) {
    int chance = (rand() % 4) + 1;

    if(chance == 1) {
        printf("Opportunity: Won a scholarship NT 1,000.\n\n");
        *money = *money + 1000;
    } else if(chance == 2) {
        printf("Opportunity: NT 500 fine for drunk driving.\n\n");
        *money = *money - 500;
    } else if(chance == 3) {
        printf("Opportunity: Back to the rest station.\n\n");
        *where = 0;
    } else if(chance == 4) {
        printf("Opportunity: Back to CCU (reward NT 1,000), but you should pay NT 800 for train fare.\n\n");
        *where = 3;
        *money = *money + 200;
    }
}