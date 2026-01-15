#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/load_menu.h"
#include "../include/hero.h"
#include "../include/village_menu.h"

void main_menu(int cheatcode_unlocked)
{
    printf("\nInitial Game Memu\n\n\n");
    printf("1. New Game\n");
    printf("2. Load Game\n");
    if (cheatcode_unlocked)
    {
        printf("3. Cheats\n");
    }
    else
    {
        printf("\nChoose an action (1-2): ");
    }

    char choice[100];
    char cheat_code[12] = "wwssadadba ";
    int cheat_attempt = 0;
    while (fgets(choice, sizeof(choice), stdin))
    {                                         // fgets reads a line from stdin: fgets(variable, size of variable, source of input)
        choice[strcspn(choice, "\n")] = '\0'; // remove \n, cause fgets gets a whole line including \n
        if (!cheatcode_unlocked && (strcmp(choice, "1") == 0 || strcmp(choice, "2") == 0))
        { // go if cheatcode is locked. strcmp returns 0 if equal
            break;
        }
        else if (cheatcode_unlocked && (strcmp(choice, "1") == 0 || strcmp(choice, "2") == 0 || strcmp(choice, "3") == 0))
        { // go if cheatcode is unlocked
            break;
        }
        if (choice[0] == cheat_code[cheat_attempt])
        { // as we have only one char to compare, we can use choice[0]
            cheat_attempt++;
            if (cheat_attempt == 11)
            {
                printf("Unclocked!\n");
                main_menu(1);
                break;
            }
        }
        else
        {
            cheat_attempt = 0; // reset if once a wrong char is entered
        }
        if (!cheatcode_unlocked)
        {
            printf("Choose an action (1-2): ");
        }
        else
        {
            printf("Choose an action (1-3): ");
        }
    }
    switch (choice[0])
    { // we can use choice[0] as we only need the first char
    case '1':
        printf("Starting a new game...\n");
        Hero hero = {20, 0, 0, 0, 0, 0, 0, 0, 0}; // initialize a new hero
        village_menu(&hero);
        break; // if you dont't put break here, it will continue to case 2
    case '2':
        printf("Loading a saved game...\n");
        load_menu(&hero);
        break;
    case '3':
        printf("Loading cheats...\n");
        // load_menu(cheats=true);
        break;
    }
}

int main()
{
    main_menu(0);
    return 0;
}