//Name: Ankur Samanta
//ID: 1006917632
//Class: APS105
//Assignment: Lab 3
//Objective: Simulate Blackjack game

//load libraries
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main(int argc, char **argv)
{
    //define base variables for dealer and player
    int dealerCard, playerCard;
    int dealerWorth, playerWorth;
    bool gameOver, playerWin;

    //define boolean values
    gameOver = false;
    playerWin = true;

    //see instructions; place before debug loops
    if (argc == 1) {
        srand(time(NULL));
    }
    else {
        srand(atoi(argv[1]));
    }

    //simulate drawing cards by generating random number from 1 to 13
    //randomnumber =    rand() % (upper - lower + 1) + lower
    dealerCard = rand() % 13 + 1;
    playerCard = rand() % 13 + 1;

    printf("First cards: player %d, dealer %d\n", playerCard, dealerCard);

    //define logic for qualifying value of the initially drawn card:
    //if card is greater than 10 (i.e 11, 12, 13), its value will be a 10
    //else, if card is not greater than 10 (i.e 1, 2, ..., 10), it will retain its integer value
    //establish the worth of the player and dealer's cards by assigning their initial value as the value of the card they drew first
    if(dealerCard > 10) {
        dealerWorth = 10;
    }
    else {
        dealerWorth = dealerCard;
    } 
    if(playerCard > 10) {
        playerWorth = 10;
    }
    else {
        playerWorth = playerCard;
    }

    //use while loop to establish the following logic and that as long as the game is not over, the player can either choose to hit or stay
    while(gameOver == false) {
        int hitOrStay;
        int drawnCard;
        printf("Type 1 for Hit, 0 to Stay:");
        scanf("%d", &hitOrStay);

        //if the player chooses to hit, the player is drawn another card and the game continues
        if(hitOrStay == 1) {
            //draw card and randomly assign integer value between 1 and 13
            drawnCard = rand() % 13 + 1;
            //base logic for determining value of drawn card
            if(drawnCard > 10) {
                playerWorth += 10;
            }
            else {
                playerWorth += drawnCard;
            }

            printf("Player gets a %d, worth is %d\n", drawnCard, playerWorth);

            //define endgame scenario where the player's worth exceeds 21 and they do not win
            if(playerWorth > 21) {
                gameOver = true;
                playerWin = false;
            }
        }
        //if the player chooses to stay, the game is over
        else if(hitOrStay == 0) {
            gameOver = true;
        }
    }

    //game-over situation where dealer wins since player has over 21
    if(playerWin == false) {
        printf("Player over 21, Dealer wins\n");
    }
    //situation where player does not have over 21
    else {
        //establish character array for the cards that the dealer draws
        char dealerCondDrawnCards[169] = "Dealer gets:";
        //while the dealer's worth is still below 17, they continue to draw random cards
        while(dealerWorth < 17)
        {
            //draw random cards
            int drawnCard = rand() % 13 + 1;
            
            //base logic for assigning value of drawn cards
            if(drawnCard > 10) {
                dealerWorth += 10;
            }
            else {
                dealerWorth += drawnCard;
            }
            sprintf(dealerCondDrawnCards, "%s %d", dealerCondDrawnCards, drawnCard);
        }
        
        printf("%s\n", dealerCondDrawnCards);

        //game-over situation where the dealer exceeds 21 while the player has not, in which case the player wins

        if(dealerWorth > 21) {
            printf("Dealer over 21, Player wins\n");
        }
        //other game-over situations
        else {
            //game-over situation where the dealer's worth is greater than the player's worth, in which case the player wins
            if(dealerWorth > playerWorth) {
                printf("Dealer better than Player, Dealer wins\n");
            }
            //game-over situation where the dealer's worth is less than the player's worth, in which case the dealer wins
            else if(dealerWorth < playerWorth) {
                printf("Player better than Dealer, Player wins\n");
            }
            //game-over situation where the dealer's worth is equal to the player's worth, in which case they tie
            else if(dealerWorth == playerWorth) {
            printf("Tie!\n");
            }
        }
    }
    //end program
    return 0;
}