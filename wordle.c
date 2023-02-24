#include <stdio.h>
#include <string.h>

/*
REQUIREMENTS:
- Cross out used words
- Scoring system
*/
int main(void) {
    FILE *file = fopen("/usr/share/dict/words", "r");
    if (file == NULL) {
        perror("fopen");
    }

    char line[500];
    while (fgets(line, 500, file) != NULL) {
        if (strlen(line) == 6 && ) {
            printf(line);
        }
    }
    fclose(file);

    char *target = "spunk";
  for (int i = 0; i < 6; ++i) {
    char guess[100];
    printf("Enter your guess: ");
    scanf("%s", guess);

    if (strlen(guess) != 5) {
      printf("That is not 5 characters, Matthew. Please learn to play the game "
             "correctly.\n");
      continue;
    }
    
    printf("                  ");
    for (int j = 0; j < 5; ++j) {
        if (target[j] == guess[j]) {
            printf("o");
        } else if (strchr(target, guess[j]) != NULL) {
            printf("a");
        } else {
            printf("x");
        }
    }
    puts("");

    if (strncmp(target, guess, 5) == 0) {
      printf("YOU WINNNNNNNNNNNNN!!!\n");
      break;
    }
  }
}