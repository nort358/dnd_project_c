#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/load_menu.h"
#include "../include/hero.h"
#include "../include/village_menu.h"
#include "../include/mission.h"
#include "../include/sword.h"
#include "../include/cheats.h"
void main_menu()
{
    srand(time(NULL));
    Hero hero;
    char input[10];
    char cheat_code[12] = "wwssadadba ";
    int cheat_pos = 0;
    int cheat_on = 0;
    MissionSystem ms;
    mission_init(&ms);
    while(1){
    while (1)
    {
        printf("\n=== GAME MENU ===\n");
        printf("0. EXIT\n");
        printf("1. New Game\n");
        printf("2. Load Game\n");
        if (cheat_on)
            printf("3. Cheats\n");
        printf("Choose: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

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

        if (!cheat_on && (strcmp(input, "1") == 0 || strcmp(input, "2") == 0|| strcmp(input, "0") == 0))
            break;
        if (cheat_on && (strcmp(input, "1") == 0 || strcmp(input, "2") == 0 || strcmp(input, "3") == 0|| strcmp(input, "0") == 0))
            break;
    }

    if (input[0] == '1')
        {
            printf("\nStarting a new game...\n");
            hero.life_points = HERO_MAX_LIFE_POINTS;
            hero.coins = 0;
            hero.sword = NO_SWORD;
            hero.armor = 0;
            hero.mission_completed[0] = 0;
            hero.mission_completed[1] = 0;
            hero.mission_completed[2] = 0;
            hero.final_mission_unlocked = 0;
            village_menu(&hero, &ms);
        }
        else if (input[0] == '2')
        {
            printf("\nLoading saved game...\n");
            load_menu(&hero, &ms, 0);
        }
        else if (input[0] == '3' && cheat_on)
        {
            cheat_menu(&hero, &ms);
            cheat_on = 1;
        }
        else if (input[0] == '0')
        {
            printf("BYE!\n");
            exit(0);
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }
}


int main()
{
    srand(time(NULL));
    main_menu();
    return 0;
}