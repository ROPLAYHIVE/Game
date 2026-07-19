// Simple Menu-Driven Program for 4 Games (Basic C Version)
#include <stdio.h>
#include <stdlib.h>



void game1() {
    int number, guess, attempts = 0;

    // generate random number between 1 and 100
    srand(time(0));
    number = rand() % 100 + 1;

    printf("\n--- Game 1: Guess the Number ---\n");
    printf("I'm thinking of a number between 1 and 100.\n");

    do {
        printf("Enter your guess: ");
        scanf("%d", &guess);
        attempts++;

        if (guess > number) {
            printf("Too high! Try again.\n");
        } else if (guess < number) {
            printf("Too low! Try again.\n");
        } else {
            printf("🎉 Correct! You guessed it in %d attempts!\n", attempts);
        }

    } while (guess != number);
}

   


void game2() {
    printf("\n--- Game 2: Hangman (stub) ---\n");
    printf("You can write your game code here.\n");
}

void game3() {
    printf("\n--- Game 3: Tic-Tac-Toe (stub) ---\n");
    printf("You can write your game code here.\n");
}

void game4() {
    printf("\n--- Game 4: Snake (stub) ---\n");
    printf("You can write your game code here.\n");
}

int main() {
    int choice;

    do {
        printf("\n==============================\n");
        printf("       MINI GAMES MENU        \n");
        printf("==============================\n");
        printf("1. Game 1 - Guess the Number\n");
        printf("2. Game 2 - Hangman\n");
        printf("3. Game 3 - Tic-Tac-Toe\n");
        printf("4. Game 4 - Snake\n");
        printf("5. Exit\n");
        printf("==============================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                game1();
                break;
            case 2:
                game2();
                break;
            case 3:
                game3();
                break;
            case 4:
                game4();
                break;
            case 5:
                printf("\nExiting... Thanks for playing!\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }

        printf("\n");
        system("pause");  // use "pause" on Windows, or comment out on Linux
        system("cls");    // use "cls" on Windows, or "clear" on Linux

    } while (choice != 5);

    return 0;
}
