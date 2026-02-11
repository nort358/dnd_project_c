#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/load_menu.h"
#include "../include/hero.h"
#include "../include/village_menu.h"

void main_menu(int cheat_unlocked)
{
    Hero hero;
    char input[10];
    char cheat_code[12] = "wwssadadba ";
    int cheat_pos = 0;
    int cheat_on = cheat_unlocked;

    while (1)
    {
        printf("\n=== GAME MENU ===\n");
        printf("1. New Game\n");
        printf("2. Load Game\n");
        if (cheat_on)
            printf("3. Cheats\n");
        printf("Choose: ");

        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        // Konami code
        if (!cheat_on && input[0] == cheat_code[cheat_pos])
        {
            cheat_pos++;
            if (cheat_pos == 11)
            {
                printf("Cheats unlocked!\n");
                cheat_on = 1;
                cheat_pos = 0;
            }
            continue;
        }
        else
            cheat_pos = 0;

        if (!cheat_on && (strcmp(input, "1") == 0 || strcmp(input, "2") == 0))
            break;
        if (cheat_on && (strcmp(input, "1") == 0 || strcmp(input, "2") == 0 || strcmp(input, "3") == 0))
            break;
    }

    if (input[0] == '1')
    {
        printf("\nStarting a new game...\n");
        hero.life_points = 20;
        hero.coins = 0;
        hero.sword = 0;
        hero.armor = 0;
        hero.health_potions = 0;
        hero.first_mission_completed = 0;
        hero.second_mission_completed = 0;
        hero.third_mission_completed = 0;
        hero.final_mission_unlocked = 0;
        village_menu(&hero);
    }
    else if (input[0] == '2')
    {
        printf("\nLoading saved game...\n");
        load_menu(&hero);
    }
    else if (input[0] == '3' && cheat_on)
    {
        printf("\nCheats menu (coming soon).\n");
        main_menu(cheat_on);
    }
}

int main()
{
    srand(time(NULL));
    main_menu(0);
    return 0;
}