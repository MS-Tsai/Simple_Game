/*****************************************************************************
 * Author: Meng-Shiun, Tsai | Date: 2015/12/09
 * Problem definition:
 * Basic: Poker game - Ten Point Half (10.5)
          There are 52 cards in a deck and each card has 4 suits. (Please avoid producing a card shown more than 4 times.)
          Rule: Winner ... Summation of received cards is most closed to ten points half. (Only one boss and one player.)
          
 * Advanced: Please make a rule to let win rate of boss higher than 60%.
             Other game rule is the same as Basic.
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int check_four_times(int[], int);
void show_cards(int[]);

int main() {
   int counter=0, times=0;

   srand((unsigned)time(NULL)); // Set random number to be different per game

   for(times=0; times<100; times++) {
      int desk[13]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
      int cards_p[5]={-1, -1, -1, -1, -1}, cards_b[5]={-1, -1, -1, -1, -1};
      int round=0, check_result=0;
      float points_p=0, points_b=0 ;

      // First of this game, Player and Boss draw a card
      cards_p[round] = (rand() % 13) + 1 ;
      points_p = (cards_p[round] > 10) ? 0.5 : cards_p[round];

      cards_b[round] = (rand() % 13) + 1 ;
      points_b = (cards_b[round] > 10) ? 0.5 : cards_b[round];

      // The round of Player
      while(points_p < 9 && round < 4) {
         round++;

         // Player draws a card
         do {
            cards_p[round] = (rand() % 13) + 1 ;
            check_result = check_four_times(desk, cards_p[round]); // Check if the card is shown more than four times
         } while(check_result == 0);
         
         // Calculate total points of Player
         points_p += (cards_p[round] > 10) ? 0.5 : cards_p[round];
      }

      if(points_p <= 10.5) {
         round = 0; // Initialize the round of Boss
         
         // The round of Boss
         while(points_b < points_p && points_b < 10.5 && round < 4) {
            round++;
            
            // Player draws a card
            do {
               cards_b[round] = (rand() % 13) + 1;
               check_result = check_four_times(desk, cards_b[round]); // Check if the card is shown more than four times
            } while(check_result == 0);

            // Calculate total points of Boss
            points_b += (cards_b[round] > 10) ? 0.5 : cards_b[round];
         }
      }

      // Judge who wins the game
      if(points_p > 10.5 && points_b > 10.5) {
         printf("Tied !\n");
      } else if(points_b > 10.5) {
         printf("Player wins! Boss loses!\n");
      } else if(points_p > 10.5) {
         printf("Player loses! Boss wins!\n");
         counter++;
      } else {
         if(cards_b[4] != -1) {
            printf("Player loses! Boss wins!\n");
            counter++;
         } else if(cards_p[4] != -1) {
            printf("Player wins! Boss loses!\n");
         } else if(points_p > points_b) {
            printf("Player wins! Boss loses!\n");
         } else {
            printf("Player loses! Boss wins!\n");
            counter++;
         }
      }

      // Show Player's and Boss's cards
      printf("\nPlayer's cards: ");
      show_cards(cards_p);
      
      printf("\nBoss's cards: ");
      show_cards(cards_b);

      // Show the final points of Player and Boss
      printf("\n\nThe points of Player's cards: %.1f\n", points_p);
      printf("The points of Boss's cards: %.1f\n", points_b);
      printf("---------------\n");
   }
   
   printf("Win rate of Boss: %.2f%%", ((float)counter / (float)times) * 100.0);

   return 0;
}

// Check if the card is shown more than four times
int check_four_times(int desk[], int current_card)
{
   if(desk[current_card-1] == 3) {
      return 0;
   } else {
      (desk[current_card-1])++;
      return 1;
   }
}

// Show card according to the point of the card
void show_cards(int cards[]) {
   int round=0;
   for(round=0; round<5; round++) {
      if(cards[round] == 1) {
         printf("A");
      } else if(cards[round] == 11) {
         printf("J");
      } else if(cards[round] == 12) {
         printf("Q");
      } else if(cards[round] == 13) {
         printf("K");
      } else {
         printf("%d", cards[round]);
      }
      
      printf((round != 4) ? ", " : "");
   }
}