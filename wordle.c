#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


int word_length; // GLOBAL VARIABLE OF WORD LENGTH
/*
* This function checks if the provided word only contains LOWERCASE ALPHABET characters
*/
int isValidWord(char word[]) {
    for (int i = 0; i < strlen(word); i++) {
        if ((word[i] > 'z' || word[i] < 'a') && !isspace(word[i])) {
            return 1;
        }
    }
    return 0; 
}
/*
Turn the printf stuff to be red
*/
void red(){
    printf("\033[0;31m");
}
/*
reset the color (default)
*/
void reset(){
    printf("\033[0m");
}
/*
Turn the printf stuff to be yellow
*/
void yellow(){
    printf("\033[0;33m");
}
/*
Turn the printf stuff to be green
*/
void green(){
    printf("\033[0;32m");
}

void play(char word_list[][word_length + 2], int size, char player[]) {
    int play_times = 1;
    bool cont = true;
    char used[26 + 1];      // Used characters
    char correct[word_length + 1];   // Characters that the target contain

    while (cont) {
        printf("\n==================\n");
        printf("GAME #%d\n", play_times);
        printf("==================\n");
        bool won = false;
        // Getting the random word
        srand(time(NULL));  // Setting the seeder
        int rand_pos = rand() % size;   // Getting the random position
        char target[word_length + 2];   
        strcpy(target, word_list[rand_pos]);    // The random word
        // printf("%s", target);    // Printing the word out for testing purpose

        // Resetting the word lists
        strcpy(used, "");   // Resetting
        strcpy(correct, "");
        int correct_count = 0;
        int used_count = 0;

        // Playing the game (6 tries)
        for (int i = 0; i < 6; ++i) {
            // Printing out the used words
            printf("Used characters: ");
            for (int k = 0; k < strlen(used); k++) {
                if (k == 0) {
                    printf("%c", used[k]);
                } else {
                    printf(", %c", used[k]);
                }
            }
            printf("\n");

            // Printing out the correct characters
            printf("The target contains: ");
            for (int l = 0; l < strlen(correct); l++) {
                if (l == 0) {
                    printf("%c", correct[l]);
                } else {
                    printf(", %c", correct[l]);
                }
            }
            printf("\n");

            // Taking the guesses
            char guess[100];
            printf("\nEnter your guess #%d (%d time(s) left): ", i, 6-i);
            // Coloring the guesses
            scanf("%s",guess);
            printf("\nCheck the guess:\n");
            printf("                                      ");
            for(int k = 0; k < word_length; ++k){
                if (target[k] == guess [k]){
                    green();
                    printf("%c", guess[k]);
                    reset();
                }else if (strchr(target, guess[k]) != NULL) {
                    yellow();
                    printf("%c", guess[k]);
                    reset();
                }else {
                    printf("%c", guess[k]);
                }
            }

            // Checking if the guess is valid (no uppercase, special characters and right length)
            if (isValidWord(guess) == 1 || strlen(guess) != word_length) {
                printf("That is not %d characters, %s. Please learn to play the game "
                    "correctly.\n", word_length, player);
                continue;
            }
            
            // Printing out whether the guess contains correct, out of place, wrong characters
            printf("\n                                      ");
            for (int j = 0; j < word_length; ++j) {
                bool correct_guess = false;
                if (target[j] == guess[j]) {
                    green(); // Let the word to be colored in green
                    printf("o");
                    reset();
                    correct_guess = true;
                } else if (strchr(target, guess[j]) != NULL) {
                    yellow(); // Let the word to be colored in yellow
                    printf("-");
                    reset();
                    correct_guess = true;
                } else {
                    red(); // Let the word to be colored in red
                    printf("x");
                    reset();
                }

                // Appending to the used words list
                if (!strchr(used, (char) guess[j]) ) {
                    used[used_count] = guess[j];
                    used_count++;
                    used[used_count] = '\0';
                }

                // Appending to the correct guess list
                if (correct_guess) {
                    if (!strchr(correct, guess[j])) {
                        correct[correct_count] = guess[j];
                        correct_count++;
                        correct[correct_count] = '\0';
                    }
                }
            }
            puts("");

            // Comparing the guess to the target
            if (strncmp(target, guess, word_length) == 0) {
                printf("WINNER WINNER CHICKEN DINNER, %s!!!!\n\n", player);
                won = true;
                break;
            }
        }

        // If losses
        if (!won) {
            printf("Out of guesses. The word is: %s. Better luck next time :)\n\n", target);
        }

        // Asking the user if they want to play once more
        printf("Do you want to play more (y/n)? ");
        char next;
        scanf(" %c", &next);
        if (next != 'y') {
            cont = false;
        } else {
            play_times++;
        }
    }
    printf("Thanks for playing. See you again soon!\n");
}


int main(void) {

    // Asking for the player name
    char player[50];
    printf("WHO ARE YOU??? ");
    scanf("%s", player);
    printf("Welcome to Wordle, %s!!!!\n", player);

    // Getting the word length
    word_length = 5;
    int size = 0;
    // Getting the counts of words first
    FILE *file = fopen("/usr/share/dict/words", "r");
    if (file == NULL) {
        perror("fopen");
    }
    char line[500];
    while (fgets(line, 500, file) != NULL) {
        if (strlen(line) == word_length + 1) {
            if (isValidWord(line) == 0) {
                size++;
            }
        }
    }
    fclose(file);

    // Opening again to create a word list
    FILE *file1 = fopen("/usr/share/dict/words", "r");
    if (file == NULL) {
        perror("fopen");
    }

    char word_list[size][word_length + 2];
    size = 0;
    char line1[500];

    // Appending to the word list 
    while (fgets(line1, 500, file1) != NULL) {
        if (strlen(line1) == word_length + 1) {
            if (isValidWord(line1) == 0) {
                // Appending
                strcpy(word_list[size], line1);
                size++;
            }
        }
    }
    fclose(file1);

    // Starting the game 
    play(word_list, size, player);
}