// SOFTWARE DEVELOPMENT FUNDAMENTALS LAB-1 PROJECT 
// ODD SEM 2025
// SUBMITTED TO- MRS. NIVEDITTA BATRA
// SUBMITTED BY- NITYA_992501220043
//               PEARL_992501220041
//               SURYANSH SINGH_992501220044
//               ROHIT GUPTA_992501220035

/* TOPIC - MENU DRIVEN GAMING ARCADE */
              
//  *   Games:
//  *   1) Guess the Number
//  *   2) Hangman
//  *   3) Flappy Bird 
//  *   4) Snake 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>  

#define FLAP_WIDTH 40
#define FLAP_HEIGHT 15

/* for Flappy Bird */
int birdY, pipeX, gapY, flapScore, flapGameOver;

/* Game functions */
void game1_guess_number(void);
void game2_hangman(void);
void game3_flappy(void);
void game4_snake(void);

void short_delay(void);

void flap_delay(void);
void flap_create(void);
void flap_input(void);
void flap_logic(void);

/* ---------- Game 1: Guess the Number ---------- */
void game1_guess_number(void) {
    int number, guess, attempts;
    number = (rand() % 100) + 1;
    attempts = 0;

    printf("\n\n\n\n\n");
    printf("--- Game 1: Guess the Number ---\n");
    printf("I have chosen a number between 1 and 100.\n");

    while (1) {
        printf("Enter your guess:\n");
        printf("Enter 0 if you want to give up.\n");

        if (scanf("%d", &guess) != 1) {
            printf("Invalid input. Please enter a number.\n");
            int c;
            while ((c = getchar()) != '\n' );
            continue;
        }
        if (guess == 0) {
            printf("You gave up. The number was %d.\n", number);
            break;
        }
        attempts++;
        if (guess < 1 || guess > 100) {
            printf("Please guess a number between 1 and 100.\n");
        } else if (guess < number) {
            printf("Try a large number.\n");
        } else if (guess > number) {
            printf("Try a small number.\n");
        } else {
            printf("You took %d attempts to guess correctly.", attempts);
            break;
        }
    }

    {
        char dummy[100];
        int c;
        while ((c = getchar()) != '\n');
        printf("\nPress Enter to return to menu...");
        fgets(dummy, sizeof(dummy), stdin);
    }
}

/* ---------- Game 2: Hangman  ---------- */
void game2_hangman(void) {
    const char *words[] = {
        "computer", "science", "program", "hangman", "college",
        "keyboard", "internet", "project", "student", "simple"
    };
    const int nwords = sizeof(words)/sizeof(words[0]);
    char word[64];
    char state[64];
    char guessed[27] = "";
    int len, wrong = 0, correct = 0;
    int max_wrong = 6;
    char c;

    strncpy(word, words[rand() % nwords], sizeof(word)-1);
    word[sizeof(word)-1] = '\0';
    len = strlen(word);

    for (int i = 0; i < len; ++i) state[i] = '_';
    state[len] = '\0';

    printf("\n\n\n\n\n");
    printf("--- Game 2: Hangman ---\n");
    while (wrong < max_wrong && correct < len) {
        printf("\nWord: ");
        for (int i = 0; i < len; ++i) printf("%c ", state[i]);
        printf("\nWrong: %d/%d\n", wrong, max_wrong);
        printf("Guessed: %s\n", guessed[0] ? guessed : "-");
        printf("Enter a letter: ");
        c = getchar();
        while (getchar() != '\n');
        if (c < 'a' || c > 'z') {
            printf("Please enter a lowercase letter a-z.\n");
            continue;
        }
        if (strchr(guessed, c)) {
            printf("You already guessed '%c'.\n", c);
            continue;
        }
        int glen = strlen(guessed);
        guessed[glen] = c;
        guessed[glen+1] = '\0';
        int found = 0;
        for (int i = 0; i < len; ++i) {
            if (word[i] == c && state[i] == '_') {
                state[i] = c;
                correct++;
                found = 1;
            }
        }
     if (!found) {
            wrong++;
            printf("Wrong guess!\n");
        } else {
            printf("Good!\n");
        }
    }
    if (correct == len)
        printf("\nYou win! The word was \"%s\".\n", word);
    else
        printf("\nYou lost! The word was \"%s\".\n", word);
    {
        char dummy[128];
        printf("\nPress Enter to return to menu...");
        fgets(dummy, sizeof(dummy), stdin);
    }
}

/* ---------- Game 3: Flappy Bird ---------- */
void game3_flappy(void) {
    birdY = FLAP_HEIGHT / 2;
    pipeX = FLAP_WIDTH - 2;
    gapY = rand() % (FLAP_HEIGHT - 5);
    flapScore = 0;
    flapGameOver = 0;
    printf("\n\n\n\n\n");
    printf("--- Game 3: Flappy Bird ---\n");
    printf("Press space to jump.\nPress any key to start...");
    _getch();
    while (!flapGameOver) {
        flap_create();
        flap_input();
        flap_logic();
        flap_delay();
    }
    printf("\nGame Over! Final Score: %d\n", flapScore);

    char dummy[128];
    printf("\nPress Enter to return to menu...");
    fgets(dummy, sizeof(dummy), stdin);
}
void flap_create(void) {
    system("cls");
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 40; x++) {
            if (x == 0 || x == FLAP_WIDTH - 1) 
            putchar('|');
            else if (x == 5 && y == birdY)
             putchar('^');
            else if (x == pipeX && (y < gapY || y > gapY + 3)) 
            putchar('#');
            else 
            putchar(' ');
        }
        putchar('\n');
    }
    printf("Score: %d\n", flapScore);
}
void flap_input(void) {
    if (_kbhit()) {
        int ch = _getch();
        if (ch == ' ') 
        birdY -= 2;
        while (_kbhit()) 
        _getch();
    }
}
void flap_logic(void) {
    birdY++;
    if (birdY >= FLAP_HEIGHT - 1)
     birdY = FLAP_HEIGHT - 2;
    if (birdY <= 0) 
    birdY = 1;
    pipeX--;
    if (pipeX <= 0) {
        pipeX = FLAP_WIDTH - 2;
        gapY = rand() % (FLAP_HEIGHT - 5);
        flapScore++;
    }
    if (pipeX == 5 && (birdY < gapY || birdY > gapY + 3))
        flapGameOver = 1;
}
void flap_delay(void) {
    for (volatile long i = 0; i < 600000000; i++);
}

/* ---------- Game 4: Snake ---------- */

void game4_snake(void) {
    const int W = 20, H = 12;
    int snake_x[100], snake_y[100];
    int snake_len = 3;
    int dirx = 1, diry = 0;
    int food_x, food_y;
    int headx, heady;
    int ch, gameover = 0;

    headx = W / 2;
    heady = H / 2;

    for (int i = 0; i < snake_len; i++) {
        snake_x[i] = headx - i;
        snake_y[i] = heady;
    }
    do {
        food_x = rand() % (W - 2) + 1;
        food_y = rand() % (H - 2) + 1;
    } while (food_x == headx && food_y == heady);
    printf("\n\n\n\n\n");
    printf("--- Game 4: Snake ---\n");
    printf("Use WASD or arrow keys. Press 'q' to quit.\n");
    short_delay();
    printf("--- Game 4: Snake ---\n");
    printf("Use WASD or arrow keys. Press 'q' to quit.\n");
    while (!gameover) {
        if (_kbhit()) {
            ch = _getch();
            if (ch == 'q' || ch == 'Q') break;              
                if ((ch == 'w' || ch == 'W') && diry != 1)  dirx = 0, diry = -1;
                if ((ch == 's' || ch == 'S') && diry != -1) dirx = 0, diry = 1;
                if ((ch == 'a' || ch == 'A') && dirx != 1)  dirx = -1, diry = 0;
                if ((ch == 'd' || ch == 'D') && dirx != -1) dirx = 1,  diry = 0;
            while (_kbhit()) _getch();
        }
        /* move snake body */
        for (int i = snake_len - 1; i > 0; i--) {
            snake_x[i] = snake_x[i-1];
            snake_y[i] = snake_y[i-1];
        }
        headx = snake_x[0] + dirx;
        heady = snake_y[0] + diry;
        snake_x[0] = headx;
        snake_y[0] = heady;
        /*detect collisions */
        if (headx <= 0 || headx >= W-1 || heady <= 0 || heady >= H-1)
            gameover = 1;
        for (int i = 1; i < snake_len; i++)
            if (snake_x[i] == headx && snake_y[i] == heady)
                gameover = 1;
        /* food of the snake*/
        if (headx == food_x && heady == food_y) {
            if (snake_len < 99) {   
                snake_x[snake_len] = snake_x[snake_len - 1];
                snake_y[snake_len] = snake_y[snake_len - 1];
                snake_len++;
            }
            do {
                food_x = rand() % (W - 2) + 1;
                food_y = rand() % (H - 2) + 1;
            } while (food_x == headx && food_y == heady);
        }
        system("cls"); 
        for (int y = 0; y < H; y++) {
            for (int x = 0; x < W; x++) {
                if (y == 0 || y == H-1 || x == 0 || x == W-1)
                    putchar('#');
                else if (x == food_x && y == food_y)
                    putchar('*');
                else {
                    int drawn = 0;
                    for (int i = 0; i < snake_len; i++) {
                        if (snake_x[i] == x && snake_y[i] == y) {
                            putchar(i == 0 ? 'O' : 'o');
                            drawn = 1;
                            break;
                        }
                    }
                    if (!drawn) putchar(' ');
                }
            }
            putchar('\n');
        }
  printf("Use WASD or arrow keys. Press 'q' to quit.\n");
        printf("Score: %d\n", snake_len - 3);
        short_delay(); 
    }
    if (gameover)
        printf("\nGame Over!\n");

    {
        char dummy[128];
        printf("\nPress Enter to return to menu...");
        fgets(dummy, sizeof(dummy), stdin);
    }
}
void short_delay(void) {
    for (volatile long i = 0; i < 700000000L; i++);
}

/* -------------------- Main menu -------------------- */
int main(void) {
    char line[128];
    int choice;
    srand(1);
    while (1) {
        printf("\n\n\n\n\n");
        printf("==============================\n");
        printf("       MINI GAMES MENU        \n");
        printf("==============================\n");
        printf("1. Game 1 - Guess the Number\n");
        printf("2. Game 2 - Hangman\n");
        printf("3. Game 3 - Flappy Bird\n");
        printf("4. Game 4 - Snake\n");
        printf("5. Exit\n");
        printf("==============================\n");
        printf("Enter your choice (1-5): ");
        if (fgets(line, sizeof(line), stdin) == NULL)
            break;
        if (sscanf(line, "%d", &choice) != 1) {
            printf("Invalid choice.\n");
            short_delay();
            continue;
        }
        switch (choice) {
            case 1: game1_guess_number(); break;
            case 2: game2_hangman(); break;
            case 3: game3_flappy(); break;
            case 4: game4_snake(); break;
            case 5: return 0;
            default:
                printf("Invalid choice!\n");
                short_delay();
                break;
        }
    }
    return 0;
}